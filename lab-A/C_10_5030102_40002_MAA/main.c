#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct Node* create_node(int v) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->vertex = v;
    node->next = NULL;
    return node;
}

struct Graph* create_graph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adj_list = (struct Node**)malloc(vertices * sizeof(struct Node*));
    
    for (int i = 0; i < vertices; i++) {
        graph->adj_list[i] = NULL;
    }
    return graph;
}

void add_edge(struct Graph* graph, int src, int dest) {
    struct Node* node = create_node(dest);
    node->next = graph->adj_list[src];
    graph->adj_list[src] = node;
}

struct Graph* read_matrix_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    
    int n;
    fscanf(file, "%d", &n);
    
    struct Graph* graph = create_graph(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int val;
            fscanf(file, "%d", &val);
            if (val == 1) {
                add_edge(graph, i, j);
            }
        }
    }
    
    fclose(file);
    return graph;
}

void print_adj_list(struct Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        printf("%d: ", i);
        struct Node* current = graph->adj_list[i];
        while (current) {
            printf("%d ", current->vertex);
            current = current->next;
        }
        printf("\n");
    }
}

void free_graph(struct Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        struct Node* current = graph->adj_list[i];
        while (current) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adj_list);
    free(graph);
}

int get_vertex_count(struct Graph* graph) {
    return graph->vertices;
}

int has_edge(struct Graph* graph, int src, int dest) {
    struct Node* current = graph->adj_list[src];
    while (current) {
        if (current->vertex == dest) return 1;
        current = current->next;
    }
    return 0;
}

int main() {
    struct Graph* graph = read_matrix_file("input.txt");
    if (!graph) {
        printf("File error\n");
        return 1;
    }
    
    printf("Adjacency list:\n");
    print_adj_list(graph);
    free_graph(graph);
    return 0;
}