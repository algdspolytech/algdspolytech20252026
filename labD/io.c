#include <stdio.h>
#include <stdlib.h>
#include "io.h"

int read_input(const char* filename, int* n, int* B, int* K, int** w, int** v) {
    FILE* file = fopen(filename, "r");
    if (!file) return 0;

    if (fscanf(file, "%d %d %d", n, B, K) != 3) {
        fclose(file);
        return 0;
    }

    *w = (int*)malloc(*n * sizeof(int));
    *v = (int*)malloc(*n * sizeof(int));

    int i;
    for (i = 0; i < *n; i++) {
        if (fscanf(file, "%d", &(*w)[i]) != 1) {
            free(*w);
            free(*v);
            fclose(file);
            return 0;
        }
    }

    for (i = 0; i < *n; i++) {
        if (fscanf(file, "%d", &(*v)[i]) != 1) {
            free(*w);
            free(*v);
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

void write_output(const char* filename, int* indices, int count) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    if (count == 0) {
        fprintf(file, "0\n");
    }
    else {
        int i;
        for (i = 0; i < count; i++) {
            fprintf(file, "%d", indices[i]);
            if (i < count - 1) fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
