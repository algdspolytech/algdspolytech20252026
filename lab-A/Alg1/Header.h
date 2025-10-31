#pragma once

#include <stdio.h>
#include <math.h> 
#include <locale.h> 
#include <malloc.h> 
#include <stdlib.h> 
#include <crtdbg.h> 

typedef struct {
    int day;
    int month;
    int year;
    char* surname;
    char* name;
    double hours;
}Worker;

typedef struct Staff {
    Worker* CurrWorker;
    struct Staff* NextWorker;
} Staff;

void FreeStaff(Staff* head);

void PrintWorker(Worker* worker);

int PrintStaff(Staff* head, double n);

int IfSameWorker(Worker* w1, Worker* w2);

int WorkerCmp(Worker* w1, Worker* w2);

int FromStr2Num(char* str, int len);

char* ReadOneData(char* lines, int lenght, int* i, int* LenInfoList, char EndChar);

Worker* CreateWorker(char* lines, int lenght, int* i);

Staff* CreateStaff(char* lines, int lenght);

Staff* InsertWorker(Staff* sorted, Staff* current);

Staff* InsertSort(Staff* Head);
