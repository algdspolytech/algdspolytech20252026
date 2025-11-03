#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// ---------- Стек на связном списке ----------

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
} StackList;

void initStackList(StackList* s);
int isEmptyList(StackList* s);
void pushList(StackList* s, int value);
int popList(StackList* s);
int peekList(StackList* s);
void clearStackList(StackList* s);

// ---------- Стек на массиве ----------

typedef struct {
    int data[MAX_SIZE];
    int top;
} StackArray;

void initStackArray(StackArray* s);
int isEmptyArray(StackArray* s);
int isFullArray(StackArray* s);
void pushArray(StackArray* s, int value);
int popArray(StackArray* s);
int peekArray(StackArray* s);

#endif
