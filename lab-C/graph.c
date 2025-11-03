#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct {
    int vertices;
    Node **adjLists;
} Graph;

Graph *createGraph(int vertices) {
    if (vertices <= 0) return NULL;
    Graph *graph = (Graph *) malloc(sizeof(Graph));
    if (!graph) return NULL;
    graph->vertices = vertices;
    graph->adjLists = (Node **) calloc(vertices, sizeof(Node *));
    return graph;
}

void addEdgeList(Graph *graph, int src, int dest) {
    if (!graph) return;
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void freeGraph(Graph *graph) {
    if (!graph) return;
    for (int i = 0; i < graph->vertices; i++) {
        Node *temp = graph->adjLists[i];
        while (temp) {
            Node *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjLists);
    free(graph);
}

int **listToMatrix(const Graph *graph) {
    if (!graph) return NULL;
    int n = graph->vertices;
    int **matrix = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *) calloc(n, sizeof(int));
        Node *temp = graph->adjLists[i];
        while (temp) {
            matrix[i][temp->vertex] = 1;
            temp = temp->next;
        }
    }
    return matrix;
}

int compareMatrices(int **m1, int **m2, int size) {
    if (!m1 || !m2) return 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (m1[i][j] != m2[i][j]) return 0;
    return 1;
}

int compareGraphs(const Graph *listGraph, int **matrixGraph, int size) {
    int **matrixFromList = listToMatrix(listGraph);
    int result = compareMatrices(matrixFromList, matrixGraph, size);
    for (int i = 0; i < size; i++) free(matrixFromList[i]);
    free(matrixFromList);
    return result;
}

Graph *parseAdjListFile(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;

    int vertices;
    if (fscanf(f, "%d\n", &vertices) != 1) {
        fclose(f);
        return NULL;
    }
    Graph *graph = createGraph(vertices);
    if (!graph) {
        fclose(f);
        return NULL;
    }

    char line[256];
    for (int i = 0; i < vertices; i++) {
        if (!fgets(line, sizeof(line), f)) break;
        char *token = strtok(line, ": ");
        token = strtok(NULL, " ");
        while (token) {
            int v = atoi(token);
            addEdgeList(graph, i, v);
            token = strtok(NULL, " \n");
        }
    }
    fclose(f);
    return graph;
}

int **parseAdjMatrixFile(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;

    int n;
    if (fscanf(f, "%d\n", &n) != 1) {
        fclose(f);
        return NULL;
    }
    int **matrix = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) fscanf(f, "%d", &matrix[i][j]);
    }
    fclose(f);
    return matrix;
}
