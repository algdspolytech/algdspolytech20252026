#pragma once
#include "stack_list.h"
#include <stdlib.h>

StackList* createStackList()
{
    StackList* stack = (StackList*)malloc(sizeof(StackList));
    if (!stack) return NULL;
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void destroyStackList(StackList* stack)
{
    if (!stack) return;
    StackNode* current = stack->top;
    while (current) {
        StackNode* next = current->next;
        free(current);
        current = next;
    }
    free(stack);
}

int pushList(StackList* stack, int value)
{
    if (!stack) return 0;
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) return 0;
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
    return 1;
}

int popList(StackList* stack, int* value)
{
    if (!stack || !value || isEmptyList(stack)) return 0;
    StackNode* temp = stack->top;
    *value = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return 1;
}

int peekList(const StackList* stack, int* value)
{
    if (!stack || !value || isEmptyList(stack)) return 0;
    *value = stack->top->data;
    return 1;
}

int isEmptyList(const StackList* stack)
{
    return !stack || stack->top == NULL;
}

size_t sizeList(const StackList* stack)
{
    return stack ? stack->size : 0;
}