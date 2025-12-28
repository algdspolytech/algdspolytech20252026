#include "set.h"
#include <stdlib.h>

Set* set_create(void) {
    Set* set = malloc(sizeof(Set));
    if (!set) return NULL;
    set->head = NULL;
    return set;
}

void set_destroy(Set* set) {
    if (!set) return;
    SetNode* cur = set->head;
    while (cur) {
        SetNode* tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    free(set);
}

bool set_contains(const Set* set, int value) {
    if (!set) return false;
    SetNode* cur = set->head;
    while (cur && cur->value < value)
        cur = cur->next;
    return cur && cur->value == value;
}

bool set_add(Set* set, int value) {
    if (!set) return false;

    SetNode** cur = &set->head;
    while (*cur && (*cur)->value < value)
        cur = &(*cur)->next;

    if (*cur && (*cur)->value == value)
        return false; // дубликат

    SetNode* node = malloc(sizeof(SetNode));
    if (!node) return false;

    node->value = value;
    node->next = *cur;
    *cur = node;
    return true;
}

bool set_remove(Set* set, int value) {
    if (!set) return false;

    SetNode** cur = &set->head;
    while (*cur && (*cur)->value < value)
        cur = &(*cur)->next;

    if (!*cur || (*cur)->value != value)
        return false;

    SetNode* tmp = *cur;
    *cur = tmp->next;
    free(tmp);
    return true;
}

Set* set_union(const Set* a, const Set* b) {
    if (!a || !b) return NULL;
    Set* res = set_create();
    if (!res) return NULL;

    SetNode* pa = a->head;
    SetNode* pb = b->head;

    while (pa || pb) {
        if (!pb || (pa && pa->value < pb->value)) {
            set_add(res, pa->value);
            pa = pa->next;
        }
        else if (!pa || pb->value < pa->value) {
            set_add(res, pb->value);
            pb = pb->next;
        }
        else {
            set_add(res, pa->value);
            pa = pa->next;
            pb = pb->next;
        }
    }
    return res;
}

Set* set_intersection(const Set* a, const Set* b) {
    if (!a || !b) return NULL;
    Set* res = set_create();
    if (!res) return NULL;

    SetNode* pa = a->head;
    SetNode* pb = b->head;

    while (pa && pb) {
        if (pa->value < pb->value)
            pa = pa->next;
        else if (pb->value < pa->value)
            pb = pb->next;
        else {
            set_add(res, pa->value);
            pa = pa->next;
            pb = pb->next;
        }
    }
    return res;
}
