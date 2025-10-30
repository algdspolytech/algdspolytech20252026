#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

// Полное определение структуры Graph
typedef struct Graph {
    int** matrix;
    int vertices;
} Graph;

// Объявление структуры Queue (неполный тип)
typedef struct Queue Queue;

// Функции для работы с очередью
Queue* createQueue(int capacity);
int isQueueEmpty(Queue* queue);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
void freeQueue(Queue* queue);

// Функции для работы с графом
Graph* createGraph(int vertices);
void freeGraph(Graph* graph);
Graph* readGraphFromFile(const char* filename);
int* findShortestPath(Graph* graph, int start, int end, int* pathLength);
void printPath(int* path, int length);

#endif