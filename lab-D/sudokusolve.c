#include "C:\Users\Asus\source\repos\sudoku\sudoku.c"
#include <gtest/gtest.h>
#include <stdio.h>

// Функция для проверки валидности решения судоку 9x9
int validate_9x9_solution(int grid[9][9]) {
    // Проверка строк
    for (int i = 0; i < 9; i++) {
        int used[10] = { 0 }; // Массив для отслеживания использованных чисел (1-9)
        for (int j = 0; j < 9; j++) {
            int num = grid[i][j];
            // Проверяем, что число в диапазоне 1-9 и не повторяется
            if (num < 1 || num > 9 || used[num]) {
                return 0;
            }
            used[num] = 1; // Помечаем число как использованное
        }
    }

    // Проверка столбцов
    for (int j = 0; j < 9; j++) {
        int used[10] = { 0 };
        for (int i = 0; i < 9; i++) {
            int num = grid[i][j];
            if (used[num]) {
                return 0;
            }
            used[num] = 1;
        }
    }

    // Проверка блоков 3x3
    for (int block_row = 0; block_row < 3; block_row++) {
        for (int block_col = 0; block_col < 3; block_col++) {
            int used[10] = { 0 };
            // Проверяем каждый блок 3x3
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int num = grid[block_row * 3 + i][block_col * 3 + j];
                    if (used[num]) {
                        return 0;
                    }
                    used[num] = 1;
                }
            }
        }
    }

    return 1;
}

// ТЕСТ 1: Инициализация структуры судоку с размером 3 (стандартное 9x9)
TEST(SudokuDLXTest, InitSudoku_ValidSize_ReturnValidStruct_no1) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    EXPECT_EQ(solver.N, 3);
    EXPECT_EQ(solver.size, 9);
    EXPECT_EQ(solver.nodeCount, 0);
    EXPECT_EQ(solver.solSize, 0);
}

// ТЕСТ 2: Инициализация структуры судоку с размером 2 (судоку 4x4)
TEST(SudokuDLXTest, InitSudoku_SizeTwo_ReturnValidStruct_no2) {
    SudokuDLX solver;
    initSudoku(&solver, 2);

    EXPECT_EQ(solver.N, 2);
    EXPECT_EQ(solver.size, 4);
}

// ТЕСТ 3: Решение полностью пустой сетки 9x9
TEST(SudokuDLXTest, SolveSudoku_EmptyGrid_ReturnSolution_no3) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            solver.grid[i][j] = 0;
        }
    }

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_TRUE(solved);

    if (solved) {
        fillSolution(&solver);
        EXPECT_TRUE(validate_9x9_solution(solver.grid));
    }
}

// ТЕСТ 4: Решение уже решенной судоку
TEST(SudokuDLXTest, SolveSudoku_AlreadySolved_ReturnSameGrid_no4) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    int solved_grid[9][9] = {
        {5,3,4,6,7,8,9,1,2},
        {6,7,2,1,9,5,3,4,8},
        {1,9,8,3,4,2,5,6,7},
        {8,5,9,7,6,1,4,2,3},
        {4,2,6,8,5,3,7,9,1},
        {7,1,3,9,2,4,8,5,6},
        {9,6,1,5,3,7,2,8,4},
        {2,8,7,4,1,9,6,3,5},
        {3,4,5,2,8,6,1,7,9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            solver.grid[i][j] = solved_grid[i][j];
        }
    }

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_TRUE(solved);

    if (solved) {
        fillSolution(&solver);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                EXPECT_EQ(solver.grid[i][j], solved_grid[i][j]);
            }
        }
    }
}

// ТЕСТ 5: Решение примера из задания
TEST(SudokuDLXTest, SolveSudoku_AssignmentExample_ReturnSolution_no5) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    int puzzle[9][9] = {
        {0,0,5,3,0,0,0,0,0},
        {8,0,0,0,0,0,0,0,2},
        {0,7,0,0,1,0,5,0,0},
        {4,0,0,0,0,5,3,0,0},
        {0,1,0,0,7,0,0,0,6},
        {0,0,3,2,0,0,0,8,0},
        {0,6,0,5,0,0,0,0,9},
        {0,0,4,0,0,0,0,3,0},
        {0,0,0,0,0,9,7,0,0}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            solver.grid[i][j] = puzzle[i][j];
        }
    }

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_TRUE(solved);

    if (solved) {
        fillSolution(&solver);
        EXPECT_TRUE(validate_9x9_solution(solver.grid));

        // Проверяем, что исходные числа не изменились
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (puzzle[i][j] != 0) {
                    EXPECT_EQ(solver.grid[i][j], puzzle[i][j]);
                }
            }
        }
    }
}

// ТЕСТ 6: Проверка на дубликаты в строке
TEST(SudokuDLXTest, SolveSudoku_DuplicateInRow_ReturnFalse_no6) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    // Создаем конфликт
    solver.grid[0][0] = 1;
    solver.grid[0][1] = 1;

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_FALSE(solved);
}

