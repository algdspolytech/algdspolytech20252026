#include <stdio.h>
#include "cells.h"

// Макрос для тестирования
#define TEST_ASSERT_EQ(actual, expected) \
    do { \
        if ((actual) != (expected)) { \
            printf(" Тест %s провален: ожидалось %d, получено %d\n", __FUNCTION__, (expected), (actual)); \
            (*fail_count)++; \
        } else { \
            (*pass_count)++; \
        } \
    } while(0)

// Вспомогательная функция для инициализации массива клеток
void init_removed(Cell* arr, int n, ...) {
    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; ++i) {
        arr[i].x = va_arg(args, int);
        arr[i].y = va_arg(args, int);
    }
    va_end(args);
}

// Тест: пустое поле 0x0 → 0 компонент
void Test_count_connected_components_EmptyGrid_no1(int* pass_count, int* fail_count) {
    Cell removed[1];
    int result = count_connected_components(0, 0, removed, 0);
    TEST_ASSERT_EQ(result, 0);
}

// Тест: поле 1x1, ничего не удалено → 1 компонент
void Test_count_connected_components_SingleCell_no2(int* pass_count, int* fail_count) {
    Cell removed[1];
    int result = count_connected_components(1, 1, removed, 0);
    TEST_ASSERT_EQ(result, 1);
}

// Тест: поле 1x1, клетка удалена → 0 компонент
void Test_count_connected_components_SingleCellRemoved_no3(int* pass_count, int* fail_count) {
    Cell removed[1] = { {0, 0} };
    int result = count_connected_components(1, 1, removed, 1);
    TEST_ASSERT_EQ(result, 0);
}

// Тест: поле 2x2, одна клетка удалена → всё равно 1 компонент
void Test_count_connected_components_TwoByTwoOneRemoved_no4(int* pass_count, int* fail_count) {
    Cell removed[1] = { {0, 0} };
    int result = count_connected_components(2, 2, removed, 1);
    TEST_ASSERT_EQ(result, 1);
}

// Тест: поле 2x2, две диагональные удалены → оставшиеся не связаны → 2 компонента
void Test_count_connected_components_TwoByTwoDiagonalRemoved_no5(int* pass_count, int* fail_count) {
    Cell removed[2] = { {0, 0}, {1, 1} };
    int result = count_connected_components(2, 2, removed, 2);
    TEST_ASSERT_EQ(result, 2);
}

// Тест: поле 3x3, удалён центр → всё ещё один компонент (остаток связный)
void Test_count_connected_components_ThreeByThreeCenterRemoved_no6(int* pass_count, int* fail_count) {
    Cell removed[1] = { {1, 1} };
    int result = count_connected_components(3, 3, removed, 1);
    TEST_ASSERT_EQ(result, 1);
}

// Тест: поле 3x3, удалены три клетки, разделяющие верх и низ → 2 компонента
void Test_count_connected_components_ThreeByThreeSplitHorizontally_no7(int* pass_count, int* fail_count) {
    Cell removed[3] = { {1, 0}, {1, 1}, {1, 2} }; // Средняя строка удалена
    int result = count_connected_components(3, 3, removed, 3);
    TEST_ASSERT_EQ(result, 2);
}

// Тест: поле 2x3, удалены две клетки, разрывающие связность → 2 компонента
void Test_count_connected_components_TwoByThreeBridgeRemoved_no8(int* pass_count, int* fail_count) {
    Cell removed[2] = { {0,1}, {1,1} }; // Удаляем средний столбец сверху и снизу
    int result = count_connected_components(2, 3, removed, 2);
    TEST_ASSERT_EQ(result, 2);
}

// Тест: поле 1x5 (линия), удалена средняя → делится на 2 части
void Test_count_connected_components_LineSplitMiddle_no9(int* pass_count, int* fail_count) {
    Cell removed[1] = { {0, 2} };
    int result = count_connected_components(1, 5, removed, 1);
    TEST_ASSERT_EQ(result, 2);
}

// Тест: поле 1x5, удалены концы → остаётся связный кусок посередине → 1 компонент
void Test_count_connected_components_LineEndsRemoved_no10(int* pass_count, int* fail_count) {
    Cell removed[2] = { {0, 0}, {0, 4} };
    int result = count_connected_components(1, 5, removed, 2);
    TEST_ASSERT_EQ(result, 1);
}

// Тест: поле 3x3, удалены граничные клетки, но внутреннее ядро цело → 1 компонент
void Test_count_connected_components_FrameRemoved_no11(int* pass_count, int* fail_count) {
    Cell removed[8] = {
        {0,0}, {0,1}, {0,2},
        {1,0},         {1,2},
        {2,0}, {2,1}, {2,2}
    }; // Удалена рамка, осталась только (1,1)
    int result = count_connected_components(3, 3, removed, 8);
    TEST_ASSERT_EQ(result, 1);
}

int main() {
    int pass_count = 0;
    int fail_count = 0;

    printf("=== Запуск тестов для count_connected_components ===\n\n");

    Test_count_connected_components_EmptyGrid_no1(&pass_count, &fail_count);
    Test_count_connected_components_SingleCell_no2(&pass_count, &fail_count);
    Test_count_connected_components_SingleCellRemoved_no3(&pass_count, &fail_count);
    Test_count_connected_components_TwoByTwoOneRemoved_no4(&pass_count, &fail_count);
    Test_count_connected_components_TwoByTwoDiagonalRemoved_no5(&pass_count, &fail_count);
    Test_count_connected_components_ThreeByThreeCenterRemoved_no6(&pass_count, &fail_count);
    Test_count_connected_components_ThreeByThreeSplitHorizontally_no7(&pass_count, &fail_count);
    Test_count_connected_components_TwoByThreeBridgeRemoved_no8(&pass_count, &fail_count);
    Test_count_connected_components_LineSplitMiddle_no9(&pass_count, &fail_count);
    Test_count_connected_components_LineEndsRemoved_no10(&pass_count, &fail_count);
    Test_count_connected_components_FrameRemoved_no11(&pass_count, &fail_count);

    printf("\n=== Результаты: ===\n");
    printf("Пройдено: %d\n", pass_count);
    printf("Провалено: %d\n", fail_count);
    printf("Всего тестов: %d\n", pass_count + fail_count);

    return fail_count > 0 ? 1 : 0;
}