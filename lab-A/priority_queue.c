#include "priority_queue.h"
#include <stdlib.h>

PriorityQueue* pq_create() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (pq) {
        pq->head = NULL;
        pq->size = 0;
    }
    return pq;
}

void pq_enqueue(PriorityQueue* pq, int data, int priority) {
    if (!pq) return;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;

    new_node->data = data;
    new_node->priority = priority;
    new_node->next = NULL;

    if (pq_is_empty(pq) || priority > pq->head->priority) {
        new_node->next = pq->head;
        pq->head = new_node;
    }
    else {
        Node* current = pq->head;
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    pq->size++;
}

int pq_dequeue(PriorityQueue* pq) {
    if (pq_is_empty(pq)) {
        return -1;
    }

    Node* temp = pq->head;
    int data = temp->data;
    pq->head = pq->head->next;
    free(temp);
    pq->size--;
    return data;
}

int pq_peek(PriorityQueue* pq) {
    if (pq_is_empty(pq)) {
        return -1;
    }
    return pq->head->data;
}

int pq_is_empty(PriorityQueue* pq) {
    return pq == NULL || pq->head == NULL;
}

int pq_size(PriorityQueue* pq) {
    return pq ? pq->size : 0;
}

void pq_clear(PriorityQueue* pq) {
    if (!pq) return;

    while (!pq_is_empty(pq)) {
        pq_dequeue(pq);
    }
}

void pq_destroy(PriorityQueue* pq) {
    if (pq) {
        pq_clear(pq);
        free(pq);
    }
}

int* pq_to_array(PriorityQueue* pq, int* size) {
    if (!pq || pq_is_empty(pq)) {
        if (size) *size = 0;
        return NULL;
    }

    int* result = (int*)malloc(pq->size * sizeof(int));
    if (!result) {
        if (size) *size = 0;
        return NULL;
    }

    Node* current = pq->head;
    int i = 0;
    while (current != NULL && i < pq->size) {
        result[i++] = current->data;
        current = current->next;
    }

    if (size) *size = pq->size;
    return result;
}