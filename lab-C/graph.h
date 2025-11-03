#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int n; // количество вершин
    int adj[MAX_VERTICES][MAX_VERTICES]; // матрица смежности
} Graph;

// Чтение графа из файла
int readGraphFromFile(Graph* g, const char* filename);

// Проверка существования пути между двумя вершинами
int dfsHasPath(Graph* g, int start, int end);

#endif
