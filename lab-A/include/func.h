#ifndef LAB_1_H
#define LAB_1_H

#ifdef __cplusplus
extern "C" {
#endif

enum{MAX_SIZE = 5};

typedef struct stack_arr{
    
    int arr[MAX_SIZE];
    int top;
}st_arr;

typedef struct item_stack{
    int data;
    struct item_stack* next;
}Node;

typedef struct stack_list{
    Node* head;
}st_list;

void InitStArr(st_arr* stack);
int PopStArr(st_arr* stack);
void PushStArr(st_arr* stack, int data);

void InitStList(st_list* stack);
void PushStList(st_list* stack, int data);
int PopStList(st_list* stack);
//void destroy(st_list* stack);

#endif

#ifdef __cplusplus
}
#endif