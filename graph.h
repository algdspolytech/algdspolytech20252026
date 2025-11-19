#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int vertexCount;
    int adjacency[MAX_VERTICES][MAX_VERTICES];
} Graph;

int readGraphFromFile(Graph* graph, const char* filename);

int dfsHasPath(Graph* graph, int source, int destination);

#endif