#pragma once

#include <stdio.h>
#include <stdlib.h>

#define TREE_SPACE_SIZE 5
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
} NodeT;

void printTree(NodeT* tree, int dataSize, int indentation);

int getMaxElement(NodeT* tree);
NodeT* treeAbs(NodeT* tree);
int getHeight(NodeT* tree);

NodeT* createLeaf(int data);
NodeT* createDisbalancedElementaryTree(int size);
NodeT* createBalancedElementaryTree(int size);
NodeT* createMixedTree(int size);
NodeT* createHeightTree(NodeT* tree);
NodeT* createCopy(NodeT* tree);
void freeTree(NodeT* tree);

enum errors {
	NOT_ENOUGHT_MEMORY = -1,
	INCORECRT_TREE_SIZE = -2,
	TREE_PTR_IS_NULL = -3
};
void ERROR(int errorCode);
