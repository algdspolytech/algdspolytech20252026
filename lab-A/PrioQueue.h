#include <stdio.h>

typedef struct {
    unsigned int prio;
    int data;
}PrioEl;

typedef struct PrioQueueUnit{
    PrioEl el;
    struct PrioQueueUnit* next;
}PrioQueueUnit;

PrioQueueUnit* InitPrioQueue();
PrioQueueUnit* fInitPrioQueue(FILE* fptr);
void FreeQueue(PrioQueueUnit* ptr);
void PushElement(PrioQueueUnit** root, PrioEl el); // Сложность O(n)
PrioEl PopElement(PrioQueueUnit* root); // Сложность O(1)
void PrintQueue(FILE* fptr, PrioQueueUnit* root);
int QueueCmp(PrioQueueUnit* q1, PrioQueueUnit* q2);
