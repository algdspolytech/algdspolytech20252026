#include "PrioQueue.h"
#include <stdio.h>
#include <stdlib.h>


PrioQueueUnit* InitPrioQueue() {
    PrioQueueUnit* root = NULL;
    return root;
};

void FreeQueue(PrioQueueUnit* ptr) {
    PrioQueueUnit* ptr2;
    if (ptr != NULL) {
        while ((ptr)->next != NULL) {
            ptr2 = (ptr)->next;
            free(ptr);
            ptr = ptr2;
        };
    };   
};

void PushElement(PrioQueueUnit** root, PrioEl inel) {
    if (*root != NULL) {
        PrioQueueUnit* curptr = *root, *prevptr = NULL, *plptr = (PrioQueueUnit*)malloc(sizeof(PrioQueueUnit));
        plptr->el = inel;
            while ((curptr != NULL)&&(inel.prio <= curptr->el.prio)) {
                prevptr = curptr;
                curptr = prevptr->next;
            };
            if (prevptr != NULL)
                prevptr->next = plptr;
            else
                *root = plptr;
            plptr->next = curptr;
    }
    else {
        *root = (PrioQueueUnit*)malloc(sizeof(PrioQueueUnit));
        (*root)->el = inel;
        (*root)->next = NULL;
    };
};

PrioQueueUnit* fInitPrioQueue(FILE* fptr) {
    PrioQueueUnit* root = InitPrioQueue();
    PrioEl element;
    while(fscanf(fptr, "%d%*c%d%*c", &element.prio, &element.data) != EOF) {
        PushElement(&root, element);
    };
    return root;
};


PrioEl PopElement(PrioQueueUnit* root) {
    if (root != NULL) {
        PrioQueueUnit bstr = *root;
        free(root);
        root = bstr.next;
        return bstr.el;
    }
    else {
        printf("Очередь пуста или не существует\n");
    }
};

void PrintQueue(FILE* fptr, PrioQueueUnit* root) {
    if (root != NULL) {
        PrioQueueUnit* curptr = root;
        while (curptr != NULL) {
            fprintf(fptr, "[%d, %d] ", curptr->el.prio, curptr->el.data);
            curptr = curptr->next;
        };
        printf("\n");
    }
    else {
        printf("Очередь пуста или не существует\n");
    }
};

int QueueCmp(PrioQueueUnit* q1, PrioQueueUnit* q2) {
    if ((q1 == NULL) || (q2 == NULL))
        return q1==q2;
    while ((q1->next != NULL) && (q2->next != NULL)) {
        if ((q1->el.data != q2->el.data) || (q1->el.prio != q2->el.prio))
            return 0;
        q1 = q1->next;
        q2 = q2->next;
    };
    return (q1->next == q2->next) && (q1->el.data == q2->el.data) && (q1->el.prio == q2->el.prio);
};