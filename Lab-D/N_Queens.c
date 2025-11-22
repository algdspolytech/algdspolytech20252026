#include "N_Queens.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int* queens = NULL;
static int n = 0;
static int found = 0;

int is_safe(int row, int col) {
    for (int i = 0; i < row; i++) {
        int prev = queens[i];
        if (prev == col || abs(prev - col) == abs(i - row))
            return 0;
    }
    return 1;
}

void backtrack(int row, int* out) {
    if (found) return;
    if (row == n) {
        found = 1;
        for (int i = 0; i < n; i++) out[i] = queens[i];
        return;
    }
    for (int col = 0; col < n; col++) {
        if (is_safe(row, col)) {
            queens[row] = col;
            backtrack(row + 1, out);
            if (found) return;
        }
    }
}

int solve_nqueens(int size, int* out) {
    n = size;
    if (n <= 0 || n >= 1000000 || n == 2 || n == 3 || n > 20) return 0;

    queens = (int*)malloc(n * sizeof(int));
    if (!queens) return 0;

    found = 0;
    backtrack(0, out);

    free(queens);
    return found;
}

int solve_nqueens_task(const char* input_file, const char* output_file) {
    FILE* in = fopen(input_file, "r");
    if (!in) return 0;
    int N;
    if (fscanf_s(in, "%d", &N) != 1) { fclose(in); return 0; }
    fclose(in);

    int* sol = (int*)malloc(N * sizeof(int));
    if (!sol) return 0;

    int ok = solve_nqueens(N, sol);

    FILE* out = fopen(output_file, "w");
    if (!out) { free(sol); return 0; }

    if (ok) {
        for (int i = 0; i < N; i++) {
            fprintf(out, "%d %d\n", i, sol[i]);
        }
    }
    else {
        fprintf(out, "No solution\n");
    }
    fclose(out);
    free(sol);
    return 1;
}