#include "graph.h"

static void dfsUtil(Graph* g, int v, int visited[], int* found, int end) {
    if (*found) return; // <-- остановка, если путь уже найден
    visited[v] = 1;
    if (v == end) {
        *found = 1;
        return;
    }
    for (int i = 0; i < g->n; i++) {
        if (*found) return; // <-- выход из цикла, если путь найден
        if (g->adj[v][i] && !visited[i]) {
            dfsUtil(g, i, visited, found, end);
        }
    }
}

int dfsHasPath(Graph* g, int start, int end) {
    if (start < 0 || start >= g->n || end < 0 || end >= g->n) return 0;
    int visited[MAX_VERTICES] = {0};
    int found = 0;
    dfsUtil(g, start, visited, &found, end);
    return found;
}

int readGraphFromFile(Graph* g, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    if (fscanf(f, "%d", &g->n) != 1 || g->n <= 0 || g->n > MAX_VERTICES) {
        fclose(f);
        return 0;
    }
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (fscanf(f, "%d", &g->adj[i][j]) != 1) {
                fclose(f);
                return 0;
            }
        }
    }
    fclose(f);
    return 1;
}
