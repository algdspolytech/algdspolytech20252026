#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include <locale.h>

// Простая система тестирования
int tests_passed = 0;
int tests_failed = 0;

#define TEST(name) void test_##name()
#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s:%d: %s\n", __FILE__, __LINE__, #condition); \
            tests_failed++; \
            return; \
        } \
    } while(0)

#define ASSERT_STREQ(expected, actual) \
    do { \
        if (strcmp((expected), (actual)) != 0) { \
            printf("FAIL: %s:%d: Expected '%s', got '%s'\n", __FILE__, __LINE__, (expected), (actual)); \
            tests_failed++; \
            return; \
        } \
    } while(0)

#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("FAIL: %s:%d: Expected %d, got %d\n", __FILE__, __LINE__, (expected), (actual)); \
            tests_failed++; \
            return; \
        } \
    } while(0)

#define ASSERT_NE(ptr, null_ptr) \
    do { \
        if ((ptr) == (null_ptr)) { \
            printf("FAIL: %s:%d: Pointer should not be NULL\n", __FILE__, __LINE__); \
            tests_failed++; \
            return; \
        } \
    } while(0)

#define RUN_TEST(test_function) \
    do { \
        printf("Running " #test_function "... "); \
        int prev_failed = tests_failed; \
        test_function(); \
        if (tests_failed == prev_failed) { \
            printf("PASS\n"); \
            tests_passed++; \
        } else { \
            printf("FAILED\n"); \
        } \
    } while(0)

// ОБЪЯВЛЕНИЯ всех тестовых функций в начале
void test_empty_list_no1();
void test_single_empty_string_no2();
void test_single_non_empty_string_no3();
void test_multiple_short_strings_no4();
void test_strings_with_different_lengths_no5();
void test_strings_with_special_chars_no6();
void test_very_long_strings_no7();
void test_mixed_empty_and_non_empty_strings_no8();
void test_numeric_strings_no9();
void test_large_number_of_strings_no10();
void test_null_list_no11();
void test_cyrillic_strings_no12();

// ТЕСТ 1: Конкатенация пустого списка
void test_empty_list_no1() {
    LinkedList* list = list_create();
    char* result = list_concat_strings(list);

    ASSERT_NE(result, NULL);
    ASSERT_STREQ(result, "");
    ASSERT_EQ(strlen(result), 0);

    free(result);
    list_destroy(list);
}

// ТЕСТ 2: Конкатенация списка с одной пустой строкой
void test_single_empty_string_no2() {
    LinkedList* list = list_create();
    list_append(list, "");
    char* result = list_concat_strings(list);

    ASSERT_NE(result, NULL);
    ASSERT_STREQ(result, "");
    ASSERT_EQ(strlen(result), 0);

    free(result);
    list_destroy(list);
}

// ТЕСТ 3: Конкатенация списка с одной непустой строкой
void test_single_non_empty_string_no3() {
    LinkedList* list = list_create();
    list_append(list, "Hello");
    char* result = list_concat_strings(list);

    ASSERT_NE(result, NULL);
    ASSERT_STREQ(result, "Hello");
    ASSERT_EQ(strlen(result), 5);

    free(result);
    list_destroy(list);
}

// ТЕСТ 4: Конкатенация нескольких коротких строк
void test_multiple_short_strings_no4() {
    LinkedList* list = list_create();
    list_append(list, "Hello");
    list_append(list, " ");
    list_append(list, "World");
    list_append(list, "!");
    char* result = list_concat_strings(list);

    ASSERT_NE(result, NULL);
    ASSERT_STREQ(result, "Hello World!");
    ASSERT_EQ(strlen(result), 12);

    free(result);
    list_destroy(list);
}

// ТЕСТ 5: Конкатенация строк с разной длиной
void test_strings_with_different_lengths_no5() {
    LinkedList* list = list_create();
    list_append(list, "A");
    list_append(list, "BB");
    list_append(list, "CCC");
    list_append(list, "DDDD");
    char* result = list_concat_strings(list);

    ASSERT_NE(result, NULL);
    ASSERT_STREQ(result, "ABBCCCDDDD");
    ASSERT_EQ(strlen(result), 10);

    free(result);
    list_destroy(list);
}


// ТЕСТ 6: Конкатенация очень длинных строк
void test_very_long_strings_no7() {
    LinkedList* list = list_create();

    // Создаем длинную строку
    char long_str1[1001];
    char long_str2[1001];
    memset(long_str1, 'A', 1000);
    memset(long_str2, 'B', 1000);
    long_str1[1000] = '\0';
    long_str2[1000] = '\0';

    list_append(list, long_str1);
    list_append(list, long_str2);
    char* result = list_concat_strings(list);

    ASSERT_NE(result, NULL);
    ASSERT_EQ(strlen(result), 2000);

    // Проверяем первые и последние символы
    ASSERT_EQ(result[0], 'A');
    ASSERT_EQ(result[999], 'A');
    ASSERT_EQ(result[1000], 'B');
    ASSERT_EQ(result[1999], 'B');

    free(result);
    list_destroy(list);
}

// ТЕСТ 7: Конкатенация смешанных строк (пустые и непустые)
void test_mixed_empty_and_non_empty_strings_no8() {
    LinkedList* list = list_create();
    list_append(list, "");
    list_append(list, "Hello");
    list_append(list, "");
    list_append(list, "World");
    list_append(list, "");
    char* result = list_concat_strings(list);

    ASSERT_NE(result, NULL);
    ASSERT_STREQ(result, "HelloWorld");
    ASSERT_EQ(strlen(result), 10);

    free(result);
    list_destroy(list);
}

// ТЕСТ 8: Конкатенация строк с числами
void test_numeric_strings_no9() {
    LinkedList* list = list_create();
    list_append(list, "123");
    list_append(list, "456");
    list_append(list, "789");
    char* result = list_concat_strings(list);

    ASSERT_NE(result, NULL);
    ASSERT_STREQ(result, "123456789");
    ASSERT_EQ(strlen(result), 9);

    free(result);
    list_destroy(list);
}

// ТЕСТ 9: Конкатенация большого количества строк
void test_large_number_of_strings_no10() {
    LinkedList* list = list_create();

    // Добавляем 100 строк
    for (int i = 0; i < 100; i++) {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "%d", i);
        list_append(list, buffer);
    }

    char* result = list_concat_strings(list);

    ASSERT_NE(result, NULL);
    // Проверяем, что результат содержит все числа
    ASSERT(strstr(result, "0") != NULL);
    ASSERT(strstr(result, "99") != NULL);

    free(result);
    list_destroy(list);
}

