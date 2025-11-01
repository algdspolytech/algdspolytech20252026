#pragma once
#define MAX 100
#define INF 2147483647

typedef struct {
    int** matrix;
    int vertices;
} Graph;

typedef struct {
    int* path;
    int length;
    int distance;
} PathResult;

// File operations
Graph* readgraph(const char* filename);
void freegraph(Graph* graph);

// Path finding
PathResult* shortpath(Graph* graph, int start, int end);
void freeresult(PathResult* result);

// Utility functions
void print(PathResult* result);