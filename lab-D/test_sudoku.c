#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"

#define MAX_TESTS 15

typedef struct {
    const char* name;
    int (*test_function)();
} TestCase;

int empty_cells_count(SudokuPuzzle* puzzle) {
    int dimension = puzzle->N * puzzle->N;
    int count = 0;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (puzzle->board[i][j] == 0) {
                count++;
            }
        }
    }
    return count;
}

int test_solve_valid_sudoku_1() {
    const char* input =
        "3\n"
        "5 3 0 0 7 0 0 0 0\n"
        "6 0 0 1 9 5 0 0 0\n"
        "0 9 8 0 0 0 0 6 0\n"
        "8 0 0 0 6 0 0 0 3\n"
        "4 0 0 8 0 3 0 0 1\n"
        "7 0 0 0 2 0 0 0 6\n"
        "0 6 0 0 0 0 2 8 0\n"
        "0 0 0 4 1 9 0 0 5\n"
        "0 0 0 0 8 0 0 7 9\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return solved == 1;
}

int test_solve_completed_sudoku_2() {
    const char* input =
        "3\n"
        "5 3 4 6 7 8 9 1 2\n"
        "6 7 2 1 9 5 3 4 8\n"
        "1 9 8 3 4 2 5 6 7\n"
        "8 5 9 7 6 1 4 2 3\n"
        "4 2 6 8 5 3 7 9 1\n"
        "7 1 3 9 2 4 8 5 6\n"
        "9 6 1 5 3 7 2 8 4\n"
        "2 8 7 4 1 9 6 3 5\n"
        "3 4 5 2 8 6 1 7 9\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return solved == 1 && validate_sudoku(&puzzle) == 1;
}

int test_solve_row_conflict_3() {
    const char* input =
        "3\n"
        "5 5 0 0 7 0 0 0 0\n"
        "6 0 0 1 9 5 0 0 0\n"
        "0 9 8 0 0 0 0 6 0\n"
        "8 0 0 0 6 0 0 0 3\n"
        "4 0 0 8 0 3 0 0 1\n"
        "7 0 0 0 2 0 0 0 6\n"
        "0 6 0 0 0 0 2 8 0\n"
        "0 0 0 4 1 9 0 0 5\n"
        "0 0 0 0 8 0 0 7 9\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return solved == 0;
}

int test_solve_empty_grid_4() {
    const char* input =
        "3\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    int valid = solved == 1 && validate_sudoku(&puzzle) == 1;

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return valid;
}

int test_solve_minimal_clues_5() {
    const char* input =
        "3\n"
        "0 0 0 0 0 0 0 1 0\n"
        "0 0 0 0 0 2 0 0 3\n"
        "0 0 0 4 0 0 0 0 0\n"
        "0 0 0 0 0 0 5 0 0\n"
        "4 0 1 6 0 0 0 0 0\n"
        "0 0 7 1 0 0 0 0 0\n"
        "0 5 0 0 0 0 2 0 0\n"
        "0 0 0 0 8 0 0 4 0\n"
        "0 3 0 9 1 0 0 0 0\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    int valid = solved == 1 && validate_sudoku(&puzzle) == 1;

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return valid;
}

int test_solve_column_conflict_6() {
    const char* input =
        "3\n"
        "1 0 0 0 0 0 0 0 0\n"
        "1 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return solved == 0;
}

int test_solve_block_conflict_7() {
    const char* input =
        "3\n"
        "1 0 0 0 0 0 0 0 0\n"
        "0 1 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return solved == 0;
}

int test_solve_diagonal_pattern_8() {
    const char* input =
        "3\n"
        "1 0 0 0 0 0 0 0 0\n"
        "0 2 0 0 0 0 0 0 0\n"
        "0 0 3 0 0 0 0 0 0\n"
        "0 0 0 4 0 0 0 0 0\n"
        "0 0 0 0 5 0 0 0 0\n"
        "0 0 0 0 0 6 0 0 0\n"
        "0 0 0 0 0 0 7 0 0\n"
        "0 0 0 0 0 0 0 8 0\n"
        "0 0 0 0 0 0 0 0 9\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    int valid = solved == 1 && validate_sudoku(&puzzle) == 1;

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return valid;
}

