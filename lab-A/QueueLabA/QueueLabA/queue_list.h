#pragma once


typedef struct Node Node;
typedef struct QueueList QueueList;

QueueList* create_queue_list();

void enqueue(QueueList* queue, int value);


int dequeue(QueueList* queue, int* status);


int peak(QueueList* queue, int* status);


int is_empty(QueueList* queue);


void destroy_queue(QueueList* queue);


int size(QueueList* queue);
