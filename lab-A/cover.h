#ifndef COVER_H
#define COVER_H

#include <stdbool.h>

#define MAX_VERTICES 50  // Уменьшили для безопасности

typedef struct {
    int u, v;
} Edge;

typedef struct {
    int vertices_count;
    int edges_count;
    Edge edges[MAX_VERTICES * MAX_VERTICES];
} Graph;

bool read_graph(const char* filename, Graph* graph, int* K);
bool write_result(const char* filename, int* cover_vertices, int cover_size);
bool find_vertex_cover(Graph* graph, int K, int* cover_vertices, int* cover_size);

#endif