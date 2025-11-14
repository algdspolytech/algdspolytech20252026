#include <stdio.h>
#include <stdlib.h>
#include "ruckzack.h"
#include "io.h"

int main() {
    int n, B, K;
    int *w, *v;

    if (!read_input("input.txt", &n, &B, &K, &w, &v)) {
        return 1;
    }

    int* result = (int*)malloc(n * sizeof(int));
    int count = knapsack_solve(n, B, K, w, v, result);

    write_output("output.txt", result, count);

    free(w);
    free(v);
    free(result);
    return 0;
}
