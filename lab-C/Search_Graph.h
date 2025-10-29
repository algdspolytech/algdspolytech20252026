
#ifndef SEARCH_GRAPH_H
#define SEARCH_GRAPH_H
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Node {
    int neigh;
    struct Node* prev;
} Node;

typedef struct {
    Node* first;
    Node* last;
} Queue;

typedef struct {
    int** matrix;
    int num_verts;
} Graph;

//Initialize a new queue
void init_queue(Queue* q);
//Add a new node to queue
void push_q(Queue* q, int value);
//Remove and return first element
int pop_q(Queue* q);
//Clear data in queue
void free_queue(Queue* q);
//Read graph from file
Graph read_graph(const char* filename);
//Cleal data in graph
void free_graph(Graph* g);
//Find the shortest path length
int pathfinder(Graph* g, int start, int end);

#endif //SEARCH_GRAPH_H
