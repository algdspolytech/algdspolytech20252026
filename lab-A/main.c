#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Реализация функций для очереди на связном списке
ListQueue* list_queue_create() {
    ListQueue* queue = (ListQueue*)malloc(sizeof(ListQueue));
    if (!queue) return NULL;

    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void list_queue_enqueue(ListQueue* queue, int value) {
    if (!queue) return;

    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) return;

    newNode->data = value;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

int list_queue_dequeue(ListQueue* queue) {
    if (!queue || list_queue_is_empty(queue)) {
        return -1;
    }

    ListNode* temp = queue->front;
    int value = temp->data;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;
    return value;
}

int list_queue_peek(ListQueue* queue) {
    if (!queue || list_queue_is_empty(queue)) {
        return -1;
    }
    return queue->front->data;
}

bool list_queue_is_empty(ListQueue* queue) {
    return queue == NULL || queue->front == NULL;
}

int list_queue_size(ListQueue* queue) {
    return queue ? queue->size : 0;
}

void list_queue_destroy(ListQueue* queue) {
    if (!queue) return;

    while (!list_queue_is_empty(queue)) {
        list_queue_dequeue(queue);
    }
    free(queue);
}

// Реализация функций для очереди на массиве
ArrayQueue* array_queue_create(int capacity) {
    if (capacity <= 0) return NULL;

    ArrayQueue* queue = (ArrayQueue*)malloc(sizeof(ArrayQueue));
    if (!queue) return NULL;

    queue->data = (int*)malloc(capacity * sizeof(int));
    if (!queue->data) {
        free(queue);
        return NULL;
    }

    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->size = 0;
    return queue;
}

void array_queue_enqueue(ArrayQueue* queue, int value) {
    if (!queue || array_queue_is_full(queue)) {
        return;
    }

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->data[queue->rear] = value;
    queue->size++;
}

int array_queue_dequeue(ArrayQueue* queue) {
    if (!queue || array_queue_is_empty(queue)) {
        return -1;
    }

    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

int array_queue_peek(ArrayQueue* queue) {
    if (!queue || array_queue_is_empty(queue)) {
        return -1;
    }
    return queue->data[queue->front];
}

bool array_queue_is_empty(ArrayQueue* queue) {
    return queue == NULL || queue->size == 0;
}

bool array_queue_is_full(ArrayQueue* queue) {
    return queue && queue->size == queue->capacity;
}

int array_queue_size(ArrayQueue* queue) {
    return queue ? queue->size : 0;
}

void array_queue_destroy(ArrayQueue* queue) {
    if (!queue) return;

    free(queue->data);
    free(queue);
}

// Демонстрационная программа
void demonstrate_list_queue() {
    printf("=== Демонстрация очереди на связном списке ===\n");

    ListQueue* queue = list_queue_create();

    printf("Добавляем элементы: 10, 20, 30\n");
    list_queue_enqueue(queue, 10);
    list_queue_enqueue(queue, 20);
    list_queue_enqueue(queue, 30);

    printf("Размер очереди: %d\n", list_queue_size(queue));
    printf("Первый элемент: %d\n", list_queue_peek(queue));

    printf("Извлекаем элементы: ");
    while (!list_queue_is_empty(queue)) {
        printf("%d ", list_queue_dequeue(queue));
    }
    printf("\n");

    list_queue_destroy(queue);
}

void demonstrate_array_queue() {
    printf("\n=== Демонстрация очереди на массиве ===\n");

    ArrayQueue* queue = array_queue_create(5);

    printf("Добавляем элементы: 100, 200, 300, 400\n");
    array_queue_enqueue(queue, 100);
    array_queue_enqueue(queue, 200);
    array_queue_enqueue(queue, 300);
    array_queue_enqueue(queue, 400);

    printf("Размер очереди: %d\n", array_queue_size(queue));
    printf("Первый элемент: %d\n", array_queue_peek(queue));

    printf("Извлекаем два элемента: ");
    printf("%d ", array_queue_dequeue(queue));
    printf("%d ", array_queue_dequeue(queue));
    printf("\n");

    printf("Добавляем еще элементы: 500, 600\n");
    array_queue_enqueue(queue, 500);
    array_queue_enqueue(queue, 600);

    printf("Извлекаем оставшиеся элементы: ");
    while (!array_queue_is_empty(queue)) {
        printf("%d ", array_queue_dequeue(queue));
    }
    printf("\n");

    array_queue_destroy(queue);
}

void compare_implementations() {
    printf("\n=== Сравнение реализаций ===\n");

    printf("Очередь на связном списке:\n");
    printf("  Преимущества:\n");
    printf("  - Динамический размер (нет ограничений по емкости)\n");
    printf("  - Не требует предварительного выделения памяти\n");
    printf("  - Проще в реализации операций\n");
    printf("  Недостатки:\n");
    printf("  - Большие накладные расходы памяти (указатели)\n");
    printf("  - Медленнее доступ к элементам\n");
    printf("  - Фрагментация памяти\n");

    printf("\nОчередь на массиве:\n");
    printf("  Преимущества:\n");
    printf("  - Меньшие накладные расходы памяти\n");
    printf("  - Быстрый доступ к элементам\n");
    printf("  - Лучшая производительность кэша\n");
    printf("  Недостатки:\n");
    printf("  - Ограниченная емкость\n");
    printf("  - Сложность реализации циклического буфера\n");
    printf("  - Необходимость перераспределения памяти при расширении\n");
}

int main() {
    demonstrate_list_queue();
    demonstrate_array_queue();
    compare_implementations();
    return 0;
}