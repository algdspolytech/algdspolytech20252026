#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "topological_sort.h"


#define MAX_WORDS 100
#define MAX_WORD_LEN 50
#define MAX_EDGES 100

// Функции для работы с очередью
Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->head = q->tail = NULL;
    return q;
}

int is_empty(Queue* q) {
    return q->head == NULL;
}

void enqueue(Queue* q, const char* word) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->word, word);
    new_node->next = NULL;

    if (q->tail == NULL) {
        q->head = q->tail = new_node;
    }
    else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

char* dequeue(Queue* q) {
    if (is_empty(q)) {
        return NULL;
    }

    Node* temp = q->head;
    char* word = (char*)malloc(MAX_WORD_LEN * sizeof(char));
    strcpy(word, temp->word);

    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    free(temp);
    return word;
}

void free_queue(Queue* q) {
    while (!is_empty(q)) {
        char* word = dequeue(q);
        free(word);
    }
    free(q);
}

// Функции для работы с графом
int find_vertex_index(Graph* graph, const char* word) {
    for (int i = 0; i < graph->vertex_count; i++) {
        if (strcmp(graph->vertices[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

int add_vertex(Graph* graph, const char* word) {
    int index = find_vertex_index(graph, word);
    if (index == -1) {
        strcpy(graph->vertices[graph->vertex_count].word, word);
        graph->vertices[graph->vertex_count].in_degree = 0;
        graph->vertices[graph->vertex_count].adj_list = NULL;
        graph->vertex_count++;
        return graph->vertex_count - 1;
    }
    return index;
}

void add_edge(Graph* graph, const char* from, const char* to) {
    int from_index = add_vertex(graph, from);
    int to_index = add_vertex(graph, to);

    AdjNode* new_adj = (AdjNode*)malloc(sizeof(AdjNode));
    new_adj->vertex_index = to_index;
    new_adj->next = graph->vertices[from_index].adj_list;
    graph->vertices[from_index].adj_list = new_adj;

    graph->vertices[to_index].in_degree++;
}

void free_graph(Graph* graph) {
    for (int i = 0; i < graph->vertex_count; i++) {
        AdjNode* current = graph->vertices[i].adj_list;
        while (current != NULL) {
            AdjNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

// Топологическая сортировка
int topological_sort(Graph* graph, char result[][MAX_WORD_LEN]) {
    Queue* q = create_queue();
    int result_count = 0;

    // Добавляем вершины с нулевой степенью входа
    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->vertices[i].in_degree == 0) {
            enqueue(q, graph->vertices[i].word);
        }
    }

    while (!is_empty(q)) {
        char* current_word = dequeue(q);
        strcpy(result[result_count++], current_word);
        free(current_word);

        int current_index = find_vertex_index(graph, result[result_count - 1]);

        // Уменьшаем степень входа соседей
        AdjNode* adj = graph->vertices[current_index].adj_list;
        while (adj != NULL) {
            int neighbor_index = adj->vertex_index;
            graph->vertices[neighbor_index].in_degree--;

            if (graph->vertices[neighbor_index].in_degree == 0) {
                enqueue(q, graph->vertices[neighbor_index].word);
            }

            adj = adj->next;
        }
    }

    free_queue(q);

    // Проверяем наличие цикла
    if (result_count != graph->vertex_count) {
        return 0; // Есть цикл
    }

    return result_count;
}

// Функция для чтения входных данных
int read_input(const char* filename, WordSet* word_set, Edge edges[], int* edge_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return 0;
    }

    char line[1000];

    // Читаем первую строку со словами
    if (!fgets(line, sizeof(line), file)) {
        fclose(file);
        return 0;
    }

    // Парсим слова из первой строки
    char* token = strtok(line, " \n");
    word_set->count = 0;
    while (token != NULL && word_set->count < MAX_WORDS) {
        strcpy(word_set->words[word_set->count], token);
        word_set->count++;
        token = strtok(NULL, " \n");
    }

    // Читаем ребра
    *edge_count = 0;
    while (fgets(line, sizeof(line), file)) {
        // Пропускаем пустые строки
        int is_empty_line = 1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (!isspace(line[i])) {
                is_empty_line = 0;
                break;
            }
        }

        if (is_empty_line) {
            continue;
        }

        char* first = strtok(line, " \n");
        char* second = strtok(NULL, " \n");

        if (first != NULL && second != NULL && *edge_count < MAX_EDGES) {
            strcpy(edges[*edge_count].from, first);
            strcpy(edges[*edge_count].to, second);
            (*edge_count)++;
        }
    }

    fclose(file);
    return 1;
}

// Функция для записи результата
void write_output(const char* filename, char result[][MAX_WORD_LEN], int count, int has_cycle) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        return;
    }

    if (has_cycle) {
        fprintf(file, "[Error]");
    }
    else {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s", result[i]);
            if (i < count - 1) {
                fprintf(file, " ");
            }
        }
    }

    fclose(file);
}

