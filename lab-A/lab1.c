#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "locale.h"
#define MAX_WORD_LEN 100
#define MAX_WORDS 1000

// Структура для хранения слова
typedef struct {
    char text[MAX_WORD_LEN];
    int length;
} Word;

// Сравнение для сортировки
int compareWords(const void* a, const void* b) {
    const Word* wordA = (const Word*)a;
    const Word* wordB = (const Word*)b;

    // Сначала по длине
    if (wordA->length != wordB->length) {
        return wordA->length - wordB->length;
    }
    // При равной длине - по алфавиту
    return strcmp(wordA->text, wordB->text);
}

// Функция для создания тестового файла
void createTestFile() {
    FILE* file = fopen("input.txt", "w");
    if (file) {
        fprintf(file, "hello world this is a test\n");
        fprintf(file, "programming algorithm data structure\n");
        fprintf(file, "cat dog elephant mouse lion\n");
        fprintf(file, "one two three four five six seven\n");
        fprintf(file, "computer science university student\n");
        fclose(file);
        printf("Файл 'input.txt' создан в текущей папке.\n");
    }
    else {
        printf("Не удалось создать файл.\n");
    }
}

// Основная программа
int main() {
    Word words[MAX_WORDS];
    int wordCount = 0;
    char filename[100];
    char buffer[MAX_WORD_LEN];
    FILE* file;
    int N, searchLength;
    setlocale(LC_ALL, "");
    printf("=== ПРОГРАММА: АНАЛИЗ СЛОВ ИЗ ФАЙЛА ===\n");
    printf("Вариант 23: Сортировка по длине и алфавиту\n\n");

    printf("Введите имя файла (или нажмите Enter для input.txt): ");

    // Читаем ввод с возможностью просто нажать Enter
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("Ошибка ввода!\n");
        return 1;
    }

    // Удаляем символ новой строки
    filename[strcspn(filename, "\n")] = '\0';

    // Если строка пустая, используем input.txt
    if (strlen(filename) == 0) {
        strcpy(filename, "input.txt");
    }

    printf("Открываю файл: %s\n", filename);

    // Пробуем открыть файл
    file = fopen(filename, "r");

    if (!file) {
        printf("Файл '%s' не найден!\n", filename);
        printf("Создаю тестовый файл 'input.txt'...\n");
        createTestFile();

        // Пробуем снова открыть
        file = fopen("input.txt", "r");
        if (!file) {
            printf("Не удалось создать или открыть файл.\n");
            return 1;
        }
        printf("Использую созданный файл.\n");
    }
    else {
        printf("Файл успешно открыт.\n");
    }

    // Чтение слов
    while (fscanf(file, "%99s", buffer) == 1 && wordCount < MAX_WORDS) {
        // Очистка от не-букв и приведение к нижнему регистру
        int j = 0;
        for (int i = 0; buffer[i] && j < MAX_WORD_LEN - 1; i++) {
            if (isalpha((unsigned char)buffer[i])) {
                buffer[j++] = tolower((unsigned char)buffer[i]);
            }
        }
        buffer[j] = '\0';

        // Добавляем только если слово не пустое
        if (strlen(buffer) > 0) {
            strcpy(words[wordCount].text, buffer);
            words[wordCount].length = (int)strlen(buffer);
            wordCount++;
        }
    }

    fclose(file);

    if (wordCount == 0) {
        printf("В файле нет слов для обработки.\n");
        return 1;
    }

    // Сортировка
    qsort(words, wordCount, sizeof(Word), compareWords);

    printf("\n=== ОТСОРТИРОВАННЫЙ СПИСОК (%d слов) ===\n", wordCount);
    for (int i = 0; i < wordCount; i++) {
        printf("%-20s (длина: %d)\n", words[i].text, words[i].length);
    }

    // Слова длиннее N
    printf("\n--- Часть 1: Слова длиннее N символов ---\n");
    printf("Введите N: ");
    while (1) {
        if (scanf("%d", &N) == 1) {
            break;
        }
        else {
            printf("Пожалуйста, введите ЧИСЛО: ");
            while (getchar() != '\n');
        }
    }

    printf("\nСлова длиннее %d символов:\n", N);
    int found = 0;
    for (int i = 0; i < wordCount; i++) {
        if (words[i].length > N) {
            printf("  %s (длина: %d)\n", words[i].text, words[i].length);
            found = 1;
        }
    }
    if (!found) {
        printf("  Не найдено\n");
    }

    // Слова заданной длины
    printf("\n--- Часть 2: Поиск слов заданной длины ---\n");
    printf("Введите длину для поиска: ");
    while (1) {
        if (scanf("%d", &searchLength) == 1) {
            break;
        }
        else {
            printf("Пожалуйста, введите ЧИСЛО: ");
            while (getchar() != '\n');
        }
    }

    printf("\nСлова длиной %d символов:\n", searchLength);
    found = 0;
    for (int i = 0; i < wordCount; i++) {
        if (words[i].length == searchLength) {
            printf("  %s\n", words[i].text);
            found = 1;
        }
    }
    if (!found) {
        printf("  Не найдено\n");
    }

    printf("\n=== АНАЛИЗ ЗАВЕРШЕН ===\n");
    printf("\nНажмите Enter для выхода...");
    getchar(); // Очистка буфера
    getchar(); // Ожидание Enter

    return 0;
}