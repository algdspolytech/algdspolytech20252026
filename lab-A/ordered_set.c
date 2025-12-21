#include "ordered_set.h"
#include <stdio.h>
#include <stdlib.h>

static Node* node_create(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node) {
        node->data = value;
        node->next = NULL;
    }
    return node;
}

OrderedSet* set_create() {
    OrderedSet* set = (OrderedSet*)malloc(sizeof(OrderedSet));
    if (set) {
        set->head = NULL;
        set->size = 0;
    }
    return set;
}

void set_destroy(OrderedSet* set) {
    if (!set) return;
    set_clear(set);
    free(set);
}

void set_clear(OrderedSet* set) {
    if (!set) return;
    
    Node* current = set->head;
    while (current) {
        Node* to_delete = current;
        current = current->next;
        free(to_delete);
    }
    
    set->head = NULL;
    set->size = 0;
}

bool set_add(OrderedSet* set, int value) {
    if (!set) return false;
    
    if (set_contains(set, value)) {
        return false;
    }
    
    Node* new_node = node_create(value);
    if (!new_node) return false;
    
    if (!set->head || value < set->head->data) {
        new_node->next = set->head;
        set->head = new_node;
        set->size++;
        return true;
    }
    
    Node* current = set->head;
    while (current->next && current->next->data < value) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    set->size++;
    
    return true;
}

bool set_remove(OrderedSet* set, int value) {
    if (!set || !set->head) return false;
    
    if (set->head->data == value) {
        Node* to_delete = set->head;
        set->head = set->head->next;
        free(to_delete);
        set->size--;
        return true;
    }
    
    Node* current = set->head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }
    
    if (current->next && current->next->data == value) {
        Node* to_delete = current->next;
        current->next = current->next->next;
        free(to_delete);
        set->size--;
        return true;
    }
    
    return false;
}

bool set_contains(const OrderedSet* set, int value) {
    if (!set) return false;
    
    Node* current = set->head;
    while (current) {
        if (current->data == value) return true;
        if (current->data > value) break;
        current = current->next;
    }
    return false;
}

OrderedSet* set_union(const OrderedSet* set1, const OrderedSet* set2) {
    OrderedSet* result = set_create();
    if (!result) return NULL;
    
    Node* current1 = set1 ? set1->head : NULL;
    Node* current2 = set2 ? set2->head : NULL;
    
    while (current1 || current2) {
        if (!current2 || (current1 && current1->data < current2->data)) {
            set_add(result, current1->data);
            current1 = current1->next;
        } else if (!current1 || (current2 && current2->data < current1->data)) {
            set_add(result, current2->data);
            current2 = current2->next;
        } else {
            set_add(result, current1->data);
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    
    return result;
}

OrderedSet* set_intersection(const OrderedSet* set1, const OrderedSet* set2) {
    OrderedSet* result = set_create();
    if (!result) return NULL;
    
    if (!set1 || !set2) return result;
    
    Node* current1 = set1->head;
    Node* current2 = set2->head;
    
    while (current1 && current2) {
        if (current1->data < current2->data) {
            current1 = current1->next;
        } else if (current2->data < current1->data) {
            current2 = current2->next;
        } else {
            set_add(result, current1->data);
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    
    return result;
}

bool set_is_empty(const OrderedSet* set) {
    return !set || set->size == 0;
}

size_t set_size(const OrderedSet* set) {
    return set ? set->size : 0;
}

void set_print(const OrderedSet* set) {
    if (!set) {
        printf("(null)\n");
        return;
    }
    
    printf("{ ");
    Node* current = set->head;
    while (current) {
        printf("%d", current->data);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf(" }\n");
}

SetIterator set_iterator_begin(const OrderedSet* set) {
    SetIterator it = {NULL};
    if (set) it.current = set->head;
    return it;
}

bool set_iterator_has_next(const SetIterator* it) {
    return it && it->current;
}

int set_iterator_next(SetIterator* it) {
    if (!it || !it->current) return 0;
    int value = it->current->data;
    it->current = it->current->next;
    return value;
}
