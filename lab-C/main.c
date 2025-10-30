#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void createDefaultGraphFile() {
    FILE* file = fopen("graph.txt", "w");
    if (file) {
        fprintf(file, "5\n");
        fprintf(file, "0 1 0 0 0\n");
        fprintf(file, "1 0 1 0 0\n");
        fprintf(file, "0 1 0 1 0\n");
        fprintf(file, "0 0 1 0 1\n");
        fprintf(file, "0 0 0 1 0\n");
        fclose(file);
        printf("Created default graph.txt file\n");
    }
}

int main() {
    const char* filename = "graph.txt";

    // Проверяем существование файла
    FILE* test = fopen(filename, "r");
    if (!test) {
        printf("Graph file not found. Creating default...\n");
        createDefaultGraphFile();
    }
    else {
        fclose(test);
    }

    Graph* graph = readGraphFromFile(filename);
    if (!graph) {
        printf("Failed to read graph from file\n");
        return 1;
    }

    printf("Graph loaded successfully with %d vertices\n", graph->vertices);
    printf("Adjacency matrix:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int start, end;
    printf("Enter start vertex: ");
    scanf("%d", &start);
    printf("Enter end vertex: ");
    scanf("%d", &end);

    int pathLength;
    int* path = findShortestPath(graph, start, end, &pathLength);

    printPath(path, pathLength);

    if (path) {
        free(path);
    }
    freeGraph(graph);

    return 0;
}