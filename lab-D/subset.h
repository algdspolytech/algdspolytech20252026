#ifndef SUBSET_H
#define SUBSET_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint64_t* selected_items;
    size_t selected_count;
    bool solution_exists;
} SelectionResult;

typedef struct {
    uint64_t target_sum;
    uint64_t* numbers;
    size_t numbers_count;
} ProblemInput;

int read_problem(const char* filename, ProblemInput* input);
int find_subset_sum(const ProblemInput* input, SelectionResult* result);
int write_result(const char* filename, const SelectionResult* result);
void free_input(ProblemInput* input);
void free_result(SelectionResult* result);

#endif
