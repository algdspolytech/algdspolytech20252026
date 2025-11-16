// main.c
#include "locale.h"
#include "tree.h"
#include <stdio.h>
// #define RUN_MAIN_PROGRAM

#ifdef RUN_MAIN_PROGRAM

// main.c
int main() {
  setlocale(LC_ALL, "Rus");

  printf("=== ПРОГРАММА ПОСТРОЕНИЯ ДЕРЕВА ПАПОК ===\n\n");

  // Создаем тестовый файл input.txt
  printf("1. Создаем тестовый файл input.txt...\n");
  FILE *input = fopen("input.txt", "w");
  if (input == NULL) {
    printf("Ошибка создания файла input.txt!\n");
    return 1;
  }

  // Записываем тестовые данные согласно примеру из условия
  fprintf(input, "7\n");
  fprintf(input, "WINNT\\SYSTEM32\\CONFIG\n");
  fprintf(input, "GAMES\n");
  fprintf(input, "WINNT\\DRIVERS\n");
  fprintf(input, "HOME\n");
  fprintf(input, "WIN\\SOFT\n");
  fprintf(input, "GAMES\\DRIVERS\n");
  fprintf(input, "WINNT\\SYSTEM32\\CERTSRV\\CERTCO~1\\X86\n");

  fclose(input);
  printf("   Файл input.txt создан успешно!\n\n");

  // Читаем пути из файла
  printf("2. Читаем пути из файла...\n");
  PathList *paths = read_paths_from_file("input.txt");
  if (paths == NULL) {
    printf("Ошибка чтения файла input.txt\n");
    return 1;
  }

  // Создаем корневой узел
  printf("3. Создаем дерево папок...\n");
  TreeNode *root = create_node("");
  if (root == NULL) {
    printf("Ошибка выделения памяти для корневого узла!\n");
    free_path_list(paths);
    return 1;
  }

  // Добавляем все пути в дерево
  PathList *current_path = paths;
  while (current_path != NULL) {
    add_path_to_tree(root, current_path->path);
    current_path = current_path->next;
  }

  // Сортируем дерево
  printf("4. Сортируем дерево...\n");
  sort_tree(root);

  // Выводим результат в файл output.txt
  printf("5. Сохраняем результат в output.txt...\n");
  FILE *output = fopen("output.txt", "w");
  if (output == NULL) {
    printf("Ошибка создания файла output.txt!\n");
    free_tree(root);
    free_path_list(paths);
    return 1;
  }

  print_tree_to_file(root->child, 0, output);

  fclose(output);
  printf("   Файл output.txt сохранен успешно!\n\n");

  // Выводим содержимое output.txt на экран
  printf("6. Содержимое output.txt:\n");
  printf("========================\n");

  FILE *output_read = fopen("output.txt", "r");
  if (output_read != NULL) {
    char line[256];
    while (fgets(line, sizeof(line), output_read)) {
      printf("%s", line);
    }
    fclose(output_read);
  }
  printf("========================\n\n");

  // Освобождаем память
  printf("7. Освобождаем память...\n");
  free_tree(root);
  free_path_list(paths);
  printf("   Память освобождена успешно!\n\n");

  printf("=== ПРОГРАММА ЗАВЕРШЕНА ===\n");
  printf("Нажмите Enter для выхода...");
  getchar();

  return 0;
}
#endif