#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define WORD_LEN 64
#define LINE_LEN 4096

typedef struct {
    int data[MAX];
    int front, rear;
} Queue;

typedef struct Node {
    int to;
    struct Node* next;
} Node;

typedef struct {
    char words[MAX][WORD_LEN];
    int count;
} WordDictionary;

void initQueue(Queue*);
int isEmpty(Queue*);
void enqueue(Queue*, int);
int dequeue(Queue*);

void initQueue(Queue*);
int isEmpty(Queue*);
void enqueue(Queue*, int);
int dequeue(Queue*);
int str_equal(const char*, const char*);
void str_copy(char*, const char*);
void addEdge(Node* [], int, int);
void initDictionary(WordDictionary*);
int findIndex(const WordDictionary*, const char*);
int addWordIfNew(WordDictionary*, const char*);
int readWord(FILE*, char*);
void parseFirstLine(FILE*, WordDictionary*);
void buildGraph(FILE*, WordDictionary*, Node* [], int[]);
int topologicalSort(Queue*, Node* [], int[], char**, const WordDictionary*);
void initQueueWithZeroDegree(Queue*, const WordDictionary*, const int[]);
void cleanupGraph(Node* []);
char** allocateResultMemory();
void freeResultMemory(char**);
int* allocateInDegreeMemory();
Node** allocateAdjacencyList();
void outputResult(FILE*, char**, int, int);