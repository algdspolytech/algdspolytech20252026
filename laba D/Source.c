#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <locale.h>

typedef unsigned long long ull;

// Глобальные переменные для основного алгоритма
char A[101];
ull B;
bool found = false;
char result[201];
char best_result[201]; 

// Функция для вычисления выражения с учетом приоритета операций
ull evaluate_with_priority(const char* expr) {
    ull numbers[100];
    char operators[100];
    int num_count = 0, op_count = 0;

   
    ull current_num = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] >= '0' && expr[i] <= '9') {
            current_num = current_num * 10 + (expr[i] - '0');
        }
        else {
            numbers[num_count++] = current_num;
            current_num = 0;
            operators[op_count++] = expr[i];
        }
    }
    numbers[num_count++] = current_num;

    // Сначала выполняем умножение и деление
    for (int i = 0; i < op_count; i++) {
        if (operators[i] == '*' || operators[i] == '/') {
            ull left = numbers[i];
            ull right = numbers[i + 1];
            ull res;

            if (operators[i] == '*') {
                res = left * right;
            }
            else { // '/'
                if (right == 0) return ULLONG_MAX;
                if (left % right != 0) return ULLONG_MAX;
                res = left / right;
            }

            numbers[i] = res;
            for (int j = i + 1; j < num_count - 1; j++) {
                numbers[j] = numbers[j + 1];
            }
            for (int j = i; j < op_count - 1; j++) {
                operators[j] = operators[j + 1];
            }
            num_count--;
            op_count--;
            i--;
        }
    }

    // Затем выполняем сложение и вычитание
    ull total = numbers[0];
    for (int i = 0; i < op_count; i++) {
        if (operators[i] == '+') {
            total += numbers[i + 1];
        }
        else { // '-'
            if (total < numbers[i + 1]) return ULLONG_MAX;
            total -= numbers[i + 1];
        }
    }

    return total;
}


int solution_quality(const char* expr) {
    int quality = 0;
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '+' || expr[i] == '-') {
            quality += 10;
        }
        else if (expr[i] == '*' || expr[i] == '/') {
            quality += 5;
        }
    }
    return quality;
}


void search_best(int pos, int expr_pos, char* current) {
    if (pos == strlen(A)) {
        current[expr_pos] = '\0';
        ull val = evaluate_with_priority(current);
        if (val == B) {
            if (!found || solution_quality(current) < solution_quality(best_result)) {
                strcpy(best_result, current);
                found = true;
            }
        }
        return;
    }

    // Добавляем текущую цифру
    current[expr_pos] = A[pos];


    if (pos < strlen(A) - 1) {
        char operators[] = { '*', '/', '+', '-' }; 

        for (int i = 0; i < 4; i++) {
            current[expr_pos + 1] = operators[i];
            search_best(pos + 1, expr_pos + 2, current);
        }
    }
    search_best(pos + 1, expr_pos + 1, current);
}

// Основная функция решения
void solve_expression(const char* a_str, ull target, char* output) {
    strcpy(A, a_str);
    B = target;
    found = false;
    best_result[0] = '\0';
    result[0] = '\0';

    char current[201] = { 0 };
    search_best(0, 0, current);

    if (found) {
        strcpy(output, best_result);
    }
    else {
        strcpy(output, "0");
    }
}

void run_all_tests(void) {
    setlocale(LC_CTYPE, "Russian");
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");

    if (!fin || !fout) {
        printf("Ошибка при открытии файлов\n");
        return 1;
    }

    char a_str[101];
    char b_str[100];
    if (fscanf(fin, "%s %s", a_str, b_str) != 2) {
        printf("Ошибка при чтении ввода\n");
        fclose(fin);
        fclose(fout);
        return 1;
    }

    ull target = strtoull(b_str, NULL, 10);
    char solution[201];

    solve_expression(a_str, target, solution);

    fprintf(fout, "%s\n", solution);
    printf("Решение: %s\n", solution);

    fclose(fin);
    fclose(fout);
    return 0;
}