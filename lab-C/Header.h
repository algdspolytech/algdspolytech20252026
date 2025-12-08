#ifndef SOURCE_H
#define SOURCE_H
#include <stdbool.h>

typedef struct node {
    int value;
    struct node* next;
} node;

typedef struct {
    int numbers;
    int* mas_of_visited;
    node** mas;
} Graf;


node* Create_Node(int a);
void Create_Graf(Graf* G, int n);
void Add_Edge(Graf* G, int src, int dest);
bool IsWay(Graf* G, int cur, int target);
void PrintGraf(Graf G);
int ReadFile(const char* filename, Graf* G);
void FreeGraf(Graf* G);
#endif // !1
