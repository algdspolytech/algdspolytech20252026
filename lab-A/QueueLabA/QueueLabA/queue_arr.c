#include<stdlib.h>
#include<stdio.h>
#include"queue_arr.h"

typedef struct QueueArray {
	int* place;
	int capacity;
	int size;
	int first;
	int end;
} QueueArray;

QueueArray* create_queue_array(int capacity) {
	QueueArray* queue = malloc(sizeof(QueueArray));
	if (!queue) {
		return NULL;
	}
	queue->place =(int*) malloc(sizeof(int)*capacity);
	if(!queue->place){
		free(queue);
		return NULL;
	}
	queue->capacity = capacity;
	queue->first = 0;
	queue->end = 0;
	queue->size = 0;

	return queue;

}
int is_empty_array(QueueArray* queue) {
	return (queue->size == 0);
}
int is_full_array(QueueArray* queue) {
	return (queue->size == queue->capacity);
}
int size_array(QueueArray* queue) {
	return queue->size;
}
int peak_array(QueueArray* queue, int* status) {
	if (is_empty_array(queue)) {
		*status = 0;
		return 0;
	}
	*status = 1;
	return queue->place[queue->first];
}
void enqueue_array(QueueArray* queue, int value,int* status) {
	if (is_full_array(queue)) {
		*status = 0;
		return;
	}
	*status = 1;
	queue->place[queue->end] = value;
	queue->end = (queue->end + 1) % queue->capacity;
	queue->size++;
}
int dequeue_array(QueueArray* queue, int* status) {
	if (is_empty_array(queue)) {
		*status = 0;
		return 0;
	}
	int value = queue->place[queue->first];
	queue->first = (queue->first + 1) % queue->capacity;
	queue->size--;
	*status = 1;
	return value;
}
void destroy_queue_array(QueueArray* queue) {
	if (queue) {
		free(queue->place);
		free(queue);
	}
}