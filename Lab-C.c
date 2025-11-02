#include "Lab-C.h"
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)

#define MAX_LINE_LENGTH 1024
#define MAX_VERTICES 100

Graph* createGraph(int vertices) {
    if (vertices <= 0) {
        return NULL;
    }

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        return NULL;
    }

    graph->vertices = vertices;

    graph->matrix = (int**)malloc(vertices * sizeof(int*));
    if (!graph->matrix) {
        free(graph);
        return NULL;
    }

    for (int i = 0; i < vertices; i++) {
        graph->matrix[i] = (int*)calloc(vertices, sizeof(int));
        if (!graph->matrix[i]) {
            for (int j = 0; j < i; j++) {
                free(graph->matrix[j]);
            }
            free(graph->matrix);
            free(graph);
            return NULL;
        }
    }

    return graph;
}

Graph* readGraphFromFile(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    int maxVertex = -1;
    char line[MAX_LINE_LENGTH];
    int vertexCount = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) == 0 || (strlen(line) == 1 && line[0] == '\n')) {
            continue;
        }

        char* token = strtok(line, " \t\n");
        if (!token) continue;

        int currentVertex = atoi(token);
        if (currentVertex > maxVertex) {
            maxVertex = currentVertex;
        }

        while ((token = strtok(NULL, " \t\n")) != NULL) {
            int neighbor = atoi(token);
            if (neighbor > maxVertex) {
                maxVertex = neighbor;
            }
        }
        vertexCount++;
    }

    if (maxVertex < 0) {
        fclose(file);
        printf("Error: No valid vertices found in file\n");
        return NULL;
    }

    int totalVertices = maxVertex + 1;

    Graph* graph = createGraph(totalVertices);
    if (!graph) {
        fclose(file);
        printf("Error: Cannot create graph\n");
        return NULL;
    }

    rewind(file);

    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) == 0 || (strlen(line) == 1 && line[0] == '\n')) {
            continue;
        }

        char* token = strtok(line, " \t\n");
        if (!token) continue;

        int currentVertex = atoi(token);

        while ((token = strtok(NULL, " \t\n")) != NULL) {
            int neighbor = atoi(token);
            addEdge(graph, currentVertex, neighbor);
        }
    }

    fclose(file);
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    if (!graph || src < 0 || dest < 0 || src >= graph->vertices || dest >= graph->vertices) {
        return;
    }

    graph->matrix[src][dest] = 1;
    graph->matrix[dest][src] = 1;
}

void printAdjacencyMatrix(Graph* graph) {
    if (!graph || !graph->matrix) {
        printf("Error: Invalid graph\n");
        return;
    }

    printf("Adjacency Matrix (%d x %d):\n\n", graph->vertices, graph->vertices);

    printf("    ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    printf("   ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("---");
    }
    printf("\n");

    for (int i = 0; i < graph->vertices; i++) {
        printf("%2d| ", i);
        for (int j = 0; j < graph->vertices; j++) {
            printf("%2d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

void writeMatrixToFile(Graph* graph, const char* filename) {
    if (!graph || !filename) {
        return;
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Cannot create output file %s\n", filename);
        return;
    }

    fprintf(file, "Adjacency Matrix (%d vertices):\n", graph->vertices);

    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            fprintf(file, "%d", graph->matrix[i][j]);
            if (j < graph->vertices - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Adjacency matrix written to %s\n", filename);
}

void destroyGraph(Graph* graph) {
    if (!graph) {
        return;
    }

    if (graph->matrix) {
        for (int i = 0; i < graph->vertices; i++) {
            free(graph->matrix[i]);
        }
        free(graph->matrix);
    }

    free(graph);
}

int getVertexCount(Graph* graph) {
    if (!graph) {
        return 0;
    }
    return graph->vertices;
}

int hasEdge(Graph* graph, int src, int dest) {
    if (!graph || !graph->matrix || src < 0 || dest < 0 ||
        src >= graph->vertices || dest >= graph->vertices) {
        return 0;
    }
    return graph->matrix[src][dest] == 1;
}