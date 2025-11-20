#pragma once
#include <stdio.h>
#include <stdlib.h>

#ifndef VERTEX_COVER_H
#define VERTEX_COVER_H

typedef struct {
    int u;
    int v;
} Edge;


typedef struct {
    Edge* edges;
    int edge_count;
    int vertex_count;
} Graph;


typedef struct {
    int* vertices;
    int count;
} VertexCover;


Graph* init_graph();
void free_graph(Graph* g);
Graph* load_graph(char* filename, int* k);
VertexCover* init_vertex_cover(void);
void free_vertex_cover(VertexCover* ds);
void add_vertex(VertexCover* ds, int vertex);
int check_cover(Graph* g, VertexCover* ds);
VertexCover* find_vertex_cover(Graph* g, int k, int current_vertex);
void write_vertex_cover(VertexCover* ds, char* filename);


#endif // VERTEX_COVER_H