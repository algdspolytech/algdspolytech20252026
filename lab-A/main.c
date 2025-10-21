#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void demonstrate_priority_queue() {
    printf("=== Демонстрация работы очереди с приоритетами ===\n\n");

    PriorityQueue* pq = pq_create();

    printf("Добавляем элементы:\n");
    printf("pq_enqueue(pq, 10, 5)\n");
    pq_enqueue(pq, 10, 5);
    printf("pq_enqueue(pq, 20, 1)\n");
    pq_enqueue(pq, 20, 1);
    printf("pq_enqueue(pq, 30, 8)\n");
    pq_enqueue(pq, 30, 8);
    printf("pq_enqueue(pq, 40, 3)\n");
    pq_enqueue(pq, 40, 3);
    printf("pq_enqueue(pq, 50, 8)  // одинаковый приоритет с 30\n");
    pq_enqueue(pq, 50, 8);

    printf("\nТекущий размер очереди: %d\n", pq_size(pq));
    printf("Первый элемент (наивысший приоритет): %d\n", pq_peek(pq));

    printf("\nИзвлекаем элементы в порядке приоритета:\n");
    while (!pq_is_empty(pq)) {
        int data = pq_dequeue(pq);
        printf("pq_dequeue() = %d\n", data);
    }

    printf("\nОчередь пуста: %s\n", pq_is_empty(pq) ? "Да" : "Нет");

    pq_destroy(pq);
}

void interactive_test() {
    printf("\n=== Интерактивное тестирование ===\n\n");

    PriorityQueue* pq = pq_create();
    int choice, data, priority;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить элемент (enqueue)\n");
        printf("2. Извлечь элемент (dequeue)\n");
        printf("3. Просмотреть первый элемент (peek)\n");
        printf("4. Размер очереди\n");
        printf("5. Проверить на пустоту\n");
        printf("6. Очистить очередь\n");
        printf("7. Выход\n");
        printf("Выберите действие: ");

        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Введите данные: ");
            scanf("%d", &data);
            printf("Введите приоритет: ");
            scanf("%d", &priority);
            pq_enqueue(pq, data, priority);
            printf("Элемент %d с приоритетом %d добавлен\n", data, priority);
            break;

        case 2:
            if (!pq_is_empty(pq)) {
                data = pq_dequeue(pq);
                printf("Извлечен элемент: %d\n", data);
            }
            else {
                printf("Очередь пуста!\n");
            }
            break;

        case 3:
            if (!pq_is_empty(pq)) {
                data = pq_peek(pq);
                printf("Первый элемент: %d\n", data);
            }
            else {
                printf("Очередь пуста!\n");
            }
            break;

        case 4:
            printf("Размер очереди: %d\n", pq_size(pq));
            break;

        case 5:
            printf("Очередь пуста: %s\n", pq_is_empty(pq) ? "Да" : "Нет");
            break;

        case 6:
            pq_clear(pq);
            printf("Очередь очищена\n");
            break;

        case 7:
            pq_destroy(pq);
            printf("Выход...\n");
            return;

        default:
            printf("Неверный выбор!\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    printf("Программа: Очередь с приоритетами на отсортированном связном списке\n");
    printf("Сложность операций:\n");
    printf(" - enqueue: O(n)\n");
    printf(" - dequeue: O(1)\n");
    printf(" - peek: O(1)\n");
    printf(" - size/is_empty: O(1)\n\n");

    demonstrate_priority_queue();

    interactive_test();

    printf("\n=== Запуск юнит-тестов ===\n");

    printf("Для запуска полных юнит-тестов скомпилируйте и запустите test_priority_queue.c\n");

    return 0;
}