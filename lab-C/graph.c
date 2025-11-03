#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

Graph* create_graph(int vertices) {
    if (vertices < 0) return NULL;

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;

    graph->vertices_count = vertices;
    graph->sizes = (int*)calloc(vertices, sizeof(int));
    if (!graph->sizes) {
        free(graph);
        return NULL;
    }

    graph->adjacency_list = (int**)malloc(vertices * sizeof(int*));
    if (!graph->adjacency_list) {
        free(graph->sizes);
        free(graph);
        return NULL;
    }

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_list[i] = NULL;
    }

    return graph;
}

void add_edge(Graph* graph, int from, int to) {
    if (!graph || from < 0 || from >= graph->vertices_count ||
        to < 0 || to >= graph->vertices_count) {
        return;
    }

    int new_size = graph->sizes[from] + 1;
    int* new_list = (int*)realloc(graph->adjacency_list[from], new_size * sizeof(int));
    if (!new_list) return;

    graph->adjacency_list[from] = new_list;
    graph->adjacency_list[from][graph->sizes[from]] = to;
    graph->sizes[from]++;
}

Graph* adjacency_matrix_to_adjacency_list(const char* filename) {
    if (!filename) return NULL;

    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    int vertices;
    if (fscanf(file, "%d", &vertices) != 1 || vertices < 0) {
        fclose(file);
        return NULL;
    }

    Graph* graph = create_graph(vertices);
    if (!graph) {
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            int value;
            if (fscanf(file, "%d", &value) != 1) {
                free_graph(graph);
                fclose(file);
                return NULL;
            }
            if (value == 1) {
                add_edge(graph, i, j);
            }
        }
    }

    fclose(file);
    return graph;
}

void free_graph(Graph* graph) {
    if (graph) {
        if (graph->adjacency_list) {
            for (int i = 0; i < graph->vertices_count; i++) {
                free(graph->adjacency_list[i]);
            }
            free(graph->adjacency_list);
        }
        free(graph->sizes);
        free(graph);
    }
}