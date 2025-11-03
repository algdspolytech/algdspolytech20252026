#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {
    setlocale(LC_CTYPE, "Russian");

    Linkedlist list;
    init_list(&list);


    while (1) {
        char* input = read_string();
        if (!input) {
            break;
        }

        if (input[0] == '\0') {
            printf("Пустая строка не добавлена.\n");
            free(input);
            continue;
        }


        add_node(&list, input);
        free(input);

        printf("Строка добавлена в список.\n");
        print_list(&list);
        printf("\n");
    }

    if (!list.first) {
        printf("Список пуст. Программа завершена.\n");
        free_list(&list);
        return 0;
    }
    print_list(&list);


    char* result = connect_strings(&list);
    if (result) {
        printf("\nРезультат объединения: \"%s\"\n", result);

        free(result);
    }
    else {
        printf("Ошибка при объединении строк!\n");
    }

    free_list(&list);

    return 0;
}