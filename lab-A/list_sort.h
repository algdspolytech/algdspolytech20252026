#ifndef LIST_SORT_H
#define LIST_SORT_H

// Структура узла списка
typedef struct ListNode {
    char* data;           // ASCII-Z строка
    struct ListNode* next;
} ListNode;

// Функции для работы со списком
ListNode* create_node(const char* data);
void free_list(ListNode* head);
void append_node(ListNode** head, const char* data);
ListNode* get_node_at_index(ListNode* head, int index);
int get_list_length(ListNode* head);

// Функции сортировки
ListNode* merge_sort(ListNode* head);
ListNode* sorted_merge(ListNode* a, ListNode* b);
void split_list(ListNode* source, ListNode** front, ListNode** back);

// Вспомогательные функции
void print_list(ListNode* head);
int compare_strings(const char* s1, const char* s2);

#endif // LIST_SORT_H