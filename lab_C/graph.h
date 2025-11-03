#pragma once
#define GRAPH_H

#define MAX_VERTICES 100

int vertices_list(const char* filename);
int matrix_size(const char* filename);
void read_list(const char* filename, int matrix[][MAX_VERTICES], int n);
void read_matrix(const char* filename, int matrix[][MAX_VERTICES], int n);
int compare_results(int n, int m1[][MAX_VERTICES], int m2[][MAX_VERTICES]);

