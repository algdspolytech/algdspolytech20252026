#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <stddef.h>

typedef struct PathResult {
    int* path;      // массив вершин пути
    int length;     // длина пути (число вершин)
} PathResult;

int** read_adjacency_matrix(const char* filename, int* n);
void free_matrix(int** matrix, int n);
PathResult find_shortest_path(int** matrix, int n, int start, int end);
void free_path_result(PathResult res);

int compare_paths(const PathResult* p1, const PathResult* p2);

#endif // SHORTEST_PATH_H
