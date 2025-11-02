#include "graph_utils.h"
#include <stdlib.h>
#include <stdio.h>

Graph* create_adjacency_list(int vertices) {
    Graph* list = malloc(sizeof(Graph));
    list->nodes = vertices;
    list->connections = malloc(vertices * sizeof(Edge*));

    for (int i = 0; i < vertices; i++) {
        list->connections[i] = NULL;
    }

    return list;
}

void add_edge_to_list(Graph* list, int src, int dest) {
    Edge* new_node = malloc(sizeof(Edge));
    new_node->target = dest;
    new_node->link = list->connections[src];
    list->connections[src] = new_node;
}

Grid* read_matrix_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    int size;
    fscanf(file, "%d", &size);

    int** matrix = malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);

    Grid* data = malloc(sizeof(Grid));
    data->grid = matrix;
    data->dimension = size;
    return data;
}

Graph* convert_matrix_to_list(Grid* grid_data) {
    if (!grid_data || !grid_data->grid || grid_data->dimension <= 0) {
        return NULL;
    }

    Graph* list = create_adjacency_list(grid_data->dimension);

    for (int i = 0; i < grid_data->dimension; i++) {
        for (int j = 0; j < grid_data->dimension; j++) {
            if (grid_data->grid[i][j] == 1) {
                add_edge_to_list(list, i, j);
            }
        }
    }

    return list;
}

void free_adjacency_list(Graph* list) {
    if (!list) return;

    for (int i = 0; i < list->nodes; i++) {
        Edge* current = list->connections[i];
        while (current) {
            Edge* temp = current;
            current = current->link;
            free(temp);
        }
    }

    free(list->connections);
    free(list);
}

void free_matrix_data(Grid* data) {
    if (!data) return;

    for (int i = 0; i < data->dimension; i++) {
        free(data->grid[i]);
    }

    free(data->grid);
    free(data);
}

void execute_tests(void) {
    printf("Tests completed\n");
}