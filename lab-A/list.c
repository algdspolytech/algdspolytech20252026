#include <stdlib.h>
#include "list.h"

Block* create_block() {
    Block* block = malloc(sizeof(Block));
    block->next = NULL;
    block->size = 0;
    return block;
}

void list_insert(UnrolledList* list, int value) {
    if (list->head == NULL) {
        list->head = create_block();
    }

    Block* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }

    if (current->size < BLOCK_CAPACITY) {
        current->data[current->size] = value;
        current->size++;
    }
    else {
        Block* new_block = create_block();
        new_block->data[0] = value;
        new_block->size = 1;
        current->next = new_block;
    }
}

int list_size(UnrolledList* list) {
    if (list == NULL || list->head == NULL) {
        return 0;
    }

    int total = 0;
    Block* current = list->head;
    while (current != NULL) {
        total += current->size;
        current = current->next;
    }
    return total;
}

int list_find_index(UnrolledList* list, int key) {
    Block* current = list->head;
    int index = 0;

    while (current != NULL) {
        for (int i = 0; i < current->size; i++) {
            if (current->data[i] == key) {
                return index;
            }
            index++;
        }
        current = current->next;
    }
    return -1;
}

int list_get_at(UnrolledList* list, int position) {
    int total = list_size(list);
    if (position < 0 || position >= total) {
        return -1;
    }

    Block* current = list->head;
    int remaining = position;

    while (remaining >= current->size) {
        remaining -= current->size;
        current = current->next;
    }

    return current->data[remaining];
}

int list_remove_at(UnrolledList* list, int position) {
    int total = list_size(list);
    if (position < 0 || position >= total) {
        return -1;
    }

    Block* current = list->head;
    Block* prev = NULL;
    int remaining = position;

    while (remaining >= current->size) {
        remaining -= current->size;
        prev = current;
        current = current->next;
    }

    int removed_value = current->data[remaining];

    for (int i = remaining; i < current->size - 1; i++) {
        current->data[i] = current->data[i + 1];
    }

    current->size--;

    if (current->size == 0) {
        if (prev == NULL) {
            list->head = current->next;
        }
        else {
            prev->next = current->next;
        }
        free(current);
    }

    return removed_value;
}

int list_get_next(UnrolledList* list, int position) {
    int total = list_size(list);
    if (position < 0 || position >= total - 1) {
        return -1;
    }
    return list_get_at(list, position + 1);
}
