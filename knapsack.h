#ifndef KNAPSACK_H
#define KNAPSACK_H

#ifdef __cplusplus
extern "C" {
#endif

int solve_knapsack(const int* weights,
                   const int* values,
                   int n,
                   int B,
                   int K,
                   int* result,
                   int* result_size);

#ifdef __cplusplus
}
#endif

#endif  // KNAPSACK_H
