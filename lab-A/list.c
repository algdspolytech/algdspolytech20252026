#include "list.h"

LinkedList* create_list(void) {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->total_length = 0;
    return list;
}

void free_list(LinkedList* list) {
    if (!list) return;

    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

void append_string(LinkedList* list, const char* str) {
    if (!list || !str) return;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;

    size_t len = strlen(str) + 1;
    new_node->data = (char*)malloc(len);
    if (!new_node->data) {
        free(new_node);
        return;
    }
    memcpy(new_node->data, str, len);

    new_node->next = NULL;
    list->total_length += strlen(str);

    if (!list->head) {
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

char* concatenate_strings(LinkedList* list) {
    if (!list || !list->head) {
        char* empty_string = (char*)malloc(1);
        if (empty_string) empty_string[0] = '\0';
        return empty_string;
    }

    char* result = (char*)malloc(list->total_length + 1);
    if (!result) return NULL;

    char* current_pos = result;
    Node* current_node = list->head;

    while (current_node != NULL) {
        size_t len = strlen(current_node->data);
        memcpy(current_pos, current_node->data, len);
        current_pos += len;
        current_node = current_node->next;
    }

    *current_pos = '\0';
    return result;
}

size_t get_total_length(LinkedList* list) {
    return list ? list->total_length : 0;
}
