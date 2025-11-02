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

Graph* create_adjacency_list(int vertices);
void add_edge_to_list(Graph* list, int src, int dest);
Grid* read_matrix_from_file(const char* filename);
Graph* convert_matrix_to_list(Grid* grid_data);
void free_adjacency_list(Graph* list);
void free_matrix_data(Grid* data);
void execute_tests(void);

#endif