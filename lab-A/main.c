#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "word_manager.h"

int main() {
    WordData data[MAX_WORDS];
    char filename[100];
    int count;

    printf("=== Программа для работы с словами и ключевыми числами ===\n");

    // Ввод имени файла
    printf("Введите имя файла: ");
    scanf("%99s", filename);

    // Чтение данных из файла с сортировкой
    count = readFile(filename, data);
    if (count == 0) {
        printf("Не удалось прочитать данные из файла или файл пуст\n");
        return 1;
    }

    printf("Прочитано %d записей из файла\n", count);

    // Проверка на дубликаты ключей
    if (hasDuplicateKeys(data, count)) {
        return 1;
    }

    // Вывод отсортированного списка
    printData(data, count);

    // Поиск по ключевому числу
    int searchKey;
    printf("\nВведите ключевое число для поиска: ");
    scanf("%d", &searchKey);

    searchByKey(data, count, searchKey);

    return 0;
}