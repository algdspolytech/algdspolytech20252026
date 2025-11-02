#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

// 1. Для массива(●'◡'●)

// 1.1 Описание структуры очереди
typedef struct {
  int items[SIZE];
  int front;
  int rear;
} Queue;

// 1.2 Добавляем "начало" и "конец"
void initializeQueue(Queue* q) {
  q->front = -1;
  q->rear = 0;
}

// 1.3 Проверка очереди на пустоту и заполненность
bool isEmpty(Queue* q) { return (q->front == q->rear - 1); }

bool isFull(Queue* q) { return (q->rear == SIZE); }

// 1.4 Добавление элемента в очередь
void enqueue(Queue* q, int add) {
  if (isFull(q)) {
    fprintf(stderr, "Queue is full\n");
    return;
  }
  q->items[q->rear] = add;
  q->rear++;
}

// 1.5 Удаление элемента из очереди
int dequeue(Queue* q) {
  if (isEmpty(q)) {
    fprintf(stderr, "Queue is empty\n");
    return -1;
  }
  q->front++;
  return q->items[q->front];
}

// 1.6 Смотрим на первый элемент очереди
int peek(Queue* q) {
  if (isEmpty(q)) {
    fprintf(stderr, "Queue is empty\n");
    return -1;
  }
  return q->items[q->front + 1];
}

// 2. Для связного списка😺☆

// 2.1 Описание структуры списка
typedef struct Node {
  int value;
  struct Node* next;
} Node;

// 2.2 Очередь
typedef struct QueueList {
  Node* front;
  Node* rear;
} QueueList;

// 2.3 Проверка на пустоту
bool isEmptyList(QueueList* q) { return q->front == NULL; }

// 2.3 Добавление нового узла
Node* newNode(int value) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->value = value;
  node->next = NULL;
  return node;
}

// 2.4 Добавление эллемента
void enqueueList(QueueList* q, int add) {
  Node* node = newNode(add);
  if (isEmptyList(q)) {
    q->front = node;
    q->rear = node;
  } else {
    q->rear->next = node;
    q->rear = node;
  }
}

// 2.5 Удаление элемента
int dequeueList(QueueList* q) {
  if (isEmptyList(q)) {
    fprintf(stderr, "Queue is empty\n");
    return -1;
  }
  Node* temp = q->front;
  int value = temp->value;
  q->front = q->front->next;

  if (q->front == NULL) {
    q->rear = NULL;
  }
  free(temp);
  return value;
}

// 2.6 Смотрим на первый элемент очереди
int peekList(QueueList* q) {
  if (isEmptyList(q)) {
    fprintf(stderr, "Queue is empty\n");
    return -1;
  }
  return q->front->value;
}