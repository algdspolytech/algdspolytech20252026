#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

static void output_zero(FILE* f) {
    fprintf(f, "0");
}

int main() {
    FILE* input = fopen("input.txt", "r");
    if (!input) return 0;

    int N;
    if (fscanf(input, "%d", &N) != 1) {
        fclose(input);
        return 0;
    }

    Puzzle* puzzle = create_puzzle(N);
    if (!puzzle) {
        fclose(input);
        FILE* out = fopen("output.txt", "w");
        if (out) {
            output_zero(out);
            fclose(out);
        }
        return 0;
    }

    int dim = N * N;
    int ok = 1;

    for (int r = 0; r < dim && ok; r++) {
        for (int c = 0; c < dim && ok; c++) {
            int val;
            if (fscanf(input, "%d", &val) != 1) {
                ok = 0;
                break;
            }
            set_cell(puzzle, r, c, val, &ok);
        }
    }

    fclose(input);

    FILE* output = fopen("output.txt", "w");
    if (!output) {
        free_puzzle(puzzle);
        return 0;
    }

    if (!ok) {
        output_zero(output);
        fclose(output);
        free_puzzle(puzzle);
        return 0;
    }

    int solved = solve_puzzle(puzzle);
    if (!solved) {
        output_zero(output);
    }
    else {
        fprintf(output, "%d\n", N);
        display_puzzle(puzzle, output);
    }

    fclose(output);
    free_puzzle(puzzle);
    return 0;
}