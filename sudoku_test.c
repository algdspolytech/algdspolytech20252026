#define _CRT_SECURE_NO_WARNINGS
#include "sudoku_solver.h"
#include <assert.h>
#include <string.h>

// Тест 1: Простая судоку 3x3 с решением
void test_easy_sudoku() {
    printf("Test 1: Easy 3x3 Sudoku\n");
    Puzzle p = { 3, 9, 3, NULL };
    p.data = malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++) p.data[i] = malloc(9 * sizeof(int));

    // Простая судоку из примера
    int board[9][9] = {
        {0,0,5,3,0,0,0,0,0},
        {8,0,0,0,0,0,0,2,0},
        {0,7,0,0,1,0,5,0,0},
        {4,0,0,0,0,5,3,0,0},
        {0,1,0,0,7,0,0,0,6},
        {0,3,2,0,0,0,0,8,0},
        {0,6,0,5,0,0,0,0,9},
        {0,0,4,0,0,0,0,3,0},
        {0,0,0,0,0,9,7,0,0}
    };

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            p.data[i][j] = board[i][j];

    assert(solveSudoku(&p) == 1);
    assert(validateSudoku(&p) == 1);

    cleanupPuzzle(&p);
    printf("✓ Passed\n\n");
}

// Тест 2: Уже решенная судоку
void test_already_solved() {
    printf("Test 2: Already solved Sudoku\n");
    Puzzle p = { 3, 9, 3, NULL };
    p.data = malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++) p.data[i] = malloc(9 * sizeof(int));

    int solved[9][9] = {
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

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            p.data[i][j] = solved[i][j];

    assert(solveSudoku(&p) == 1);
    assert(validateSudoku(&p) == 1);

    cleanupPuzzle(&p);
    printf("✓ Passed\n\n");
}

// Тест 3: Нерешаемая судоку (противоречивые значения)
void test_unsolvable() {
    printf("Test 3: Unsolvable Sudoku\n");
    Puzzle p = { 3, 9, 3, NULL };
    p.data = malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++) p.data[i] = malloc(9 * sizeof(int));

    // Противоречие: две пятерки в одной строке
    int board[9][9] = {
        {5,5,0,0,0,0,0,0,0},  // Две пятерки в первой строке!
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0}
    };

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            p.data[i][j] = board[i][j];

    assert(solveSudoku(&p) == 0);

    cleanupPuzzle(&p);
    printf("✓ Passed\n\n");
}

// Тест 4: Пустая судоку (все нули)
void test_empty_sudoku() {
    printf("Test 4: Empty Sudoku board\n");
    Puzzle p = { 3, 9, 3, NULL };
    p.data = malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++) {
        p.data[i] = malloc(9 * sizeof(int));
        for (int j = 0; j < 9; j++)
            p.data[i][j] = 0;
    }

    assert(solveSudoku(&p) == 1);
    assert(validateSudoku(&p) == 1);

    cleanupPuzzle(&p);
    printf("✓ Passed\n\n");
}

// Тест 5: Судоку с минимальным количеством подсказок (17 - минимальное для однозначного решения)
void test_minimal_clues() {
    printf("Test 5: Sudoku with minimal clues (17)\n");
    Puzzle p = { 3, 9, 3, NULL };
    p.data = malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++) {
        p.data[i] = malloc(9 * sizeof(int));
        for (int j = 0; j < 9; j++)
            p.data[i][j] = 0;
    }

    // Одна из минимальных конфигураций с 17 подсказками
    int clues[17][3] = {
        {0,0,1}, {0,7,2}, {1,1,3}, {1,4,4}, {2,3,5},
        {2,6,6}, {3,2,7}, {3,5,8}, {4,1,9}, {4,8,1},
        {5,0,2}, {5,3,3}, {5,6,4}, {6,2,5}, {6,7,6},
        {7,4,7}, {8,1,8}
    };

    for (int i = 0; i < 17; i++) {
        p.data[clues[i][0]][clues[i][1]] = clues[i][2];
    }

    assert(solveSudoku(&p) == 1);
    assert(validateSudoku(&p) == 1);

    cleanupPuzzle(&p);
    printf("✓ Passed\n\n");
}

// Тест 6: Судоку 2x2 (маленький размер)
void test_small_sudoku() {
    printf("Test 6: 2x2 Sudoku (N=2)\n");
    Puzzle p = { 2, 4, 2, NULL };
    p.data = malloc(4 * sizeof(int*));
    for (int i = 0; i < 4; i++) p.data[i] = malloc(4 * sizeof(int));

    int board[4][4] = {
        {0,0,0,1},
        {0,0,2,0},
        {0,3,0,0},
        {4,0,0,0}
    };

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            p.data[i][j] = board[i][j];

    assert(solveSudoku(&p) == 1);
    assert(validateSudoku(&p) == 1);

    cleanupPuzzle(&p);
    printf("✓ Passed\n\n");
}

