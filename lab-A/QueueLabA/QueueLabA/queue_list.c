#include<stdio.h>
#include<stdlib.h>
#include"queue_list.h"
typedef struct Node {
	int value;
	Node* next;
};
typedef struct QueueList {
	int size;
	Node* head;
	Node* tail;

};

QueueList* create_queue_list() {
	QueueList* queue = malloc(sizeof(QueueList));
	if (!queue) {
		return NULL;
	}

	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;


	return queue;
}

int is_empty(QueueList* queue) {
	return (queue->size == 0);
}

int peak(QueueList* queue, int* status) {
	if (is_empty(queue)) {
		*status = 0;
		return 0;
	
	}

	*status = 1;
	return queue->head->value;
	
}

void enqueue(QueueList* queue, int value) {

	Node* new_node = malloc(sizeof(Node));
	if (!new_node) {
		return;
	}
	new_node->value = value;
	new_node->next = NULL;

	if (is_empty(queue)) {

		queue->head = new_node;
		queue->tail = new_node;
		
	}
	else {
		queue->tail->next = new_node;
		queue->tail = new_node;
	}
	queue->size++;
}


int dequeue(QueueList* queue, int* status) {

	if (is_empty(queue)) {
		*status = 0;
		return 0;
	}
	
	*status = 1;

	Node* dequeued_node = queue->head;
	
	if (queue->size == 1) {
		queue->head = NULL;
		queue->tail = NULL;
	}else {
		queue->head = queue->head->next;
	}
	


	int value = dequeued_node->value;

	free(dequeued_node);

	queue->size--;

	return value;
		

	

}




void destroy_queue(QueueList* queue) {

	Node* current_node = queue->head;

	

	while (current_node != NULL) {

		Node* to_delete = current_node;

		

		current_node = current_node->next;

		free(to_delete);
		queue->size--;
	}
	free(queue);

}


int size(QueueList* queue) {
	return queue->size;
}