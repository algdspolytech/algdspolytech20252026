#include <stdio.h>
#include <locale.h>
#include "config.h"
#include "list.h"


int main(int argc, char* argv[]) {
    setlocale(LC_CTYPE, "Russian");
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    Graph graph;
    char line[256];
    char words[MAX_WORDS][MAX_WORD_LEN];
    char result[MAX_WORDS][MAX_WORD_LEN];
    int word_count;
    int i;

    init_graph(&graph);

    // Чтение вершин
    if (fgets(line, sizeof(line), input)) {
        word_count = parse_words(line, words);

        for (i = 0; i < word_count; i++) {
            add_node(&graph, words[i]);
        }
    }

    // Чтение ребер
    while (fgets(line, sizeof(line), input)) {
        if (strlen(line) <= 1) continue;

        word_count = parse_words(line, words);

        if (word_count >= 2) {
            add_edge(&graph, words[0], words[1]);
        }
    }

    // Топологическая сортировка
    if (topological_sort(&graph, result)) {
        printf("Топологический порядок: ");
        for (int i = 0; i < graph.node_count; i++) {
            fprintf(output, "%s", result[i]);
            printf("%s", result[i]);
            if (i < graph.node_count - 1) {
                fprintf(output, " ");
                printf(" ");
            }
        }
        fprintf(output, "\n");
        printf("\n");
        printf("Успех: Топологическая сортировка завершена. Проверьте output.txt\n");
    }
    else {
        fprintf(output, "[Ошибка]\n");
        printf("Ошибка: Обнаружен цикл в графе. Проверьте output.txt\n");
    }

    fclose(input);
    fclose(output);
    free_graph(&graph);

    extern void run_all_tests(void);
    run_all_tests();
   

    return 0;
}