#ifndef WEATHER_JOURNAL_H
#define WEATHER_JOURNAL_H

#include "temp.h"

WeatherJournal* WJ_create();
void WJ_destroy(WeatherJournal* journal);
int WJ_insert_sorted(WeatherJournal* journal, WeatherDate date, double temp);
WeatherNode* WJ_find_temperature(const WeatherJournal* journal, double temp);
void WJ_show_negative_temps(const WeatherJournal* journal);
int WJ_validate_date(const WeatherDate* date);
int WJ_check_temperature(double temp);
int WJ_count_negative_days(const WeatherJournal* journal);
int WJ_compare_nodes(const WeatherNode* a, const WeatherNode* b);

#endif