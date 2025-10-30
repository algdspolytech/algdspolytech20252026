#include "dfs.h"

int main() {
    Graph graph;
    char filename[100];
    int start, end;

    printf("DFS Path Finder - Universal Version\n");
    printf("===================================\n\n");

    // Чтение графа из файла
    printf("Enter graph filename (default: graph.txt): ");
    if (scanf("%99s", filename) != 1) {
        strcpy(filename, "graph.txt");
    }

    if (!read_graph_from_file(&graph, filename)) {
        printf("Failed to read graph from file. Using default graph.\n");

        initialize_graph(&graph);
        add_edge(&graph, 0, 1);
        add_edge(&graph, 1, 2);
        add_edge(&graph, 2, 3);
        add_edge(&graph, 3, 4);
    }

    printf("\nGraph information:\n");
    printf("Number of vertices: %d\n", graph.vertices_count);
    printf("Graph capacity: %d\n", graph.capacity);
    print_graph(&graph);

    printf("\nEnter start and end vertices to check path: ");
    if (scanf("%d %d", &start, &end) != 2) {
        printf("Invalid input. Using default vertices 0 and 4.\n");
        start = 0;
        end = 4;
    }

    if (path_exists(&graph, start, end)) {
        printf("\nPath exists from vertex %d to vertex %d\n", start, end);
    }
    else {
        printf("\nNo path exists from vertex %d to vertex %d\n", start, end);
    }

    printf("\nAdditional path checks:\n");
    printf("0 -> 1: %s\n", path_exists(&graph, 0, 1) ? "Exists" : "No path");
    printf("0 -> %d: %s\n", graph.vertices_count - 1,
        path_exists(&graph, 0, graph.vertices_count - 1) ? "Exists" : "No path");

    destroy_graph(&graph);
    return 0;
}