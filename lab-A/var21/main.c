#include "main.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS

Node* createNode(const char* word, int key) {
	setlocale(LC_ALL, "russian");
	Node* node = (Node*)malloc(sizeof(Node));
	if (!node) {
		fprintf(stderr, "Ошибка выделения памяти\n");
		exit(1);
	}
	strncpy(node->word, word, MAX_WORD_LEN - 1);
	node->word[MAX_WORD_LEN - 1] = '\0';
	node->key = key;
	node->next = NULL;
	return node;
}

Node* insertSorted(Node* head, const char* word, int key) {
	if (!head || key < head->key) {
		Node* n = createNode(word, key);
		n->next = head;
		return n;
	}

	Node* cur = head;
	while (cur->next && cur->next->key < key)
		cur = cur->next;

	if ((cur->key == key) || (cur->next && cur->next->key == key)) {
		setlocale(LC_ALL, "russian");
		printf("Ошибка: повтор ключа %d\n", key);
		return head;
	}

	Node* n = createNode(word, key);
	n->next = cur->next;
	cur->next = n;
	return head;
}

void printList(Node* head) {
	Node* p = head;
	while (p) {
		printf("%s %d\n", p->word, p->key);
		p = p->next;
	}
}

void findWord(Node* head, int searchKey) {
	setlocale(LC_ALL, "russian");
	Node* p = head;
	while (p) {
		if (p->key == searchKey) {
			printf("Найдено слово: %s (ключ %d)\n", p->word, p->key);
			return;
		}
		p = p->next;
	}
	printf("Слова с ключом %d не найдено.\n", searchKey);
}

void freeList(Node* head) {
	while (head) {
		Node* t = head;
		head = head->next;
		free(t);
	}
}

//int main() {
//	setlocale(LC_ALL, "russian");
//	Node* head = NULL;
//	FILE* f = fopen("data.txt", "r");
//	if (!f) {
//		printf("Не удалось открыть файл.\n");
//		return 1;
//	}
//
//	char word[MAX_WORD_LEN];
//	int key;
//	while (fscanf(f, "%s %d", word, &key) == 2)
//		head = insertSorted(head, word, key);
//	fclose(f);
//
//	printf("Список из файла:\n");
//	printList(head);
//
//	printf("Введите ключ для поиска: ");
//	scanf("%d", &key);
//	findWord(head, key);
//
//	freeList(head);
//	return 0;
//}
