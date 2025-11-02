#include <stdio.h>
#include "Header.h"

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable: 4996)

#define MAX 100

void Createqueue(queue* a) {
	a->back = -1;
	a->head = -1;
}

int isqueueempty(queue* a) {
	if (a->back == -1) {
		return 1;
	}
	return 0;
}

void Addinqueue(queue* a, int value) {
	if (a->head == -1) {
		a->head = 0;
	}
	a->back++;
	a->vertices[a->back] = value;
}

int Removefromqueue(queue* a) {
	int value;
	if (isqueueempty(a) == 1) {
		return -1;
	}
	else {
		value = a->vertices[a->head];
		a->head++;
		if (a->head > a->back) {
			a->head = -1;
			a->back = -1;
		}
		return value;
	}
}

void Createstack(stack* b) {
	b->top = -1;
}

int isstackempty(stack* b) {
	if (b->top == -1) {
		return 1;
	}
	return 0;
}

void Addinstack(stack* b, int value) {
	b->top++;
	b->vertices[b->top] = value;
}

int Removefromstack(stack* b) {
	int value;
	if (isstackempty(b) == 1) {
		return -1;
	}
	else {
		value = b->vertices[b->top];
		b->top--;
		return value;
	}
}

void pathfinder(int matrix[MAX][MAX], int n, int start, int end, PathResult* result) {
	int visited[MAX] = { 0 };
	int prev[MAX] = { -1 };
	queue a;
	Createqueue(&a);
	result->found = 0;
	result->length = 0;
	visited[start] = 1;
	prev[start] = -1;
	Addinqueue(&a, start);
	while (isqueueempty(&a) == 0) {
		int current = Removefromqueue(&a);
		if (current == end) {
			result->found = 1;
			break;
		}
		for (int i = 0; i < n; i++) {
			if (matrix[current][i] == 1 && visited[i] == 0) {
				visited[i] = 1;
				prev[i] = current;
				Addinqueue(&a, i);
			}
		}
	}
	if (result->found == 1) {
		stack b;
		Createstack(&b);
		int current = end;
		while (current != -1) {
			Addinstack(&b, current);
			current = prev[current];
		}
		result->length = 0;
		while (isstackempty(&b) == 0) {
			result->path[result->length] = Removefromstack(&b);
			result->length++;
		}
	}
}

void pathprinter(const PathResult* result, int start, int end) {
	if (result->found == 0) {
		printf("Пути между вершинами %i и %i - нет", start, end);
		return;
	}

	printf("Кратчайший путь:\n");
	for (int i = 0; i < result->length; i++) {
		printf("%i", result->path[i]);
		if (i < result->length - 1) {
			printf(" -> ");
		}
	}
	printf("\nОбщая длина пути: %i", result->length - 1);
}