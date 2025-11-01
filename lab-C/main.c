#include "func.h"
#include <stdio.h>
#include <locale.h>
int main() {
    setlocale(LC_ALL, "Russia");
    const char* filename = "graph_list.txt";  // файл со списком смежностей
    int n;
    
    // Читаем список смежностей из файла
    struct Graph* graph = readAdjacencyList(filename, &n);
    if (graph == NULL) {
        return 1;
    }
    
    // Выводим исходный список смежностей
    printAdjacencyList(graph);
    printf("\n");
    
    // Строим матрицу смежности
    int** matrix = buildAdjacencyMatrix(graph);
    
    // Выводим матрицу смежности
    printAdjacencyMatrix(matrix, n);
    
    // Освобождаем память
    freeMatrix(matrix, n);
    freeGraph(graph);
    
    return 0;
}