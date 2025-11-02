//Михайленко Валерия 5030102/40002
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "list.h"

int tests_passed = 0;
int tests_failed = 0;
int test_number = 1;




void RUN_TEST(int test_num, const char* test_name, int (*test_func)(void)) {
    printf("Тест %d: %s\n", test_num, test_name);
    if (test_func()) {
        printf("Пройден \n");
        tests_passed++;
    }
    else {
        printf("Ошибка \n");
        tests_failed++;
    }
    printf("\n");
}


int tempty_list(void) {
    LinkedList* list = create_list();
    char* result = concatenate_strings(list);
    if (result == NULL) return 0;
    if (strcmp(result, "") != 0) return 0;
    free(result);
    free_list(list);
    return 1;
}

int single_string(void) {
    LinkedList* list = create_list();
    append_string(list, "Код");
    char* result = concatenate_strings(list);
    if (result == NULL) return 0;
    if (strcmp(result, "Код") != 0) return 0;
    free(result);
    free_list(list);
    return 1;
}

int multiple_strings(void) {
    LinkedList* list = create_list();
    append_string(list, "Hello");
    append_string(list, ", ");
    append_string(list, "world");
    append_string(list, "!");
    char* result = concatenate_strings(list);
    if (result == NULL) return 0;
    if (strcmp(result, "Hello, world!") != 0) return 0;
    free(result);
    free_list(list);
    return 1;
}

int empty_strings(void) {
    LinkedList* list = create_list();
    append_string(list, "");
    append_string(list, "");
    append_string(list, "");
    char* result = concatenate_strings(list);
    if (result == NULL) return 0;
    if (strcmp(result, "") != 0) return 0;
    free(result);
    free_list(list);
    return 1;
}

int different_length_strings(void) {
    LinkedList* list = create_list();
    append_string(list, "А");
    append_string(list, "ББ");
    append_string(list, "ВВВ");
    append_string(list, "ГГГГ");
    char* result = concatenate_strings(list);
    if (result == NULL) return 0;
    if (strcmp(result, "АББВВВГГГГ") != 0) return 0;
    free(result);
    free_list(list);
    return 1;
}

int check_total_length(void) {
    LinkedList* list = create_list();

    if (get_total_length(list) != 0) return 0;

    append_string(list, "Test");
    if (get_total_length(list) != 4) return 0;

    append_string(list, "123");
    if (get_total_length(list) != 7) return 0;

    append_string(list, "");
    if (get_total_length(list) != 7) return 0;

    free_list(list);
    return 1;
}

int special_characters(void) {
    LinkedList* list = create_list();
    append_string(list, "Строка1\n");
    append_string(list, "Строка2\t");
    append_string(list, "Строка3");
    char* result = concatenate_strings(list);

    if (result == NULL) return 0;

    int found1 = (strstr(result, "Строка1") != NULL);
    int found2 = (strstr(result, "Строка2") != NULL);
    int found3 = (strstr(result, "Строка3") != NULL);

    free(result);
    free_list(list);

    return found1 && found2 && found3;
}

int null_string(void) {
    LinkedList* list = create_list();
    append_string(list, "Уолл-стрит");
    append_string(list, NULL);
    append_string(list, "фильм");
    char* result = concatenate_strings(list);

    if (result == NULL) return 0;
    int success = (strcmp(result, "Уолл-стритфильм") == 0);

    free(result);
    free_list(list);
    return success;
}

int null_list(void) {
    char* result = concatenate_strings(NULL);
    if (result == NULL) return 0;
    if (strcmp(result, "") != 0) {
        free(result);
        return 0;
    }

    if (get_total_length(NULL) != 0) return 0;

    return 1;
}

int memory_management(void) {
    LinkedList* list = create_list();

    append_string(list, "Строка0");
    append_string(list, "Строка1");
    append_string(list, "Строка2");
    append_string(list, "Строка3");
    append_string(list, "Строка4");

    char* result = concatenate_strings(list);
    if (result == NULL) return 0;

    int found0 = (strstr(result, "Строка0") != NULL);
    int found1 = (strstr(result, "Строка1") != NULL);
    int found2 = (strstr(result, "Строка2") != NULL);

    free(result);
    free_list(list);

    return found0 && found1 && found2;
}

int long_strings(void) {
    LinkedList* list = create_list();

    char long_str1[51];
    char long_str2[51];

    for (int i = 0; i < 50; i++) {
        long_str1[i] = 'A';
        long_str2[i] = 'B';
    }
    long_str1[50] = '\0';
    long_str2[50] = '\0';

    append_string(list, long_str1);
    append_string(list, long_str2);
    char* result = concatenate_strings(list);

    if (result == NULL) return 0;

    size_t result_len = strlen(result);
    int success = (result_len == 100) &&
        (result[0] == 'A') &&
        (result[49] == 'A') &&
        (result[50] == 'B');

    free(result);
    free_list(list);
    return success;
}

void run_all_tests(void) {
    setlocale(LC_CTYPE, "Russian");

    printf("=== Тесты ===\n\n");

    RUN_TEST(1, "Объединение пустого списка", tempty_list);
    RUN_TEST(2, "Объединение одной строки", single_string);
    RUN_TEST(3, "Объединение нескольких строк", multiple_strings);
    RUN_TEST(4, "Объединение пустых строк", empty_strings);
    RUN_TEST(5, "Объединение строк разной длины", different_length_strings);
    RUN_TEST(6, "Проверка общей длины", check_total_length);
    RUN_TEST(7, "Специальные символы", special_characters);
    RUN_TEST(8, "Добавление NULL строки", null_string);
    RUN_TEST(9, "Операции с NULL списком", null_list);
    RUN_TEST(10, "Управление памятью", memory_management);
    RUN_TEST(11, "Длинные строки", long_strings);

    printf("=== Результат ===\n");
    printf("Всего тестов: %d\n", tests_passed + tests_failed);
    printf("Пройдено: %d\n", tests_passed);
    printf("Не пройдено: %d\n", tests_failed);


    if (tests_failed == 0) {
        printf("\n Все тесты успешно пройдены!\n");
    }
    else {
        printf("\n Некоторые тесты не пройдены!\n");
    }
}