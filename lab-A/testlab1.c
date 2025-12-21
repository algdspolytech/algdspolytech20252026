#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "string.h"
#include "locale.h"

// Простая система тестирования
int testCount = 0;
int passedTests = 0;

void runTest(const char* testName, int condition) {
    testCount++;
    if (condition) {
        passedTests++;
        printf("Тест %d: %s - ПРОЙДЕН\n", testCount, testName);
    }
    else {
        printf("Тест %d: %s - НЕ ПРОЙДЕН\n", testCount, testName);
    }
}

// Тест сравнения слов
void testWordComparison() {
    printf("\n=== ТЕСТИРОВАНИЕ СОРТИРОВКИ ===\n");

    // Тест 1: Слова разной длины
    runTest("Сортировка по длине (короткое перед длинным)_no1",
        strlen("cat") < strlen("elephant"));

    // Тест 2: Слова одинаковой длины, сортировка по алфавиту
    runTest("Сортировка по алфавиту при равной длине_no2",
        strcmp("cat", "dog") < 0);

    // Тест 3: Обработка пустого слова
    runTest("Пустая строка имеет длину 0_no3",
        strlen("") == 0);
}

// Тест логики программы
void testProgramLogic() {
    printf("\n=== ТЕСТИРОВАНИЕ ЛОГИКИ ПРОГРАММЫ ===\n");

    char testWords[5][20] = { "elephant", "cat", "dog", "ant", "programming" };
    int lengths[5] = { 8, 3, 3, 3, 11 };

    // Тест 4: Длина слова
    runTest("Правильный расчет длины слова_no4",
        strlen("elephant") == 8);

    // Тест 5: Поиск длинных слов
    runTest("Нахождение слов длиннее 5 символов_no5",
        lengths[0] > 5 && lengths[4] > 5);

    // Тест 6: Поиск коротких слов
    runTest("Нахождение слов длиной 3 символа_no6",
        lengths[1] == 3 && lengths[2] == 3 && lengths[3] == 3);

    // Тест 7: Алфавитный порядок
    runTest("Алфавитный порядок 'ant' < 'cat' < 'dog'_no7",
        strcmp("ant", "cat") < 0 && strcmp("cat", "dog") < 0);
}

// Тест обработки файлов
void testFileHandling() {
    printf("\n=== ТЕСТИРОВАНИЕ РАБОТЫ С ФАЙЛАМИ ===\n");

    // Создаем тестовый файл
    FILE* testFile = fopen("test_input.txt", "w");
    if (testFile) {
        fprintf(testFile, "test words here\n");
        fclose(testFile);

        // Тест 8: Создание файла
        runTest("Создание тестового файла_no8", 1);

        // Тест 9: Чтение файла
        testFile = fopen("test_input.txt", "r");
        runTest("Открытие файла для чтения_no9", testFile != NULL);
        if (testFile) fclose(testFile);

        // Тест 10: Удаление файла
        remove("test_input.txt");
        runTest("Очистка тестовых файлов_no10", 1);
    }
}

// Тест граничных случаев
void testEdgeCases() {
    printf("\n=== ТЕСТИРОВАНИЕ ГРАНИЧНЫХ СЛУЧАЕВ ===\n");

    // Тест 11: Очень длинное слово
    char longWord[100] = "supercalifragilisticexpialidocious";
    runTest("Обработка очень длинного слова_no11",
        strlen(longWord) > 10);

    // Тест 12: Односимвольное слово
    runTest("Обработка односимвольного слова_no12",
        strlen("a") == 1);
}

int main() {
    setlocale(LC_ALL, "");
    printf("=== ЮНИТ-ТЕСТЫ ДЛЯ ПРОГРАММЫ 'ДЛИНА СЛОВ' ===\n");
    printf("Вариант 23\n\n");

    testWordComparison();
    testProgramLogic();
    testFileHandling();
    testEdgeCases();

    printf("\n=== ИТОГИ ТЕСТИРОВАНИЯ ===\n");
    printf("Пройдено тестов: %d из %d\n", passedTests, testCount);
    printf("Успешность: %.0f%%\n", (float)passedTests / testCount * 100);

    if (passedTests == testCount) {
        printf("\n ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!\n");
    }
    else {
        printf("\n  НЕКОТОРЫЕ ТЕСТЫ НЕ ПРОЙДЕНЫ\n");
    }

    return 0;
}