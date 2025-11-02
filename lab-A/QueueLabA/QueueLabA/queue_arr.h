#pragma once
#include<stdlib.h>
#include<stdio.h>

typedef struct QueueArray QueueArray;

QueueArray* create_queue_array(int capacity);


int is_empty_array(QueueArray* queue);


int is_full_array(QueueArray* queue);


int size_array(QueueArray* queue);


int peak_array(QueueArray* queue, int* status);


void enqueue_array(QueueArray* queue, int value, int* status);


int dequeue_array(QueueArray* queue, int* status);


void destroy_queue_array(QueueArray* queue);
