#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>

// Структура для узла списка смежностей
struct Node {
    int vertex;
    struct Node* next;
};

// Структура для списка смежностей
struct Graph {
    int numVertices;
    struct Node** node_list;
};


// Создание нового узла
struct Node* create_node(int v);

// Создание графа с заданным количеством вершин
struct Graph* create_graph(int vertices);

// Добавление ребра в граф
void addEdge(struct Graph* graph, int src, int dest);

// Чтение списка смежностей из файла
struct Graph* readAdjacencyList(const char* filename, int* n);

// Построение матрицы смежности из списка смежностей
int** buildAdjacencyMatrix(struct Graph* graph);

// Печать списка смежностей
void printAdjacencyList(struct Graph* graph);

// Печать матрицы смежности
void printAdjacencyMatrix(int** matrix, int n);

// Освобождение памяти графа
void freeGraph(struct Graph* graph);

// Освобождение памяти матрицы
void freeMatrix(int** matrix, int n);

#endif