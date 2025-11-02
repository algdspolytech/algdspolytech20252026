#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define MAX 100

#pragma warning(disable: 4996)

typedef struct {
	int vertices[MAX];
	int head;
	int back;
} queue;

typedef struct {
	int vertices[MAX];
	int top;
} stack;

typedef struct {
	int path[MAX];
	int length;
	int found;
} PathResult;

void Createqueue(queue* a);

int isqueueempty(queue* a);

void Addinqueue(queue* a, int value);

int Removefromqueue(queue* a);

void Createstack(stack* b);

int isstackempty(stack* b);

void Addinstack(stack* b, int value);

int Removefromstack(stack* b);

void pathfinder(int matrix[MAX][MAX], int n, int start, int end, PathResult* result);

void pathprinter(const PathResult* result, int start, int end);