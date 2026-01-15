#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "main.h"

// LinkedList

void create_linked_list(LinkedListQueue* queue)
{
	queue->first = NULL;
	queue->last = NULL;
}

void add_linked_list(LinkedListQueue* queue, double value)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL)
	{
		return;
	}

	new_node->data = value;
	new_node->next = NULL;

	if (queue->first == NULL)
	{
		queue->first = new_node;
		queue->last = new_node;
	}
	else
	{
		queue->last->next = new_node;
		queue->last = new_node;
	}
}

double del_linked_list(LinkedListQueue* queue)
{
	if (queue->first == NULL)
	{
		printf("The queue is empty, deletion can't be performed\n");
		return -1;
	}

	double value = queue->first->data;
	queue->first = queue->first->next;

	if (queue->first == NULL)
	{
		queue->last = NULL;
	}

	return value;
}

void print_linked_list(LinkedListQueue* queue)
{
	Node* current_node = queue->first;

	while (current_node)
	{
		printf("%lf ", current_node->data);
		current_node = current_node->next;
	}

	printf("\n");
}

void free_linked_list(LinkedListQueue* queue)
{
	while (queue->first != NULL)
	{
		Node* current_node = queue->first;
		queue->first = queue->first->next;
		free(current_node);
	}

	queue->last = NULL;
}

// Array

void create_array(ArrayQueue* queue, int capacity)
{
	if (capacity <= 0)
	{
		printf("The capacity mustn't be negative\n");
		return;
	}

	queue->capacity = capacity;
	queue->arr = (double*)malloc(capacity * sizeof(double));
	queue->first = 0;
	queue->last = -1;
	queue->size = 0;
}

void add_array(ArrayQueue* queue, double value)
{
	if (queue->size == queue->capacity)
	{
		printf("The queue is full: capacity is %d\n", queue->capacity);
		return;
	}
	queue->last = (queue->last + 1) % queue->capacity;
	queue->arr[queue->last] = value;
	queue->size++;
}

double del_array(ArrayQueue* queue)
{
	if (!queue->size || queue->size == 0)
	{
		printf("The size of queue is 0, deletion can't be performed\n");
		return -1;
	}

	double value = queue->arr[queue->first];
	queue->first = (queue->first + 1) % queue->capacity;
	queue->size--;

	return value;
}

void print_array(ArrayQueue* queue)
{
	int index = queue->first;

	for (int i = 0; i < queue->size; i++)
	{
		printf("%lf ", queue->arr[index]);
		index = (index + 1) % queue->capacity;
	}

	printf("\n");
}

void free_array(ArrayQueue* queue)
{
	queue->arr = NULL;
	queue->capacity = 0;
	queue->first = 0;
	queue->last = -1;
	queue->size = 0;
}