// ТЕСТ 7: Проверка на дубликаты в столбце
TEST(SudokuDLXTest, SolveSudoku_DuplicateInColumn_ReturnFalse_no7) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    // Создаем конфликт
    solver.grid[0][0] = 1;
    solver.grid[1][0] = 1;

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_FALSE(solved);
}

// ТЕСТ 8: Проверка на дубликаты в блоке 3x3
TEST(SudokuDLXTest, SolveSudoku_DuplicateInBlock_ReturnFalse_no8) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    // Создаем конфликт:
    solver.grid[0][0] = 1;
    solver.grid[1][1] = 1;

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_FALSE(solved);
}

// ТЕСТ 9: Решение с единственной подсказкой
TEST(SudokuDLXTest, SolveSudoku_SingleClue_ReturnSolution_no9) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    // Создаем почти пустую сетку с одной подсказкой в центре
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            solver.grid[i][j] = 0;
        }
    }
    solver.grid[4][4] = 1; // Единственная подсказка

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_TRUE(solved); // Ожидаем успешное решение

    if (solved) {
        fillSolution(&solver);
        EXPECT_TRUE(validate_9x9_solution(solver.grid));
        EXPECT_EQ(solver.grid[4][4], 1); // Проверяем сохранность подсказки
    }
}

// ТЕСТ 10: Решение почти полной сетки
TEST(SudokuDLXTest, SolveSudoku_AlmostComplete_ReturnSolution_no10) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    // Почти полная сетка с одной пустой клеткой
    int almost[9][9] = {
        {5,3,4,6,7,8,9,1,2},
        {6,7,2,1,9,5,3,4,8},
        {1,9,8,3,4,2,5,6,7},
        {8,5,9,7,6,1,4,2,3},
        {4,2,6,8,5,3,7,9,1},
        {7,1,3,9,2,4,8,5,6},
        {9,6,1,5,3,7,2,8,4},
        {2,8,7,4,1,9,6,3,0}, // Пустая клетка
        {3,4,5,2,8,6,1,7,9}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            solver.grid[i][j] = almost[i][j];
        }
    }

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_TRUE(solved);

    if (solved) {
        fillSolution(&solver);
        EXPECT_TRUE(validate_9x9_solution(solver.grid));
        EXPECT_EQ(solver.grid[7][8], 5);
    }
}

// ТЕСТ 11: Решение судоку с диагональным паттерном
// Проверяет работу с необычным распределением подсказок
TEST(SudokuDLXTest, SolveSudoku_DiagonalPattern_ReturnSolution_no11) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    // Заполняем только главную диагональ (1-9)
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            solver.grid[i][j] = 0;
        }
    }

    for (int i = 0; i < 9; i++) {
        solver.grid[i][i] = i + 1;
    }

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_TRUE(solved);

    if (solved) {
        fillSolution(&solver);
        EXPECT_TRUE(validate_9x9_solution(solver.grid));

        // Проверяем сохранность диагонали
        for (int i = 0; i < 9; i++) {
            EXPECT_EQ(solver.grid[i][i], i + 1);
        }
    }
}

// ТЕСТ 12: Решение судоку с X-образным паттерном
TEST(SudokuDLXTest, SolveSudoku_XPattern_ReturnSolution_no12) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    // X-образный паттерн подсказок
    int x_pattern[9][9] = {
        {1,0,0,0,0,0,0,0,2},
        {0,3,0,0,0,0,0,4,0},
        {0,0,5,0,0,0,6,0,0},
        {0,0,0,7,0,8,0,0,0},
        {0,0,0,0,9,0,0,0,0},
        {0,0,0,1,0,2,0,0,0},
        {0,0,3,0,0,0,4,0,0},
        {0,5,0,0,0,0,0,6,0},
        {7,0,0,0,0,0,0,0,8}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            solver.grid[i][j] = x_pattern[i][j];
        }
    }

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_TRUE(solved);

    if (solved) {
        fillSolution(&solver);
        EXPECT_TRUE(validate_9x9_solution(solver.grid));
    }
}

// ТЕСТ 13: Попытка решения невозможной судоку
TEST(SudokuDLXTest, SolveSudoku_NoSolution_ReturnFalse_no13) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    // Невозможная конфигурация: 9 в строке противоречит 9 в столбце
    int impossible[9][9] = {
        {1,2,3,4,5,6,7,8,0},
        {0,0,0,0,0,0,0,0,9},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            solver.grid[i][j] = impossible[i][j];
        }
    }

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_FALSE(solved);
}

// ТЕСТ 14: Попытка решения с одинаковыми числами во всех клетках
TEST(SudokuDLXTest, SolveSudoku_AllOnes_ReturnFalse_no14) {
    SudokuDLX solver;
    initSudoku(&solver, 3);

    // Все клетки заполнены 1 - явно некорректно
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            solver.grid[i][j] = 1;
        }
    }

    buildExactCover(&solver);
    int solved = solveSudoku(&solver);

    EXPECT_FALSE(solved);
}

// Основная функция запуска тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv)
    return RUN_ALL_TESTS();
}
