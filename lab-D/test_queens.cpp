#define _CRT_SECURE_NO_WARNINGS
#include <gtest/gtest.h>
#include <cstdlib>
#include "queens.h"

// Вспомогательная функция для проверки корректности решения
bool IsValidSolution(int* board, int N) {
    for (int i = 0; i < N; ++i) {
        if (board[i] == -1) return false;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (board[i] == board[j]) return false;
            if (abs(i - j) == abs(board[i] - board[j])) return false;
        }
    }
    return true;
}

// Тест 1: Проверка функции Check на пустой доске
TEST(QueensTest, CheckEmptyBoard) {
    const int N = 8;
    int board[N];
    for (int i = 0; i < N; ++i) board[i] = -1;

    EXPECT_EQ(Check(board, N, 0, 0), 1);
    EXPECT_EQ(Check(board, N, 3, 4), 1);
    EXPECT_EQ(Check(board, N, 7, 7), 1);
}

// Тест 2: Проверка функции Check на конфликт по колонке
TEST(QueensTest, CheckColumnConflict) {
    const int N = 8;
    int board[N];
    for (int i = 0; i < N; ++i) board[i] = -1;

    board[2] = 3;

    EXPECT_EQ(Check(board, N, 3, 5), 0);
    EXPECT_EQ(Check(board, N, 3, 0), 0);
}

// Тест 3: Проверка функции Check на конфликт по диагонали
TEST(QueensTest, CheckDiagonalConflict) {
    const int N = 8;
    int board[N];
    for (int i = 0; i < N; ++i) board[i] = -1;

    board[2] = 2;

    EXPECT_EQ(Check(board, N, 1, 1), 0);
    EXPECT_EQ(Check(board, N, 3, 3), 0);
}

// Тест 4: Проверка функции Check на безопасные позиции
TEST(QueensTest, CheckValidPositions) {
    const int N = 8;
    int board[N];
    for (int i = 0; i < N; ++i) board[i] = -1;

    board[2] = 3;

    EXPECT_EQ(Check(board, N, 0, 0), 1);
    EXPECT_EQ(Check(board, N, 7, 5), 1);
}

// Тест 5: Алгоритм для N=1 (тривиальный случай)
TEST(QueensTest, N1HasSolution) {
    const int N = 1;
    int board[N];

    bool found = false;
    for (int i = 0; i < N; ++i) {
        board[0] = -1;
        if (Queens(board, N, i, 0, 0)) {
            found = true;
            break;
        }
    }

    EXPECT_TRUE(found);
    if (found) EXPECT_TRUE(IsValidSolution(board, N));
}

// Тест 6: Алгоритм для N=2 (нет решения)
TEST(QueensTest, N2NoSolution) {
    const int N = 2;
    int board[N];

    bool found = false;
    for (int i = 0; i < N; ++i) {
        board[0] = -1;
        board[1] = -1;
        if (Queens(board, N, i, 0, 0)) {
            found = true;
            break;
        }
    }

    EXPECT_FALSE(found);
}

// Тест 7: Алгоритм для N=3 (нет решения)
TEST(QueensTest, N3NoSolution) {
    const int N = 3;
    int board[N];

    bool found = false;
    for (int i = 0; i < N; ++i) {
        board[0] = -1;
        board[1] = -1;
        board[2] = -1;
        if (Queens(board, N, i, 0, 0)) {
            found = true;
            break;
        }
    }

    EXPECT_FALSE(found);
}

// Тест 8: Алгоритм для N=4 (есть решение)
TEST(QueensTest, N4HasSolution) {
    const int N = 4;
    int board[N];

    bool found = false;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) board[j] = -1;
        if (Queens(board, N, i, 0, 0)) {
            found = true;
            break;
        }
    }

    EXPECT_TRUE(found);
    if (found) EXPECT_TRUE(IsValidSolution(board, N));
}

// Тест 9: Алгоритм для N=8 (классическая задача)
TEST(QueensTest, N8HasSolution) {
    const int N = 8;
    int board[N];

    bool found = false;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) board[j] = -1;
        if (Queens(board, N, i, 0, 0)) {
            found = true;
            break;
        }
    }

    EXPECT_TRUE(found);
    if (found) EXPECT_TRUE(IsValidSolution(board, N));
}

// Тест 10: Проверка корректности найденного решения
TEST(QueensTest, SolutionCorrectness) {
    const int N = 4;
    int board[N];

    // Известное решение для N=4
    board[0] = 1;
    board[1] = 3;
    board[2] = 0;
    board[3] = 2;

    EXPECT_TRUE(IsValidSolution(board, N));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}