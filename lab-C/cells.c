#include "cells.h"
#include <stdio.h>
#include <stdlib.h>

static void DFS(Grid* pg, int x, int y, int component_id) {
    if (x < 0 || x >= pg->M || y < 0 || y >= pg->N || pg->grid[x][y] != 0) return;

    pg->grid[x][y] = component_id;

    DFS(pg, x + 1, y, component_id);
    DFS(pg, x - 1, y, component_id);
    DFS(pg, x, y + 1, component_id);
    DFS(pg, x, y - 1, component_id);
}

Grid* CreateGrid(int M, int N) {
    if (M <= 0 || N <= 0) return NULL;

    Grid* pg = (Grid*)malloc(sizeof(Grid));
    if (!pg) return NULL;

    pg->M = M;
    pg->N = N;

    pg->grid = (int**)malloc(M * sizeof(int*));
    if (!pg->grid) {
        free(pg);
        return NULL;
    }
    for (int i = 0; i < M; i++) {
        pg->grid[i] = (int*)calloc(N, sizeof(int));

        if (!pg->grid[i]) {
            for (int j = 0; j < i; j++) {
                free(pg->grid[j]);
            }
            free(pg->grid);
            free(pg);
            return NULL;
        }
    }

    return pg;
}

void FreeGrid(Grid* pg) {
    if (!pg) return;

    if (pg->grid) {
        for (int i = 0; i < pg->M; i++) {
            free(pg->grid[i]);
        }
        free(pg->grid);
    }
    free(pg);
}

void RemoveCell(Grid* pg, int x, int y) {
    if (pg && pg->grid && x >= 0 && x < pg->M && y >= 0 && y < pg->N) {
        pg->grid[x][y] = -1;
    }
}

int ConnectComponents(Grid* pg) {
    if (!pg || !pg->grid) return 0;
    int count = 0;

    for (int i = 0; i < pg->M; i++) {
        for (int j = 0; j < pg->N; j++) {
            if (pg->grid[i][j] == 0) {
                count++;
                dfs(pg, i, j, count);
            }
        }
    }

    return count;
}

Grid* LoadFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    int M, N, K;
    if (fscanf(file, "%d %d %d", &M, &N, &K) != 3) {
        fclose(file);
        return NULL;
    }

    Grid* pg = CreateGrid(M, N);
    if (!pg) {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < K; i++) {
        int x, y;
        if (fscanf(file, "%d %d", &x, &y) == 2) {
            RemoveCell(pg, x, y);
        }
    }

    fclose(file);
    return pg;
}

Grid* LoadStdin() {
    int M, N, K;
    if (scanf("%d %d %d", &M, &N, &K) != 3) return NULL;

    Grid* pg = create_grid(M, N);
    if (!pg) return NULL;

    for (int i = 0; i < K; i++) {
        int x, y;
        if (scanf("%d %d", &x, &y) == 2) {
            RemoveCell(pg, x, y);
        }
    }

    return pg;
}
}
