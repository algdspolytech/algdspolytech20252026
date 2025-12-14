#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

Node* create(const char* str) {
    // Вычисляем длину строки вручную
    size_t len = 0;
    const char* p = str;
    while (*p++) len++;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return NULL;

    // Выделяем память под строку
    new_node->str = (char*)malloc(len + 1);
    if (!new_node->str) {
        free(new_node);
        return NULL;
    }

    // Копируем строку вручную
    char* dest = new_node->str;
    const char* src = str;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';

    new_node->l = len;
    new_node->next = NULL;
    return new_node;
}

// Добавление элемента в конец списка
void add_node(Linkedlist* list, const char* str) {
    Node* new_node = create(str);
    if (!new_node) return;

    if (!list->first) {
        list->first = new_node;
        list->last = new_node;
    }
    else {
        list->last->next = new_node;
        list->last = new_node;
    }

    list->totallen += new_node->l;
}

// ОСНОВНАЯ ФУНКЦИЯ: Эффективное объединение строк
char* connect_strings(const Linkedlist* list) {
    if (!list || !list->first) {
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    // Выделяем память сразу для всей результирующей строки
    char* result = (char*)malloc(list->totallen + 1);
    if (!result) return NULL;

    char* current_pos = result;
    Node* current_node = list->first;

    // Копируем все строки в результирующий буфер
    while (current_node) {
        // Копируем символы текущей строки
        const char* src = current_node->str;
        while (*src) {
            *current_pos++ = *src++;
        }
        current_node = current_node->next;
    }

    *current_pos = '\0';
    return result;
}

// Инициализация списка
void init_list(Linkedlist* list) {
    list->first = list->last = NULL;
    list->totallen = 0;
}

// Освобождение памяти списка
void free_list(Linkedlist* list) {
    Node* current = list->first;
    while (current) {
        Node* next = current->next;
        free(current->str);
        free(current);
        current = next;
    }
    list->first = list->last = NULL;
    list->totallen = 0;
}

// Функция для чтения строки из консоли
char* read_string() {
    char buffer[1024]; // Буфер для ввода
    printf("Введите строку для узла (или quit_prog для завершения): ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }

    // Удаляем символ новой строки
    size_t len = 0;
    while (buffer[len] != '\0' && buffer[len] != '\n') {
        len++;
    }
    buffer[len] = '\0';

    // Если введено quit_prog, возвращаем NULL
    if (strcmp(buffer, "quit_prog") == 0) {
        return NULL;
    }

    // Копируем строку в динамическую память
    char* result = (char*)malloc(len + 1);
    if (!result) return NULL;

    for (size_t i = 0; i <= len; i++) {
        result[i] = buffer[i];
    }

    return result;
}

// Функция для вывода списка на экран
void print_list(const Linkedlist* list) {
    printf("\nТекущий список:\n");
    if (!list->first) {
        printf("Список пуст\n");
        return;
    }

    Node* current = list->first;
    int index = 1;
    while (current) {
        printf("Узел %d: \"%s\" \n", index, current->str);
        current = current->next;
        index++;
    }
}

