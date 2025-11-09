#pragma once
#ifndef STACK_LIST_H
#define STACK_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    size_t size;
} StackList;

StackList* s_create(void);
void s_destroy(StackList* stack);
bool s_push(StackList* stack, int value);
bool s_pop(StackList* stack, int* out_value);
bool s_peek(const StackList* stack, int* out_value);
bool s_is_empty(const StackList* stack);
size_t s_size(const StackList* stack);

#endif