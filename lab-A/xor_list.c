#include "xor_list.h"

Node* xor_ptr(Node* a, Node* b) {
    return (Node*)((uintptr_t)a ^ (uintptr_t)b);
}

void init_list(XORList* list) {
    list->head = NULL;
    list->tail = NULL;
}

void insert(XORList* list, const char* str) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        perror("malloc failed");
        exit(1);
    }

    new_node->data = _strdup(str);
    if (!new_node->data) {
        perror("strdup failed");
        free(new_node);
        exit(1);
    }

    new_node->link = (uintptr_t)list->head;

    if (list->head != NULL) {
        list->head->link ^= (uintptr_t)new_node;
    }
    else {
        list->tail = new_node;
    }

    list->head = new_node;
}

Node* find(XORList* list, const char* key) {
    Node* prev = NULL;
    Node* current = list->head;

    while (current != NULL) {
        if (strcmp(current->data, key) == 0) {
            return current;
        }
        Node* next = xor_ptr(prev, (Node*)current->link);
        prev = current;
        current = next;
    }
    return NULL;
}

void remove_by_key(XORList* list, const char* key) {
    Node* to_remove = find(list, key);
    if (to_remove == NULL) {
        return;
    }
    remove_by_ptr(list, to_remove);
}

void remove_by_ptr(XORList* list, Node* to_remove) {
    if (to_remove == NULL) {
        return;
    }

    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;

    while (current != NULL && current != to_remove) {
        next = xor_ptr(prev, (Node*)current->link);
        prev = current;
        current = next;
    }

    if (current != to_remove) {
        return;
    }

    next = xor_ptr(prev, (Node*)current->link);

    if (prev != NULL) {
        prev->link ^= (uintptr_t)current ^ (uintptr_t)next;
    }
    else {
        list->head = next;
    }

    if (next != NULL) {
        next->link ^= (uintptr_t)current ^ (uintptr_t)prev;
    }
    else {
        list->tail = prev;
    }

    free(to_remove->data);
    free(to_remove);
}

void iterate(XORList* list) {
    Node* prev = NULL;
    Node* current = list->head;

    while (current != NULL) {
        printf("%s\n", current->data);
        Node* next = xor_ptr(prev, (Node*)current->link);
        prev = current;
        current = next;
    }
}

void free_list(XORList* list) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next;

    while (current != NULL) {
        next = xor_ptr(prev, (Node*)current->link);
        free(current->data);
        free(current);
        prev = current;
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}