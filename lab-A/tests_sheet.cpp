#include <gtest/gtest.h>

extern "C" {
#include "sheet.h"
}

// Вспомогательная функция для подсчета связных кусков
int count_connected_pieces() {
    // Сбрасываем visited
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++)
            visited[y][x] = 0;

    int pieces = 0;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++)
            if (!visited[y][x] && grid[y][x] == 0) {
                dfs(x, y);
                pieces++;
            }
    return pieces;
}

// 1. Пустой лист (ни одной удаленной клетки)
TEST(SheetTest, EmptySheet_no1) {
    M = 3; N = 3;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++) grid[y][x] = 0;

    EXPECT_EQ(count_connected_pieces(), 1);
}

// 2. Лист полностью удалён
TEST(SheetTest, FullyRemoved_no2) {
    M = 2; N = 2;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++) grid[y][x] = 1;

    EXPECT_EQ(count_connected_pieces(), 0);
}

// 3. Один удаленный элемент
TEST(SheetTest, OneRemoved_no3) {
    M = 2; N = 2;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++) grid[y][x] = 0;
    grid[0][0] = 1;

    EXPECT_EQ(count_connected_pieces(), 1);
}

// 4. Несколько удалённых клеток в одной связной области
TEST(SheetTest, OneClusterRemoved_no4) {
    M = 3; N = 3;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++) grid[y][x] = 0;
    grid[1][1] = 1;
    grid[1][2] = 1;

    EXPECT_EQ(count_connected_pieces(), 1);
}

// 5. Несколько удалённых клеток разрозненно
TEST(SheetTest, DisjointRemoved_no5) {
    M = 3; N = 3;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++) grid[y][x] = 0;
    grid[0][0] = 1;
    grid[2][2] = 1;

    EXPECT_EQ(count_connected_pieces(), 1);
}

// 6. Граничные случаи (углы)
TEST(SheetTest, CornerRemoved_no6) {
    M = 3; N = 3;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++) grid[y][x] = 0;
    grid[0][0] = 1;
    grid[0][2] = 1;
    grid[2][0] = 1;
    grid[2][2] = 1;

    EXPECT_EQ(count_connected_pieces(), 1);
}

// 7. Лист 1x1
TEST(SheetTest, OneByOne_no7) {
    M = 1; N = 1;
    grid[0][0] = 0;

    EXPECT_EQ(count_connected_pieces(), 1);
}

// 8. Все клетки удалены кроме одной
TEST(SheetTest, OnlyOneLeft_no8) {
    M = 3; N = 3;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++) grid[y][x] = 1;
    grid[1][1] = 0;

    EXPECT_EQ(count_connected_pieces(), 1);
}

// 9. Несколько маленьких “островков”
TEST(SheetTest, MultipleIslands_no9) {
    M = 3; N = 3;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++) grid[y][x] = 1;
    grid[0][0] = 0;
    grid[0][2] = 0;
    grid[2][1] = 0;

    EXPECT_EQ(count_connected_pieces(), 3);
}

// 10. Случайный пример 5x5 с K=5 и известным результатом
TEST(SheetTest, RandomExample_no10) {
    M = 5; N = 5;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++) grid[y][x] = 0;
    grid[0][0] = 1;
    grid[1][1] = 1;
    grid[2][2] = 1;
    grid[3][3] = 1;
    grid[4][4] = 1;

    EXPECT_EQ(count_connected_pieces(), 2);
}

// main для запуска тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
