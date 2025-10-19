#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 100
#define MAX_LINE_LENGTH 256

// Структура для представления графа
typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} Graph;

// Функции для работы с графом
void initialize_graph(Graph *graph, int num_vertices);
void add_edge_from_adjacency_list(Graph *graph, int vertex, const int *neighbors, int count);
void print_adjacency_matrix(const Graph *graph);
int read_graph_from_file(Graph *graph, const char *filename);
int get_vertex_count_from_file(const char *filename);

#endif // GRAPH_H