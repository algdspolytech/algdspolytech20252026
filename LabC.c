#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LabC.h"

Graph* readgraph(const char* filename) {

    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    // Read number of vertices
    int vertices;
    if (fscanf(file, "%d", &vertices) != 1) {
        fclose(file);
        return NULL;
    }

    if (vertices <= 0 || vertices > MAX) {
        fclose(file);
        return NULL;
    }

    // Skip to next line
    int c;
    while ((c = fgetc(file)) != '\n' && c != EOF) {
        // skip characters until newline
    }

    // Allocate graph structure
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        fclose(file);
        return NULL;
    }

    graph->vertices = vertices;

    // Allocate matrix rows
    graph->matrix = (int**)malloc(vertices * sizeof(int*));
    if (!graph->matrix) {
        free(graph);
        fclose(file);
        return NULL;
    }

    // Initialize pointers to NULL
    for (int i = 0; i < vertices; i++) {
        graph->matrix[i] = NULL;
    }

    // Allocate each matrix row
    for (int i = 0; i < vertices; i++) {
        graph->matrix[i] = (int*)malloc(vertices * sizeof(int));
        if (!graph->matrix[i]) {
            // Cleanup already allocated rows
            for (int j = 0; j < i; j++) {
                free(graph->matrix[j]);
            }
            free(graph->matrix);
            free(graph);
            fclose(file);
            return NULL;
        }
    }

    // Read matrix data
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            // Skip whitespace
            int c;
            do {
                c = fgetc(file);
            } while (isspace(c) && c != '\n' && c != EOF);

            if (c == EOF) {
                // Cleanup
                for (int k = 0; k < vertices; k++) {
                    free(graph->matrix[k]);
                }
                free(graph->matrix);
                free(graph);
                fclose(file);
                return NULL;
            }

            // Put character back
            ungetc(c, file);

            // Read integer
            int value;
            if (fscanf(file, "%d", &value) != 1) {
                // Cleanup
                for (int k = 0; k < vertices; k++) {
                    free(graph->matrix[k]);
                }
                free(graph->matrix);
                free(graph);
                fclose(file);
                return NULL;
            }

            graph->matrix[i][j] = value;
        }

        // Skip to next line after reading each row
        while ((c = fgetc(file)) != '\n' && c != EOF) {
            // skip remaining characters on line
        }
    }

    fclose(file);
    return graph;
}

void freegraph(Graph* graph) {
    if (!graph) return;

    if (graph->matrix) {
        for (int i = 0; i < graph->vertices; i++) {
            free(graph->matrix[i]);
        }
        free(graph->matrix);
    }
    free(graph);
}

static int mindistance(int dist[], int visited[], int vertices) {
    int min = INF, min_index = -1;

    for (int v = 0; v < vertices; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

PathResult* shortpath(Graph* graph, int start, int end) {
    if (!graph || start < 0 || start >= graph->vertices ||
        end < 0 || end >= graph->vertices) {
        return NULL;
    }

    if (start == end) {
        PathResult* result = (PathResult*)malloc(sizeof(PathResult));
        if (!result) return NULL;

        result->path = (int*)malloc(sizeof(int));
        if (!result->path) {
            free(result);
            return NULL;
        }

        result->path[0] = start;
        result->length = 1;
        result->distance = 0;
        return result;
    }

    int* dist = (int*)malloc(graph->vertices * sizeof(int));
    int* visited = (int*)malloc(graph->vertices * sizeof(int));
    int* prev = (int*)malloc(graph->vertices * sizeof(int));

    if (!dist || !visited || !prev) {
        free(dist);
        free(visited);
        free(prev);
        return NULL;
    }

    for (int i = 0; i < graph->vertices; i++) {
        dist[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < graph->vertices - 1; count++) {
        int u = mindistance(dist, visited, graph->vertices);

        if (u == -1 || u == end) break;

        visited[u] = 1;

        for (int v = 0; v < graph->vertices; v++) {
            if (!visited[v] && graph->matrix[u][v] != 0 &&
                dist[u] != INF && dist[u] + graph->matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->matrix[u][v];
                prev[v] = u;
            }
        }
    }

    PathResult* result = NULL;

    if (dist[end] != INF) {
        result = (PathResult*)malloc(sizeof(PathResult));
        if (result) {
            result->distance = dist[end];

            // Reconstruct path
            int* temp_path = (int*)malloc(graph->vertices * sizeof(int));
            if (temp_path) {
                int path_index = 0;
                int current = end;

                while (current != -1) {
                    temp_path[path_index++] = current;
                    current = prev[current];
                }

                result->path = (int*)malloc(path_index * sizeof(int));
                if (result->path) {
                    result->length = path_index;
                    for (int i = 0; i < path_index; i++) {
                        result->path[i] = temp_path[path_index - 1 - i];
                    }
                }
                else {
                    free(result);
                    result = NULL;
                }
                free(temp_path);
            }
            else {
                free(result);
                result = NULL;
            }
        }
    }

    free(dist);
    free(visited);
    free(prev);

    return result;
}

void freeresult(PathResult* result) {
    if (result) {
        free(result->path);
        free(result);
    }
}

void print(PathResult* result) {
    if (!result) {
        printf("No path exists\n");
        return;
    }

    printf("Shortest path distance: %d\n", result->distance);
    printf("Path: ");
    for (int i = 0; i < result->length; i++) {
        printf("%d", result->path[i]);
        if (i < result->length - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}