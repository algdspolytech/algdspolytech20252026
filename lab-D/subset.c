#include "subset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1000

static int parse_input_file(FILE* file, ProblemInput* data) {
    if (fscanf(file, "%lu", &data->target_sum) != 1) {
        return 0;
    }
    
    unsigned int n;
    if (fscanf(file, "%u", &n) != 1) {
        return 0;
    }
    
    if (n == 0 || n > MAX_INPUT_SIZE) {
        return 0;
    }
    
    data->numbers_count = n;
    data->numbers = (uint64_t*)malloc(n * sizeof(uint64_t));
    if (data->numbers == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < data->numbers_count; i++) {
        if (fscanf(file, "%lu", &data->numbers + i) != 1) {
            free(data->numbers);
            data->numbers = NULL;
            return 0;
        }
    }
    return 1;
}

int read_problem(const char* filename, ProblemInput* input) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }
    
    int success = parse_input_file(file, input);
    fclose(file);
    
    return success;
}

static int solve_dp(const uint64_t* arr, size_t n, uint64_t target, uint64_t* result_items, size_t* result_count) {
    if (target == 0) {
        *result_count = 0;
        return 1;
    }
    
    if (n == 0) {
        return 0;
    }
    
    bool** dp = (bool**)malloc((n + 1) * sizeof(bool*));
    if (dp == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i <= n; i++) {
        dp[i] = (bool*)malloc((target + 1) * sizeof(bool));
        if (dp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return 0;
        }
        memset(dp[i], 0, (target + 1) * sizeof(bool));
        dp[i][0] = true;
    }
    
    for (size_t i = 1; i <= n; i++) {
        uint64_t current = arr[i - 1];
        for (uint64_t sum = 1; sum <= target; sum++) {
            if (current > sum) {
                dp[i][sum] = dp[i - 1][sum];
            } else {
                dp[i][sum] = dp[i - 1][sum] || dp[i - 1][sum - current];
            }
        }
    }
    
    if (!dp[n][target]) {
        for (size_t i = 0; i <= n; i++) free(dp[i]);
        free(dp);
        return 0;
    }
    
    *result_count = 0;
    size_t i = n;
    uint64_t remaining = target;
    
    while (i > 0 && remaining > 0) {
        if (!dp[i - 1][remaining]) {
            result_items[*result_count] = arr[i - 1];
            (*result_count)++;
            remaining -= arr[i - 1];
        }
        i--;
    }
    
    for (size_t i = 0; i <= n; i++) free(dp[i]);
    free(dp);
    
    return 1;
}

int find_subset_sum(const ProblemInput* input, SelectionResult* result) {
    if (input == NULL || result == NULL) {
        return 0;
    }
    
    result->selected_items = NULL;
    result->selected_count = 0;
    result->solution_exists = false;
    
    result->selected_items = (uint64_t*)malloc(input->numbers_count * sizeof(uint64_t));
    if (result->selected_items == NULL) {
        return 0;
    }
    
    result->solution_exists = solve_dp(input->numbers, input->numbers_count, input->target_sum, result->selected_items, &result->selected_count);
    
    if (!result->solution_exists) {
        free(result->selected_items);
        result->selected_items = NULL;
        result->selected_count = 0;
    }
    
    return 1;
}

int write_result(const char* filename, const SelectionResult* result) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return 0;
    }
    
    if (!result->solution_exists || result->selected_count == 0) {
        fprintf(file, "0\n");
    } else {
        for (size_t i = 0; i < result->selected_count; i++) {
            fprintf(file, "%lu", result->selected_items[i]);
            if (i < result->selected_count - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }
    
    fclose(file);
    return 1;
}

void free_input(ProblemInput* input) {
    if (input != NULL) {
        if (input->numbers != NULL) {
            free(input->numbers);
            input->numbers = NULL;
        }
        input->numbers_count = 0;
        input->target_sum = 0;
    }
}

void free_result(SelectionResult* result) {
    if (result != NULL) {
        if (result->selected_items != NULL) {
            free(result->selected_items);
            result->selected_items = NULL;
        }
        result->selected_count = 0;
        result->solution_exists = false;
    }
}
