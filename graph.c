#define _CRT_SECURE_NO_WARNINGS
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>



// Глобальный массив посещенных вершин
int visited[MAX_VERTICES];

// Поиск в глубину для проверки существования пути
int dfs(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int current, int target) {
    if (current == target) {
        return 1;
    }
    visited[current] = 1;
    for (int i = 0; i < vertices; i++) {
        if (graph[current][i] == 1 && !visited[i]) {
            if (dfs(graph, vertices, i, target)) {
                return 1;
            }
        }
    }
    return 0;
}

// Сброс массива посещенных вершин
void reset_visited(int vertices) {
    for (int i = 0; i < vertices; i++) {
        visited[i] = 0;
    }
}

// Проверка существования пути между двумя вершинами
int has_path(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int start, int end) {
    if (start < 0 || start >= vertices || end < 0 || end >= vertices) {
        return -1; // Некорректные входные данные
    }
    reset_visited(vertices);
    return dfs(graph, vertices, start, end);
}

// Загрузка графа из файла
void load_graph_from_file(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertices) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        *vertices = 0;
        return;
    }

    fscanf(file, "%d", vertices);
    for (int i = 0; i < *vertices; i++) {
        for (int j = 0; j < *vertices; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);
}