#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

// Структура узла очереди
typedef struct Node {
    int data;
    int priority;
    struct Node* next;
    struct Node* prev;
} Node;

// Структура очереди
typedef struct PriorityQueue {
    Node* head;
} PriorityQueue;

// Инициализация очереди
void initPriorityQueue(PriorityQueue* pq);

// Добавление элемента с приоритетом
void enqueue(PriorityQueue* pq, int data, int priority);

// Извлечение элемента с максимальным приоритетом
// Возвращает значение и статус (1 - успешно, 0 - очередь пуста)
int dequeue(PriorityQueue* pq, int* data);

// Очистка очереди
void clearQueue(PriorityQueue* pq);

// Проверка, пуста ли очередь
int isEmpty(PriorityQueue* pq);

#endif
