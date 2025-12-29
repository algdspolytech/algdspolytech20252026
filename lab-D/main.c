#include "sudoku.h"

int main() {
    SudokuPuzzle puzzle;

    if (!load_puzzle("input.txt", &puzzle)) {
        printf("Error reading input file\n");
        return 1;
    }

    initialize_solver(&puzzle, puzzle.N);
    int solved = solve_puzzle(&puzzle);

    if (solved) {
        printf("Sudoku solved successfully!\n");
    }
    else {
        printf("No solution found for sudoku\n");
    }

    save_result("output.txt", &puzzle, solved);

    free(puzzle.nodes);
    free(puzzle.solution);

    return 0;
}