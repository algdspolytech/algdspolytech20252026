#ifndef GRAPH_COLORING_H
#define GRAPH_COLORING_H
#include <stdbool.h>

// В структуре graph я храню матрицу смежности для ускорения проверки соседей

typedef struct {
    int n;
    bool** adj;
} Graph;

// Работа с памятью

// Функция создания графа
Graph* createGraph(int n);
// Функция очистки графа
void freeGraph(Graph* g);

// Проверка валидности покраски
bool isSafe(Graph* g, const int* colors, int v, int K);

// Рекурсивная функция поиска с возвратом, которая пытается покрасить вершины,
// начиная с v
bool graphColoringRecursive(Graph* g, int* colors, int v, int K);

// Основная функция для внешнего вызова, которую мы будем тестировать. Будет
// возврашать true, если раскраска будет найдена и запишет цвета в result_colors
bool graphColoring(Graph* g, int K, int* result_colors);

// Функция чтения графа по списку смежности из файла
bool readGraphFromFile(const char* filename, Graph** graph, int* K);

// Функция вывода цвета вершин, если K раскраскка существует
bool writeResultToFile(const char* filename, const int* colors, int n,
                       bool successs);

#endif
