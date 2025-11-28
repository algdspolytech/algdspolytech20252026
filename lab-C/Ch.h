#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define MAX 100

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

typedef struct {
	int x;
	int  y;
} point;

typedef struct {
	point info[MAX * MAX];
	int head;
	int back;
} queue;

void Createqueue(queue* a);

int isqueueempty(queue* a);

void Addinqueue(queue* a, point p);

point Removefromqueue(queue* a);

int SheetSeparation(int m, int n, int matrix[MAX][MAX]);
