#ifndef DATA_PARSER_H
#define DATA_PARSER_H

#include "weather_journal.h"

int DP_parse_line(const char* line, WeatherDate* date, double* temp);
int DP_read_data_file(WeatherJournal* journal, const char* filename);
const char* DP_get_error_text(int error_code);

#endif