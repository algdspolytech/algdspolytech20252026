#define _CRT_SECURE_NO_WARNINGS
#include "sudoku_solver.h"

void writeFailure(const char* fname) {
    FILE* fp = fopen(fname, "w");
    if (fp) {
        fprintf(fp, "0\n");
        fclose(fp);
    }
}

int main(int argc, char* argv[]) {
    const char* inputFile = "input.txt";
    const char* outputFile = "output.txt";

    if (argc > 1) inputFile = argv[1];
    if (argc > 2) outputFile = argv[2];

    Puzzle puzzle;
    loadPuzzle(inputFile, &puzzle);

    printf("Solving Sudoku (N=%d, size=%dx%d)...\n",
        puzzle.order, puzzle.dim, puzzle.dim);

    if (solveSudoku(&puzzle)) {
        if (validateSudoku(&puzzle)) {
            printf("Solution found and validated!\n");
            storePuzzle(outputFile, &puzzle);
        }
        else {
            printf("Solution found but invalid!\n");
            writeFailure(outputFile);
        }
    }
    else {
        printf("No solution found.\n");
        writeFailure(outputFile);
    }

    cleanupPuzzle(&puzzle);
    return 0;
}