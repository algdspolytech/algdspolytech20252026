#pragma once
#ifndef STACK_LIST_H
#define STACK_LIST_H

#include <stddef.h>

typedef struct StackNode 
{
    int data;
    struct StackNode* next;
} StackNode;

typedef struct 
{
    StackNode* top;
    size_t size;
} StackList;

StackList* createStackList();
void destroyStackList(StackList* stack);
int pushList(StackList* stack, int value);
int popList(StackList* stack, int* value);
int peekList(const StackList* stack, int* value);
int isEmptyList(const StackList* stack);
size_t sizeList(const StackList* stack);

#endif