// ТЕСТ 10: Проверка на NULL список
void test_null_list_no11() {
    char* result = list_concat_strings(NULL);

    ASSERT_NE(result, NULL);
    ASSERT_STREQ(result, "");

    free(result);
}

// ТЕСТ 11: Конкатенация строк с кириллицей
void test_cyrillic_strings_no12() {
    LinkedList* list = list_create();
    list_append(list, "Привет");
    list_append(list, " ");
    list_append(list, "Мир");
    list_append(list, "!");
    char* result = list_concat_strings(list);

    ASSERT_NE(result, NULL);
    ASSERT_STREQ(result, "Привет Мир!");

    free(result);
    list_destroy(list);
}

int main() {
    setlocale(LC_ALL, "Russian");

    printf("=== Запуск тестов для конкатенации строк ===\n\n");

    // Запускаем все тесты
    RUN_TEST(test_empty_list_no1);
    RUN_TEST(test_single_empty_string_no2);
    RUN_TEST(test_single_non_empty_string_no3);
    RUN_TEST(test_multiple_short_strings_no4);
    RUN_TEST(test_strings_with_different_lengths_no5);
    RUN_TEST(test_very_long_strings_no7);
    RUN_TEST(test_mixed_empty_and_non_empty_strings_no8);
    RUN_TEST(test_numeric_strings_no9);
    RUN_TEST(test_large_number_of_strings_no10);
    RUN_TEST(test_null_list_no11);
    RUN_TEST(test_cyrillic_strings_no12);

    printf("\n=== Результаты тестирования ===\n");
    printf("Пройдено: %d\n", tests_passed);
    printf("Не пройдено: %d\n", tests_failed);
    printf("Всего: %d\n", tests_passed + tests_failed);

    if (tests_failed == 0) {
        printf("\nВсе тесты пройдены успешно!\n");
        return 0;
    }
    else {
        printf("\nЕсть непройденные тесты!\n");
        return 1;
    }
}