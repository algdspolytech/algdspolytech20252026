#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "longest_path.h"

static int dfs(int v, int t, int k, int depth,
               int *visited, int *path,
               int **adj, int *deg,
               int *result, int *res_len) {
    visited[v] = 1;
    path[depth] = v;

    if (v == t && depth >= k) {
        memcpy(result, path, (depth + 1) * sizeof(int));
        *res_len = depth + 1;
        return 1;
    }

    for (int i = 0; i < deg[v]; i++) {
        int to = adj[v][i];
        if (!visited[to]) {
            if (dfs(to, t, k, depth + 1, visited, path, adj, deg, result, res_len))
                return 1;
        }
    }

    visited[v] = 0;
    return 0;
}

int find_path(int v_count, int **adj, int *deg,
              int s, int t, int k,
              int *result, int *res_len) {
    int *visited = calloc(v_count, sizeof(int));
    int *path = malloc(v_count * sizeof(int));
    int found = dfs(s, t, k, 0, visited, path, adj, deg, result, res_len);
    free(visited);
    free(path);
    return found;
}
