#include <stdio.h>
#include <stdlib.h>
#include "longest_path.h"

int main(void) {
    int V, s, t, K;
    if (scanf("%d %d %d %d", &V, &s, &t, &K) != 4)
        return 0;

    s--; t--;

    int **adj = malloc(V * sizeof(int *));
    int *deg = calloc(V, sizeof(int));

    for (int i = 0; i < V; i++) {
        adj[i] = malloc(V * sizeof(int));
        int x;
        while (scanf("%d", &x) == 1) {
            adj[i][deg[i]++] = x - 1;
            if (getchar() == '\n')
                break;
        }
    }

    int *result = malloc(V * sizeof(int));
    int len = 0;

    if (!find_path(V, adj, deg, s, t, K, result, &len)) {
        printf("0");
    } else {
        for (int i = 0; i < len; i++)
            printf("%d ", result[i] + 1);
    }

    for (int i = 0; i < V; i++)
        free(adj[i]);
    free(adj);
    free(deg);
    free(result);
    return 0;
}
