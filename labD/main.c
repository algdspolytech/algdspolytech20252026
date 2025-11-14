#include <stdio.h>
#include <stdlib.h>
#include "ruckzack.h"

int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return 1;
    }

    int n, B, K;
    fscanf(input, "%d %d %d", &n, &B, &K);

    int* w = (int*)malloc(n * sizeof(int));
    int* v = (int*)malloc(n * sizeof(int));
    int* r = (int*)malloc(n * sizeof(int));
    int rc = 0;

    int i;
    for (i = 0; i < n; i++)
        fscanf(input, "%d", &w[i]);
    for (i = 0; i < n; i++)
        fscanf(input, "%d", &v[i]);

    solve_ruckzack(n, B, K, w, v, r, &rc);

    if (rc == 0) {
        fprintf(output, "0\n");
    }
    else {
        for (i = 0; i < rc; i++) {
            fprintf(output, "%d", r[i]);
            if (i < rc - 1) fprintf(output, " ");
        }
        fprintf(output, "\n");
    }

    free(w);
    free(v);
    free(r);
    fclose(input);
    fclose(output);
    return 0;
}