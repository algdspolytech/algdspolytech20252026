#include "stack_array.h"
#include <stdlib.h>

#define INITIAL_CAPACITY 4

StackArray* createStackArray()
{
    StackArray* stack = (StackArray*)malloc(sizeof(StackArray));
    if (!stack) return NULL;
    stack->data = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
    if (!stack->data)
    {
        free(stack);
        return NULL;
    }
    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;
    return stack;
}

void destroyStackArray(StackArray* stack)
{
    if (!stack) return;
    free(stack->data);
    free(stack);
}

static int resize(StackArray* stack)
{
    size_t newCapacity = stack->capacity * 2;
    int* newData = (int*)realloc(stack->data, newCapacity * sizeof(int));
    if (!newData) return 0;
    stack->data = newData;
    stack->capacity = newCapacity;
    return 1;
}

int pushArray(StackArray* stack, int value)
{
    if (!stack) return 0;
    if (stack->size >= stack->capacity && !resize(stack)) return 0;
    stack->data[stack->size++] = value;
    return 1;
}

int popArray(StackArray* stack, int* value)
{
    if (!stack || !value || isEmptyArray(stack)) return 0;
    *value = stack->data[--stack->size];
    return 1;
}

int peekArray(const StackArray* stack, int* value)
{
    if (!stack || !value || isEmptyArray(stack)) return 0;
    *value = stack->data[stack->size - 1];
    return 1;
}

int isEmptyArray(const StackArray* stack)
{
    return !stack || stack->size == 0;
}

size_t sizeArray(const StackArray* stack)
{
    return stack ? stack->size : 0;
}