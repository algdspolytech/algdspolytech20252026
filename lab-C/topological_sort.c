#define _CRT_SECURE_NO_WARNINGS
#include "topological_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

// Вспомогательная функция для поиска индекса слова в графе
int find_word_index(Graph* g, const char* word) {
    if (!g || !word) {
        return -1;
    }
    for (int i = 0; i < g->word_count; i++) {
        if (strcmp(g->words[i], word) == 0) { 
            return i;
        }
    }
    return -1;
}

// Вспомогательная функция для добавления уникального слова в граф
int add_word(Graph* g, const char* word) {
    if (!g || !word) {
        return -1;
    }
    if (g->word_count >= MAX_WORDS) {
        return -1; 
    }
    if (find_word_index(g, word) != -1) {
        return 0; 
    }
    strcpy(g->words[g->word_count], word); 
    g->word_count++;
    return 0;
}

// Реализация функции create_graph_from_file
Graph* create_graph_from_file(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    Graph* g = (Graph*)malloc(sizeof(Graph));
    if (!g) {
        fclose(file);
        return NULL; 
    }
    g->vertices = 0;
    g->word_count = 0;
    for (int i = 0; i < MAX_WORDS; i++) {
        for (int j = 0; j < MAX_WORDS; j++) {
            g->adj_matrix[i][j] = 0;
        }
    }

    char word1[MAX_WORD_LEN];
    char word2[MAX_WORD_LEN];

    int c;
    int word_idx = 0;
    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (c == ' ') {
            if (word_idx > 0) { 
                word1[word_idx] = '\0';
                add_word(g, word1);
                word_idx = 0;
            }
        }
        else if (c != ' ') {
            if (word_idx < MAX_WORD_LEN - 1) {
                word1[word_idx++] = c;
            }
        }
    }
    if (word_idx > 0) { 
        word1[word_idx] = '\0';
        add_word(g, word1);
    }

    // Считываем оставшиеся строки - множество рёбер E
    while (fscanf(file, "%s %s", word1, word2) == 2) {
        int u_idx = find_word_index(g, word1);
        int v_idx = find_word_index(g, word2);

        if (u_idx != -1 && v_idx != -1) {
            g->adj_matrix[u_idx][v_idx] = 1;
        }
    }

    g->vertices = g->word_count;
    fclose(file);
    return g;
}

// Вспомогательная функция для нахождения лексикографически наименьшей вершины с in_degree = 0
int find_min_index_with_zero_in_degree(int* in_degree, Graph* g, int* visited) {
    int min_idx = -1;
    char min_word[MAX_WORD_LEN] = { 0 };

    for (int i = 0; i < g->vertices; i++) {
        if (!visited[i] && in_degree[i] == 0) {
            if (min_idx == -1 || strcmp(g->words[i], min_word) < 0) {
                min_idx = i;
                strcpy(min_word, g->words[i]);
            }
        }
    }
    return min_idx;
}

// Реализация функции topological_sort с лексикографическим порядком
int topological_sort(Graph* g, int* sorted_indices) {
    if (!g || !sorted_indices) {
        return -1;
    }

    int in_degree[MAX_WORDS] = { 0 };
    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            if (g->adj_matrix[i][j]) {
                in_degree[j]++;
            }
        }
    }

    int visited[MAX_WORDS] = { 0 };
    int index = 0;

    for (int count = 0; count < g->vertices; count++) {
        int u = find_min_index_with_zero_in_degree(in_degree, g, visited);
        if (u == -1) {
            return -1;
        }

        sorted_indices[index++] = u;
        visited[u] = 1;

        for (int v = 0; v < g->vertices; v++) {
            if (g->adj_matrix[u][v]) {
                in_degree[v]--;
            }
        }
    }

    if (index != g->vertices) {
        return -1;
    }

    return 0; 
}

// Реализация функции write_result_to_file
int write_result_to_file(Graph* g, int* sorted_indices, const char* filename) {
    if (!g || !sorted_indices || !filename) {
        return -1;
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        return -1;
    }

    for (int i = 0; i < g->vertices; i++) {
        fprintf(file, "%s", g->words[sorted_indices[i]]);
        if (i < g->vertices - 1) {
            fprintf(file, " ");
        }
    }
    fprintf(file, "\n");
    fclose(file);
    return 0;
}