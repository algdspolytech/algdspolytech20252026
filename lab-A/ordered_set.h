#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    size_t size;
} OrderedSet;

typedef struct {
    Node* current;
} SetIterator;

OrderedSet* set_create();
void set_destroy(OrderedSet* set);
void set_clear(OrderedSet* set);

bool set_add(OrderedSet* set, int value);
bool set_remove(OrderedSet* set, int value);
bool set_contains(const OrderedSet* set, int value);

OrderedSet* set_union(const OrderedSet* set1, const OrderedSet* set2);
OrderedSet* set_intersection(const OrderedSet* set1, const OrderedSet* set2);

bool set_is_empty(const OrderedSet* set);
size_t set_size(const OrderedSet* set);
void set_print(const OrderedSet* set);

SetIterator set_iterator_begin(const OrderedSet* set);
bool set_iterator_has_next(const SetIterator* it);
int set_iterator_next(SetIterator* it);

#endif
