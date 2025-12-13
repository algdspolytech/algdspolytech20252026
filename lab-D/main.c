#include "func.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (!input || !output) {
        return 1;
    }

    char A[101];
    long long B;

    if (fscanf(input, "%s %lld", A, &B) != 2) {
        fclose(input);
        fclose(output);
        return 1;
    }

    char result[MAX_LENGTH];

    if (search(A, B, result)) {
        fprintf(output, "%s\n", result);
        printf("Found expression: %s\n", result);
    }
    else {
        fprintf(output, "\n");
        printf("0\n");
    }

    fclose(input);
    fclose(output);
    return 0;
}