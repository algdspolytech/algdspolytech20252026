#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    printf("=== Graph Path Finder (DFS) ===\n\n");

    // чтение графа из файла
    Graph* graph = read_graph_from_file("graph.txt");
    if (!graph) {
        printf("Please create graph.txt file in the same folder as .exe\n");
        return 1;
    }

    printf("Graph loaded successfully!\n");
    printf("Number of vertices: %d\n\n", graph->vertices);

    // ввод вершин от пользователя
    int start, target;
    printf("Enter start vertex (0-%d): ", graph->vertices - 1);
    scanf("%d", &start);

    printf("Enter target vertex (0-%d): ", graph->vertices - 1);
    scanf("%d", &target);

    // проверка существования пути
    if (path_exists(graph, start, target)) {
        printf("\n Path exists from %d to %d!\n", start, target);
    }
    else {
        printf("\n No path from %d to %d.\n", start, target);
    }

    // освобождение памяти
    free_graph(graph);

    printf("\nPress Enter to exit...");
    getchar();
    return 0;
}