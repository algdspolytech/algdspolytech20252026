#pragma once

#define ELEM_IN_ARR 4

typedef struct node_ {
	struct node_* next;
	int data[ELEM_IN_ARR];
	int filled_num;
} node;

typedef struct {
	node* head;
} UnrolledList;

#ifdef __cplusplus
extern "C" {
#endif

	node* create_node();
	void add_to_list(UnrolledList* list, int x);
	int count_elem(UnrolledList* list);
	int num_by_key(UnrolledList* list, int key);
	int delete_by_num(UnrolledList* list, int num);
	int elem_by_num(UnrolledList* list, int num);
	int next_by_num(UnrolledList* list, int num);

#ifdef __cplusplus
}
#endif