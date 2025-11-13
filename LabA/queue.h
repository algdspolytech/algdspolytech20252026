#ifndef QUEUE_H
#define QUEUE_H

typedef struct Q {
  int val;
  int priority;
  struct Q* next;
} Q;

void insert(Q** head, int val, int priority);
void dequeue(Q** head);
int peek(Q* head);
int isEmpty(Q* head);

#endif  // QUEUE_H
