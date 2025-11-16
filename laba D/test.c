#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <locale.h>

typedef unsigned long long ull;


void solve_expression(const char* a_str, ull target, char* output);
ull evaluate_with_priority(const char* expr);

// Функция для запуска одного теста
void run_test(const char* test_name, const char* input_a, ull target_b, const char* expected, int test_num) {
    char actual[201];

    printf("Тест %d: %s\n", test_num, test_name);
    printf("  Вход: A='%s', B=%llu\n", input_a, target_b);
    printf("  Ожидается: %s\n", expected);

    solve_expression(input_a, target_b, actual);

    printf("  Получено: %s\n", actual);

    // Проверка для действительно невозможных случаев
    if (test_num == 9) {
        if (strcmp(actual, "0") == 0) {
            printf("  ПРОЙДЕН (правильно определил как невозможный)\n\n");
        }
        else {
            ull actual_value = evaluate_with_priority(actual);
            if (actual_value == target_b) {
                printf("  ! ПРОБЛЕМА ТЕСТА: Этот случай на самом деле возможен\n\n");
            }
            else {
                printf("   ПРОВАЛ (неверное решение)\n\n");
            }
        }
    }
    // Проверка для всех остальных тестов - важна корректность, а не точное совпадение
    else {
        ull actual_value = evaluate_with_priority(actual);
        if (actual_value == target_b) {
            if (strcmp(actual, expected) == 0) {
                printf("   ПРОЙДЕН (точное совпадение)\n\n");
            }
            else {
                printf("   ПРОЙДЕН (другое но корректное решение)\n\n");
            }
        }
        else {
            printf("   ПРОВАЛ (неверное решение, дает %llu)\n\n", actual_value);
        }
    }
}

// Функция проверки вычисления выражений
void test_evaluation(const char* expr, ull expected, int test_num) {
    ull result = evaluate_with_priority(expr);
    printf("Тест вычисления %d: %s = %llu (ожидается %llu) %s\n",
        test_num, expr, result, expected,
        result == expected ? "+" : "-");
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    printf("=== ЗАПУСК ЮНИТ-ТЕСТОВ ===\n\n");

    // Тест 1: Простое сложение
    run_test("Простое сложение", "12", 3, "1+2", 1);

    // Тест 2: Простое умножение
    run_test("Простое умножение", "23", 6, "2*3", 2);

    // Тест 3: Простое вычитание
    run_test("Простое вычитание", "32", 1, "3-2", 3);

    // Тест 4: Простое деление
    run_test("Простое деление", "42", 2, "4/2", 4);

    // Тест 5: Приоритет операций
    run_test("Приоритет операций", "234", 14, "2+3*4", 5);

    // Тест 6: Многозначные числа
    run_test("Многозначные числа", "1234", 46, "12+34", 6);

    // Тест 7: Оригинальная задача из условия
    run_test("Оригинальная задача", "123456789", 1214, "12+34*56-78*9", 7);

    // Тест 8: Все операции сложения
    run_test("Все операции сложения", "12345", 15, "1+2+3+4+5", 8);

    // Тест 9: Невозможный случай
    run_test("Невозможный случай", "111", 1000, "0", 9);

    // Тест 10: Число равно самому себе
    run_test("Число равно целевому", "123", 123, "123", 10);

    printf("\n=== ТЕСТЫ ВЫЧИСЛЕНИЯ ВЫРАЖЕНИЙ ===\n\n");

    // Проверка корректности вычислений
    test_evaluation("1+2*3", 7, 1);
    test_evaluation("10-4/2", 8, 2);
    test_evaluation("12+34*56-78*9", 1214, 3);
    test_evaluation("100/10*5", 50, 4);
    test_evaluation("8/2/2", 2, 5);
    test_evaluation("1*2*3+4+5", 15, 6);

    printf("\n=== СВОДКА ТЕСТОВ ===\n");
    printf("Все 10 тестов проверяют различные сценарии:\n");
    printf("1. Базовое сложение\n");
    printf("2. Базовое умножение\n");
    printf("3. Базовое вычитание\n");
    printf("4. Базовое деление\n");
    printf("5. Приоритет операций\n");
    printf("6. Многозначные числа\n");
    printf("7. Сложная оригинальная задача\n");
    printf("8. Множественные операции\n");
    printf("9. Невозможный случай\n");
    printf("10. Тривиальный случай\n");

    printf("\n=== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ ===\n");

    return 0;
}