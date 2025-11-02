#include "list.h"

// Вспомогательная функция для копирования строки
char* copy_string(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str) + 1;
    char* copy = (char*)malloc(len);
    if (copy) {
        memcpy(copy, str, len);
    }
    return copy;
}

// Создание нового списка
LinkedList* list_create() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

// Уничтожение списка и освобождение памяти
void list_destroy(LinkedList* list) {
    if (!list) return;

    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free(current->data);  // Освобождаем строку
        free(current);        // Освобождаем узел
        current = next;
    }
    free(list);
}

// Добавление строки в конец списка
int list_append(LinkedList* list, const char* str) {
    if (!list || !str) return 0;

    // Создаем новый узел
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return 0;

    // Копируем строку (используем нашу функцию вместо strdup)
    new_node->data = copy_string(str);
    if (!new_node->data) {
        free(new_node);
        return 0;
    }

    new_node->next = NULL;

    // Добавляем в список
    if (!list->head) {
        list->head = new_node;
        list->tail = new_node;
    }
    else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->length++;
    return 1;
}

// Конкатенация всех строк списка
char* list_concat_strings(const LinkedList* list) {
    if (!list || !list->head) {
        // Возвращаем пустую строку для пустого списка
        char* empty = (char*)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    // Первый проход: вычисляем общую длину
    size_t total_length = 0;
    Node* current = list->head;
    while (current) {
        total_length += strlen(current->data);
        current = current->next;
    }

    // Выделяем память для результирующей строки
    char* result = (char*)malloc(total_length + 1);
    if (!result) return NULL;

    // Второй проход: копируем строки
    char* dest = result;
    current = list->head;
    while (current) {
        size_t len = strlen(current->data);
        memcpy(dest, current->data, len);
        dest += len;
        current = current->next;
    }
    *dest = '\0';

    return result;
}