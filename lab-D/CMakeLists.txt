#include "vertex_cover.h"
#include <stdio.h>

int main() {
    printf("Vertex Cover Problem Solver\n");
    printf("===========================\n\n");

    // Решаем задачу для заданных файлов
    solve_vertex_cover("input.txt", "output.txt");

    printf("Result written to output.txt\n");

    // Выводим результат на экран для проверки
    FILE* output = fopen("output.txt", "r");
    if (output) {
        char result[4096];
        if (fgets(result, sizeof(result), output)) {
            printf("Vertex cover: %s\n", result);
        }
        fclose(output);
    }

    return 0;
}