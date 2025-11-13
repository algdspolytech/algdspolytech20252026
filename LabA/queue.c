#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Q* newNode(int v, int p) {
  Q* node = (Q*)malloc(sizeof(Q));
  if (!node) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }
  node->val = v;
  node->priority = p;
  node->next = NULL;
  return node;
}

void insert(Q** head, int v, int p) {
  Q* start = *head;
  Q* node = newNode(v, p);

  if (*head == NULL || (*head)->priority > p) {
    node->next = *head;
    *head = node;
  } else {
    while (start->next != NULL && start->next->priority <= p) {
      start = start->next;
    }
    node->next = start->next;
    start->next = node;
  }
}

void dequeue(Q** head) {
  if (*head == NULL) {
    return;
  }
  Q* temp = *head;
  *head = (*head)->next;
  free(temp);
}

int peek(Q* head) {
  if (head == NULL) {
    return -1;
  }
  return head->val;
}

int isEmpty(Q* head) {
  return head == NULL;
}
