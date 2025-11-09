#include "stack_a.h"
#include <stdlib.h>
#include <string.h>

StackArray* a_create(void) {
    StackArray* stack = (StackArray*)malloc(sizeof(StackArray));
    if (!stack) return NULL;

    stack->data = (int*)malloc(STACK_A_INITIAL_CAPACITY * sizeof(int));
    if (!stack->data) {
        free(stack);
        return NULL;
    }

    stack->size = 0;
    stack->capacity = STACK_A_INITIAL_CAPACITY;
    return stack;
}

void a_destroy(StackArray* stack) {
    if (!stack) return;
    free(stack->data);
    free(stack);
}

static bool a_resize(StackArray* stack, size_t new_capacity) {
    int* new_data = (int*)realloc(stack->data, new_capacity * sizeof(int));
    if (!new_data) return false;

    stack->data = new_data;
    stack->capacity = new_capacity;
    return true;
}

bool a_push(StackArray* stack, int value) {
    if (!stack) return false;

    if (stack->size >= stack->capacity) {
        if (!a_resize(stack, stack->capacity * 2)) {
            return false;
        }
    }

    stack->data[stack->size] = value;
    stack->size++;
    return true;
}

bool a_pop(StackArray* stack, int* out_value) {
    if (!stack || stack->size == 0) return false;

    stack->size--;
    *out_value = stack->data[stack->size];
    return true;
}

bool a_peek(const StackArray* stack, int* out_value) {
    if (!stack || stack->size == 0) return false;

    *out_value = stack->data[stack->size - 1];
    return true;
}

bool a_is_empty(const StackArray* stack) {
    return !stack || stack->size == 0;
}

size_t a_size(const StackArray* stack) {
    return stack ? stack->size : 0;
}

size_t a_capacity(const StackArray* stack) {
    return stack ? stack->capacity : 0;
}