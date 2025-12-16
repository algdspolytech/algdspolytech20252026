#ifndef SUBSET_SUM_SOLVER_H
#define SUBSET_SUM_SOLVER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        int* items;
        int length;
        bool found;
    } SubsetSolution;

    // Основные функции
    SubsetSolution solve_subset_sum_problem(int target, int* numbers, int count);
    bool* find_subset_indices(int target, int* numbers, int count, int* subset_size);
    int compute_subset_total(const int* subset, int size);
    void release_solution(SubsetSolution* solution);

    // Вспомогательные функции
    int* load_data_from_file(const char* filename, int* target, int* count);
    void store_result_to_file(const char* filename, const SubsetSolution* result);
    void arrange_descending(int* array, int length);

#ifdef __cplusplus
}
#endif

#endif // SUBSET_SUM_SOLVER_H