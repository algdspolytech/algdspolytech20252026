#define _CRT_SECURE_NO_WARNINGS
#include "Lab1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Создание нового узла
ListNode* create_node(const char* data) {
    if (data == NULL) {
        return NULL;
    }

    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = (char*)malloc(strlen(data)+1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }
    strncpy(new_node->data, data, strlen(data));
    new_node->data[strlen(data)] = '\0';
    new_node->next = NULL;
    return new_node;
}

// Освобождение памяти списка
void free_list(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        ListNode* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

// Добавление в начало списка
void push_front(ListNode** head, const char* data) {
    if (head == NULL || data == NULL) {
        return;
    }

    ListNode* new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }

    new_node->next = *head;
    *head = new_node;
}

// Добавление в конец списка
void push_back(ListNode** head, const char* data) {
    if (head == NULL || data == NULL) {
        return;
    }

    ListNode* new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    ListNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

// Получение длины списка
size_t list_length(const ListNode* head) {
    size_t length = 0;
    const ListNode* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

// Получение узла по индексу
ListNode* get_node_at(ListNode* head, size_t index) {
    ListNode* current = head;
    size_t current_index = 0;

    while (current != NULL && current_index < index) {
        current = current->next;
        current_index++;
    }

    return current;
}

// Получение данных по индексу
char* get_data_at(ListNode* head, size_t index) {
    ListNode* node = get_node_at(head, index);
    return (node != NULL) ? node->data : NULL;
}

// Разделение списка на две части
void front_back_split(ListNode* source, ListNode** front, ListNode** back) {
    if (source == NULL || source->next == NULL) {
        *front = source;
        *back = NULL;
        return;
    }

    ListNode* slow = source;
    ListNode* fast = source->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

// Слияние двух отсортированных списков
ListNode* sorted_merge(ListNode* a, ListNode* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    ListNode* result = NULL;

    if (strcmp(a->data, b->data) <= 0) {
        result = a;
        result->next = sorted_merge(a->next, b);
    }
    else {
        result = b;
        result->next = sorted_merge(b->next, a);
    }

    return result;
}

// Сортировка слиянием
ListNode* merge_sort(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    ListNode* front = NULL;
    ListNode* back = NULL;

    front_back_split(head, &front, &back);

    front = merge_sort(front);
    back = merge_sort(back);

    return sorted_merge(front, back);
}

// Печать списка
void print_list(const ListNode* head) {
    const ListNode* current = head;
    while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}

// Проверка отсортированности списка
int is_sorted(const ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return 1;
    }

    const ListNode* current = head;
    while (current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            return 0;
        }
        current = current->next;
    }

    return 1;
}