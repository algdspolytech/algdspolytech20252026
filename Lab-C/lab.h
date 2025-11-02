#pragma once
#ifndef LAB_H
#define LAB_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100
#define MAX_LINE_LENGTH 100

typedef struct {
    int adjacency_list[MAX_VERTICES][MAX_VERTICES];
    int size[MAX_VERTICES];
    int vertex_count;
} Graph;

void init_graph(Graph* graph);
void add_edge(Graph* graph, int from, int to);
int dfs(Graph* graph, int current, int target, int visited[]);
int path_exists(Graph* graph, int start, int end);
int read_graph(const char* filename, Graph* graph);
void run_all_tests(void);

#endif
