#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Создание графа
Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;

    graph->matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->matrix[i] = (int*)calloc(vertices, sizeof(int));
    }

    return graph;
}

// Освобождение памяти
void free_graph(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

// Рекурсивный поиск в глубину
int dfs(Graph* graph, int current, int target, int* visited) {
    if (current == target) {
        return 1;  // путь найден!
    }

    visited[current] = 1;

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->matrix[current][i] == 1 && !visited[i]) {
            if (dfs(graph, i, target, visited)) {
                return 1;
            }
        }
    }

    return 0;  // путь не найден
}

// Проверка существования пути
int path_exists(Graph* graph, int start, int target) {
    if (start < 0 || start >= graph->vertices ||
        target < 0 || target >= graph->vertices) {
        return 0;
    }

    int* visited = (int*)calloc(graph->vertices, sizeof(int));
    int result = dfs(graph, start, target, visited);
    free(visited);

    return result;
}

// Чтение графа из файла
Graph* read_graph_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return NULL;
    }

    int vertices;
    fscanf(file, "%d", &vertices);

    Graph* graph = create_graph(vertices);

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            fscanf(file, "%d", &graph->matrix[i][j]);
        }
    }

    fclose(file);
    return graph;
}