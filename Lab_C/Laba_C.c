
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

typedef struct Node {
    char word[MAX_WORD_LEN];
    int index;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

// Функции для работы со списком
void init_list(LinkedList* list) {
    list->head = NULL;
}

void add_to_list(LinkedList* list, const char* word, int index) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    strcpy(new_node->word, word);
    new_node->index = index;
    new_node->next = list->head;
    list->head = new_node;
}

int find_in_list(LinkedList* list, const char* word) {
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            return current->index;
        }
        current = current->next;
    }
    return -1;
}

void free_list(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

// Функция для топологической сортировки (алгоритм Кана)
int topological_sort(int n, int graph[MAX_WORDS][MAX_WORDS], int* order) {
    int in_degree[MAX_WORDS] = { 0 };

    // Вычисляем полустепень захода для каждой вершины
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j]) {
                in_degree[j]++;
            }
        }
    }

    // Находим вершины с нулевой полустепенью захода
    int queue[MAX_WORDS];
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            queue[rear++] = i;
        }
    }

    int count = 0;
    while (front < rear) {
        int u = queue[front++];
        order[count++] = u;

        for (int v = 0; v < n; v++) {
            if (graph[u][v]) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    return (count == n) ? 1 : 0; // Успех если все вершины обработаны
}

int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    char line[1000];
    char words[MAX_WORDS][MAX_WORD_LEN];
    int graph[MAX_WORDS][MAX_WORDS] = { 0 };
    LinkedList word_list;
    init_list(&word_list);

    int word_count = 0;

    // Читаем первую строку - слова множества V
    if (fgets(line, sizeof(line), input) != NULL) {
        char* token = strtok(line, " \t\n");
        while (token != NULL && word_count < MAX_WORDS) {
            strcpy(words[word_count], token);
            add_to_list(&word_list, token, word_count);
            word_count++;
            token = strtok(NULL, " \t\n");
        }
    }

    // Читаем остальные строки - пары предшествования
    while (fgets(line, sizeof(line), input) != NULL) {
        // Пропускаем пустые строки
        int empty = 1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (!isspace(line[i])) {
                empty = 0;
                break;
            }
        }
        if (empty) continue;

        char word1[MAX_WORD_LEN], word2[MAX_WORD_LEN];
        if (sscanf(line, "%s %s", word1, word2) == 2) {
            int idx1 = find_in_list(&word_list, word1);
            int idx2 = find_in_list(&word_list, word2);

            if (idx1 != -1 && idx2 != -1) {
                graph[idx1][idx2] = 1;
            }
        }
    }

    // Выполняем топологическую сортировку
    int order[MAX_WORDS];
    int success = topological_sort(word_count, graph, order);

    if (success) {
        // Выводим результат
        for (int i = 0; i < word_count; i++) {
            fprintf(output, "%s", words[order[i]]);
            if (i < word_count - 1) {
                fprintf(output, " ");
            }
        }
        fprintf(output, "\n");
    }
    else {
        fprintf(output, "[Error]\n");
    }

    // Очищаем ресурсы
    free_list(&word_list);
    fclose(input);
    fclose(output);

    return 0;
}