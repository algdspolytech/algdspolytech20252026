#include <stdio.h>
#include <stdlib.h>
#include "Ah.h"

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable: 4996)

#define MAX 100

void CreateAS(arr_stack* a) {
    a->top = -1; // Пустой стек
}

node_stack* CreateNS(int value) {
    node_stack* node = (node_stack*)malloc(sizeof(node_stack));
    node->value = value;
    node->next = NULL;
    return node;
}


int isASempty(arr_stack* a) {
    if (a->top == -1) {
        return 1;
    }
    return 0;
}

void pushAS(arr_stack* a, int value) {
    a->top++;
    a->elements[a->top] = value;
}

void pushNS(node_stack** b, int value) {
    node_stack* new_node = CreateNS(value);
    if (new_node == NULL) {
        return;
    }
    new_node->next = *b;
    *b = new_node;
}

int popAS(arr_stack* a) {
    int value;
    if (isASempty(a) == 1) {
        return -1; // Ошибка, стек пуст
    }
    else {
        value = a->elements[a->top];
        a->top--;
        return value;
    }
}

int popNS(node_stack** b) {
    if (*b == NULL) {
        return -1; // Ошибка, стек пуст
    }
    node_stack* temp = *b;
    int value = temp->value;
    *b = (*b)->next;
    free(temp);
    return value;
}

void printAS(arr_stack* a) {
    if (isASempty(a)) {
        printf("Массив-Стек пуст\n");
        return;
    }
    printf("Массив-Стек: ");
    for (int i = 0; i <= a->top; i++) {
        printf("%i ", a->elements[i]);
    }
    printf("\n");
}

void printNS(node_stack* b) {
    if (b == NULL) {
        printf("Список-Стек пуст\n");
        return;
    }
    printf("Список-Стек: ");
    node_stack* current = b;
    while (current != NULL) {
        printf("%i ", current->value);
        current = current->next;
    }
    printf("\n");
}

void freeNS(node_stack** b) {
    while (*b != NULL) {
        node_stack* temp = *b;
        *b = (*b)->next;
        free(temp);
    }
}
