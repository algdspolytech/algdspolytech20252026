#include "weather_journal.h"
#include "data_parser.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static WeatherDate create_date(int year, int month, int day) {
    WeatherDate date = { year, month, day };
    return date;
}

void TestWJCreate_EmptyJournal_ReturnsValidJournal_no1() {
    WeatherJournal* journal = WJ_create();
    assert(journal != NULL);
    assert(journal->head == NULL);
    assert(journal->tail == NULL);
    assert(journal->count == 0);
    WJ_destroy(journal);
}

void TestWJInsertSorted_EmptyList_ElementAddedSuccessfully_no2() {
    WeatherJournal* journal = WJ_create();
    WeatherDate date = create_date(2006, 3, 10);
    int result = WJ_insert_sorted(journal, date, 8.5);
    assert(result == 1);
    assert(journal->count == 1);
    assert(journal->head != NULL);
    assert(journal->head->temp_value == 8.5);
    WJ_destroy(journal);
}

void TestWJValidateDate_InvalidMonth_ReturnsFalse_no3() {
    WeatherDate date = create_date(2006, 15, 25);
    int result = WJ_validate_date(&date);
    assert(result == 0);
}

void TestWJValidateDate_ValidDate_ReturnsTrue_no4() {
    WeatherDate date = create_date(2006, 12, 25);
    int result = WJ_validate_date(&date);
    assert(result == 1);
}

void TestDPParseLine_ValidLine_ParsesCorrectly_no5() {
    WeatherDate date;
    double temp;
    const char* valid_line = "2006-12-25  -8.2";
    int result = DP_parse_line(valid_line, &date, &temp);
    assert(result == 0);
    assert(date.year == 2006);
    assert(date.month == 12);
    assert(date.day == 25);
    assert(temp == -8.2);
}

void TestWJFindTemperature_ExistingTemp_ReturnsNode_no6() {
    WeatherJournal* journal = WJ_create();
    WeatherDate date1 = create_date(2006, 5, 15);
    WeatherDate date2 = create_date(2006, 7, 20);
    WJ_insert_sorted(journal, date1, 12.5);
    WJ_insert_sorted(journal, date2, 18.3);
    WeatherNode* found = WJ_find_temperature(journal, 12.5);
    assert(found != NULL);
    assert(found->temp_value == 12.5);
    WJ_destroy(journal);
}

void TestWJInsertSorted_MiddlePosition_InsertedCorrectly_no7() {
    WeatherJournal* journal = WJ_create();
    WeatherDate date1 = create_date(2006, 1, 5);
    WeatherDate date2 = create_date(2006, 1, 25);
    WeatherDate date3 = create_date(2006, 1, 15);
    WJ_insert_sorted(journal, date1, 5.0);
    WJ_insert_sorted(journal, date2, 15.0);
    WJ_insert_sorted(journal, date3, 10.0);
    assert(journal->count == 3);
    assert(journal->head->temp_value == 5.0);
    assert(journal->head->next->temp_value == 10.0);
    assert(journal->tail->temp_value == 15.0);
    WJ_destroy(journal);
}

void TestWJCheckTemperature_ExtremeValues_ReturnsValid_no8() {
    assert(WJ_check_temperature(-100.0) == 1);
    assert(WJ_check_temperature(100.0) == 1);
    assert(WJ_check_temperature(-101.0) == 0);
    assert(WJ_check_temperature(101.0) == 0);
}

void TestWJCountNegativeDays_MixedTemps_ReturnsCorrectCount_no9() {
    WeatherJournal* journal = WJ_create();
    WeatherDate date1 = create_date(2006, 2, 10);
    WeatherDate date2 = create_date(2006, 6, 15);
    WeatherDate date3 = create_date(2006, 11, 30);
    WJ_insert_sorted(journal, date1, -7.5);
    WJ_insert_sorted(journal, date2, 22.8);
    WJ_insert_sorted(journal, date3, -3.2);
    int count = WJ_count_negative_days(journal);
    assert(count == 2);
    WJ_destroy(journal);
}

void TestWJInsertSorted_EqualTemps_SortedByDate_no10() {
    WeatherJournal* journal = WJ_create();
    WeatherDate date1 = create_date(2006, 8, 20);
    WeatherDate date2 = create_date(2006, 8, 5);
    WeatherDate date3 = create_date(2006, 8, 30);
    WJ_insert_sorted(journal, date1, 25.0);
    WJ_insert_sorted(journal, date2, 25.0);
    WJ_insert_sorted(journal, date3, 25.0);
    assert(journal->count == 3);
    assert(journal->head->date.day == 5);
    assert(journal->head->next->date.day == 20);
    assert(journal->tail->date.day == 30);
    WJ_destroy(journal);
}

void TestDPParseLine_InvalidFormat_ReturnsError_no11() {
    WeatherDate date;
    double temp;
    const char* invalid_line = "2006/04/12  15.5";
    int result = DP_parse_line(invalid_line, &date, &temp);
    assert(result != 0);
}

void TestWJCompareNodes_DifferentTemps_ComparesCorrectly_no12() {
    WeatherNode node1 = { create_date(2006, 1, 1), 10.0, NULL, NULL };
    WeatherNode node2 = { create_date(2006, 1, 1), 20.0, NULL, NULL };
    int result = WJ_compare_nodes(&node1, &node2);
    assert(result < 0);
}

int main() {
    TestWJCreate_EmptyJournal_ReturnsValidJournal_no1();
    TestWJInsertSorted_EmptyList_ElementAddedSuccessfully_no2();
    TestWJValidateDate_InvalidMonth_ReturnsFalse_no3();
    TestWJValidateDate_ValidDate_ReturnsTrue_no4();
    TestDPParseLine_ValidLine_ParsesCorrectly_no5();
    TestWJFindTemperature_ExistingTemp_ReturnsNode_no6();
    TestWJInsertSorted_MiddlePosition_InsertedCorrectly_no7();
    TestWJCheckTemperature_ExtremeValues_ReturnsValid_no8();
    TestWJCountNegativeDays_MixedTemps_ReturnsCorrectCount_no9();
    TestWJInsertSorted_EqualTemps_SortedByDate_no10();
    TestDPParseLine_InvalidFormat_ReturnsError_no11();
    TestWJCompareNodes_DifferentTemps_ComparesCorrectly_no12();
    printf("All tests passed successfully!\n");
    return 0;
}