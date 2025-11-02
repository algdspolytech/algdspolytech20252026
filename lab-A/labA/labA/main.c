#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int compareWords(const char* word1, const char* word2) {
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    if (len1 != len2) return len1 - len2;
    return strcmp(word1, word2);
}

void InsertWord(struct Item** head, const char* word) {
    struct Item* NewItem = (struct Item*)malloc(sizeof(struct Item));
    NewItem->Word = (char*)malloc(strlen(word) + 1);
    strcpy(NewItem->Word, word);
    if (*head == NULL || compareWords(word, (*head)->Word) < 0) {
        NewItem->NextItem = *head;
        *head = NewItem;
        return;
    }
    struct Item* current = *head;
    while (current->NextItem != NULL && compareWords(word, current->NextItem->Word) > 0) {
        current = current->NextItem;
    }
    NewItem->NextItem = current->NextItem;
    current->NextItem = NewItem;
}

void PrintLongWords(struct Item* head, int n) {
    struct Item* current = head;
    printf("Words longer than %d characters:\n", n);
    while (current != NULL) {
        if (strlen(current->Word) > n) {
            printf("%s\n", current->Word);
        }
        current = current->NextItem;
    }
}

void PrintWordsByLength(struct Item* head, int length) {
    struct Item* current = head;
    int found = 0;
    printf("Words with length %d:\n", length);
    while (current != NULL) {
        if (strlen(current->Word) == length) {
            printf("%s\n", current->Word);
            found = 1;
        }
        current = current->NextItem;
    }
    if (!found) {
        printf("No words with this length\n");
    }
}

void FreeList(struct Item* head) {
    struct Item* current = head;
    while (current != NULL) {
        struct Item* temp = current;
        current = current->NextItem;
        free(temp->Word);
        free(temp);
    }
}