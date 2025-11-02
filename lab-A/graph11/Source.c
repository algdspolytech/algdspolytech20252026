#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable: 4996)

int_t* ReadTolong() {
    int_t* head = NULL;
    char c;

    printf("¬ведите число:");
    while (1) {
        c = getchar();
        if (c == '\n') {
            break;
        }
        int digit = c - '0';
        int_t* nnode = Createnode(digit);
        nnode->next = head;
        head = nnode;
    }
    return head;
}

int_t* Add(int_t* a, int_t* b) {
    int_t* head = NULL;
    int_t* back = NULL;
    int adds = 0;
    while (a != NULL || b != NULL || adds != 0) {
        int sum = adds;
        if (a != NULL) {
            sum += a->digit;
            a = a->next;
        }
        if (b != NULL) {
            sum += b->digit;
            b = b->next;
        }
        if (sum > 9) {
            adds = 1;
            sum -= 10;
        }
        else {
            adds = 0;
        }
        int_t* nnode = Createnode(sum);
        if (head == NULL) {
            head = nnode;
            back = nnode;
        }
        else {
            back->next = nnode;
            back = nnode;
        }
    }
    return head;
}

int_t* Mul(int_t* a, int_t* b) {
    int_t* total = Createnode(0);
    int deg = 0;
    int_t* a1 = a;
    while (a1 != NULL) {
        int_t* b1 = b;
        int_t* head = NULL;
        int_t* back = NULL;
        int adds = 0;
        while (b1 != NULL || adds != 0) {
            int pro = adds;
            if (b1 != NULL) {
                pro += a1->digit * b1->digit;
                b1 = b1->next;
            }
            adds = pro / 10;
            pro = pro % 10;
            int_t* nnode = Createnode(pro);
            if (head == NULL) {
                head = nnode;
                back = nnode;
            }
            else {
                back->next = nnode;
                back = nnode;
            }
        }
        a1 = a1->next;
        Mul10x(&head, deg);
        int_t* total1 = Add(total, head);
        FreeList(total);
        FreeList(head);
        total = total1;
        deg++;
    }
    return total;
}

int_t* Poww(int_t* a, int_t* b) {
    int_t* b1 = b;
    int_t* c = Createnode(1);
    int mul = 1;
    while (b1 != NULL) {
        for (int i = 0; i < (b1->digit * mul); i++) {
            int_t* c1 = Mul(c, a);
            FreeList(c);
            c = c1;
        }
        b1 = b1->next;
        mul *= 10;
    }
    return c;
}

int StrLen(const char* s) {
    int k = 0;
    while (s[k] != '\0') {
        k++;
    }
    return k;
}

void Mul10x(int_t** a, int x) {
    if (x > 0) {
        for (int i = 0; i < x; i++) {
            int_t* node = Createnode(0);
            node->next = *a;
            *a = node;
        }
    }
}

int_t* Createnode(int digit) {
    int_t* node = (int_t*)malloc(sizeof(int_t));
    node->digit = digit;
    node->next = NULL;
    return node;
}

void Bend(int_t** head, int digit) {
    int_t* nnode = Createnode(digit);
    nnode->next = *head;
    *head = nnode;
}

void FreeList(int_t* a) {
    while (a != NULL) {
        int_t* temp = a;
        a = a->next;
        free(temp);
    }
}

void PrintLong(int_t* a) {
    if (a == NULL) {
        printf("0");
        return;
    }
    if (a->next != NULL) {
        PrintLong(a->next);
    }
    printf("%i", a->digit);
}