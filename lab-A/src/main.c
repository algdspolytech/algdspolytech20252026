#include <stdio.h>
#include <stdlib.h>
#include "birthdays.h"

int main() {
    Node* head = NULL;
    FILE* file = fopen("birthdays.txt", "r");

    if (file == NULL) {
        printf("Error opening file birthdays.txt\n");
        printf("Make sure birthdays.txt is in the same folder as .exe file\n");
        return 1;
    }

    // чтение данных из файла
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Person p;
        if (sscanf(line, "%49s %49s %49s %d.%d.%d",
            p.last_name, p.first_name, p.patronymic,
            &p.day, &p.month, &p.year) == 6) {
            insert_sorted(&head, p);
        }
    }
    fclose(file);

    // вывод отсортированного списка
    print_list(head);

    // Поиск по дате
    int search_day, search_month;
    printf("Enter date to search (day month): ");
    scanf("%d %d", &search_day, &search_month);

    find_by_date(head, search_day, search_month);

    // освобождение памяти
    free_list(head);

    printf("Press Enter to exit...");
    getchar();
    getchar(); // ждём нажатия Enter
    return 0;
}