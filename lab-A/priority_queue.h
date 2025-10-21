#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} PriorityQueue;

// Инициализация очереди
PriorityQueue* pq_create();

// Добавление элемента с приоритетом
void pq_enqueue(PriorityQueue* pq, int data, int priority);

// Извлечение элемента с наивысшим приоритетом
int pq_dequeue(PriorityQueue* pq);

// Просмотр элемента с наивысшим приоритетом без извлечения
int pq_peek(PriorityQueue* pq);

// Проверка на пустоту
int pq_is_empty(PriorityQueue* pq);

// Получение размера очереди
int pq_size(PriorityQueue* pq);

// Очистка очереди
void pq_clear(PriorityQueue* pq);

// Освобождение памяти
void pq_destroy(PriorityQueue* pq);

// Безопасная функция для тестирования - возвращает массив данных
int* pq_to_array(PriorityQueue* pq, int* size);

#endif