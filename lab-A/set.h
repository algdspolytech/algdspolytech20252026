#pragma once
#include <stdbool.h>

typedef struct SetNode {
    int value;
    struct SetNode* next;
} SetNode;

typedef struct {
    SetNode* head;
} Set;

Set* set_create(void);
void set_destroy(Set* set);

bool set_add(Set* set, int value);
bool set_remove(Set* set, int value);
bool set_contains(const Set* set, int value);

Set* set_union(const Set* a, const Set* b);
Set* set_intersection(const Set* a, const Set* b);
