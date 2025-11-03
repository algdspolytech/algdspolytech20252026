#define _CRT_SECURE_NO_WARNINGS
#include "list_sort.h"
#include <stdlib.h>
#include <string.h>

Node* create_node(const char* str) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;
    size_t len = strlen(str) + 1;
    n->data = (char*)malloc(len);
    if (!n->data) {
        free(n);
        return NULL;
    }
    strncpy(n->data, str, len - 1); // безопасное копирование
    n->data[len - 1] = '\0';       // явно завершаем строку
    n->next = NULL;
    return n;
}

void free_list(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp->data);
        free(tmp);
    }
}

Node* create_list(const char* arr[], size_t n) {
    if (n == 0) return NULL;
    Node* head = create_node(arr[0]);
    Node* curr = head;
    for (size_t i = 1; i < n; i++) {
        curr->next = create_node(arr[i]);
        curr = curr->next;
    }
    return head;
}

int compare_lists(Node* a, Node* b) {
    while (a && b) {
        if (strcmp(a->data, b->data) != 0) return 0;
        a = a->next; b = b->next;
    }
    return (a == NULL && b == NULL);
}

static Node* sorted_merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (strcmp(a->data, b->data) <= 0) {
        a->next = sorted_merge(a->next, b);
        return a;
    }
    else {
        b->next = sorted_merge(a, b->next);
        return b;
    }
}

static void front_back_split(Node* source, Node** front, Node** back) {
    Node* slow = source, * fast = source->next;
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next; fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next; slow->next = NULL;
}

void merge_sort(Node** head_ref) {
    Node* head = *head_ref;
    if (!head || !head->next) return;
    Node* a, * b;
    front_back_split(head, &a, &b);
    merge_sort(&a); merge_sort(&b);
    *head_ref = sorted_merge(a, b);
}
