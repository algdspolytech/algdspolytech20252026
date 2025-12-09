#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "paper.h"
#include <locale.h>

#define ASSERT_EQ(actual, expected, message) \
    do { \
        if ((actual) != (expected)) { \
            fprintf(stderr, "TEST FAILED: %s (Ожидалось: %d, Получено: %d)\n", message, expected, actual); \
            exit(1); \
        } \
    } while (0)

#define ASSERT_NE(actual, expected, message) \
    do { \
        if ((actual) == (expected)) { \
            fprintf(stderr, "TEST FAILED: %s (Получено NULL)\n", message); \
            exit(1); \
        } \
    } while (0)

#define ASSERT_NULL(actual, message) \
    do { \
        if ((actual) != NULL) { \
            fprintf(stderr, "TEST FAILED: %s (Получен объект, ожидался NULL)\n", message); \
            exit(1); \
        } \
    } while (0)


// 10 юнит-тестов

// 1. проверка успешного создания листа
void test_01_create_valid_paper() {
    Paper* paper = create_paper(10, 5);
    ASSERT_NE(paper, NULL, "01. Создание листа 10x5");
    destroy_paper(paper);
    printf("Тест 01: Успешно\n");
}

// 2. проверка создания с недопустимыми размерами
void test_02_create_invalid_paper() {
    Paper* paper = create_paper(0, 4);
    ASSERT_NULL(paper, "02. Создание с нулевой строкой должно вернуть NULL");

    paper = create_paper(3, -1);
    ASSERT_NULL(paper, "02. Создание с отрицательным столбцом должно вернуть NULL");

    printf("Тест 02: Успешно\n");
}

// 3. проверка подсчета для пустого листа (NULL-указатель)
void test_03_null_paper_count() {
    int components = count_connected_components(NULL);
    ASSERT_EQ(components, 0, "03. Подсчет на NULL-указателе должен быть 0");
    printf("Тест 03: Успешно\n");
}

// 4. проверка листа без удалений
void test_04_no_cells_removed() {
    Paper* paper = create_paper(5, 5);
    int components = count_connected_components(paper);
    ASSERT_EQ(components, 1, "04. Целый лист 5x5 должен быть 1 куском");
    destroy_paper(paper);
    printf("Тест 04: Успешно\n");
}

// 5. проверка полностью удаленного листа
void test_05_all_cells_removed() {
    Paper* paper = create_paper(2, 2);
    int x[] = { 0, 0, 1, 1 };
    int y[] = { 0, 1, 0, 1 };
    remove_cells(paper, 4, x, y);
    int components = count_connected_components(paper);
    ASSERT_EQ(components, 0, "05. Все клетки удалены, должно быть 0 кусков");
    destroy_paper(paper);
    printf("Тест 05: Успешно\n");
}

// 6. проверка разрезания на две части
void test_06_cut_into_two_pieces() {
    // 2x4, удаляем центр верт линию: (0, 1), (1, 1)
    Paper* paper = create_paper(2, 4);
    int x[] = { 0, 1 };
    int y[] = { 1, 1 };
    remove_cells(paper, 2, x, y);
    int components = count_connected_components(paper);
    ASSERT_EQ(components, 2, "06. Разрезание 2x4 на 2 куска");
    destroy_paper(paper);
    printf("Тест 06: Успешно\n");
}

// 7. проверка разрезания на три изолированных куска в строке
void test_07_cut_into_three_pieces() {
    // 1x7. Удаляем (0, 2) и (0, 4). Остаются: (0, 0), (0, 1); (0, 3); (0, 5), (0, 6)
    Paper* paper = create_paper(1, 7);
    int x[] = { 0, 0 };
    int y[] = { 2, 4 };
    remove_cells(paper, 2, x, y);
    int components = count_connected_components(paper);
    ASSERT_EQ(components, 3, "07. Разрезание 1x7 на 3 куска");
    destroy_paper(paper);
    printf("Тест 07: Успешно\n");
}

// 8. проверка полного разделения на 4 изолированных угла
void test_08_four_isolated_corners() {
    // 3x3. удаляем центральный крест (строка 1 и колонка 1), оставляя углы (0,0), (0,2), (2,0), (2,2)
    Paper* paper = create_paper(3, 3);
    int x[] = { 0, 1, 2, 1, 1 };
    int y[] = { 1, 1, 1, 0, 2 };
    remove_cells(paper, 5, x, y);
    int components = count_connected_components(paper);
    ASSERT_EQ(components, 4, "08. Удаление крестом, должно быть 4 изолированных угла");
    destroy_paper(paper);
    printf("Тест 08: Успешно\n");
}

// 9. проверка паттерна "шахматной доски" (макс изоляция)
void test_09_checkerboard_pattern() {
    // 4x4. Остается 8 изолированных клеток.
    Paper* paper = create_paper(4, 4);
    int x[8], y[8];
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if ((i + j) % 2 != 0) { // удаляем клетки 1го цвета
                x[k] = i;
                y[k] = j;
                k++;
            }
        }
    }
    remove_cells(paper, k, x, y);
    int components = count_connected_components(paper);
    ASSERT_EQ(components, 8, "09. Шахматная доска 4x4, должно быть 8 изолированных кусков");
    destroy_paper(paper);
    printf("Тест 09: Успешно\n");
}

// 10. проверка удаления за пределами границ (должно игнорироваться)
void test_10_remove_out_of_bounds() {
    // 3x3. удаляем несуществующие (5, 5) и (-1, 0)
    Paper* paper = create_paper(3, 3);
    int x[] = { 5, -1 };
    int y[] = { 5, 0 };
    remove_cells(paper, 2, x, y);
    int components = count_connected_components(paper);
    ASSERT_EQ(components, 1, "10. Удаление вне границ должно игнорироваться, остался 1 кусок");
    destroy_paper(paper);
    printf("Тест 10: Успешно\n");
}

// запуск всех 10 тестов
int main() {
    setlocale(LC_ALL, "Russian");
    printf("--- Начало тестирования Lab B (10 Юнит-тестов) ---\n");
    test_01_create_valid_paper();
    test_02_create_invalid_paper();
    test_03_null_paper_count();
    test_04_no_cells_removed();
    test_05_all_cells_removed();
    test_06_cut_into_two_pieces();
    test_07_cut_into_three_pieces();
    test_08_four_isolated_corners();
    test_09_checkerboard_pattern();
    test_10_remove_out_of_bounds();
    printf("Все 10 тестов успешно завершены\n");
    return 0;
}