#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "list_sort.h"

// Функция для демонстрации работы программы
void run_program() {
    printf("=== Демонстрация сортировки односвязного списка ===\n\n");

    // Создаем тестовый список
    ListNode* head = NULL;

    // Добавляем строки в разном порядке
    append_node(&head, "banana");
    append_node(&head, "apple");
    append_node(&head, "cherry");
    append_node(&head, "date");
    append_node(&head, "blueberry");

    printf("Исходный список:\n");
    print_list(head);

    // Сортируем список
    head = merge_sort(head);

    printf("\nОтсортированный список:\n");
    print_list(head);

    // Освобождаем память
    free_list(head);

    printf("\n=== Демонстрация завершена ===\n");
}

int main() {
    setlocale(LC_ALL, "Russian");
    run_program();
    return 0;
}