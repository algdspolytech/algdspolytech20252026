#include "xor_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Указатели на голову и хвост списка
Node *head = NULL;
Node *tail = NULL;

// Вспомогательная функция для выполнения XOR-операции над указателями
Node* xor_ptrs(Node *a, Node *b) {
    return (Node*)((uintptr_t)a ^ (uintptr_t)b);
}

// Операция: Добавить элемент в список (в конец)
void add_to_list(const char *str) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Ошибка выделения памяти для узла");
        return;
    }

    new_node->data = (char *)malloc(strlen(str) + 1);
    if (new_node->data == NULL) {
        perror("Ошибка выделения памяти для строки");
        free(new_node);
        return;
    }
    strcpy(new_node->data, str);

    if (head == NULL) {
        new_node->xor_address = (uintptr_t)xor_ptrs(NULL, NULL);
        head = new_node;
        tail = new_node;
    } else {
        new_node->xor_address = (uintptr_t)xor_ptrs(tail, NULL);
        tail->xor_address = (uintptr_t)xor_ptrs((Node *)((uintptr_t)tail->xor_address ^ (uintptr_t)NULL), new_node);
        tail = new_node;
    }
}

// Найти элемент по ключу
Node *find_by_key(const char *key) {
    Node *curr = head;
    Node *prev = NULL;
    Node *next;

    while (curr != NULL) {
        if (strcmp(curr->data, key) == 0) {
            return curr;
        }
        next = xor_ptrs(prev, (Node *)curr->xor_address);
        prev = curr;
        curr = next;
    }
    return NULL;
}

// Итерирование по списку и печать элементов
void iterate_list() {
    Node *curr = head;
    Node *prev = NULL;
    Node *next;

    printf("Содержимое списка: \n");
    if (curr == NULL) {
        printf("(Список пуст)\n");
        return;
    }

    while (curr != NULL) {
        printf("-> %s ", curr->data);
        next = xor_ptrs(prev, (Node *)curr->xor_address);
        prev = curr;
        curr = next;
    }
    printf("\n");
}

// Удалить элемент из списка по ключу
void remove_by_key(const char *key) {
    Node *node_to_delete = find_by_key(key);
    if (node_to_delete) {
        // printf("Удаление элемента: %s\n", key); 
        remove_by_pointer(node_to_delete);
    } else {
        // printf("Элемент с ключом '%s' не найден.\n", key); 
    }
}

// Удалить узел по указателю
void remove_by_pointer(Node *node_to_delete) {
    if (node_to_delete == NULL)
        return;

    Node *prev = NULL;
    Node *curr = head;
    Node *next_node = NULL;

    while (curr != NULL && curr != node_to_delete) {
        next_node = xor_ptrs(prev, (Node *)curr->xor_address);
        prev = curr;
        curr = next_node;
    }

    if (curr == NULL)
        return;

    next_node = xor_ptrs(prev, (Node *)curr->xor_address);

    if (prev == NULL) {
        head = next_node;
    } else {
        
        prev->xor_address = (uintptr_t)xor_ptrs((Node *)((uintptr_t)prev->xor_address ^ (uintptr_t)curr), next_node);
    }

    if (next_node == NULL) {
        tail = prev;
    } else {
        
        next_node->xor_address = (uintptr_t)xor_ptrs(prev, (Node *)((uintptr_t)next_node->xor_address ^ (uintptr_t)curr));
    }

    free(curr->data);
    free(curr);
}

// Функция очистки списка, используемая тестами
void cleanup_list_for_test() {
   
    Node *curr = head;
    Node *prev = NULL;
    Node *next;
    while (curr != NULL) {
        next = xor_ptrs(prev, (Node *)curr->xor_address);
        if (curr->data != NULL) {
            free(curr->data);
        }
        free(curr); // Освобождаем узел
        prev = curr; // Обновляем предыдущий указатель
        curr = next; // Переходим к следующему
    }
    head = NULL;
    tail = NULL;
}


// ГЛАВНАЯ ФУНКЦИЯ ДЛЯ ДЕМОНСТРАЦИИ 
int main_demo() {
    add_to_list("первая_строка");
    add_to_list("вторая_строка");
    add_to_list("третья_строка");

    iterate_list();

    Node *found_node = find_by_key("вторая_строка");
    if (found_node) {
        printf("Элемент найден: %s\n", found_node->data);
    } else {
        printf("Элемент не найден.\n");
    }

    remove_by_key("вторая_строка");
    iterate_list();

    add_to_list("новая_строка");
    iterate_list();

    Node *node_to_remove = find_by_key("новая_строка");
    if (node_to_remove) {
        printf("Удаление элемента по адресу: %s\n", node_to_remove->data);
        remove_by_pointer(node_to_remove);
    }
    iterate_list();

    // Очистка памяти в конце демонстрации
    cleanup_list_for_test();

    return 0;
}
