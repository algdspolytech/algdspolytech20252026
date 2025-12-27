#pragma once
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    // Структура узла двусвязного списка
    typedef struct linkedListNode {
        char* data;
        struct linkedListNode* next;
        struct linkedListNode* prev;
    } linkedListNode;

    // Функции для работы со списком
    linkedListNode* createNode(const char* data);
    linkedListNode* appendNode(linkedListNode* head, const char* data);
    int listLength(linkedListNode* head);
    void freeList(linkedListNode* head);
    void printList(linkedListNode* head);
    linkedListNode* bubbleSort(linkedListNode* head);

#ifdef __cplusplus
}
#endif

#endif // DOUBLY_LINKED_LIST_H