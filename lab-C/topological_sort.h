#pragma once
#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

// Структура для хранения графа
typedef struct {
    int vertices;
    int adj_matrix[MAX_WORDS][MAX_WORDS];
    char words[MAX_WORDS][MAX_WORD_LEN];
    int word_count;
} Graph;

// Функции, объявленные в заголовочном файле

Graph* create_graph_from_file(const char* filename);

int topological_sort(Graph* g, int* sorted_indices);
int write_result_to_file(Graph* g, int* sorted_indices, const char* filename);
int find_word_index(Graph* g, const char* word);
int add_word(Graph* g, const char* word);

#endif 