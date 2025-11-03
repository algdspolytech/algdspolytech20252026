#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;
typedef struct {
    int vertices;
    Node **adjLists;
} Graph;

// Прототипы функций из graph.c
Graph *parseAdjListFile(const char *filename);

int **parseAdjMatrixFile(const char *filename);

int compareGraphs(const Graph *listGraph, int **matrixGraph, int size);

void freeGraph(Graph *graph);

int main(void) {
    const char *listFile = "adjacency_list.txt";
    const char *matrixFile = "adjacency_matrix.txt";

    Graph *listGraph = parseAdjListFile(listFile);
    int **matrixGraph = parseAdjMatrixFile(matrixFile);

    if (!listGraph) {
        printf("Error reading adjacency list file: %s\n", listFile);
        return 1;
    }
    if (!matrixGraph) {
        printf("Error reading adjacency matrix file: %s\n", matrixFile);
        freeGraph(listGraph);
        return 1;
    }

    int vertices = listGraph->vertices;  // Сохраняем количество вершин перед освобождением памяти

    if (compareGraphs(listGraph, matrixGraph, vertices))
        printf("Graphs are equal\n");
    else
        printf("Graphs are different\n");

    // Освобождаем память
    freeGraph(listGraph);
    for (int i = 0; i < vertices; i++) free(matrixGraph[i]);
    free(matrixGraph);

    return 0;
}
