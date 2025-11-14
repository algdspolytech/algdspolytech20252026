#include "ruckzack.h"

void solve_ruckzack(int n, int B, int K, int* w, int* v, int* r, int* rc) {
    int i, j;
    static int dp[1001][1001];

    for (i = 0; i <= n; i++)
        for (j = 0; j <= B; j++)
            dp[i][j] = 0;

    for (i = 1; i <= n; i++) {
        for (j = 0; j <= B; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= w[i - 1]) {
                int nv = dp[i - 1][j - w[i - 1]] + v[i - 1];
                if (nv > dp[i][j])
                    dp[i][j] = nv;
            }
        }
    }

    *rc = 0;
    if (dp[n][B] < K)
        return;

    int curB = B;
    for (i = n; i >= 1; i--) {
        if (dp[i][curB] != dp[i - 1][curB]) {
            r[*rc] = i;
            (*rc)++;
            curB -= w[i - 1];
        }
    }
}