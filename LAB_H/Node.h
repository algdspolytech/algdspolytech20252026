#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;

typedef struct Node {
    int key, priority;
    Node* l;
    Node* r;
} Node;
typedef Node* pNode;

pNode createNode(int x, int y); // replacing the constructor
void add(pNode* t, pNode a);
void split(pNode t, int x, pNode* l, pNode* r);
void merge(pNode* t, pNode l, pNode r);
void removeAt(pNode* t, int key);
void freeTree(pNode t);
void printTree(pNode t, int space);