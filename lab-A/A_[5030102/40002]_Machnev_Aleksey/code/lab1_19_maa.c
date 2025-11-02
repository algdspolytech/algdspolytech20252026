#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct Node* create_node(const char *str) {
    if (str == NULL) return NULL;
    
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = (char*)malloc(strlen(str) + 1);
    strcpy(new_node->data, str);
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void add_to_list(struct Node **head, struct Node **tail, const char *str) {
    if (str == NULL) return;
    
    struct Node *new_node = create_node(str);
    if (!new_node) return;
    
    if (*head == NULL) {
        *head = new_node;
        *tail = new_node;
    } else {
        (*tail)->next = new_node;
        new_node->prev = *tail;
        *tail = new_node;
    }
}

void split_list(struct Node *source, struct Node **front, struct Node **back) {
    if (source == NULL || source->next == NULL) {
        *front = source;
        *back = NULL;
        return;
    }
    
    struct Node *slow = source;
    struct Node *fast = source->next;
    
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    
    *front = source;
    *back = slow->next;
    slow->next = NULL;
    if (*back != NULL) {
        (*back)->prev = NULL;
    }
}

struct Node* merge_sorted(struct Node *a, struct Node *b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    
    struct Node *result = NULL;
    
    if (strcmp(a->data, b->data) <= 0) {
        result = a;
        result->next = merge_sorted(a->next, b);
    } else {
        result = b;
        result->next = merge_sorted(a, b->next);
    }
    
    if (result->next != NULL) {
        result->next->prev = result;
    }
    
    return result;
}

void sort_list(struct Node **head) {
    struct Node *h = *head;
    if (h == NULL || h->next == NULL) return;
    
    struct Node *a, *b;
    split_list(h, &a, &b);
    sort_list(&a);
    sort_list(&b);
    *head = merge_sorted(a, b);
    
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) printf(" -> ");
        current = current->next;
    }
    printf("\n");
}

void free_list(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

// Вспомогательные функции для тестов
struct Node* get_tail(struct Node *head) {
    if (head == NULL) return NULL;
    struct Node *current = head;
    while (current->next != NULL) current = current->next;
    return current;
}

int list_size(struct Node *head) {
    int count = 0;
    struct Node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int is_sorted(struct Node *head) {
    if (head == NULL || head->next == NULL) return 1;
    
    struct Node *current = head;
    while (current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

char* get_node_data(struct Node *head, int index) {
    if (head == NULL || index < 0) return NULL;
    
    struct Node *current = head;
    int i = 0;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }
    
    return (current != NULL) ? current->data : NULL;
}

int main() {
    struct Node *head = NULL;
    struct Node *tail = NULL;
    
    add_to_list(&head, &tail, "orange");
    add_to_list(&head, &tail, "apple");
    add_to_list(&head, &tail, "banana");
    add_to_list(&head, &tail, "grape");
    add_to_list(&head, &tail, "cherry");
    
    printf("Original list:\n");
    print_list(head);
    
    sort_list(&head);
    
    printf("\nSorted list:\n");
    print_list(head);
    
    free_list(head);
    return 0;
}