#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 100

typedef struct {
    int n;
    int adj[MAX_NODES][MAX_NODES];
} Graph;

void graph_init(Graph* g, int n);
int graph_add_edge(Graph* g, int u, int v);
int graph_has_edge(const Graph* g, int u, int v);
int graph_edge_count(const Graph* g);

int graph_load_from_file(Graph* g, const char* filename);
void graph_print_matrix(const Graph* g);
int graph_save_matrix(const Graph* g, const char* filename);

int graph_vertex_valid(const Graph* g, int v);

#endif
