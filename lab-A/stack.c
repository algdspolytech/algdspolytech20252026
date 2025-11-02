#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// Реализация стека на основе связанного списка
void createListStack(ListStack* stack) {
    if (stack == NULL) return;
    stack->top = NULL;
    stack->size = 0;
}

void pushListStack(ListStack* stack, int value) {
    if (stack == NULL) {
        printf("Ошибка: стек не инициализирован\n");
        return;
    }
    
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("Ошибка: не удалось выделить память для нового узла\n");
        return;
    }
    
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

int popListStack(ListStack* stack) {
    if (stack == NULL || stack->top == NULL) {
        printf("Ошибка: стек пуст\n");
        return -1;
    }
    
    ListNode* temp = stack->top;
    int poppedValue = temp->data;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
    
    return poppedValue;
}

int peekListStack(ListStack* stack) {
    if (stack == NULL || stack->top == NULL) {
        printf("Ошибка: стек пуст\n");
        return -1;
    }
    return stack->top->data;
}

// Реализация стека на основе массива
void createArrayStack(ArrayStack* stack) {
    if (stack == NULL) return;
    stack->top = -1;
}

void pushArrayStack(ArrayStack* stack, int value) {
    if (stack == NULL) {
        printf("Ошибка: стек не инициализирован\n");
        return;
    }
    
    if (stack->top >= MAX_STACK_SIZE - 1) {
        printf("Ошибка: стек переполнен\n");
        return;
    }
    
    stack->top++;
    stack->data[stack->top] = value;
}

int popArrayStack(ArrayStack* stack) {
    if (stack == NULL || stack->top == -1) {
        printf("Ошибка: стек пуст\n");
        return -1;
    }
    
    return stack->data[stack->top--];
}

int peekArrayStack(ArrayStack* stack) {
    if (stack == NULL || stack->top == -1) {
        printf("Ошибка: стек пуст\n");
        return -1;
    }
    return stack->data[stack->top];
}
