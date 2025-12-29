#include "graph.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");

    Graph* graph = graph_read_from_file("graph.txt");
    if (!graph) {
        printf("Ошибка чтения файла\n");
        return 1;
    }

    int** matrix = graph_to_matrix(graph);

    printf("Матрица смежности:\n");
    for (int i = 0; i < graph->vertexCount; i++) {
        for (int j = 0; j < graph->vertexCount; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }

    matrix_destroy(matrix, graph->vertexCount);
    graph_destroy(graph);
    return 0;
}
