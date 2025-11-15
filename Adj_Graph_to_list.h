#ifndef ADJ_GRAPH_TO_LIST_H
#define ADJ_GRAPH_TO_LIST_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define FILENAME "adjacency_matrix.txt"

typedef struct AdjListNode {
  int dest;
  struct AdjListNode* next;
} AdjListNode;

typedef struct Graph {
  int V;
  struct AdjListNode** head;
} Graph;

AdjListNode* newAdjListNode(int dest);
Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest);
Graph* matrixToList();
void printGraph(Graph* graph);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif  // ADJ_GRAPH_TO_LIST_H
