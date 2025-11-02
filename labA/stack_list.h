#pragma once
#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include <stddef.h>

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} StackArray;

StackArray* createStackArray();
void destroyStackArray(StackArray* stack);
int pushArray(StackArray* stack, int value);
int popArray(StackArray* stack, int* value);
int peekArray(const StackArray* stack, int* value);
int isEmptyArray(const StackArray* stack);
size_t sizeArray(const StackArray* stack);

#endif