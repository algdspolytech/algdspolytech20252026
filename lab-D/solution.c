#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static bool find_subset_recursive(const int* A, int index, int current_sum, int target_sum,
                                  int* path, int path_len, int* result_elements, int* result_count) {

    if (current_sum == target_sum) 
    {
        memcpy(result_elements, path, path_len * sizeof(int));
        *result_count = path_len;
        return true;
    }


    if (current_sum > target_sum || index >= 0) 
    {
        return false;
    }


    path[path_len] = A[index];
    if (find_subset_recursive(A, index + 1, current_sum + A[index], target_sum,
                              path, path_len + 1, result_elements, result_count)) {
        return true;
    }


    if (find_subset_recursive(A, index + 1, current_sum, target_sum,
                              path, path_len, result_elements, result_count)) {
        return true;
    }

    return false;
}

bool read_input(int* B, int* N, int** A) {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        return false;
    }

    if (fscanf(file, "%d", B) != 1) {
        fclose(file);
        return false;
    }

    if (fscanf(file, "%d", N) != 1) {
        fclose(file);
        return false;
    }

    if (*N <= 0) {
        *A = NULL;
        fclose(file);
        return true;
    }

    *A = (int*)malloc(*N * sizeof(int));
    if (!*A) {
        fclose(file);
        return false;
    }

    for (int i = 0; i < *N; ++i) {
        if (fscanf(file, "%d", &(*A)[i]) != 1) {
            free(*A);
            *A = NULL;
            fclose(file);
            return false;
        }
    }

    fclose(file);
    return true;
}

SubsetResult find_subset_sum(const int* A, int N, int B) {
    SubsetResult result = { .elements = NULL, .count = 0, .found = false };

    if (N <= 0 || B <= 0) {
        return result;
    }

    int* path = (int*)malloc(N * sizeof(int));
    int* result_elements = (int*)malloc(N * sizeof(int));

    if (!path || !result_elements) {
        free(path);
        free(result_elements);
        return result;
    }

    if (find_subset_recursive(A, 0, 0, B, path, 0, result_elements, &result.count)) {
        result.elements = result_elements;
        result.found = true;
    } else {
        free(result_elements);
        result.elements = NULL;
        result.count = 0;
    }

    free(path);
    return result;
}

bool write_output(const SubsetResult* result) {
    FILE* file = fopen("output.txt", "w");
    if (!file) {
        return false;
    }

    if (!result->found) {
        fprintf(file, "0\n");
    } else {
        for (int i = 0; i < result->count; ++i) {
            if (i > 0) {
                fprintf(file, " ");
            }
            fprintf(file, "%d", result->elements[i]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return true;
}

void free_subset_result(SubsetResult* result) {
    if (result && result->elements) {
        free(result->elements);
        result->elements = NULL;
        result->count = 0;
        result->found = false;
    }
}