#include "unrolled_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

UnrolledList* unrolled_list_create() {
	UnrolledList* list = (UnrolledList*)malloc(sizeof(UnrolledList));
	if (!list) return NULL;

	list->head = NULL;
	list->tail = NULL;
	list->total_elements = 0;
	return list;
}

void unrolled_list_destroy(UnrolledList* list) {
	if (!list) return;

	UnrolledNode* current = list->head;
	while (current) {
		UnrolledNode* next = current->next;
		free(current);
		current = next;
	}
	free(list);
}

bool unrolled_list_add(UnrolledList* list, int value) {
	if (!list) return false;

	if (!list->tail) {
		UnrolledNode* new_node = (UnrolledNode*)malloc(sizeof(UnrolledNode));
		if (!new_node) return false;

		new_node->data[0] = value;
		new_node->count = 1;
		new_node->next = NULL;

		list->head = new_node;
		list->tail = new_node;
		list->total_elements = 1;
		return true;
	}

	if (list->tail->count < BLOCK_CAPACITY) {
		list->tail->data[list->tail->count] = value;
		list->tail->count++;
		list->total_elements++;
		return true;
	}

	UnrolledNode* new_node = (UnrolledNode*)malloc(sizeof(UnrolledNode));
	if (!new_node) return false;

	new_node->data[0] = value;
	new_node->count = 1;
	new_node->next = NULL;

	list->tail->next = new_node;
	list->tail = new_node;
	list->total_elements++;
	return true;
}

int unrolled_list_find_index(UnrolledList* list, int value) {
	if (!list || !list->head) return -1;

	UnrolledNode* current = list->head;
	int global_index = 0;

	while (current) {
		for (int i = 0; i < current->count; i++) {
			if (current->data[i] == value) {
				return global_index;
			}
			global_index++;
		}
		current = current->next;
	}

	return -1;
}

bool unrolled_list_get_at(UnrolledList* list, int index, int* result) {
	if (!list || !result || index < 0 || index >= list->total_elements) {
		return false;
	}

	UnrolledNode* current = list->head;
	int current_index = 0;

	while (current) {
		if (index < current_index + current->count) {
			int local_index = index - current_index;
			*result = current->data[local_index];
			return true;
		}
		current_index += current->count;
		current = current->next;
	}

	return false;
}

bool unrolled_list_remove_at(UnrolledList* list, int index) {
	if (!list || index < 0 || index >= list->total_elements) {
		return false;
	}

	UnrolledNode* current = list->head;
	UnrolledNode* prev = NULL;
	int current_index = 0;

	while (current) {
		if (index < current_index + current->count) {
			int local_index = index - current_index;

			for (int i = local_index; i < current->count - 1; i++) {
				current->data[i] = current->data[i + 1];
			}
			current->count--;
			list->total_elements--;

			if (current->count == 0) {
				if (prev) {
					prev->next = current->next;
				}
				else {
					list->head = current->next;
				}

				if (current == list->tail) {
					list->tail = prev;
				}

				free(current);
			}

			return true;
		}

		current_index += current->count;
		prev = current;
		current = current->next;
	}

	return false;
}

int unrolled_list_size(UnrolledList* list) {
	return list ? list->total_elements : 0;
}

bool unrolled_list_get_next(UnrolledList* list, int value, int* next_value) {
	if (!list || !next_value) return false;

	UnrolledNode* current = list->head;

	while (current) {
		for (int i = 0; i < current->count; i++) {
			if (current->data[i] == value) {
				if (i + 1 < current->count) {
					*next_value = current->data[i + 1];
					return true;
				}
				else if (current->next && current->next->count > 0) {
					*next_value = current->next->data[0];
					return true;
				}
				else {
					return false;
				}
			}
		}
		current = current->next;
	}

	return false;
}

void unrolled_list_print(UnrolledList* list) {
	if (!list) {
		printf("List is NULL\n");
		return;
	}

	printf("Unrolled List (total elements: %d):\n", list->total_elements);

	UnrolledNode* current = list->head;
	int node_num = 1;

	while (current) {
		printf("  Node %d [%d/%d]: ", node_num, current->count, BLOCK_CAPACITY);
		for (int i = 0; i < current->count; i++) {
			printf("%d ", current->data[i]);
		}
		printf("\n");
		current = current->next;
		node_num++;
	}
}