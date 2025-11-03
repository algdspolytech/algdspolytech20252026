#include "stack.h"

// ---------- Реализация стека на связном списке ----------

void initStackList(StackList* s) {
    s->top = NULL;
}

int isEmptyList(StackList* s) {
    return s->top == NULL;
}

void pushList(StackList* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int popList(StackList* s) {
    if (isEmptyList(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    Node* temp = s->top;
    int value = temp->data;
    s->top = temp->next;
    free(temp);
    return value;
}

int peekList(StackList* s) {
    if (isEmptyList(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    return s->top->data;
}

void clearStackList(StackList* s) {
    while (!isEmptyList(s)) {
        popList(s);
    }
}

// ---------- Реализация стека на массиве ----------

void initStackArray(StackArray* s) {
    s->top = -1;
}

int isEmptyArray(StackArray* s) {
    return s->top == -1;
}

int isFullArray(StackArray* s) {
    return s->top == MAX_SIZE - 1;
}

void pushArray(StackArray* s, int value) {
    if (isFullArray(s)) {
        fprintf(stderr, "Stack overflow\n");
        exit(1);
    }
    s->data[++s->top] = value;
}

int popArray(StackArray* s) {
    if (isEmptyArray(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(1);
    }
    return s->data[s->top--];
}

int peekArray(StackArray* s) {
    if (isEmptyArray(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    return s->data[s->top];
}
