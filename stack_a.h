#pragma once
#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include <stddef.h>
#include <stdbool.h>

#define STACK_A_INITIAL_CAPACITY 10

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} StackArray;

StackArray* a_create(void);
void a_destroy(StackArray* stack);
bool a_push(StackArray* stack, int value);
bool a_pop(StackArray* stack, int* out_value);
bool a_peek(const StackArray* stack, int* out_value);
bool a_is_empty(const StackArray* stack);
size_t a_size(const StackArray* stack);
size_t a_capacity(const StackArray* stack);

#endif