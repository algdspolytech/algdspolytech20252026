#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES 100

// Внешняя переменная, объявленная в graph.c
extern int visited[MAX_VERTICES];

// Прототипы функций
int dfs(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int current, int target);
void reset_visited(int vertices);
int has_path(int graph[MAX_VERTICES][MAX_VERTICES], int vertices, int start, int end);
void load_graph_from_file(const char* filename, int graph[MAX_VERTICES][MAX_VERTICES], int* vertices);

#endif // GRAPH_H#pragma once
