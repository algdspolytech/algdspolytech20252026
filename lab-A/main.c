#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct Yzel {
    int data;
    struct Yzel *next;
} Yzel;

typedef struct {
    Yzel *nachalo;
    Yzel *konec;
} Ochered;

void newochered(Ochered *q) {
    q->nachalo = NULL;
    q->konec = NULL;
}

int emptyList(Ochered *q) {
    return q->nachalo == NULL;
}

void enqueueList(Ochered *q, int value) {
    Yzel *newNode = (Yzel *) malloc(sizeof(Yzel));
    if (newNode == NULL) return;
    newNode->data = value;
    newNode->next = NULL;

    if (q->konec == NULL) {
        q->nachalo = q->konec = newNode;
        return;
    }

    q->konec->next = newNode;
    q->konec = newNode;
}

int dequeueList(Ochered *q, int *value) {
    if (emptyList(q)) return 0;
    Yzel *temp = q->nachalo;
    *value = temp->data;
    q->nachalo = q->nachalo->next;
    if (q->nachalo == NULL) q->konec = NULL;
    free(temp);
    return 1;
}

void freeQueueList(Ochered *q) {
    int temp;
    while (dequeueList(q, &temp)) {
    }
}

// очередь на массиве
typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
    int size;
} QueueArray;

void initQueueArray(QueueArray *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

int isEmptyArray(QueueArray *q) {
    return q->size == 0;
}

int isFullArray(QueueArray *q) {
    return q->size == MAX_SIZE;
}

int newElement(QueueArray *q, int value) {
    if (isFullArray(q)) return 0;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = value;
    q->size++;
    return 1;
}

int deliteElement(QueueArray *q, int *value) {
    if (isEmptyArray(q)) return 0;
    *value = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return 1;
}