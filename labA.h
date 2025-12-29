#ifndef LAB_A_H
#define LAB_A_H
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 100
#define MAX_WORDS 1000

typedef struct {
	char word[MAX_WORD_LENGTH];
	int length;
} WordInfo;

int compare_words(const void* a, const void* b);

void insert_sorted(WordInfo* words, int* count, const char* new_word);

void print_words_longer_than(WordInfo* words, int count, int N);

void print_words_by_length(WordInfo* words, int count, int target_length);

int read_word(FILE* file, char* buffer);

#endif