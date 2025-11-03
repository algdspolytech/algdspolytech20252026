#ifndef LIST_H
#define LIST_H

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adj_list;
};

struct Node* create_node(int v);
struct Graph* create_graph(int vertices);
void add_edge(struct Graph* graph, int src, int dest);
struct Graph* read_matrix_file(const char* filename);
void print_adj_list(struct Graph* graph);
void free_graph(struct Graph* graph);
int get_vertex_count(struct Graph* graph);
int has_edge(struct Graph* graph, int src, int dest);

#endif