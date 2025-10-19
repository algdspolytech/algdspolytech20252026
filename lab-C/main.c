#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#ifdef _WIN32
    #include <direct.h>
    #define GET_CWD _getcwd
#else
    #include <unistd.h>
    #define GET_CWD getcwd
#endif

void print_current_directory() {
    char cwd[1024];
    if (GET_CWD(cwd, sizeof(cwd)) != NULL) {
        printf("Текущая директория: %s\n", cwd);
    } else {
        printf("Не удалось определить текущую директорию\n");
    }
}

int main() {
    Graph graph;
    const char *filename = "graph.txt";

    printf("=== Построение матрицы смежности из списка смежностей ===\n");
    print_current_directory();
    printf("Ищем файл: %s\n", filename);

    // Проверяем существование файла
    FILE *test_file = fopen(filename, "r");
    if (test_file == NULL) {
        printf("Файл '%s' не найден в текущей директории!\n", filename);
        printf("Создайте файл graph.txt с данными графа.\n");
        return 1;
    }
    fclose(test_file);

    if (read_graph_from_file(&graph, filename)) {
        printf("Граф успешно прочитан из файла '%s'\n", filename);
        print_adjacency_matrix(&graph);
    } else {
        printf("Ошибка при чтении графа из файла '%s'\n", filename);
        printf("Проверьте формат файла.\n");
        return 1;
    }

    return 0;
}