#include "mail_scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// --- Вспомогательные функции для тестов ---

void create_test_file(const char* filename, const char* content) {
    FILE* f = fopen(filename, "w");
    assert(f != NULL);
    fprintf(f, "%s", content);
    fclose(f);
}

void remove_test_file(const char* filename) {
    remove(filename);
}

// --- Функция для запуска теста ---

void RUN_TEST(void (*test_func)(void), const char* test_name) {
    printf("Running %s ... ", test_name);
    test_func();
    printf("PASSED\n");
}

// --- Тесты ---

void test_read_telegrams_from_file_ValidInput_returnCountAndData_no1() {
    const char* content = "2 10\n1 1 5\n2 2 3\n";
    create_test_file("temp_mail_input.txt", content);

    Telegram telegrams[MAX_TELEGRAMS];
    int K;
    int res = read_telegrams_from_file("temp_mail_input.txt", telegrams, &K);

    assert(res == 2);
    assert(K == 10);
    assert(telegrams[0].l == 1 && telegrams[0].d == 1 && telegrams[0].w == 5 && telegrams[0].id == 1);
    assert(telegrams[1].l == 2 && telegrams[1].d == 2 && telegrams[1].w == 3 && telegrams[1].id == 2);

    remove_test_file("temp_mail_input.txt");
}

void test_read_telegrams_from_file_EmptyFile_returnMinusOne_no2() {
    const char* content = "";
    create_test_file("temp_mail_input_empty.txt", content);

    Telegram telegrams[MAX_TELEGRAMS];
    int K;
    int res = read_telegrams_from_file("temp_mail_input_empty.txt", telegrams, &K);

    assert(res == -1);

    remove_test_file("temp_mail_input_empty.txt");
}

void test_read_telegrams_from_file_InvalidFormat_returnMinusOne_no3() {
    const char* content = "2\n1 1\n2 2 3\n";
    create_test_file("temp_mail_input_invalid.txt", content);

    Telegram telegrams[MAX_TELEGRAMS];
    int K;
    int res = read_telegrams_from_file("temp_mail_input_invalid.txt", telegrams, &K);

    assert(res == -1);

    remove_test_file("temp_mail_input_invalid.txt");
}

void test_read_telegrams_from_file_NullFilename_returnMinusOne_no4() {
    Telegram telegrams[MAX_TELEGRAMS];
    int K;
    int res = read_telegrams_from_file(NULL, telegrams, &K);
    assert(res == -1);
}

void test_read_telegrams_from_file_NonExistentFile_returnMinusOne_no5() {
    Telegram telegrams[MAX_TELEGRAMS];
    int K;
    int res = read_telegrams_from_file("non_existent_mail.txt", telegrams, &K);
    assert(res == -1);
}

void test_calculate_optimal_schedule_SingleTelegramNoPenalty_returnValidSchedule_no6() {
    Telegram telegrams[] = { {1, 10, 1, 1} };
    int K = 0;
    int sorted_order[MAX_TELEGRAMS];

    int res = calculate_optimal_schedule(telegrams, 1, K, sorted_order);

    assert(res == 0); 
    assert(sorted_order[0] == 0); 
}

void test_calculate_optimal_schedule_TwoTelegramsFirstCausesPenalty_returnValidSchedule_no7() {
    Telegram telegrams[] = {
        {10, 0, 1, 1}, 
        {1, 5, 10, 2}  
    };
    int K = 5; 
    int sorted_order[MAX_TELEGRAMS];

    int res = calculate_optimal_schedule(telegrams, 2, K, sorted_order);

    assert(res == 1);
    assert(sorted_order[0] == 1); 
    assert(sorted_order[1] == 0); 
}

void test_calculate_optimal_schedule_TwoTelegramsOrderMatters_returnValidSchedule_no8() {
    Telegram telegrams_scenario[] = {
        {2, 3, 1, 1},
        {3, 3, 2, 2}, 
        {1, 4, 3, 3}  
    };
    int K = 0;
    int sorted_order[MAX_TELEGRAMS];

    int res = calculate_optimal_schedule(telegrams_scenario, 3, K, sorted_order);

    assert(res == 0);
    assert(sorted_order[2] == 1);
    assert((sorted_order[0] == 0 && sorted_order[1] == 2) || (sorted_order[0] == 2 && sorted_order[1] == 0));
}

void test_calculate_optimal_schedule_TotalPenaltyExceedsK_returnMinusOne_no9() {
    Telegram telegrams[] = {
        {1, 0, 10, 1}, 
        {1, 0, 10, 2}  
    };
    int K = 5; 
    int sorted_order[MAX_TELEGRAMS];
    int res = calculate_optimal_schedule(telegrams, 2, K, sorted_order);

    assert(res == -1);
}

void test_calculate_optimal_schedule_NullTelegrams_returnMinusOne_no10() {
    int sorted_order[MAX_TELEGRAMS];
    int res = calculate_optimal_schedule(NULL, 1, 10, sorted_order);
    assert(res == -1);
}

void test_calculate_optimal_schedule_NullOrder_returnMinusOne_no11() {
    Telegram telegrams[] = { {1, 1, 1, 1} };
    int res = calculate_optimal_schedule(telegrams, 1, 10, NULL);
    assert(res == -1);
}

