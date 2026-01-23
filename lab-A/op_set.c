#include "op_set.h"
#include <stdio.h>
#include <stdlib.h>


static ListNode* create_node(int val) {
    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (new_node != NULL) {
        new_node->value = val;
        new_node->next = NULL;
    }
    return new_node;
}


OpSet* create_set(void) {
    OpSet* new_set = (OpSet*)malloc(sizeof(OpSet));
    if (new_set != NULL) {
        new_set->first = NULL;
        new_set->count = 0;
    }
    return new_set;
}


void delete_set(OpSet* set) {
    if (set == NULL) return;
    clear_set(set);
    free(set);
}


void clear_set(OpSet* set) {
    if (set == NULL) return;
    
    ListNode* curr = set->first;
    while (curr != NULL) {
        ListNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
    
    set->first = NULL;
    set->count = 0;
}


bool insert_elem(OpSet* set, int val) {
    if (set == NULL) return false;
    
    
    if (has_elem(set, val)) {
        return false;
    }
    
    ListNode* new_node = create_node(val);
    if (new_node == NULL) return false;
    
    
    if (set->first == NULL || val < set->first->value) {
        new_node->next = set->first;
        set->first = new_node;
        set->count++;
        return true;
    }
    
    
    ListNode* curr = set->first;
    while (curr->next != NULL && curr->next->value < val) {
        curr = curr->next;
    }
    
    
    new_node->next = curr->next;
    curr->next = new_node;
    set->count++;
    
    return true;
}


bool delete_elem(OpSet* set, int val) {
    if (set == NULL || set->first == NULL) return false;
    
    
    if (set->first->value == val) {
        ListNode* to_remove = set->first;
        set->first = set->first->next;
        free(to_remove);
        set->count--;
        return true;
    }
    
    
    ListNode* curr = set->first;
    while (curr->next != NULL && curr->next->value != val) {
        curr = curr->next;
    }
    
    
    if (curr->next != NULL && curr->next->value == val) {
        ListNode* to_remove = curr->next;
        curr->next = curr->next->next;
        free(to_remove);
        set->count--;
        return true;
    }
    
    return false;
}


bool has_elem(const OpSet* set, int val) {
    if (set == NULL) return false;
    
    ListNode* curr = set->first;
    while (curr != NULL) {
        if (curr->value == val) return true;
        if (curr->value > val) break;
        curr = curr->next;
    }
    return false;
}


OpSet* union_sets(const OpSet* s1, const OpSet* s2) {
    OpSet* result = create_set();
    if (result == NULL) return NULL;
    
    ListNode* ptr1 = (s1 != NULL) ? s1->first : NULL;
    ListNode* ptr2 = (s2 != NULL) ? s2->first : NULL;
    
    
    while (ptr1 != NULL || ptr2 != NULL) {
        if (ptr2 == NULL || (ptr1 != NULL && ptr1->value < ptr2->value)) {
            insert_elem(result, ptr1->value);
            ptr1 = ptr1->next;
        } else if (ptr1 == NULL || (ptr2 != NULL && ptr2->value < ptr1->value)) {
            insert_elem(result, ptr2->value);
            ptr2 = ptr2->next;
        } else {
            
            insert_elem(result, ptr1->value);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    
    return result;
}


OpSet* intersect_sets(const OpSet* s1, const OpSet* s2) {
    OpSet* result = create_set();
    if (result == NULL) return NULL;
    
    if (s1 == NULL || s2 == NULL) return result;
    
    ListNode* ptr1 = s1->first;
    ListNode* ptr2 = s2->first;
    
    
    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1->value < ptr2->value) {
            ptr1 = ptr1->next;
        } else if (ptr2->value < ptr1->value) {
            ptr2 = ptr2->next;
        } else {
            
            insert_elem(result, ptr1->value);
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
    }
    
    return result;
}


bool is_set_empty(const OpSet* set) {
    return set == NULL || set->count == 0;
}


size_t get_set_size(const OpSet* set) {
    return (set != NULL) ? set->count : 0;
}


void display_set(const OpSet* set) {
    if (set == NULL) {
        printf("(пустое множество)\n");
        return;
    }
    
    printf("{ ");
    ListNode* curr = set->first;
    while (curr != NULL) {
        printf("%d", curr->value);
        if (curr->next != NULL) printf(", ");
        curr = curr->next;
    }
    printf(" }\n");
}


SetIter get_iterator(const OpSet* set) {
    SetIter iter = {NULL};
    if (set != NULL) {
        iter.current = set->first;
    }
    return iter;
}


bool has_more_elems(const SetIter* iter) {
    return iter != NULL && iter->current != NULL;
}


int get_next_elem(SetIter* iter) {
    if (iter == NULL || iter->current == NULL) {
        return 0;
    }
    
    int val = iter->current->value;
    iter->current = iter->current->next;
    return val;
}
