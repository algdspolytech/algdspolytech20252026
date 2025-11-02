#include <stdio.h>
#include "list.h"
#include <locale.h>

int main(void) {
    setlocale(LC_CTYPE, "Russian");

    printf("=== Конкатенация строк ===\n\n");

     // Демонстрация работы
    LinkedList* list = create_list();

    printf("Добавление строк:\n");
    append_string(list, "Hello");
    printf(" - 'Hello'\n");
    append_string(list, ", ");
    printf(" - ', '\n");
    append_string(list, "World");
    printf(" - 'World'\n");
    append_string(list, "!");
    printf(" - '!'\n");

    printf("\nОбъединенный результат: %zu\n", get_total_length(list));

    char* result = concatenate_strings(list);
    printf("Объединенный результат: '%s'\n", result);

    free(result);
    free_list(list);

    printf("\n");

    //  Запуск тестов
    extern void run_all_tests(void);
    run_all_tests();
   

    return 0;
}