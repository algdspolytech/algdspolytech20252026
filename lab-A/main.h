#pragma once

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

	// ----------- STRUCTURES -----------

	typedef struct Node
	{
		double data;
		struct Node* next;
	} Node;

	typedef struct
	{
		Node* first;
		Node* last;
	} LinkedListQueue;

	typedef struct
	{
		double* arr;
		int capacity;
		int first;
		int last;
		int size;
	} ArrayQueue;

	// ----------- FUNCTIONS -----------

	// initialization a linked list queue
	void create_linked_list(LinkedListQueue* queue);

	// add some value to the linked list queue
	void add_linked_list(LinkedListQueue* queue, double value);

	// delete value from the linked list queue
	double del_linked_list(LinkedListQueue* queue);

	// displaying the linked list queue
	void print_linked_list(LinkedListQueue* queue);

	// clearing the linked list queue
	void free_linked_list(LinkedListQueue* queue);


	// initialization an array queue 
	void create_array(ArrayQueue* queue, int capacity);

	// add some value to the array queue
	void add_array(ArrayQueue* queue, double value);

	// delete value from the array queue
	double del_array(ArrayQueue* queue);

	// displaying the array queue
	void print_array(ArrayQueue* queue);

	// clearing the array queue
	void free_array(ArrayQueue* queue);

#ifdef __cplusplus
}
#endif

#endif