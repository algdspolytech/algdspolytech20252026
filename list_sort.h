#ifndef LIST_SORT_H
#define LIST_SORT_H

#include <stddef.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

Node* create_node(const char* str);
void free_list(Node* head);
Node* create_list(const char* arr[], size_t n);
int compare_lists(Node* a, Node* b);
void merge_sort(Node** head_ref);

#endif // LIST_SORT_H
