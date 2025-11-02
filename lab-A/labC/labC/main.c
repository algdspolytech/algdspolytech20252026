#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define MAX_VERTICES 100

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

int DFS(struct Graph* graph, int current, int target) {
    if (current == target) {
        return 1;
    }
    graph->visited[current] = 1;
    struct Node* temp = graph->adjLists[current];
    while (temp != NULL) {
        int adjacentVertex = temp->vertex;
        if (!graph->visited[adjacentVertex]) {
            if (DFS(graph, adjacentVertex, target)) {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

int pathExists(struct Graph* graph, int start, int end) {
    if (start == end) {
        return 1;
    }
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
    return DFS(graph, start, end);
}

void printAdjacencyList(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d: ", i);
        struct Node* temp = graph->adjLists[i];
        while (temp != NULL) {
            printf("%d", temp->vertex);
            if (temp->next != NULL) {
                printf(" -> ");
            }
            temp = temp->next;
        }
        printf("\n");
    }
}

void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* current = graph->adjLists[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);
}