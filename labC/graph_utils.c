#include "graph_utils.h"
#include <stdlib.h>
#include <stdio.h>

Graph* init_graph(int n) {
    Graph* g = malloc(sizeof(Graph));
    g->nodes = n;
    g->connections = malloc(n * sizeof(Edge*));

    for (int i = 0; i < n; i++) {
        g->connections[i] = NULL;
    }

    return g;
}

void link_nodes(Graph* g, int a, int b) {
    Edge* e = malloc(sizeof(Edge));
    e->target = b;
    e->link = g->connections[a];
    g->connections[a] = e;
}

Grid* load_grid(const char* path) {
    FILE* f = fopen(path, "r");
    if (!f) return NULL;

    int dim;
    fscanf(f, "%d", &dim);

    int** g = malloc(dim * sizeof(int*));
    for (int i = 0; i < dim; i++) {
        g[i] = malloc(dim * sizeof(int));
        for (int j = 0; j < dim; j++) {
            fscanf(f, "%d", &g[i][j]);
        }
    }

    fclose(f);

    Grid* data = malloc(sizeof(Grid));
    data->grid = g;
    data->dimension = dim;
    return data;
}

Graph* grid_to_graph(Grid* g) {
    if (!g || !g->grid || g->dimension <= 0) {
        return NULL;
    }

    Graph* graph = init_graph(g->dimension);

    for (int i = 0; i < g->dimension; i++) {
        for (int j = 0; j < g->dimension; j++) {
            if (g->grid[i][j] == 1) {
                link_nodes(graph, i, j);
            }
        }
    }

    return graph;
}

void release_graph(Graph* g) {
    if (!g) return;

    for (int i = 0; i < g->nodes; i++) {
        Edge* e = g->connections[i];
        while (e) {
            Edge* t = e;
            e = e->link;
            free(t);
        }
    }

    free(g->connections);
    free(g);
}

void release_grid(Grid* g) {
    if (!g) return;

    for (int i = 0; i < g->dimension; i++) {
        free(g->grid[i]);
    }

    free(g->grid);
    free(g);
}