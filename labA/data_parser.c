#include "data_parser.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ERROR_BAD_FORMAT 1
#define ERROR_BAD_DATE 2
#define ERROR_BAD_TEMP 3

int DP_parse_line(const char* line, WeatherDate* date, double* temp) {
    if (!line || strlen(line) < 12) return ERROR_BAD_FORMAT;

    char date_text[11];
    if (sscanf(line, "%10s", date_text) != 1) return ERROR_BAD_FORMAT;

    if (strlen(date_text) != 10 || date_text[4] != '-' || date_text[7] != '-') {
        return ERROR_BAD_FORMAT;
    }

    if (sscanf(date_text, "%d-%d-%d", &date->year, &date->month, &date->day) != 3) {
        return ERROR_BAD_DATE;
    }

    const char* temp_text = line + 10;
    while (*temp_text && isspace(*temp_text)) temp_text++;

    if (sscanf(temp_text, "%lf", temp) != 1) {
        return ERROR_BAD_TEMP;
    }

    return 0;
}

int DP_read_data_file(WeatherJournal* journal, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return -1;

    char line[256];
    int line_num = 0;
    int success_count = 0;

    while (fgets(line, sizeof(line), file)) {
        line_num++;

        if (line[0] == '\n' || line[0] == '#') continue;

        WeatherDate date;
        double temp;
        int parse_result = DP_parse_line(line, &date, &temp);

        if (parse_result == 0) {
            if (WJ_insert_sorted(journal, date, temp)) {
                success_count++;
            }
        }
        else {
            printf("Ошибка в строке %d: %s\n", line_num, DP_get_error_text(parse_result));
        }
    }

    fclose(file);
    return success_count > 0 ? 0 : -1;
}

const char* DP_get_error_text(int error_code) {
    switch (error_code) {
    case ERROR_BAD_FORMAT: return "Invalid line format";
    case ERROR_BAD_DATE: return "Invalid date";
    case ERROR_BAD_TEMP: return "Invalid temperature";
    default: return "Unknown error";
    }
}