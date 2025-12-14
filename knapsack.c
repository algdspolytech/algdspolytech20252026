#include "knapsack.h"
#include <stdio.h>
#include <stdlib.h>

int solve_knapsack(const int* weights,
                   const int* values,
                   int n,
                   int B,
                   int K,
                   int* result,
                   int* result_size) {
  if (n <= 0 || B < 0) {
    *result_size = 0;
    return 0;
  }

  int* dp = (int*)malloc((B + 1) * sizeof(int));
  int* parent = (int*)malloc((B + 1) * sizeof(int));
  int* item = (int*)malloc((B + 1) * sizeof(int));

  if (!dp || !parent || !item) {
    free(dp);
    free(parent);
    free(item);
    return 0;
  }

  for (int w = 0; w <= B; w++) {
    dp[w] = -1;
    parent[w] = -1;
    item[w] = -1;
  }
  dp[0] = 0;

  for (int i = 0; i < n; i++) {
    for (int w = B; w >= weights[i]; w--) {
      if (dp[w - weights[i]] != -1) {
        int candidate = dp[w - weights[i]] + values[i];
        if (candidate > dp[w]) {
          dp[w] = candidate;
          parent[w] = w - weights[i];
          item[w] = i;
        }
      }
    }
  }

  int best_w = -1;
  for (int w = 0; w <= B; w++) {
    if (dp[w] >= K) {
      best_w = w;
      break;
    }
  }

  if (best_w == -1) {
    free(dp);
    free(parent);
    free(item);
    *result_size = 0;
    return 0;
  }

  int count = 0;
  while (best_w > 0 && item[best_w] != -1) {
    result[count++] = item[best_w] + 1;
    best_w = parent[best_w];
  }

  *result_size = count;

  free(dp);
  free(parent);
  free(item);
  return 1;
}

int main(void) {
  FILE* in = fopen("input.txt", "r");
  FILE* out = fopen("output.txt", "w");

  if (!in || !out) {
    return 1;
  }

  int n;
  unsigned int B, K;
  fscanf(in, "%d %u %u", &n, &B, &K);

  int* weights = (int*)malloc(n * sizeof(int));
  int* values = (int*)malloc(n * sizeof(int));

  for (int i = 0; i < n; i++) {
    fscanf(in, "%d", &weights[i]);
  }
  for (int i = 0; i < n; i++) {
    fscanf(in, "%d", &values[i]);
  }

  int* result = (int*)malloc(n * sizeof(int));
  int result_size = 0;

  if (!solve_knapsack(weights, values, n, B, K, result, &result_size)) {
    fprintf(out, "0");
  } else {
    for (int i = 0; i < result_size; i++) {
      fprintf(out, "%d ", result[i]);
    }
  }

  free(weights);
  free(values);
  free(result);
  fclose(in);
  fclose(out);

  return 0;
}
