#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

    typedef struct Node {
        int vertex;
        struct Node* next;
    } Node;

    typedef struct {
        int num_vertices;
        Node** adj_lists; // массив списков смежности
    } Graph;

    Graph* create_graph(int vertices);
    void add_edge(Graph* graph, int src, int dest);
    Graph* read_graph_from_file(const char* filename);
    void print_graph(const Graph* graph);
    void free_graph(Graph* graph);

#ifdef __cplusplus
}
#endif

#endif // GRAPH_H