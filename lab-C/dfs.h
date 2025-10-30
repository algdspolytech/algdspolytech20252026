#ifndef DFS_H
#define DFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 50

typedef struct {
    int** adjacency_list;
    int vertices_count; 
    int capacity;
} Graph;

void initialize_graph(Graph* graph);
void destroy_graph(Graph* graph);
int add_edge(Graph* graph, int src, int dest);
int read_graph_from_file(Graph* graph, const char* filename);
void print_graph(const Graph* graph);

int dfs(const Graph* graph, int start, int end, int visited[]);
int path_exists(const Graph* graph, int start, int end);

#endif