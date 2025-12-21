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

#include "hamiltonian.h"
#include <stdio.h>
#include <locale.h>
#include <windows.h>


int main(void) {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    printf("Программа поиска гамильтонова пути в графе\n");
    printf("==========================================\n\n");

    printf("Запуск юнит-тестов\n");
    printf("==========================================\n\n");
    UnitTests();

    printf("Запуск основной программы\n");
    printf("==========================================\n\n");

    HumiltonianFinder();
    return 0;
}