#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

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

// Функция для тестирования - создает временные файлы
void run_test(const char* input_content, const char* expected_output, const char* test_name) {
    printf("Running test: %s\n", test_name);

    // Создаем входной файл
    FILE* input = fopen("test_input.txt", "w");
    fprintf(input, "%s", input_content);
    fclose(input);

    // Запускаем основную программу на тестовых данных
    FILE* input_file = fopen("test_input.txt", "r");
    FILE* output_file = fopen("test_output.txt", "w");

    char line[1000];
    char words[MAX_WORDS][MAX_WORD_LEN];
    int graph[MAX_WORDS][MAX_WORDS] = { 0 };
    LinkedList word_list;
    init_list(&word_list);

    int word_count = 0;

    // Читаем первую строку - слова множества V
    if (fgets(line, sizeof(line), input_file) != NULL) {
        char* token = strtok(line, " \t\n");
        while (token != NULL && word_count < MAX_WORDS) {
            strcpy(words[word_count], token);
            add_to_list(&word_list, token, word_count);
            word_count++;
            token = strtok(NULL, " \t\n");
        }
    }

    // Читаем остальные строки - пары предшествования
    while (fgets(line, sizeof(line), input_file) != NULL) {
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
        for (int i = 0; i < word_count; i++) {
            fprintf(output_file, "%s", words[order[i]]);
            if (i < word_count - 1) {
                fprintf(output_file, " ");
            }
        }
        fprintf(output_file, "\n");
    }
    else {
        fprintf(output_file, "[Error]\n");
    }

    free_list(&word_list);
    fclose(input_file);
    fclose(output_file);

    // Проверяем результат
    FILE* result_file = fopen("test_output.txt", "r");
    char result[1000];
    fgets(result, sizeof(result), result_file);
    fclose(result_file);

    // Удаляем символ новой строки
    result[strcspn(result, "\n")] = 0;

    printf("Expected: '%s'\n", expected_output);
    printf("Got:      '%s'\n", result);

    if (strcmp(result, expected_output) == 0) {
        printf("✓ TEST PASSED\n\n");
    }
    else {
        printf("✗ TEST FAILED\n\n");
    }

    // Удаляем временные файлы
    remove("test_input.txt");
    remove("test_output.txt");
}

// Юнит-тесты
void run_all_tests() {
    printf("=== TOPOLOGICAL SORT UNIT TESTS ===\n\n");

    // Тест 1: Простой линейный порядок
    run_test("a b c\n"
        "a b\n"
        "b c",
        "a b c",
        "Simple linear order");

    // Тест 2: Цикл - должен быть ошибка
    run_test("a b c\n"
        "a b\n"
        "b c\n"
        "c a",
        "[Error]",
        "Cycle detection");

    // Тест 3: Несколько независимых цепочек
    run_test("a b c d e\n"
        "a b\n"
        "c d\n"
        "d e",
        "a c b d e",
        "Multiple independent chains");

    // Тест 4: Дерево зависимостей
    run_test("a b c d\n"
        "a b\n"
        "a c\n"
        "b d\n"
        "c d",
        "a b c d",
        "Tree structure");

    // Тест 5: Один элемент
    run_test("hello",
        "hello",
        "Single element");

    // Тест 6: Нет зависимостей - лексикографический порядок
    run_test("z y x a",
        "a x y z",
        "No dependencies");

    // Тест 7: Сложный граф
    run_test("a b c d e f\n"
        "a b\n"
        "a c\n"
        "b d\n"
        "c d\n"
        "d e\n"
        "d f",
        "a b c d e f",
        "Complex graph");

    // Тест 8: Частичный порядок
    run_test("m n o p q\n"
        "m n\n"
        "m o\n"
        "n p\n"
        "o p\n"
        "p q",
        "m n o p q",
        "Partial order");

    // Тест 9: Две отдельные компоненты
    run_test("a b x y\n"
        "a b\n"
        "x y",
        "a x b y",
        "Two separate components");

    // Тест 10: Самоссылка (должна быть ошибка)
    run_test("a b\n"
        "a a",
        "[Error]",
        "Self-reference error");

    printf("=== ALL TESTS COMPLETED ===\n");
}

int main() {
    run_all_tests();
    return 0;
}