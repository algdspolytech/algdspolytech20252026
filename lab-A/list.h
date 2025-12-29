#pragma once

#define BLOCK_CAPACITY 4

typedef struct Block {
    struct Block* next;
    int data[BLOCK_CAPACITY];
    int size;
} Block;

typedef struct {
    Block* head;
} UnrolledList;

#ifdef __cplusplus
extern "C" {
#endif

    Block* create_block();
    void list_insert(UnrolledList* list, int value);
    int list_size(UnrolledList* list);
    int list_find_index(UnrolledList* list, int key);
    int list_get_at(UnrolledList* list, int position);
    int list_remove_at(UnrolledList* list, int position);
    int list_get_next(UnrolledList* list, int position);

#ifdef __cplusplus
}
#endif
