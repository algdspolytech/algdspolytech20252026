#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// helper: strdup replacement (portable)
static char* str_dup(const char* s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char* p = (char*)malloc(n);
    if (!p) return NULL;
    memcpy(p, s, n);
    return p;
}

void create_list(SortedList* list) {
    if (!list) return;
    list->head = NULL;
}

int insert_sorted(SortedList* list, const char* word, int key) {
    if (!list || !word) return 2; // treat as malloc error / invalid

    // check duplicates
    Node* prev = NULL;
    Node* cur = list->head;
    while (cur) {
        if (cur->key == key) {
            return 1; // duplicate
        }
        if (cur->key > key) break; // insert before cur
        prev = cur;
        cur = cur->next;
    }

    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) return 2;
    node->word = str_dup(word);
    if (!node->word) { free(node); return 2; }
    node->key = key;
    node->next = cur;

    if (prev == NULL) {
        // insert at head
        list->head = node;
    }
    else {
        prev->next = node;
    }
    return 0;
}

int insert_from_line(SortedList* list, const char* line) {
    if (!list || !line) return -1;
    // Skip leading spaces
    while (*line && isspace((unsigned char)*line)) line++;

    if (*line == '\0') return -1;

    // word up to whitespace, then integer
    char wordbuf[256];
    int key;
    // Use sscanf; restrict to avoid overflow
    int n = sscanf(line, " %255s %d", wordbuf, &key);
    if (n != 2) return -1;
    return insert_sorted(list, wordbuf, key);
}

const char* find_by_key(SortedList* list, int key) {
    if (!list) return NULL;
    Node* cur = list->head;
    while (cur) {
        if (cur->key == key) return cur->word;
        if (cur->key > key) return NULL;
        cur = cur->next;
    }
    return NULL;
}

void print_list(SortedList* list) {
    if (!list) return;
    Node* cur = list->head;
    while (cur) {
        printf("%s %d\n", cur->word, cur->key);
        cur = cur->next;
    }
}

void free_list(SortedList* list) {
    if (!list) return;
    Node* cur = list->head;
    while (cur) {
        Node* next = cur->next;
        if (cur->word) free(cur->word);
        free(cur);
        cur = next;
    }
    list->head = NULL;
}