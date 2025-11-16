// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>

#define SIZE 100

#ifdef __cplusplus
extern "C" {
#endif

	// Структура графа
	typedef struct {
		int n;
		int matrix[SIZE][SIZE];
	} Graph;

	// Функции
	void init_graph(Graph* g, int n);
	void read_from_list(Graph* g, const char* filename);
	void read_from_matrix(Graph* g, const char* filename);
	int compare_graphs(const Graph* a, const Graph* b);
	void print_graph(const Graph* g);

#ifdef __cplusplus
}
#endif

#endif