#include "stack_s.h"
#include <stdlib.h>

StackList* s_create(void) {
    StackList* stack = (StackList*)malloc(sizeof(StackList));
    if (stack) {
        stack->top = NULL;
        stack->size = 0;
    }
    return stack;
}

void s_destroy(StackList* stack) {
    if (!stack) return;

    StackNode* current = stack->top;
    while (current) {
        StackNode* next = current->next;
        free(current);
        current = next;
    }
    free(stack);
}

bool s_push(StackList* stack, int value) {
    if (!stack) return false;

    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    if (!new_node) return false;

    new_node->data = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;

    return true;
}

bool s_pop(StackList* stack, int* out_value) {
    if (!stack || !stack->top) return false;

    StackNode* top_node = stack->top;
    *out_value = top_node->data;
    stack->top = top_node->next;
    free(top_node);
    stack->size--;

    return true;
}

bool s_peek(const StackList* stack, int* out_value) {
    if (!stack || !stack->top) return false;

    *out_value = stack->top->data;
    return true;
}

bool s_is_empty(const StackList* stack) {
    return !stack || stack->top == NULL;
}

size_t s_size(const StackList* stack) {
    return stack ? stack->size : 0;
}