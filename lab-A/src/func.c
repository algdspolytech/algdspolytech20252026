#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void InitStArr(st_arr* stack)
{
    stack->top = 0;
    int i = 0;
    for(; i < MAX_SIZE; i++){
        stack->arr[i] = 0;
    }
}

int PopStArr(st_arr* stack)
{
    if(stack->top == 0)
    {
        return -1;
    }
    stack->top--;
    stack->arr[stack->top + 1] = 0;
    int data = stack->arr[stack->top];
    
    return data;
}

void PushStArr(st_arr* stack, int data)
{
    if(stack->top + 1 == MAX_SIZE)
    {
        return;
    }
    stack->arr[stack->top] = data;
    stack->top++;
}

void InitStList(st_list* stack)
{
    stack->head = NULL;
}

void PushStList(st_list* stack, int data)
{
    Node* ptr = (Node*)malloc(sizeof(Node));
    ptr->data = data;
    ptr->next = stack->head;
    stack->head = ptr;
}

int PopStList(st_list* stack)
{
    if(stack->head == NULL){
        return -1;
    }
    Node* ptr = stack->head->next;
    int data = stack->head->data;
    free(stack->head);
    stack->head = ptr;

    return data;
}



// void destroy(st_list* stack){
//     while(stack->head != NULL)
//     {
//         pop(stack);
//     }
// }


// #include "func.h"
// int add(int a, int b) {
//     return a + b;
// }

