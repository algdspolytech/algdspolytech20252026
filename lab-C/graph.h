#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

/* Узел списка смежности */
typedef struct GraphNode {
    int toVertex;
    struct GraphNode* next;
} GraphNode;

/* Граф */
typedef struct {
    int vertexCount;
    GraphNode** adjacencyLists;
} Graph;

/* Создание узла */
GraphNode* node_create(int toVertex);

/* Создание графа */
Graph* graph_create(int vertices);

/* Добавление ребра */
int graph_add_edge(Graph* graph, int from, int to);

/* Чтение графа из файла */
Graph* graph_read_from_file(const char* filename);

/* Построение матрицы смежности */
int** graph_to_matrix(const Graph* graph);

/* Освобождение памяти */
void graph_destroy(Graph* graph);
void matrix_destroy(int** matrix, int size);

#endif
