#include "labA19.h"
#include <stdlib.h>
#include <string.h>

//Добавление элемента в начало списка
Node* push(Node* head,
    const char* str) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = _strdup(str);
    node->prev = NULL;
    node->next = head;
    if (head) {
        head->prev = node;
    }
    return node;
}

//Удаление элемента по значению
Node* deletenode(Node* head,
    const char* str) {
    Node* current = head;
    while (current) {
        if (strcmp(current->data, str) == 0) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            }

            free(current->data);
            free(current);
            break;
        }
        current = current->next;
    }
    return head;
}

//Разделение списка на две половины
Node* split(Node* head) {
    Node* twoel = head;
    Node* oneel = head;
    while (twoel->next && twoel->next->next) {
        twoel = twoel->next->next;
        oneel = oneel->next;
    }
    Node* second = oneel->next;
    oneel->next = NULL;
    if (second) {
        second->prev = NULL;
    }
    return second;
}

//Слияние двух отсортированных списков
Node* merge(Node* first, Node* second) {
    if (!first) {
        return second;
    }
    if (!second) {
        return first;
    }

    if (strcmp(first->data, second->data) <= 0) {
        first->next = merge(first->next, second);
        if (first->next) {
            first->next->prev = first;
        }
        first->prev = NULL;
        return first;
    }
    else {
        second->next = merge(first, second->next);
        if (second->next) {
            second->next->prev = second;
        }
        second->prev = NULL;
        return second;
    }
}

//Сортировка списка
Node* mergeSort(Node* head) {
    if (!head || !head->next) {
        return head;
    }
    Node* second = split(head);
    head = mergeSort(head);
    second = mergeSort(second);
    return merge(head, second);
}