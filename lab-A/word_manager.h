#pragma once
#ifndef WORD_MANAGER_H
#define WORD_MANAGER_H

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

typedef struct {
    char word[MAX_WORD_LENGTH];
    int key;
} WordData;

// Объявления функций
int readFile(const char* filename, WordData data[]);
int hasDuplicateKeys(WordData data[], int count);
void insertSorted(WordData data[], int* count, const char* word, int key);
void printData(WordData data[], int count);
void searchByKey(WordData data[], int count, int searchKey);

#endif