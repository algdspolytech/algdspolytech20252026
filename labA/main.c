#include "weather_journal.h"
#include "data_parser.h"
#include <stdio.h>

void show_welcome() {
    printf("=== Weather Data Analyzer ===\n");
    printf("Temperature data sorting and analysis\n\n");
}

void display_negative_temperatures(const WeatherJournal* journal) {
    if (!journal || journal->count == 0) {
        printf("No data available.\n");
        return;
    }
    printf("Days with negative temperature:\n");
    printf("-------------------------------\n");
    WeatherNode* current = journal->head;
    int found_negative = 0;
    while (current) {
        if (current->temp_value < 0) {
            printf("%04d-%02d-%02d: %6.1fC\n",
                current->date.year, current->date.month, current->date.day,
                current->temp_value);
            found_negative = 1;
        }
        current = current->next;
    }
    if (!found_negative) {
        printf("No days with negative temperature found.\n");
    }
    printf("\n");
}

int main() {
    show_welcome();
    WeatherJournal* journal = WJ_create();
    if (!journal) {
        printf("Error creating data journal.\n");
        return 1;
    }
    if (DP_read_data_file(journal, "weather_data.txt") != 0) {
        printf("Error loading weather_data.txt\n");
        WJ_destroy(journal);
        return 1;
    }
    printf("Successfully loaded records: %d\n", journal->count);
    printf("Negative temperature days: %d\n\n", WJ_count_negative_days(journal));
    display_negative_temperatures(journal);
    double search_temp;
    printf("Enter temperature to search: ");
    if (scanf("%lf", &search_temp) == 1) {
        WeatherNode* found = WJ_find_temperature(journal, search_temp);
        if (found) {
            printf("Found day: %04d-%02d-%02d with temperature %.1fC\n",
                found->date.year, found->date.month, found->date.day,
                found->temp_value);
        }
        else {
            printf("Days with temperature %.1fC not found.\n", search_temp);
        }
    }
    else {
        printf("Temperature input error.\n");
    }
    WJ_destroy(journal);
    return 0;
}