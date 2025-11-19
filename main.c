#include "graph.h"

static void dfsUtil(Graph* graph, int current, int visited[], int* pathFound, int target) {
    if (*pathFound) return;
    visited[current] = 1;
    if (current == target) {
        *pathFound = 1;
        return;
    }
    for (int neighbor = 0; neighbor < graph->vertexCount; neighbor++) {
        if (*pathFound) return;
        if (graph->adjacency[current][neighbor] && !visited[neighbor]) {
            dfsUtil(graph, neighbor, visited, pathFound, target);
        }
    }
}

int dfsHasPath(Graph* graph, int source, int destination) {
    if (source < 0 || source >= graph->vertexCount || destination < 0 || destination >= graph->vertexCount) return 0;
    int visited[MAX_VERTICES] = { 0 };
    int pathFound = 0;
    dfsUtil(graph, source, visited, &pathFound, destination);
    return pathFound;
}

int readGraphFromFile(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return 0;
    if (fscanf(file, "%d", &graph->vertexCount) != 1 || graph->vertexCount <= 0 || graph->vertexCount > MAX_VERTICES) {
        fclose(file);
        return 0;
    }
    for (int i = 0; i < graph->vertexCount; i++) {
        for (int j = 0; j < graph->vertexCount; j++) {
            if (fscanf(file, "%d", &graph->adjacency[i][j]) != 1) {
                fclose(file);
                return 0;
            }
        }
    }
    fclose(file);
    return 1;
}