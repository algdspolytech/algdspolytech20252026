#define _CRT_SECURE_NO_WARNINGS
#include "shortest_path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>


int** read_adjacency_matrix(const char* filename, int* n) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    if (fscanf(file, "%d", n) != 1) {
        fclose(file);
        return NULL;
    }

    int** matrix = (int**)malloc((*n) * sizeof(int*));
    for (int i = 0; i < *n; i++) {
        matrix[i] = (int*)malloc((*n) * sizeof(int));
        for (int j = 0; j < *n; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                for (int k = 0; k <= i; k++) free(matrix[k]);
                free(matrix);
                fclose(file);
                return NULL;
            }
        }
    }

    fclose(file);
    return matrix;
}

void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

PathResult find_shortest_path(int** matrix, int n, int start, int end) {
    PathResult result = { NULL, 0 };
    if (start < 0 || start >= n || end < 0 || end >= n) return result;

    int* queue = (int*)malloc(n * sizeof(int));
    int* visited = (int*)calloc(n, sizeof(int));
    int* parent = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = -1;

    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;

    int found = 0;
    while (front < rear && !found) {
        int u = queue[front++];
        for (int v = 0; v < n; v++) {
            if (matrix[u][v] != 0 && !visited[v]) {
                visited[v] = 1;
                parent[v] = u;
                queue[rear++] = v;
                if (v == end) {
                    found = 1;
                    break;
                }
            }
        }
    }

    if (!found) {
        free(queue);
        free(visited);
        free(parent);
        return result;
    }

    // Восстановление пути
    int path_length = 0;
    for (int cur = end; cur != -1; cur = parent[cur]) path_length++;
    int* path = (int*)malloc(path_length * sizeof(int));
    for (int i = path_length - 1, cur = end; i >= 0; i--, cur = parent[cur]) {
        path[i] = cur;
    }

    result.path = path;
    result.length = path_length;

    free(queue);
    free(visited);
    free(parent);
    return result;
}

void free_path_result(PathResult res) {
    if (res.path) free(res.path);
}

int compare_paths(const PathResult* p1, const PathResult* p2) {
    if (p1->length != p2->length) return 0;
    for (int i = 0; i < p1->length; i++) {
        if (p1->path[i] != p2->path[i]) return 0;
    }
    return 1;
}