void test_calculate_optimal_schedule_NegativeK_returnMinusOne_no12() {
    Telegram telegrams[] = { {1, 1, 1, 1} };
    int sorted_order[MAX_TELEGRAMS];
    int res = calculate_optimal_schedule(telegrams, 1, -1, sorted_order);
    assert(res == -1);
}

void test_write_result_to_file_ValidSchedule_success_no13() {
    int schedule[] = { 2, 0, 1 };
    int size = 3;

    int res = write_result_to_file(schedule, size, "temp_mail_output.txt");
    assert(res == 0);

    FILE* f = fopen("temp_mail_output.txt", "r");
    char line[256];
    assert(f != NULL);
    fgets(line, sizeof(line), f);
    fclose(f);
    assert(strncmp(line, "3 1 2", 5) == 0);
    remove_test_file("temp_mail_output.txt");
}

void test_write_result_to_file_ErrorCode_success_no14() {
    int res = write_result_to_file(NULL, -1, "temp_mail_output_error.txt");
    assert(res == 0);

    FILE* f = fopen("temp_mail_output_error.txt", "r");
    char line[256];
    assert(f != NULL);
    fgets(line, sizeof(line), f);
    fclose(f);
    assert(strncmp(line, "0", 1) == 0);
    remove_test_file("temp_mail_output_error.txt");
}

void test_write_result_to_file_NullFilename_returnMinusOne_no15() {
    int schedule[] = { 0 };
    int res = write_result_to_file(schedule, 1, NULL);
    assert(res == -1);
}

int main() {
    RUN_TEST(test_read_telegrams_from_file_ValidInput_returnCountAndData_no1, "test_read_telegrams_from_file_ValidInput_returnCountAndData_no1");
    RUN_TEST(test_read_telegrams_from_file_EmptyFile_returnMinusOne_no2, "test_read_telegrams_from_file_EmptyFile_returnMinusOne_no2");
    RUN_TEST(test_read_telegrams_from_file_InvalidFormat_returnMinusOne_no3, "test_read_telegrams_from_file_InvalidFormat_returnMinusOne_no3");
    RUN_TEST(test_read_telegrams_from_file_NullFilename_returnMinusOne_no4, "test_read_telegrams_from_file_NullFilename_returnMinusOne_no4");
    RUN_TEST(test_read_telegrams_from_file_NonExistentFile_returnMinusOne_no5, "test_read_telegrams_from_file_NonExistentFile_returnMinusOne_no5");
    RUN_TEST(test_calculate_optimal_schedule_SingleTelegramNoPenalty_returnValidSchedule_no6, "test_calculate_optimal_schedule_SingleTelegramNoPenalty_returnValidSchedule_no6");
    RUN_TEST(test_calculate_optimal_schedule_TwoTelegramsFirstCausesPenalty_returnValidSchedule_no7, "test_calculate_optimal_schedule_TwoTelegramsFirstCausesPenalty_returnValidSchedule_no7");
    RUN_TEST(test_calculate_optimal_schedule_TwoTelegramsOrderMatters_returnValidSchedule_no8, "test_calculate_optimal_schedule_TwoTelegramsOrderMatters_returnValidSchedule_no8");
    RUN_TEST(test_calculate_optimal_schedule_TotalPenaltyExceedsK_returnMinusOne_no9, "test_calculate_optimal_schedule_TotalPenaltyExceedsK_returnMinusOne_no9");
    RUN_TEST(test_calculate_optimal_schedule_NullTelegrams_returnMinusOne_no10, "test_calculate_optimal_schedule_NullTelegrams_returnMinusOne_no10");
    RUN_TEST(test_calculate_optimal_schedule_NullOrder_returnMinusOne_no11, "test_calculate_optimal_schedule_NullOrder_returnMinusOne_no11");
    RUN_TEST(test_calculate_optimal_schedule_NegativeK_returnMinusOne_no12, "test_calculate_optimal_schedule_NegativeK_returnMinusOne_no12");
    RUN_TEST(test_write_result_to_file_ValidSchedule_success_no13, "test_write_result_to_file_ValidSchedule_success_no13");
    RUN_TEST(test_write_result_to_file_ErrorCode_success_no14, "test_write_result_to_file_ErrorCode_success_no14");
    RUN_TEST(test_write_result_to_file_NullFilename_returnMinusOne_no15, "test_write_result_to_file_NullFilename_returnMinusOne_no15");

    printf("All tests passed!\n");

    // --- Основная логика программы ---
    Telegram telegrams[MAX_TELEGRAMS];
    int K;
    int num_telegrams = read_telegrams_from_file("input.txt", telegrams, &K);

    if (num_telegrams == -1) {
        FILE* out = fopen("output.txt", "w");
        if (out) {
            fprintf(out, "0\n");
            fclose(out);
        }
        return 1;
    }

    int sorted_order[MAX_TELEGRAMS];
    int penalty = calculate_optimal_schedule(telegrams, num_telegrams, K, sorted_order);

    if (penalty == -1) {
        write_result_to_file(NULL, -1, "output.txt"); // Вывод "0"
    }
    else {
        write_result_to_file(sorted_order, num_telegrams, "output.txt");
    }

    return 0;
}