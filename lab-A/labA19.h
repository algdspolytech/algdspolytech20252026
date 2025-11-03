#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Node {
        char* data;
        struct Node* prev;
        struct Node* next;
    }
    Node;

    //Добавление элемента в начало списка
    Node* push(Node* head,
        const char* str);

    //Удаление элемента по значению
    Node* deletenode(Node* head,
        const char* str);

    //Сортировка списка (с использованием merge sort)
    Node* mergeSort(Node* head);
#ifdef __cplusplus
}
#endif