#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    long long N = read_input("input.txt");

    if (N < 1 || N >= 1000000) {
        FILE* fout = fopen("output.txt", "w");
        fprintf(fout, "error N\n");
        fclose(fout);
        return 0;
    }

    if (N == 2 || N == 3) {
        FILE* fout = fopen("output.txt", "w");
        fprintf(fout, "no solution\n");
        fclose(fout);
        return 0;
    }

    long long* cols = (long long*)malloc(N * sizeof(long long));
    if (!cols) {
        printf("error memory allocation\n");
        return 1;
    }

    generate_solution(cols, N);
    write_output("output.txt", cols, N);

    free(cols);
    return 0;
}
