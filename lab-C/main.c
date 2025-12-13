#include <stdio.h>
#include <stdlib.h>
#include "main.h"


// ----------- ADJACENCY LIST GRAPH -----------


void create_graph_list(Graph* graph, int vertices)
{
	graph->array = (AdjList*)malloc(vertices * sizeof(AdjList));
	if (graph->array == NULL)
	{
		return;
	}

	for (int i = 0; i < vertices; i++)
	{
		graph->array[i].head = NULL;
	}

	graph->vertices = vertices;
}

AdjListNode* new_node_list(int destination)
{
	AdjListNode* new_node = (AdjListNode*)malloc(sizeof(AdjListNode));
	if (new_node == NULL)
	{
		return;
	}

	new_node->destination = destination;
	new_node->next = NULL;

	return new_node;
}

void add_edge_list(Graph* graph, int source, int destination)
{
	AdjListNode* new_node = new_node_list(destination);
	new_node->next = graph->array[source].head;
	graph->array[source].head = new_node;

	new_node = new_node_list(source);
	new_node->next = graph->array[destination].head;
	graph->array[destination].head = new_node;
}

void print_graph_list(Graph* graph)
{
	for (int i = 0; i < graph->vertices; i++)
	{
		AdjListNode* temp = graph->array[i].head;
		printf("vertice %d: ", i);
		while (temp)
		{
			printf("%d -> ", temp->destination);
			temp = temp->next;
		}
		printf("NULL\n");
	}
}

void free_graph_list(Graph* graph)
{
	for (int i = 0; i < graph->vertices; i++)
	{
		AdjListNode* current = graph->array[i].head;
		while (current != NULL)
		{
			AdjListNode* temp = current;
			current = current->next;
			free(temp);
		}
	}
	free(graph->array);
}


// ----------- ADJACENCY MATRIX GRAPH -----------

void create_matrix_graph(GraphMatrix* graph, int vertices)
{
	graph->vertices = vertices;
	graph->matrix = (int**)malloc(vertices * sizeof(int*));
	if (graph->matrix == NULL)
	{
		return;
	}

	for (int i = 0; i < vertices; i++)
	{
		graph->matrix[i] = (int*)calloc(vertices, sizeof(int));
		if (graph->matrix[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				free(graph->matrix[j]);
			}
			return;
		}
	}
}

void add_edge_matrix(GraphMatrix* graph, int source, int destination)
{
	graph->matrix[source][destination] = 1;
	graph->matrix[destination][source] = 1;
}

void print_graph_matrix(GraphMatrix* graph)
{
	printf("   ");
	for (int i = 0; i < graph->vertices; i++)
	{
		printf("%d ", i);
	}
	printf("\n");

	for (int i = 0; i < graph->vertices; i++)
	{
		printf("%d: ", i);
		for (int j = 0; j < graph->vertices; j++)
		{
			printf("%d ", graph->matrix[i][j]);
		}
		printf("\n");
	}
}

void free_graph_matrix(GraphMatrix* graph)
{
	for (int i = 0; i < graph->vertices; i++)
	{
		free(graph->matrix[i]);
	}
}