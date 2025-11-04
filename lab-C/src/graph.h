#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 100

// Структура графа
typedef struct {
    int** matrix;    // матрица смежности
    int vertices;    // количество вершин
} Graph;

// Основные функции
Graph* create_graph(int vertices);
void free_graph(Graph* graph);
int dfs(Graph* graph, int start, int target, int* visited);
int path_exists(Graph* graph, int start, int target);
Graph* read_graph_from_file(const char* filename);

#endif