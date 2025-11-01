#include <stdio.h>
#include "graph_utils.h"

void show_graph(Graph* g) {
    if (!g) return;

    for (int i = 0; i < g->nodes; i++) {
        printf("Node %d: ", i);
        Edge* e = g->connections[i];
        while (e) {
            printf("%d ", e->target);
            e = e->link;
        }
        printf("\n");
    }
}

int main() {
    execute_tests();

    printf("\n--- Application ---\n");

    Grid* data = load_grid("input.txt");
    if (!data) {
        printf("Cannot read file\n");
        return 1;
    }

    Graph* g = grid_to_graph(data);

    printf("Graph structure:\n");
    show_graph(g);

    release_graph(g);
    release_grid(data);

    return 0;
}