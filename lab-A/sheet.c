#define _CRT_SECURE_NO_WARNINGS
#include "sheet.h"
#include <stdio.h>

int M, N;
int grid[MAX][MAX];
int visited[MAX][MAX];

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

int valid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

void dfs(int x, int y) {
    visited[y][x] = 1;
    for (int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (valid(nx, ny) && !visited[ny][nx] && grid[ny][nx] == 0) {
            dfs(nx, ny);
        }
    }
}

int count_connected() {
    // Сброс visited
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++)
            visited[y][x] = 0;

    int pieces = 0;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++)
            if (!visited[y][x] && grid[y][x] == 0) {
                dfs(x, y);
                pieces++;
            }
    return pieces;
}

void init_sheet() {
    for (int y = 0; y < N; y++)
        for (int x = 0; x < M; x++) {
            grid[y][x] = 0;
            visited[y][x] = 0;
        }
}

void set_removed(int x, int y) {
    if (valid(x, y)) grid[y][x] = 1;
}

void print_field() {
    printf("\nField (0 = cell exists, X = removed):\n\n");

    for (int y = N - 1; y >= 0; y--) {
        printf("%2d ", y);
        for (int x = 0; x < M; x++) {
            if (grid[y][x] == 1) printf("%3s", "X");
            else printf("%3s", "0");
        }
        printf("\n");
    }

    printf("\n   ");
    for (int x = 0; x < M; x++)
        printf("%3d", x);
    printf("\n\n");
}
