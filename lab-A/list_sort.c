#include "list_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Создание нового узла
ListNode* create_node(const char* data) {
    if (data == NULL) return NULL;

    ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
    if (new_node == NULL) return NULL;

    new_node->data = (char*)malloc(strlen(data) + 1);
    if (new_node->data == NULL) {
        free(new_node);
        return NULL;
    }

    strcpy(new_node->data, data);
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

// Добавление узла в конец списка
void append_node(ListNode** head, const char* data) {
    ListNode* new_node = create_node(data);
    if (new_node == NULL) return;

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

// Получение узла по индексу
ListNode* get_node_at_index(ListNode* head, int index) {
    ListNode* current = head;
    int count = 0;

    while (current != NULL && count < index) {
        current = current->next;
        count++;
    }

    return current;
}

// Получение длины списка
int get_list_length(ListNode* head) {
    int length = 0;
    ListNode* current = head;

    while (current != NULL) {
        length++;
        current = current->next;
    }

    return length;
}

// Сравнение строк (аналог strcmp)
int compare_strings(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// Слияние двух отсортированных списков
ListNode* sorted_merge(ListNode* a, ListNode* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    ListNode* result = NULL;

    if (compare_strings(a->data, b->data) <= 0) {
        result = a;
        result->next = sorted_merge(a->next, b);
    }
    else {
        result = b;
        result->next = sorted_merge(b->next, a);
    }

    return result;
}

// Разделение списка на две части
void split_list(ListNode* source, ListNode** front, ListNode** back) {
    if (source == NULL || source->next == NULL) {
        *front = source;
        *back = NULL;
        return;
    }

    ListNode* slow = source;
    ListNode* fast = source->next;

    // fast движется в два раза быстрее slow
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

// Сортировка слиянием для списка
ListNode* merge_sort(ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    ListNode* a;
    ListNode* b;

    // Разделяем список на две части
    split_list(head, &a, &b);

    // Рекурсивно сортируем каждую часть
    a = merge_sort(a);
    b = merge_sort(b);

    // Сливаем отсортированные части
    return sorted_merge(a, b);
}

// Печать списка (для отладки)
void print_list(ListNode* head) {
    ListNode* current = head;
    while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}