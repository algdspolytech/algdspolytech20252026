#include "weather_journal.h"
#include "data_parser.h"
#include <assert.h>
#include <stdio.h>

void test_WJ_create_EmptyJournal_ReturnValidVal() {
    WeatherJournal* journal = WJ_create();
    assert(journal != NULL);
    assert(journal->head == NULL);
    assert(journal->tail == NULL);
    assert(journal->count == 0);
    WJ_destroy(journal);
}

void test_WJ_insertSorted_EmptyList_ReturnSuccess() {
    WeatherJournal* journal = WJ_create();
    WeatherDate date = { 2024, 1, 15 };

    int result = WJ_insert_sorted(journal, date, 5.0);

    assert(result == 1);
    assert(journal->count == 1);
    assert(journal->head != NULL);
    assert(journal->head->temp_value == 5.0);

    WJ_destroy(journal);
}

void test_WJ_validateDate_InvalidMonth_ReturnFalse() {
    WeatherDate date = { 2024, 13, 15 };
    int result = WJ_validate_date(&date);
    assert(result == 0);
}

void test_DP_parseLine_ValidLine_ReturnZero() {
    WeatherDate date;
    double temp;
    const char* valid_line = "2024-01-15  -5.5";

    int result = DP_parse_line(valid_line, &date, &temp);

    assert(result == 0);
    assert(date.year == 2024);
    assert(date.month == 1);
    assert(date.day == 15);
    assert(temp == -5.5);
}

void test_WJ_findTemperature_ExistingTemp_ReturnValidRecord() {
    WeatherJournal* journal = WJ_create();
    WeatherDate date1 = { 2024, 1, 15 };
    WeatherDate date2 = { 2024, 1, 16 };

    WJ_insert_sorted(journal, date1, 5.0);
    WJ_insert_sorted(journal, date2, 10.0);

    WeatherNode* found = WJ_find_temperature(journal, 5.0);

    assert(found != NULL);
    assert(found->temp_value == 5.0);

    WJ_destroy(journal);
}

int main() {
    test_WJ_create_EmptyJournal_ReturnValidVal();
    test_WJ_insertSorted_EmptyList_ReturnSuccess();
    test_WJ_validateDate_InvalidMonth_ReturnFalse();
    test_DP_parseLine_ValidLine_ReturnZero();
    test_WJ_findTemperature_ExistingTemp_ReturnValidRecord();

    printf("Все тесты пройдены успешно!\n");
    return 0;
}