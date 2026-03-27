#pragma once
#ifndef MAIN_H
#define MAIN_H

#define MAX_WORD_LEN 100

typedef struct Node {
	char word[MAX_WORD_LEN];
	int key;
	struct Node* next;
} Node;

Node* createNode(const char* word, int key);
Node* insertSorted(Node* head, const char* word, int key);
void printList(Node* head);
void findWord(Node* head, int searchKey);
void freeList(Node* head);

#endif
