#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stack_a.h"
#include "stack_s.h"
#include "unit_tests.h"
#include <locale.h>

void demo_stack_list(void) {
    printf(">>>>> StackList\n");
    StackList* stack = s_create();

    s_push(stack, 10);
    s_push(stack, 20);
    s_push(stack, 30);

    printf("Размер стека: %zu\n", s_size(stack));

    int value;
    while (s_pop(stack, &value)) {
        printf("Изъято: %d\n", value);
    }

    s_destroy(stack);
}

void demo_stack_array(void) {
    printf(">>>>> StackArray\n");
    StackArray* stack = a_create();

    for (int i = 1; i <= 15; i++) {
        a_push(stack, i * 10);
    }

    printf("Размер стека: %zu\n", a_size(stack));
    printf("Вместимость стека(capacity): %zu\n", a_capacity(stack));

    int value;
    while (a_pop(stack, &value)) {
        printf("Изъято: %d\n", value);
    }

    a_destroy(stack);
}

int main(void) {
    setlocale(LC_CTYPE, "Russian");
    printf("Выбрать вывод :\n");
    printf("1 - Запуск unit tests\n");
    printf("2 - Запуск Demo\n");
    printf("3 - Запустить unit tests и Demo\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1 || choice == 3) {
        unit_tests();
        printf("\n");
    }

    if (choice == 2 || choice == 3) {
        demo_stack_list();
        printf("\n");
        demo_stack_array();
    }

    return 0;
}