#pragma once
#include <stdio.h> 
#include <math.h> 
#include <locale.h> 
#include <malloc.h> 
#include <stdlib.h> 
#include <crtdbg.h> 


typedef struct {
    int* NeighboursVert;
    int NumOfNeigh;
    int Vertnum;
}vertex;

typedef struct Node {
    vertex vert;
    struct Node* next;
}Node;

typedef struct Queue {
    Node* first;
    Node* last;
}Queue;

int FromStr2Num(char* str, int len);

Node* DeQueue(Queue* Q);

void InQueue(Node* pN, Queue* Q);

int* FindTheWay(int* waylen, vertex* graph, int graphlen, int FromNum, int ToNum);

vertex* ReadGraph(char* lines, int lenght, int* graphlen);

void FreeGraph(vertex* graph, int len);