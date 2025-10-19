#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Инициализация графа
void initialize_graph(Graph *graph, int num_vertices) {
    if (graph == NULL || num_vertices <= 0 || num_vertices > MAX_VERTICES) {
        return;
    }

    graph->num_vertices = num_vertices;

    // Заполняем матрицу нулями
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }
}

// Добавление ребер из списка смежности для конкретной вершины
void add_edge_from_adjacency_list(Graph *graph, int vertex, const int *neighbors, int count) {
    if (graph == NULL || neighbors == NULL || vertex < 0 || vertex >= graph->num_vertices) {
        return;
    }

    for (int i = 0; i < count; i++) {
        int neighbor = neighbors[i];
        if (neighbor >= 0 && neighbor < graph->num_vertices) {
            graph->matrix[vertex][neighbor] = 1;
            // Для неориентированного графа добавляем обратное ребро
            graph->matrix[neighbor][vertex] = 1;
        }
    }
}

// Печать матрицы смежности
void print_adjacency_matrix(const Graph *graph) {
    if (graph == NULL) {
        return;
    }

    printf("Матрица смежности (%d вершин):\n", graph->num_vertices);
    printf("   ");
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < graph->num_vertices; i++) {
        printf("%2d ", i);
        for (int j = 0; j < graph->num_vertices; j++) {
            printf("%2d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

// Получение количества вершин из файла
int get_vertex_count_from_file(const char *filename) {
    if (filename == NULL) {
        return -1;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int max_vertex = -1;

    while (fgets(line, sizeof(line), file)) {
        // Пропускаем пустые строки
        if (strlen(line) == 0 || (strlen(line) == 1 && line[0] == '\n')) {
            continue;
        }

        // Извлекаем номер вершины
        char *token = strtok(line, ":");
        if (token != NULL) {
            int vertex = atoi(token);
            if (vertex > max_vertex) {
                max_vertex = vertex;
            }

            // Проверяем соседей
            token = strtok(NULL, ":");
            if (token != NULL) {
                char *neighbor_token = strtok(token, " ,\n");
                while (neighbor_token != NULL) {
                    int neighbor = atoi(neighbor_token);
                    if (neighbor > max_vertex) {
                        max_vertex = neighbor;
                    }
                    neighbor_token = strtok(NULL, " ,\n");
                }
            }
        }
    }

    fclose(file);
    return max_vertex + 1; // Вершины нумеруются с 0
}

// Чтение графа из файла
int read_graph_from_file(Graph *graph, const char *filename) {
    if (graph == NULL || filename == NULL) {
        return 0;
    }

    // Определяем количество вершин
    int num_vertices = get_vertex_count_from_file(filename);
    if (num_vertices <= 0) {
        return 0;
    }

    // Инициализируем граф
    initialize_graph(graph, num_vertices);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        // Пропускаем пустые строки
        if (strlen(line) == 0 || (strlen(line) == 1 && line[0] == '\n')) {
            continue;
        }

        // Разбираем строку формата "vertex: neighbor1 neighbor2 ..."
        char *token = strtok(line, ":");
        if (token != NULL) {
            int vertex = atoi(token);

            // Получаем список соседей
            token = strtok(NULL, ":\n");
            if (token != NULL) {
                int neighbors[MAX_VERTICES];
                int neighbor_count = 0;

                char *neighbor_token = strtok(token, " ,");
                while (neighbor_token != NULL && neighbor_count < MAX_VERTICES) {
                    // Пропускаем нечисловые токены
                    int is_number = 1;
                    for (int i = 0; neighbor_token[i] != '\0'; i++) {
                        if (!isdigit(neighbor_token[i]) && neighbor_token[i] != '-' && neighbor_token[i] != '+') {
                            is_number = 0;
                            break;
                        }
                    }

                    if (is_number) {
                        neighbors[neighbor_count++] = atoi(neighbor_token);
                    }
                    neighbor_token = strtok(NULL, " ,");
                }

                // Добавляем ребра в граф
                add_edge_from_adjacency_list(graph, vertex, neighbors, neighbor_count);
            }
        }
    }

    fclose(file);
    return 1;
}