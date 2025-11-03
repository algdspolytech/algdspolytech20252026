#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Узел
typedef struct Node {
    char* str;
    size_t l;
    struct Node* next;
} Node;

//Связанный список
typedef struct {
    Node* first;
    Node* last;
    size_t totallen;
} Linkedlist;

Node* create(const char*); //создать новый узел
void add_node(Linkedlist*, const char*); //добавить новый элемент(в конец)
char* connect_strings(const Linkedlist*); //объединение строк
void init_list(Linkedlist*); //инициализация списка
void free_list(Linkedlist*); //освободить память
char* read_string(); //чтение строки из консоли
void print_list(const Linkedlist*); //вывод на экран