int test_solve_last_cell_empty_9() {
    const char* input =
        "3\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "1 2 3 4 5 6 7 8 0\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    int valid = solved == 1 && validate_sudoku(&puzzle) == 1 && puzzle.board[8][8] == 9;

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return valid;
}

int test_file_not_found_10() {
    SudokuPuzzle puzzle;
    int result = load_puzzle("nonexistent.txt", &puzzle);
    return result == 0;
}

int test_validate_correct_board_11() {
    SudokuPuzzle puzzle;
    puzzle.N = 3;

    int correct[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    memcpy(puzzle.board, correct, sizeof(correct));

    return validate_sudoku(&puzzle) == 1;
}

int test_validate_incorrect_board_12() {
    SudokuPuzzle puzzle;
    puzzle.N = 3;

    int incorrect[9][9] = {
        {5, 5, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    memcpy(puzzle.board, incorrect, sizeof(incorrect));

    return validate_sudoku(&puzzle) == 0;
}

int test_solve_single_cell_13() {
    const char* input =
        "3\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 1 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    int valid = solved == 1 && validate_sudoku(&puzzle) == 1;

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return valid;
}

int test_invalid_grid_size_14() {
    const char* input =
        "2\n"
        "1 2 3 4\n"
        "3 4 1 2\n"
        "2 1 4 3\n"
        "4 3 2 1\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        remove("test_input.txt");
        return 1;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return solved == 1;
}

int test_solve_complex_pattern_15() {
    const char* input =
        "3\n"
        "0 0 0 0 0 6 0 0 0\n"
        "0 0 7 2 0 0 0 0 1\n"
        "3 0 0 0 0 0 0 0 0\n"
        "0 9 0 0 0 0 8 0 0\n"
        "0 0 0 5 0 4 0 0 0\n"
        "0 0 4 0 0 0 0 3 0\n"
        "0 0 0 0 0 0 0 0 6\n"
        "1 0 0 0 0 7 9 0 0\n"
        "0 0 0 8 0 0 0 0 0\n";

    FILE* file = fopen("test_input.txt", "w");
    fprintf(file, "%s", input);
    fclose(file);

    SudokuPuzzle puzzle;
    if (!load_puzzle("test_input.txt", &puzzle)) {
        return 0;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    int valid = solved == 1 && validate_sudoku(&puzzle) == 1;

    free(puzzle.nodes);
    free(puzzle.solution);
    remove("test_input.txt");

    return valid;
}

TestCase tests[MAX_TESTS] = {
    {"test_solve_valid_sudoku_1", test_solve_valid_sudoku_1},
    {"test_solve_completed_sudoku_2", test_solve_completed_sudoku_2},
    {"test_solve_row_conflict_3", test_solve_row_conflict_3},
    {"test_solve_empty_grid_4", test_solve_empty_grid_4},
    {"test_solve_minimal_clues_5", test_solve_minimal_clues_5},
    {"test_solve_column_conflict_6", test_solve_column_conflict_6},
    {"test_solve_block_conflict_7", test_solve_block_conflict_7},
    {"test_solve_diagonal_pattern_8", test_solve_diagonal_pattern_8},
    {"test_solve_last_cell_empty_9", test_solve_last_cell_empty_9},
    {"test_file_not_found_10", test_file_not_found_10},
    {"test_validate_correct_board_11", test_validate_correct_board_11},
    {"test_validate_incorrect_board_12", test_validate_incorrect_board_12},
    {"test_solve_single_cell_13", test_solve_single_cell_13},
    {"test_invalid_grid_size_14", test_invalid_grid_size_14},
    {"test_solve_complex_pattern_15", test_solve_complex_pattern_15}
};

int main() {
    printf("Running Sudoku tests...\n");
    printf("=======================\n");

    int passed = 0;
    int total = MAX_TESTS;

    for (int i = 0; i < MAX_TESTS; i++) {
        printf("Test %2d: %-40s ", i + 1, tests[i].name);
        int result = tests[i].test_function();

        if (result) {
            printf("PASS\n");
            passed++;
        }
        else {
            printf("FAIL\n");
        }
    }

    printf("=======================\n");
    printf("Passed: %d/%d\n", passed, total);

    return passed == total ? 0 : 1;
}