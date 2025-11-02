#pragma once

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable: 4996)

#include <stdio.h>

#include <stdlib.h>

typedef struct node {
	int digit;
	struct node* next;
} int_t;

int_t* ReadTolong();

int_t* Add(int_t* a, int_t* b);

int_t* Mul(int_t* a, int_t* b);

int_t* Poww(int_t* a, int_t* b);

void Mul10x(int_t** a, int x);

int_t* Createnode(int digit);

void Bend(int_t** head, int digit);

int StrLen(const char* s);

void FreeList(int_t* a);

void PrintLong(int_t* a);


