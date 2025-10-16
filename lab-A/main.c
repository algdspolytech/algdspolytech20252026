// main.c
#include <locale.h>
#include "tree.h"
#include <stdio.h>

#define RUN_PROGRAM

#ifdef RUN_PROGRAM

int main() {
    setlocale(LC_ALL, "Russian");

    printf("=== ПРОГРАММА ДЛЯ ПОСТРОЕНИЯ ДЕРЕВА КАТАЛОГОВ ===\n\n");

    printf("1. Формируем входной файл input.txt...\n");
    FILE* input_file = fopen("input.txt", "w");
    if (!input_file) {
        printf("Ошибка: не удалось создать input.txt!\n");
        return 1;
    }

    fprintf(input_file, "7\n");
    fprintf(input_file, "WINNT\\SYSTEM32\\CONFIG\n");
    fprintf(input_file, "GAMES\n");
    fprintf(input_file, "WINNT\\DRIVERS\n");
    fprintf(input_file, "HOME\n");
    fprintf(input_file, "WIN\\SOFT\n");
    fprintf(input_file, "GAMES\\DRIVERS\n");
    fprintf(input_file, "WINNT\\SYSTEM32\\CERTSRV\\CERTCO~1\\X86\n");

    fclose(input_file);
    printf("   Файл input.txt успешно создан!\n\n");

    printf("2. Загружаем пути из файла...\n");
    PathList* path_collection = read_paths_from_file("input.txt");
    if (!path_collection) {
        printf("Ошибка чтения input.txt\n");
        return 1;
    }

    printf("3. Формируем дерево каталогов...\n");
    TreeNode* root_node = create_node("");
    if (!root_node) {
        printf("Ошибка выделения памяти для корневого узла!\n");
        free_path_list(path_collection);
        return 1;
    }

    PathList* current = path_collection;
    while (current) {
        add_path_to_tree(root_node, current->path);
        current = current->next;
    }

    printf("4. Сортируем дерево...\n");
    sort_tree(root_node);

    printf("5. Сохраняем результат в output.txt...\n");
    FILE* output_file = fopen("output.txt", "w");
    if (!output_file) {
        printf("Ошибка создания output.txt!\n");
        free_tree(root_node);
        free_path_list(path_collection);
        return 1;
    }

    print_tree_to_file(root_node->child, 0, output_file);
    fclose(output_file);
    printf("   Файл output.txt успешно сохранен!\n\n");

    printf("6. Содержимое output.txt:\n");
    printf("========================\n");

    FILE* result_file = fopen("output.txt", "r");
    if (result_file) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), result_file)) {
            printf("%s", buffer);
        }
        fclose(result_file);
    }
    printf("========================\n\n");

    printf("7. Освобождаем память...\n");
    free_tree(root_node);
    free_path_list(path_collection);
    printf("   Память успешно освобождена!\n\n");

    printf("=== ВЫПОЛНЕНИЕ ПРОГРАММЫ ЗАВЕРШЕНО ===\n");
    printf("Нажмите Enter для выхода...");
    getchar();

    return 0;
}
#endif