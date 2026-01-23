#ifndef OP_SET_H
#define OP_SET_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* first;
    size_t count;     
} OpSet;


typedef struct {
    ListNode* current;
} SetIter;


OpSet* create_set(void);
void delete_set(OpSet* set);
void clear_set(OpSet* set);


bool insert_elem(OpSet* set, int val);
bool delete_elem(OpSet* set, int val);
bool has_elem(const OpSet* set, int val);


OpSet* union_sets(const OpSet* s1, const OpSet* s2);
OpSet* intersect_sets(const OpSet* s1, const OpSet* s2);


bool is_set_empty(const OpSet* set);
size_t get_set_size(const OpSet* set);
void display_set(const OpSet* set);


SetIter get_iterator(const OpSet* set);
bool has_more_elems(const SetIter* iter);
int get_next_elem(SetIter* iter);

#endif
