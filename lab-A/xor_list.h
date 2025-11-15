#ifndef XOR_LIST_H
#define XOR_LIST_H

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

// Максимальная длина строки
#define MAX_STRING_LEN 256

// Структура узла XOR-связного списка
typedef struct Node {
    char *data;
    uintptr_t xor_address;
} Node;

// Глобальные указатели
extern Node *head;
extern Node *tail;


// Операции
Node* xor_ptrs(Node *a, Node *b); 
void add_to_list(const char *str);
Node *find_by_key(const char *key);
void iterate_list();
void remove_by_key(const char *key);
void remove_by_pointer(Node *node);
void cleanup_list_for_test(); 

#ifdef __cplusplus
}
#endif

#endif // XOR_LIST_H
