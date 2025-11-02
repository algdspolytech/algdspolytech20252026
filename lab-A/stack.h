#ifndef labA
#define labA

#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#define MAX_STACK_SIZE 50

// Структура узла связного списка
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// Структура стека на основе связного списка
typedef struct {
    ListNode* top;
    int size;
} ListStack;

// Функции для работы со стеком на основе связного списка
void createListStack(ListStack* stack);
void pushListStack(ListStack* stack, int value);
int popListStack(ListStack* stack);
int peekListStack(ListStack* stack);

// Структура стека на основе массива
typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} ArrayStack;

// Функции для работы со стеком на основе массива
void createArrayStack(ArrayStack* stack);
void pushArrayStack(ArrayStack* stack, int value);
int popArrayStack(ArrayStack* stack);
int peekArrayStack(ArrayStack* stack);

#endif

#ifdef __cplusplus
}
#endif
#endif
