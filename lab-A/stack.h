#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

// ================================
// Реализация через связный список
// ================================

typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* top;
    int size;
} ListStack;

ListStack* create_list_stack(void);
void destroy_list_stack(ListStack* stack);
bool list_push(ListStack* stack, int value);
int list_pop(ListStack* stack);
int list_peek(const ListStack* stack);
bool list_is_empty(const ListStack* stack);
int list_size(const ListStack* stack);

// ================================
// Реализация через массив
// ================================

#define ARRAY_STACK_CAPACITY 100

typedef struct {
    int data[ARRAY_STACK_CAPACITY];
    int top;
} ArrayStack;

ArrayStack* create_array_stack(void);
void destroy_array_stack(ArrayStack* stack);
bool array_push(ArrayStack* stack, int value);
int array_pop(ArrayStack* stack);
int array_peek(const ArrayStack* stack);
bool array_is_empty(const ArrayStack* stack);
int array_size(const ArrayStack* stack);

#endif // STACK_H