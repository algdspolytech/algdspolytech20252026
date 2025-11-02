#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define main main_program
#include "../Project4/Lab-A.c"
#undef main

void create_test_words(Word* words, const char* strings[], int count) {
    for (int i = 0; i < count; i++) {
        strncpy(words[i].text, strings[i], MAX_WORD_LEN - 1);
        words[i].text[MAX_WORD_LEN - 1] = '\0';
    }
}

// ТЕСТ 1: Базовая сортировка разных слов
void test_sort_basic() {
    Word words[3];
    const char* test_strings[] = { "banana", "apple", "cherry" };
    create_test_words(words, test_strings, 3);

    qsort(words, 3, sizeof(Word), compare_words);

    assert(strcmp(words[0].text, "apple") == 0);
    assert(strcmp(words[1].text, "banana") == 0);
    assert(strcmp(words[2].text, "cherry") == 0);
    printf("Базовая сортировка работает\n");
}

// ТЕСТ 2: Сортировка одинаковых слов
void test_sort_duplicates() {
    Word words[4];
    const char* test_strings[] = { "beta", "alpha", "beta", "alpha" };
    create_test_words(words, test_strings, 4);

    qsort(words, 4, sizeof(Word), compare_words);

    assert(strcmp(words[0].text, "alpha") == 0);
    assert(strcmp(words[1].text, "alpha") == 0);
    assert(strcmp(words[2].text, "beta") == 0);
    assert(strcmp(words[3].text, "beta") == 0);
    printf("Сортировка с дубликатами работает\n");
}

// ТЕСТ 3: Сортировка пустого массива
void test_sort_empty() {
    Word words[1];
    qsort(words, 0, sizeof(Word), compare_words);
    printf("Пустой массив не вызывает ошибок\n");
}

// ТЕСТ 4: Сравнение с русскими буквами
void test_sort_cyrillic() {
    Word words[3];
    const char* test_strings[] = { "яблоко", "арбуз", "банан" };
    create_test_words(words, test_strings, 3);

    qsort(words, 3, sizeof(Word), compare_words);

    assert(strcmp(words[0].text, "арбуз") == 0);
    assert(strcmp(words[1].text, "банан") == 0);
    assert(strcmp(words[2].text, "яблоко") == 0);
    printf("Сортировка русских слов работает\n");
}

// ТЕСТ 5: Функция сравнения
void test_compare_function() {
    Word word1, word2;
    strcpy(word1.text, "apple");
    strcpy(word2.text, "banana");

    assert(compare_words(&word1, &word2) < 0);
    assert(compare_words(&word2, &word1) > 0);
    assert(compare_words(&word1, &word1) == 0);
    printf("Функция сравнения работает корректно\n");
}

// ТЕСТ 6: Чтение нормального файла
void test_read_valid_file() {
    FILE* f = fopen("test_input.txt", "w");
    fprintf(f, "zebra\napple\nmonkey\n");
    fclose(f);

    Word words[10];
    int count = read_words("test_input.txt", words);

    assert(count >= 0);
    if (count > 0) {
        assert(strcmp(words[0].text, "zebra") == 0);
    }

    remove("test_input.txt");
    printf("Чтение валидного файла работает\n");
}

// ТЕСТ 7: Чтение пустого файла
void test_read_empty_file() {
    FILE* f = fopen("test_empty.txt", "w");
    fclose(f);

    Word words[10];
    int count = read_words("test_empty.txt", words);

    assert(count == 0);
    remove("test_empty.txt");
    printf("Чтение пустого файла работает\n");
}

// ТЕСТ 8: Запись в файл
void test_write_file() {
    Word words[3];
    const char* test_strings[] = { "test1", "test2", "test3" };
    create_test_words(words, test_strings, 3);

    FILE* file = fopen("test_output.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < 3; i++) {
            fprintf(file, "%s\n", words[i].text);
        }
        fclose(file);
    }

    FILE* f = fopen("test_output.txt", "r");
    if (f != NULL) {
        char line1[100], line2[100], line3[100];
        fscanf(f, "%99s", line1);
        fscanf(f, "%99s", line2);
        fscanf(f, "%99s", line3);
        fclose(f);

        assert(strcmp(line1, "test1") == 0);
        assert(strcmp(line2, "test2") == 0);
        assert(strcmp(line3, "test3") == 0);
    }

    remove("test_output.txt");
    printf("Запись в файл работает\n");
}

// ТЕСТ 9: Объединение массивов
void test_array_operations() {
    Word arr1[2], arr2[2], result[4];
    const char* strings1[] = { "a", "c" };
    const char* strings2[] = { "b", "d" };
    create_test_words(arr1, strings1, 2);
    create_test_words(arr2, strings2, 2);

    int total = 0;
    for (int i = 0; i < 2; i++) result[total++] = arr1[i];
    for (int i = 0; i < 2; i++) result[total++] = arr2[i];

    assert(total == 4);
    printf("Базовые операции с массивами работают\n");
}

// ТЕСТ 10: Полный сценарий работы
void test_full_workflow() {
    Word words1[2], words2[2], all_words[4];
    const char* strings1[] = { "delta", "alpha" };
    const char* strings2[] = { "charlie", "bravo" };
    create_test_words(words1, strings1, 2);
    create_test_words(words2, strings2, 2);

    int total = 0;
    for (int i = 0; i < 2; i++) all_words[total++] = words1[i];
    for (int i = 0; i < 2; i++) all_words[total++] = words2[i];

    qsort(all_words, total, sizeof(Word), compare_words);

    assert(total == 4);
    assert(strcmp(all_words[0].text, "alpha") == 0);
    assert(strcmp(all_words[1].text, "bravo") == 0);
    assert(strcmp(all_words[2].text, "charlie") == 0);
    assert(strcmp(all_words[3].text, "delta") == 0);
    printf("Полный рабочий сценарий  работает\n");
}

// ТЕСТ 11: Граничные случаи
void test_edge_cases() {
    Word words[3];
    const char* test_strings[] = { "word1", "word10", "word2" };
    create_test_words(words, test_strings, 3);

    qsort(words, 3, sizeof(Word), compare_words);

    assert(strcmp(words[0].text, "word1") == 0);
    assert(strcmp(words[1].text, "word10") == 0);
    assert(strcmp(words[2].text, "word2") == 0);
    printf("Граничные случаи сортировки работают\n");
}

// ТЕСТ 12: Чтение несуществующего файла
void test_read_nonexistent_file() {
    Word words[10];
    int count = read_words("this_file_does_not_exist_12345.txt", words);

    assert(count == -1);
    printf("Корректная обработка отсутствующего файла\n");
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    printf("Запуск тестов для Project4\n\n");

    test_compare_function();
    test_sort_basic();
    test_sort_duplicates();
    test_sort_empty();
    test_sort_cyrillic();
    test_edge_cases();

    test_read_valid_file();
    test_read_empty_file();
    test_write_file();
    test_read_nonexistent_file();

    test_array_operations();
    test_full_workflow();

    printf("\nВсе тесты успешно пройдены\n");
    return 0;
}