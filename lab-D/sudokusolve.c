#include "sudoku.h"
#include <stdio.h>

int main() {
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");

    if (!fin) {
        printf("Error: Cannot open input.txt\n");
        return 1;
    }

    if (!fout) {
        printf("Error: Cannot open output.txt\n");
        fclose(fin);
        return 1;
    }

    int N;
    if (fscanf_s(fin, "%d", &N) != 1) {
        fprintf(fout, "0\n");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    // В задании указано N=3
    if (N != 3) {
        fprintf(fout, "0\n");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    SudokuDLX s;
    initSudoku(&s, N);

    int size = s.size; // 9 для N=3

    // Читаем сетку
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fscanf_s(fin, "%d", &s.grid[i][j]) != 1) {
                fprintf(fout, "0\n");
                fclose(fin);
                fclose(fout);
                return 0;
            }
        }
    }

    // Решаем судоку
    buildExactCover(&s);
    if (solveSudoku(&s)) {
        fillSolution(&s);

        // Записываем результат
        fprintf(fout, "%d\n", N);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                fprintf(fout, "%d", s.grid[i][j]);
                if (j < size - 1) fprintf(fout, " ");
            }
            fprintf(fout, "\n");
        }
    }
    else {
        fprintf(fout, "0\n");
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
