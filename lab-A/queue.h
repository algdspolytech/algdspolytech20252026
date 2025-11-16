#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>

// Структура для узла связного списка
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// Структура для очереди на основе связного списка
typedef struct {
    ListNode* front;
    ListNode* rear;
    int size;
} ListQueue;

// Структура для очереди на основе массива
typedef struct {
    int* data;
    int front;
    int rear;
    int capacity;
    int size;
} ArrayQueue;

// Функции для очереди на основе связного списка
ListQueue* list_queue_create();
void list_queue_enqueue(ListQueue* queue, int value);
int list_queue_dequeue(ListQueue* queue);
int list_queue_peek(ListQueue* queue);
bool list_queue_is_empty(ListQueue* queue);
int list_queue_size(ListQueue* queue);
void list_queue_destroy(ListQueue* queue);

// Функции для очереди на основе массива
ArrayQueue* array_queue_create(int capacity);
void array_queue_enqueue(ArrayQueue* queue, int value);
int array_queue_dequeue(ArrayQueue* queue);
int array_queue_peek(ArrayQueue* queue);
bool array_queue_is_empty(ArrayQueue* queue);
bool array_queue_is_full(ArrayQueue* queue);
int array_queue_size(ArrayQueue* queue);
void array_queue_destroy(ArrayQueue* queue);

#endif