// Тест 7: Валидация корректной судоку
void test_validation_correct() {
    printf("Test 7: Validation of correct Sudoku\n");
    Puzzle p = { 3, 9, 3, NULL };
    p.data = malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++) p.data[i] = malloc(9 * sizeof(int));

    int correct[9][9] = {
        {1,2,3,4,5,6,7,8,9},
        {4,5,6,7,8,9,1,2,3},
        {7,8,9,1,2,3,4,5,6},
        {2,3,4,5,6,7,8,9,1},
        {5,6,7,8,9,1,2,3,4},
        {8,9,1,2,3,4,5,6,7},
        {3,4,5,6,7,8,9,1,2},
        {6,7,8,9,1,2,3,4,5},
        {9,1,2,3,4,5,6,7,8}
    };

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            p.data[i][j] = correct[i][j];

    assert(validateSudoku(&p) == 1);

    cleanupPuzzle(&p);
    printf("✓ Passed\n\n");
}

// Тест 8: Валидация некорректной судоку (повтор в строке)
void test_validation_incorrect_row() {
    printf("Test 8: Validation of incorrect Sudoku (row duplicate)\n");
    Puzzle p = { 3, 9, 3, NULL };
    p.data = malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++) p.data[i] = malloc(9 * sizeof(int));

    int incorrect[9][9] = {
        {1,1,3,4,5,6,7,8,9},  // Две единицы в первой строке
        {4,5,6,7,8,9,1,2,3},
        {7,8,9,1,2,3,4,5,6},
        {2,3,4,5,6,7,8,9,1},
        {5,6,7,8,9,1,2,3,4},
        {8,9,1,2,3,4,5,6,7},
        {3,4,5,6,7,8,9,1,2},
        {6,7,8,9,1,2,3,4,5},
        {9,1,2,3,4,5,6,7,8}
    };

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            p.data[i][j] = incorrect[i][j];

    assert(validateSudoku(&p) == 0);

    cleanupPuzzle(&p);
    printf("✓ Passed\n\n");
}

// Тест 9: Валидация некорректной судоку (повтор в столбце)
void test_validation_incorrect_col() {
    printf("Test 9: Validation of incorrect Sudoku (column duplicate)\n");
    Puzzle p = { 3, 9, 3, NULL };
    p.data = malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++) p.data[i] = malloc(9 * sizeof(int));

    int incorrect[9][9] = {
        {1,2,3,4,5,6,7,8,9},
        {1,5,6,7,8,9,2,3,4},  // Единица в первом столбце (дубликат)
        {7,8,9,1,2,3,4,5,6},
        {2,3,4,5,6,7,8,9,1},
        {5,6,7,8,9,1,2,3,4},
        {8,9,1,2,3,4,5,6,7},
        {3,4,5,6,7,8,9,1,2},
        {6,7,8,9,1,2,3,4,5},
        {9,1,2,3,4,5,6,7,8}
    };

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            p.data[i][j] = incorrect[i][j];

    assert(validateSudoku(&p) == 0);

    cleanupPuzzle(&p);
    printf("✓ Passed\n\n");
}

// Тест 10: Валидация некорректной судоку (повтор в квадрате)
void test_validation_incorrect_box() {
    printf("Test 10: Validation of incorrect Sudoku (box duplicate)\n");
    Puzzle p = { 3, 9, 3, NULL };
    p.data = malloc(9 * sizeof(int*));
    for (int i = 0; i < 9; i++) p.data[i] = malloc(9 * sizeof(int));

    int incorrect[9][9] = {
        {1,2,3,4,5,6,7,8,9},
        {4,5,6,7,8,9,1,2,3},
        {7,8,1,2,3,4,5,6,7},  // Две семерки в третьем квадрате
        {2,3,4,5,6,7,8,9,1},
        {5,6,7,8,9,1,2,3,4},
        {8,9,1,2,3,4,5,6,7},
        {3,4,5,6,7,8,9,1,2},
        {6,7,8,9,1,2,3,4,5},
        {9,1,2,3,4,5,6,7,8}
    };

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            p.data[i][j] = incorrect[i][j];

    assert(validateSudoku(&p) == 0);

    cleanupPuzzle(&p);
    printf("✓ Passed\n\n");
}

int main() {
    printf("=== Running Sudoku Solver Unit Tests ===\n\n");

    test_easy_sudoku();
    test_already_solved();
    test_unsolvable();
    test_empty_sudoku();
    test_minimal_clues();
    test_small_sudoku();
    test_validation_correct();
    test_validation_incorrect_row();
    test_validation_incorrect_col();
    test_validation_incorrect_box();

    printf("=== All 10 tests passed! ===\n");
    return 0;
}