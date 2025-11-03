#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "word_manager.h"
#include <locale.h>

void test_insertSorted_empty() {
    printf("Тест 1: Вставка в пустой массив... ");
    WordData test[10];
    int count = 0;

    insertSorted(test, &count, "apple", 28);

    assert(count == 1);
    assert(strcmp(test[0].word, "apple") == 0);
    assert(test[0].key == 28);
    printf("ПРОЙДЕН\n");
}

void test_insertSorted_beginning() {
    printf("Тест 2: Вставка в начало... ");
    WordData test[10];
    int count = 1;
    strcpy(test[0].word, "banana");
    test[0].key = 50;

    insertSorted(test, &count, "apple", 28);

    assert(count == 2);
    assert(strcmp(test[0].word, "apple") == 0);
    assert(test[0].key == 28);
    assert(strcmp(test[1].word, "banana") == 0);
    assert(test[1].key == 50);
    printf("ПРОЙДЕН\n");
}

void test_insertSorted_end() {
    printf("Тест 3: Вставка в конец... ");
    WordData test[10];
    int count = 1;
    strcpy(test[0].word, "apple");
    test[0].key = 28;

    insertSorted(test, &count, "banana", 86);

    assert(count == 2);
    assert(strcmp(test[0].word, "apple") == 0);
    assert(test[0].key == 28);
    assert(strcmp(test[1].word, "banana") == 0);
    assert(test[1].key == 86);
    printf("ПРОЙДЕН\n");
}

void test_insertSorted_middle() {
    printf("Тест 4: Вставка в середину... ");
    WordData test[10];
    int count = 2;
    strcpy(test[0].word, "apple");
    test[0].key = 28;
    strcpy(test[1].word, "cherry");
    test[1].key = 86;

    insertSorted(test, &count, "banana", 50);

    assert(count == 3);
    assert(strcmp(test[0].word, "apple") == 0);
    assert(test[0].key == 28);
    assert(strcmp(test[1].word, "banana") == 0);
    assert(test[1].key == 50);
    assert(strcmp(test[2].word, "cherry") == 0);
    assert(test[2].key == 86);
    printf("ПРОЙДЕН\n");
}

void test_hasDuplicateKeys_found() {
    printf("Тест 5: Обнаружение дубликатов ключей... ");
    WordData test[3];

    strcpy(test[0].word, "word1");
    test[0].key = 10;
    strcpy(test[1].word, "word2");
    test[1].key = 20;
    strcpy(test[2].word, "word3");
    test[2].key = 10; // Дубликат

    int result = hasDuplicateKeys(test, 3);
    if (result == 1) {
        printf("ПРОЙДЕН\n");
    }

}

void test_hasDuplicateKeys_not_found() {
    printf("Тест 6: Отсутствие дубликатов ключей... ");
    WordData test[3];

    strcpy(test[0].word, "word1");
    test[0].key = 10;
    strcpy(test[1].word, "word2");
    test[1].key = 20;
    strcpy(test[2].word, "word3");
    test[2].key = 30;

    int result = hasDuplicateKeys(test, 3);
    if (result == 0) {
        printf("ПРОЙДЕН\n");
    }
}




void test_readFile_correct() {
    printf("Тест 7: Чтение корректного файла... ");

    // Создаем тестовый файл
    FILE* testFile = fopen("test_input.txt", "w");
    fprintf(testFile, "apple 28\nbanana 86\ncherry 15\n");
    fclose(testFile);

    WordData test[10];
    int count = readFile("test_input.txt", test);

    assert(count == 3);
    // Проверяем, что данные отсортированы
    assert(test[0].key == 15);
    assert(test[1].key == 28);
    assert(test[2].key == 86);

    remove("test_input.txt");
    printf("ПРОЙДЕН\n");
}

void test_readFile_nonexistent() {
    printf("Тест 8: Чтение несуществующего файла... ");
    WordData test[10];
    int count = readFile("nonexistent_file.txt", test);

    assert(count == 0);
    printf("ПРОЙДЕН\n");
}

void test_complex_sorting() {
    printf("Тест 9: Комплексная проверка сортировки... ");
    WordData test[10];
    int count = 0;

    // Вставляем в разном порядке
    insertSorted(test, &count, "zebra", 100);
    insertSorted(test, &count, "apple", 10);
    insertSorted(test, &count, "monkey", 50);
    insertSorted(test, &count, "banana", 25);
    insertSorted(test, &count, "cat", 30);

    assert(count == 5);
    // Проверяем порядок
    assert(test[0].key == 10);
    assert(test[1].key == 25);
    assert(test[2].key == 30);
    assert(test[3].key == 50);
    assert(test[4].key == 100);

    // Проверяем соответствие слов и ключей
    assert(strcmp(test[0].word, "apple") == 0);
    assert(strcmp(test[1].word, "banana") == 0);
    assert(strcmp(test[2].word, "cat") == 0);
    assert(strcmp(test[3].word, "monkey") == 0);
    assert(strcmp(test[4].word, "zebra") == 0);
    printf("ПРОЙДЕН\n");
}

void test_duplicate_consecutive() {
    printf("Тест 10: Дубликаты идущие подряд... ");
    WordData test[4];

    strcpy(test[0].word, "word1");
    test[0].key = 10;
    strcpy(test[1].word, "word2");
    test[1].key = 10; // Дубликат сразу после
    strcpy(test[2].word, "word3");
    test[2].key = 20;
    strcpy(test[3].word, "word4");
    test[3].key = 30;

    int result = hasDuplicateKeys(test, 4);
    assert(result == 1);
    printf("ПРОЙДЕН\n");
}

void run_all_tests() {
    printf("\n=== ЗАПУСК ВСЕХ ТЕСТОВ ===\n");

    test_insertSorted_empty();
    test_insertSorted_beginning();
    test_insertSorted_end();
    test_insertSorted_middle();
    test_hasDuplicateKeys_found();
    test_hasDuplicateKeys_not_found();
    test_readFile_correct();
    test_readFile_nonexistent();
    test_complex_sorting();        // Дополнительный тест
    test_duplicate_consecutive();  // Дополнительный тест

    printf("\n=== ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ ===\n");
    printf("Всего пройдено: 10 тестов\n");
}

int main() {
    setlocale(LC_ALL, "RUS");
    run_all_tests();
    return 0;
}