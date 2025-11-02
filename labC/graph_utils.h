#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

typedef struct Edge {
    int target;
    struct Edge* link;
} Edge;

typedef struct {
    Edge** connections;
    int nodes;
} Graph;

typedef struct {
    int** grid;
    int dimension;
} Grid;

Graph* init_graph(int n);
void link_nodes(Graph* g, int a, int b);
Grid* load_grid(const char* path);
Graph* grid_to_graph(Grid* g);
void release_graph(Graph* g);
void release_grid(Grid* g);
void execute_tests(void);

#endif