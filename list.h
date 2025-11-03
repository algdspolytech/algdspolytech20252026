#pragma once

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Node {
        char* word;
        int key;
        struct Node* next;
    } Node;

    typedef struct {
        Node* head;
    } SortedList;

    // initialize list
    void create_list(SortedList* list);

    // insert (sorted by key). return 0 = ok, 1 = duplicate key, 2 = malloc fail
    int insert_sorted(SortedList* list, const char* word, int key);

    // parse "word key" line and insert. returns same codes as insert_sorted,
    // or -1 if line parsing failed.
    int insert_from_line(SortedList* list, const char* line);

    // find word by key. returns pointer to internal string (do NOT free it), or NULL.
    const char* find_by_key(SortedList* list, int key);

    // print list to stdout: each line "word key\n"
    void print_list(SortedList* list);

    // free all memory and reset list
    void free_list(SortedList* list);

#ifdef __cplusplus
}
#endif

#endif // LIST_H