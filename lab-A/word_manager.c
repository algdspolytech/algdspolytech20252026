#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_manager.h"

// Функция для чтения данных из файла с одновременной сортировкой
int readFile(const char* filename, WordData data[]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return 0;
    }

    int count = 0;
    char buffer[100];
    char word[MAX_WORD_LENGTH];
    int key;

    while (fgets(buffer, sizeof(buffer), file) != NULL && count < MAX_WORDS) {
        // Пропускаем пустые строки
        if (strlen(buffer) <= 1) continue;

        // Читаем слово и число
        if (sscanf(buffer, "%49s %d", word, &key) == 2) {
            // Вставляем с сохранением сортировки
            insertSorted(data, &count, word, key);
        }
    }

    fclose(file);
    return count;
}

// Функция для проверки уникальности ключей
int hasDuplicateKeys(WordData data[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int k = i + 1; k <= count - 1; k++) {
            if (data[i].key == data[k].key) {

                return 1;
            }
        }
    }
    return 0;
}

// Функция для вставки с сохранением сортировки
void insertSorted(WordData data[], int* count, const char* word, int key) {
    int pos = 0;

    // Находим позицию для вставки
    while (pos < *count && data[pos].key < key) {
        pos++;
    }

    // Сдвигаем элементы вправо
    for (int i = *count; i > pos; i--) {
        data[i] = data[i - 1];
    }

    // Вставляем новый элемент
    strcpy(data[pos].word, word);
    data[pos].key = key;
    (*count)++;
}

// Функция для вывода списка
void printData(WordData data[], int count) {
    printf("\nОтсортированный список:\n");
    printf("Слово\t\tКлючевое число\n");
    printf("----------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-15s\t%d\n", data[i].word, data[i].key);
    }
    printf("----------------------------\n");
}

// Функция для поиска слова по ключевому числу
void searchByKey(WordData data[], int count, int searchKey) {
    // Используем бинарный поиск, так как массив отсортирован
    int left = 0;
    int right = count - 1;
    int found = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (data[mid].key == searchKey) {
            printf("Найдено слово: '%s' с ключевым числом %d\n", data[mid].word, searchKey);
            found = 1;
            break;
        }

        if (data[mid].key < searchKey) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (!found) {
        printf("Слово с ключевым числом %d не найдено в списке\n", searchKey);
    }
}