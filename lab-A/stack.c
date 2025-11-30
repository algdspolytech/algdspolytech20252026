#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

// ================================
// List Stack
// ================================

ListStack* create_list_stack(void) {
    ListStack* stack = (ListStack*)malloc(sizeof(ListStack));
    if (!stack) return NULL;
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void destroy_list_stack(ListStack* stack) {
    if (!stack) return;
    while (stack->top != NULL) {
        ListNode* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
    free(stack);
}

bool list_push(ListStack* stack, int value) {
    if (!stack) return false;
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) return false;
    node->data = value;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
    return true;
}

int list_pop(ListStack* stack) {
    if (!stack || !stack->top) {
        fprintf(stderr, "Ошибка: попытка извлечь из пустого стека\n");
        exit(1);
    }
    ListNode* temp = stack->top;
    int value = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return value;
}

int list_peek(const ListStack* stack) {
    if (!stack || !stack->top) {
        fprintf(stderr, "Ошибка: peek на пустом стеке\n");
        exit(1);
    }
    return stack->top->data;
}

bool list_is_empty(const ListStack* stack) {
    return stack == NULL || stack->top == NULL;
}

int list_size(const ListStack* stack) {
    return stack ? stack->size : 0;
}

// ================================
// Array Stack
// ================================

ArrayStack* create_array_stack(void) {
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    if (!stack) return NULL;
    stack->top = -1;
    return stack;
}

void destroy_array_stack(ArrayStack* stack) {
    free(stack);
}

bool array_push(ArrayStack* stack, int value) {
    if (!stack || stack->top >= ARRAY_STACK_CAPACITY - 1)
        return false;
    stack->data[++stack->top] = value;
    return true;
}

int array_pop(ArrayStack* stack) {
    if (!stack || stack->top < 0) {
        fprintf(stderr, "Ошибка: pop из пустого массивного стека\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

int array_peek(const ArrayStack* stack) {
    if (!stack || stack->top < 0) {
        fprintf(stderr, "Ошибка: peek на пустом массивном стеке\n");
        exit(1);
    }
    return stack->data[stack->top];
}

bool array_is_empty(const ArrayStack* stack) {
    return stack == NULL || stack->top == -1;
}

int array_size(const ArrayStack* stack) {
    return stack ? stack->top + 1 : 0;
}