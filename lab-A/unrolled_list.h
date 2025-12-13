#pragma once
#ifndef UNROLLED_LIST_H
#define UNROLLED_LIST_H

#include <stdbool.h>

#define BLOCK_CAPACITY 4

typedef struct UnrolledNode {
	int data[BLOCK_CAPACITY];
	int count;               
	struct UnrolledNode* next;
} UnrolledNode;

typedef struct {
	UnrolledNode* head;      
	UnrolledNode* tail;        
	int total_elements;        
} UnrolledList;


UnrolledList* unrolled_list_create();


void unrolled_list_destroy(UnrolledList* list);


bool unrolled_list_add(UnrolledList* list, int value);

int unrolled_list_find_index(UnrolledList* list, int value);

bool unrolled_list_get_at(UnrolledList* list, int index, int* result);

bool unrolled_list_remove_at(UnrolledList* list, int index);

int unrolled_list_size(UnrolledList* list);

bool unrolled_list_get_next(UnrolledList* list, int value, int* next_value);

void unrolled_list_print(UnrolledList* list);

#endif