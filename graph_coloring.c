#include "graph_coloring.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Graph* createGraph(int n) {
    Graph* g = (Graph*)malloc(n * sizeof(Graph));
    if (!g) return NULL;
    g->n = n;
    g->adj = (bool**)malloc(n * sizeof(bool*));
    for (int i = 0; i < n; i++) {
        g->adj[i] = (bool*)calloc(
            n * sizeof(bool),
            sizeof(bool));  // все биты для переменной типа bool обнуляются, что
                            // соответствует типу false. Т.о. матрица связности
                            // инициализируется успешно
        // На всякий - освобождение памяти при ошибке
        if (!g->adj[i]) {
            for (int k = 0; k < i; k++) {
                free(g->adj[k]);
            }
            free(g->adj);
            free(g);
            return NULL;
        }
    }
    return g;
}

void freeGraph(Graph* g) {
    if (!g) {
        return;
    }
    for (int k = 0; k < g->n; k++) {
        free(g->adj[k]);
    }
    free(g->adj);
    free(g);
}

// Функция проверяет, нет ли у вершины v сосед заданного цвета с (цвета вершин
// хранятся в списке colors[v])
bool isSafe(Graph* g, const int* colors, int v, int c) {
    for (int i = 0; i < g->n; i++) {
        if (i != v && g->adj[v][i] && colors[i] == c) {
            return false;
        }
    }
    return true;
}

bool graphColoringRecursive(Graph* g, int* colors, int v, int K) {
    // Если мы смогли успешно пройти v вершин, то наконец верни true. Здесь под
    // номером вершины подразумевается v - 1 (для индексации массивов), поэтому
    // и проверка равенству n (значит - пришли к n + 1 вершине)
    if (v == g->n) {
        return true;
    }
    for (int c = 1; c <= K; c++) {
        if (isSafe(g, colors, v, c)) {
            colors[v] = c;
            if (graphColoringRecursive(g, colors, v + 1, K)) {
                return true;
            }
            // Для следующей вершины ни один цвет не подошёл, потому стираем у
            // этой цвет (0 - нет цвета)
            colors[v] = 0;
        }
    }
    return false;
}

bool graphColoring(Graph* g, int K, int* result_colors) {
    if (!g || K <= 0) {
        return false;  // Проверка на правильность параметров
    }
    int* colors = (int*)malloc(
        g->n * sizeof(int));  // Внутри создам массив для накопления ответа
    if (!colors) {
        return false;
    }
    for (int i = 0; i < g->n; i++) {
        colors[i] = 0;
    }
    bool success = graphColoringRecursive(g, colors, 0, K);
    if (success) {
        // Копируем значения внцтреннего массива colors во внешний found_colors
        for (int i = 0; i < g->n; i++) {
            result_colors[i] = colors[i];
        }
    }
    free(colors);
    return success;
}

// Функция чтения графа из файла по списку смежных вершин для каждой. Передаю
// указатель на ячейку памати, содержащую указатель на структуру Graph (чтобы
// снаружи можно было передать адрес указателя, а эта функция при выполнении
// присвоила бы туда указатель на созданный внутри граф). Аналогично с числом K
bool readGraphFromFile(const char* filename, Graph** graph, int* K) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        return false;
    }
    int n;

    // Проверка на корректность первой строки
    if (fscanf(f, "%d %d", &n, K) != 2) {
        fclose(f);
        return false;
    }

    *graph = createGraph(n);
    if (!*graph) {
        fclose(f);
        return false;
    }

    for (int i = 0; i < n; i++) {
        int neighbor;
        // Последовательно считываем из файла по числу
        while (fscanf(f, "%d", &neighbor) == 1) {
            if (neighbor >= 1 && neighbor <= n) {
                (*graph)->adj[i][neighbor - 1] =
                    true;  // neighbor - 1 для индексации с нуля
                (*graph)->adj[i][neighbor - 1] = true;  // граф неориентирован
            }
        }
        int character;
        while ((character = fgetc(f)) != '\n' &&
               character != EOF);  // Считываем по символу, пока не съедим \n
                                   // или EOF. В случае \n следующий fscanf
                                   // начнёт с числой новой строки
    }

    fclose(f);
    return true;
}

// Запись результата в файл. Если success == true - записываем список цветов
// через пробел, иначе просто 0. Результат функции - true, если успешно записано
// и false, если нет
bool writeResultToFile(const char* filename, const int* colors, int n,
                       bool success) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        return false;  //
    }
    if (!success) {
        fprintf(f, "0");
    } else {
        for (int i = 0; i < n; i++) {
            fprintf(f, "%d ", colors[i]);
        }
    }
    fclose(f);
    return true;
}