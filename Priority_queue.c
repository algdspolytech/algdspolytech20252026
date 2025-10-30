#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

void initPriorityQueue(PriorityQueue* pq) {
    pq->head = NULL;
}

void enqueue(PriorityQueue* pq, int data, int priority) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->priority = priority;
    new_node->next = NULL;
    new_node->prev = NULL;

    if (pq->head == NULL) {
        pq->head = new_node;
        return;
    }

    // Если новый приоритет больше, вставляем в начало
    if (priority > pq->head->priority) {
        new_node->next = pq->head;
        pq->head->prev = new_node;
        pq->head = new_node;
        return;
    }

    Node* current = pq->head;

    // Идем вперед, пока не найдем место для вставки
    while (current->next != NULL && current->next->priority >= priority) {
        // Если следующий элемент имеет такой же приоритет, идем дальше
        current = current->next;
    }

    // Вставка после current
    new_node->next = current->next;
    if (current->next != NULL) {
        current->next->prev = new_node;
    }
    current->next = new_node;
    new_node->prev = current;
}

int dequeue(PriorityQueue* pq, int* data) {
    if (pq->head == NULL) {
        return 0; // очередь пуста
    }
    // Максимальный приоритет у головы
    Node* max_node = pq->head;
    *data = max_node->data;

    pq->head = max_node->next;
    if (pq->head != NULL) {
        pq->head->prev = NULL;
    }
    free(max_node);
    return 1; // успешно
}

void clearQueue(PriorityQueue* pq) {
    Node* current = pq->head;
    while (current != NULL) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
    pq->head = NULL;
}

int isEmpty(PriorityQueue* pq) {
    return pq->head == NULL;
}