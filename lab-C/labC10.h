#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#include <stdlib.h>

//Узел списка смежности
typedef struct {
	int vertex;
	struct Node* next;
}
Node;

//Граф
typedef struct {
	int numVert;
	Node** adjLists;
}
Graph;

//Создание узла
Node* createNode(int v);

//Создание графа
Graph* createGraph(int vertices);

//Добавление ребра
void addEdge(Graph* graph, int st, int end);

//Преобразование матрицы смежности в список
Graph* convertMatrixToList(int** matrix, int size);

//Печать списка смежности
void printGraph(Graph* graph);

//Освобождение памяти
void freeGraph(Graph* graph);

//Чтение матрицы смежности из файла
int** readMatrixFromFile(const char* filename, int* size);

#endif