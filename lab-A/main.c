#include <stdio.h>
#include "cover.h"

int main() {
    Graph graph;
    int K;
    int cover_vertices[MAX_VERTICES];
    int cover_size = 0;

    // Пробуем открыть файл
    if (!read_graph("input.txt", &graph, &K)) {
        printf("Error: Cannot find input.txt\n");
        return 1;
    }

    printf("Graph: %d vertices, %d edges, K=%d\n",
        graph.vertices_count, graph.edges_count, K);

    // Показываем рёбра
    if (graph.edges_count > 0) {
        printf("Edges:\n");
        for (int i = 0; i < graph.edges_count; i++) {
            printf("  %d-%d\n", graph.edges[i].u + 1, graph.edges[i].v + 1);
        }
    }

    // Ищем покрытие
    printf("Finding vertex cover...\n");
    bool found = find_vertex_cover(&graph, K, cover_vertices, &cover_size);

    // Записываем результат
    if (!write_result("output.txt", cover_vertices, cover_size)) {
        printf("Error writing output file\n");
        return 1;
    }

    // Показываем результат
    if (cover_size > 0) {
        printf("Vertex cover found: ");
        for (int i = 0; i < cover_size; i++) {
            printf("%d ", cover_vertices[i] + 1);
        }
        printf("\n");
    }
    else {
        printf("No vertex cover found\n");
    }

    printf("Result written to output.txt\n");
    return 0;
}