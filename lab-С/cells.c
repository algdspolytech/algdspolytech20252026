#include "cells.h"
#include <string.h>

// Размеры поля
#define MAX_M 20
#define MAX_N 20

static bool grid[MAX_M][MAX_N];
static bool visited[MAX_M][MAX_N];

// Проверка границ
static bool in_bounds(int x, int y, int M, int N) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

// DFS для обхода связного компонента
static void dfs(int x, int y, int M, int N) {
    if (!in_bounds(x, y, M, N) || !grid[x][y] || visited[x][y])
        return;

    visited[x][y] = true;

    // 4 направления: вверх, вниз, влево, вправо
    dfs(x + 1, y, M, N);
    dfs(x - 1, y, M, N);
    dfs(x, y + 1, M, N);
    dfs(x, y - 1, M, N);
}

int count_connected_components(int M, int N, Cell* removed, int K) {
    // Инициализация сетки: все клетки изначально есть
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            grid[i][j] = true;

    // Удаляем клетки
    for (int i = 0; i < K; ++i) {
        int x = removed[i].x;
        int y = removed[i].y;
        if (in_bounds(x, y, M, N)) {
            grid[x][y] = false;
        }
    }

    // Инициализация visited
    memset(visited, 0, sizeof(visited));

    int components = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] && !visited[i][j]) {
                dfs(i, j, M, N);
                components++;
            }
        }
    }

    return components;
}