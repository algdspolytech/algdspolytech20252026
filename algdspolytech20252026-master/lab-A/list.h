#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

// Структура узла списка
typedef struct Node {
    char* data;           // Строка
    struct Node* next;    // Указатель на следующий узел
} Node;

// Структура списка
typedef struct {
    Node* head;
    Node* tail;
    size_t length;
} LinkedList;

// Функции для работы со списком
LinkedList* list_create();
void list_destroy(LinkedList* list);
int list_append(LinkedList* list, const char* str);
char* list_concat_strings(const LinkedList* list);

#endif // LIST_H