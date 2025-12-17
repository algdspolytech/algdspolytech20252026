#pragma once

#include <stdio.h>
#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICE 1000

typedef struct {
	int vertice;
	int edge;
	int** adjacency;
}Graph;

Graph* CreateGraph(int vertice, int edge);

Graph* ReadGraph(const char* filename, Graph* graph, int K);

void WriteGraph(const char* filename, Graph* graph, int K);

void DestroyGraph(Graph* graph);

bool CheckVertexCover(Graph* graph, int K);

void FindVertexCover(Graph* graph, int K, int* cover, int* cover_size);

bool VertexCoverUtil(Graph* graph, int* edges_u, int* edges_v, int edge_count, int K);

int CountEdges(Graph* graph);

void GetEdges(Graph* graph, int* edges_u, int* edges_v, int* edge_count);

void RemoveIncidentEdges(Graph* graph, int vertex, int* edges_u, int* edges_v, int* edge_count);

bool IsCoverValid(Graph* graph, int* cover, int cover_size);