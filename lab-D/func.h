#ifndef LAB_1_H
#include <stdio.h>
#define LAB_1_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    int id;
    int l;
    int d;
    int w;
}Telegram;


typedef struct
{
    Telegram* tel;
    int* used;
    int* order;
    int* result;

    int T;
    int K;
    int cur_time;
    int cur_tax;
    int found;
}Data;


int ReadFile(FILE* file, Data* data);

void PrintPath(int* arr, int N);

int Backtrack(int pos, Data* data);

void FreeData(Data* data);

void InitData(Data* data);

#endif

#ifdef __cplusplus
}
#endif