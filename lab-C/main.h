#pragma once

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

	// ----------- STRUCTURES -----------

	typedef struct AdjListNode
	{
		int destination;
		struct AdjListNode* next;
	} AdjListNode;

	typedef struct
	{
		AdjListNode* head;
	} AdjList;

	typedef struct
	{
		int vertices;
		AdjList* array;
	} Graph;


	typedef struct
	{
		int vertices;
		int** matrix;
	} GraphMatrix;

	// ----------- FUNCTIONS -----------


	void create_graph_list(Graph* graph, int vertices);

	AdjListNode* new_node_list(int destination);

	void add_edge_list(Graph* graph, int source, int destination);

	void print_graph_list(Graph* graph);

	void free_graph_list(Graph* graph);

	void create_matrix_graph(GraphMatrix* graph, int vertices);

	void add_edge_matrix(GraphMatrix* graph, int source, int destination);

	void print_graph_matrix(GraphMatrix* graph);

	void free_graph_matrix(GraphMatrix* graph);

#ifdef __cplusplus
}
#endif

#endif