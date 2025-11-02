#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура узла списка
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

// Структура списка
typedef struct {
    Node* head;
    Node* tail;
    size_t total_length;
} LinkedList;


LinkedList* create_list(void);
void free_list(LinkedList* list);
void append_string(LinkedList* list, const char* str);
char* concatenate_strings(LinkedList* list);
size_t get_total_length(LinkedList* list);
