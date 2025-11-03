#include "birthdays.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Создание нового узла
Node* create_node(Person p) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    new_node->data = p;
    new_node->next = NULL;
    return new_node;
}

// Сравнение двух дат
int compare_dates(Person p1, Person p2) {
    if (p1.year != p2.year) return p1.year - p2.year;
    if (p1.month != p2.month) return p1.month - p2.month;
    return p1.day - p2.day;
}


// Вставка в отсортированный список
void insert_sorted(Node** head, Person p) {
    Node* new_node = create_node(p);
    if (new_node == NULL) return;

    // Если список пуст или новый элемент должен быть первым
    if (*head == NULL || compare_dates(p, (*head)->data) < 0) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    // Поиск места для вставки
    Node* current = *head;
    while (current->next != NULL && compare_dates(p, current->next->data) >= 0) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

// Вывод списка
void print_list(Node* head) {
    printf("Sorted list by birth date:\n");
    printf("--------------------------\n");
    Node* current = head;
    while (current != NULL) {
        printf("%s %02d.%02d.%d\n",
            current->data.last_name,
            current->data.day,
            current->data.month,
            current->data.year);
        current = current->next;
    }
    printf("--------------------------\n");
}

// Поиск по дате рождения
void find_by_date(Node* head, int day, int month) {
    printf("People born on %02d.%02d:\n", day, month);
    int found = 0;

    Node* current = head;
    while (current != NULL) {
        if (current->data.day == day && current->data.month == month) {
            printf("- %s %s %s\n",
                current->data.last_name,
                current->data.first_name,
                current->data.patronymic);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No people found\n");
    }
}

// Освобождение памяти
void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}