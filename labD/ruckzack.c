#include "ruckzack.h"
#include <stdlib.h>

int knapsack_solve(int n, int B, int K, int* w, int* v, int* result_indices) {
    if (n <= 0 || B <= 0 || K <= 0) return 0;
    
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    int i, j;
    
    for (i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((B + 1) * sizeof(int));
        for (j = 0; j <= B; j++) {
            dp[i][j] = 0;
        }
    }
    
    for (i = 1; i <= n; i++) {
        for (j = 0; j <= B; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i - 1]) {
                int new_val = dp[i - 1][j - w[i - 1]] + v[i - 1];
                if (new_val > dp[i][j]) {
                    dp[i][j] = new_val;
                }
            }
        }
    }
    
    if (dp[n][B] < K) {
        for (i = 0; i <= n; i++) free(dp[i]);
        free(dp);
        return 0;
    }
    
    int count = 0;
    int current_weight = B;
    
    for (i = n; i >= 1; i--) {
        if (dp[i][current_weight] != dp[i - 1][current_weight]) {
            result_indices[count++] = i;
            current_weight -= w[i - 1];
        }
    }
    
    for (i = 0; i <= n; i++) free(dp[i]);
    free(dp);
    return count;
}