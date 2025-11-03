#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Graph {
        int** adjacency_list;
        int* sizes;
        int vertices_count;
    } Graph;

    Graph* create_graph(int vertices);
    void add_edge(Graph* graph, int from, int to);
    Graph* adjacency_matrix_to_adjacency_list(const char* filename);
    void free_graph(Graph* graph);

#ifdef __cplusplus
}
#endif