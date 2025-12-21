// main.c
/**
 * @file main.c
 * @brief Главная программа для тестирования и запуска преобразования списка смежности
 *
 * @version 1.0
 * @date 2025.12.21
 * @author Д.Смирнов
 */

#pragma warning(disable:4996)

#include "List2Matrix.h"
#include <stdio.h>
#include <locale.h>
#include <windows.h>


int main(void) {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("Программа преобразования списка смежности в матрицу смежности\n");
    printf("=============================================================\n\n");

    printf("Запуск юнит-тестов\n");
    printf("=============================================================\n\n");
    UnitTests();

    printf("Запуск основной программы\n");
    printf("=============================================================\n\n");

    List2Matrix();
    return 0;
}