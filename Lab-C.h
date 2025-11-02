#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int** matrix;
    int vertices;
} Graph;

Graph* createGraph(int vertices);

Graph* readGraphFromFile(const char* filename);

void addEdge(Graph* graph, int src, int dest);

void printAdjacencyMatrix(Graph* graph);

void writeMatrixToFile(Graph* graph, const char* filename);

void destroyGraph(Graph* graph);

int getVertexCount(Graph* graph);

int hasEdge(Graph* graph, int src, int dest);

#endif