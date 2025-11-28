#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define MAX 100

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

typedef struct {
	int elements[MAX];
	int top;
} arr_stack;

typedef struct node {
	int value;
	struct node* next;
} node_stack;

void CreateAS(arr_stack* a);

node_stack* CreateNS(int value);

int isASempty(arr_stack* a);

void pushAS(arr_stack* a, int value);

void pushNS(node_stack** b, int value);

int popAS(arr_stack* a);

int popNS(node_stack** b);

void printAS(arr_stack* a);

void printNS(node_stack* b);

void freeNS(node_stack** b);
