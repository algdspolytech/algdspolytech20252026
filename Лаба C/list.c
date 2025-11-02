#include <stdlib.h>
#include <locale.h>
#include "config.h"
#include "list.h"


void safe_string_copy(char* dest, const char* src, int max_len) {
    int i;
    for (i = 0; i < max_len - 1 && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

void init_graph(Graph* graph) {
    graph->node_count = 0;
}

Node* find_node(Graph* graph, const char* word) {
    for (int i = 0; i < graph->node_count; i++) {
        if (graph->nodes[i] != NULL && strcmp(graph->nodes[i]->word, word) == 0) {
            return graph->nodes[i];
        }
    }
    return NULL;
}

Node* add_node(Graph* graph, const char* word) {
    Node* existing = find_node(graph, word);
    if (existing != NULL) {
        return existing;
    }

    if (graph->node_count >= MAX_WORDS) {
        return NULL;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }

    safe_string_copy(new_node->word, word, MAX_WORD_LEN);
    new_node->in_degree = 0;
    new_node->index = graph->node_count;
    new_node->neighbors = NULL;
    new_node->neighbor_count = 0;

    graph->nodes[graph->node_count] = new_node;
    graph->node_count++;
    return new_node;
}

void add_edge(Graph* graph, const char* from, const char* to) {
    Node* from_node = add_node(graph, from);
    Node* to_node = add_node(graph, to);

    if (from_node == NULL || to_node == NULL) {
        return;
    }

    // Проверка на дубликат ребра
    for (int i = 0; i < from_node->neighbor_count; i++) {
        if (from_node->neighbors[i] == to_node) {
            return;
        }
    }

    // Безопасное расширение массива соседей
    Node** temp = (Node**)realloc(from_node->neighbors,
        (from_node->neighbor_count + 1) * sizeof(Node*));
    if (temp == NULL) {
        return;
    }
    from_node->neighbors = temp;

    from_node->neighbors[from_node->neighbor_count] = to_node;
    from_node->neighbor_count++;
    to_node->in_degree++;
}

bool topological_sort(Graph* graph, char result[][MAX_WORD_LEN]) {
    if (graph->node_count == 0) {
        return true;
    }

    int in_degree[MAX_WORDS];
    for (int i = 0; i < graph->node_count; i++) {
        in_degree[i] = graph->nodes[i]->in_degree;
    }

    int result_index = 0;

    while (result_index < graph->node_count) {
        int selected_index = -1;
        for (int i = 0; i < graph->node_count; i++) {
            if (in_degree[i] == 0) {
                selected_index = i;
                break;
            }
        }

        if (selected_index == -1) {
            return false; // цикл
        }

        in_degree[selected_index] = -1;
        safe_string_copy(result[result_index], graph->nodes[selected_index]->word, MAX_WORD_LEN);
        result_index++;

        for (int j = 0; j < graph->nodes[selected_index]->neighbor_count; j++) {
            Node* neighbor = graph->nodes[selected_index]->neighbors[j];
            in_degree[neighbor->index]--;
        }
    }

    return true;
}

void free_graph(Graph* graph) {
    for (int i = 0; i < graph->node_count; i++) {
        if (graph->nodes[i] != NULL) {
            free(graph->nodes[i]->neighbors);
            free(graph->nodes[i]);
        }
    }
}

int parse_words(const char* line, char words[][MAX_WORD_LEN]) {
    int word_count = 0;
    int char_index = 0;
    int i = 0;

    while (line[i] != '\0' && word_count < MAX_WORDS) {
        if (line[i] == ' ' || line[i] == '\n' || line[i] == '\r' || line[i] == '\t') {
            if (char_index > 0) {
                words[word_count][char_index] = '\0';
                word_count++;
                char_index = 0;
            }
        }
        else {
            if (char_index < MAX_WORD_LEN - 1) {
                words[word_count][char_index] = line[i];
                char_index++;
            }
        }
        i++;
    }

    if (char_index > 0) {
        words[word_count][char_index] = '\0';
        word_count++;
    }

    return word_count;
}