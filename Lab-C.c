#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#define MAX_SIZE 100

// Структуры для графов
typedef struct {
    int n;                          // количество вершин
    int list[MAX_SIZE][MAX_SIZE];   // списки смежности
    int sizes[MAX_SIZE];            // размеры списков
} GraphList;

typedef struct {
    int n;                          // количество вершин
    int matrix[MAX_SIZE][MAX_SIZE]; // матрица смежности
} GraphMatrix;

// Инициализация графа-списка
void init_list(GraphList* g, int vertices) {
    g->n = vertices;
    for (int i = 0; i < vertices; i++) {
        g->sizes[i] = 0;
        for (int j = 0; j < vertices; j++) {
            g->list[i][j] = -1;
        }
    }
}

// Инициализация графа-матрицы
void init_matrix(GraphMatrix* g, int vertices) {
    g->n = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->matrix[i][j] = 0;
        }
    }
}

// Чтение графа из файла в формате списков
bool read_list(const char* filename, GraphList* g) {
    FILE* f = fopen(filename, "r");
    if (!f) return false;

    char line[256];
    int count = 0;

    // Считаем количество строк (вершин)
    while (fgets(line, sizeof(line), f)) {
        count++;
    }

    rewind(f);
    init_list(g, count);

    // Читаем списки смежности
    for (int i = 0; i < count && fgets(line, sizeof(line), f); i++) {
        char* token = strtok(line, " \n");
        int pos = 0;

        while (token) {
            int neighbor = atoi(token);
            if (neighbor >= 0) {
                g->list[i][pos++] = neighbor;
            }
            token = strtok(NULL, " \n");
        }
        g->sizes[i] = pos;
    }

    fclose(f);
    return true;
}

// Чтение графа из файла в формате матрицы
bool read_matrix(const char* filename, GraphMatrix* g) {
    FILE* f = fopen(filename, "r");
    if (!f) return false;

    char line[256];
    int n = 0;

    // Определяем размер матрицы по первой строке
    if (fgets(line, sizeof(line), f)) {
        char* token = strtok(line, " \n");
        while (token) {
            n++;
            token = strtok(NULL, " \n");
        }
    }

    rewind(f);
    init_matrix(g, n);

    // Читаем матрицу
    for (int i = 0; i < n && fgets(line, sizeof(line), f); i++) {
        char* token = strtok(line, " \n");
        for (int j = 0; j < n && token; j++) {
            g->matrix[i][j] = atoi(token);
            token = strtok(NULL, " \n");
        }
    }

    fclose(f);
    return true;
}

// Проверка эквивалентности графов
bool graphs_equal(const GraphList* list, const GraphMatrix* matrix) {
    if (list->n != matrix->n) return false;

    int n = list->n;

    // Проверяем, что все ребра из списка есть в матрице
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < list->sizes[i]; j++) {
            int to = list->list[i][j];
            if (matrix->matrix[i][to] != 1) {
                return false;
            }
        }
    }

    // Проверяем, что все ребра из матрицы есть в списке
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix->matrix[i][j] == 1) {
                int found = 0;
                for (int k = 0; k < list->sizes[i]; k++) {
                    if (list->list[i][k] == j) {
                        found = 1;
                        break;
                    }
                }
                if (!found) return false;
            }
        }
    }

    return true;
}

int main() {
    setlocale(LC_CTYPE, "Russian");

    GraphList list_graph;
    GraphMatrix matrix_graph;

    if (!read_list("list.txt", &list_graph)) {
        printf("Ошибка: не могу открыть list.txt\n");
        return 1;
    }

    if (!read_matrix("matrix.txt", &matrix_graph)) {
        printf("Ошибка: не могу открыть matrix.txt\n");
        return 1;
    }
    printf("Список смежности: %d вершин\n", list_graph.n);
    printf("Матрица смежности: %d вершин\n", matrix_graph.n);

    if (graphs_equal(&list_graph, &matrix_graph)) {
        printf("\nГрафы идентичны :)\n");
    }
    else {
        printf("\nГрафы различаются :(\n");
    }

    return 0;
}