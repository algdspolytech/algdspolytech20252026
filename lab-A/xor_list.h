#pragma once
#ifndef XOR_LIST_H
#define XOR_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    // Узел XOR-списка: хранит строку и XOR указателей на соседние элементы.
    typedef struct Node {
        char* data;
        uintptr_t link;
    } Node;

    // Структура списка: указатели на начало и конец.
    typedef struct {
        Node* head;
        Node* tail;
    } XORList;

    // Возвращает XOR двух указателей.
    Node* xor_ptr(Node* a, Node* b);

    // Инициализация пустого списка.
    void init_list(XORList* list);

    // Вставка нового узла в начало списка.
    void insert(XORList* list, const char* str);

    // Поиск узла по строковому ключу.
    Node* find(XORList* list, const char* key);

    // Удаление узла по строковому ключу.
    void remove_by_key(XORList* list, const char* key);

    // Удаление узла по указателю.
    void remove_by_ptr(XORList* list, Node* to_remove);

    // Обход списка и вывод содержимого.
    void iterate(XORList* list);

    // Освобождение памяти списка.
    void free_list(XORList* list);

#ifdef __cplusplus
}
#endif

#endif  // XOR_LIST_H