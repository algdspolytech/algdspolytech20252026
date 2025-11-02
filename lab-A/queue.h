#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#define SIZE 1000

#ifdef __cplusplus
extern "C" {
#endif

// Массив
typedef struct {
  int items[SIZE];
  int front;
  int rear;
} Queue;

void initializeQueue(Queue* q);
bool isEmpty(Queue* q);
bool isFull(Queue* q);
void enqueue(Queue* q, int add);
int dequeue(Queue* q);
int peek(Queue* q);

// Связной список
typedef struct Node {
  int value;
  struct Node* next;
} Node;

typedef struct {
  Node* front;
  Node* rear;
} QueueList;

bool isEmptyList(QueueList* q);
Node* newNode(int value);
void enqueueList(QueueList* q, int add);
int dequeueList(QueueList* q);
int peekList(QueueList* q);

#ifdef __cplusplus
}
#endif

#endif
