#define _CRT_SECURE_NO_WARNINGS
#include "queens.h"
#include <locale.h>

int main() {
    setlocale(LC_CTYPE, "Russian");

    FILE* file = fopen("size.txt", "r");
    if (file == NULL) {
        printf("Ошибка: не найден файл size.txt\n");
        printf("Создайте файл size.txt с числом N (например, 8)\n");
        return 1;
    }

    int N;
    fscanf(file, "%d", &N);
    fclose(file);

    if (N > 0) {
        int* A = (int*)malloc(N * sizeof(int));

        int solution_found = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) { A[j] = -1; }
            if (Queens(A, N, i, 0, 0)) {
                Print(A, N);
                solution_found = 1;
                break;
            }
        }
        if (!solution_found) {
            printf("Не повезло, хнык-хнык\n");
        }

        free(A);
    }
    else {
        printf("Анекдот про шарик...\n");
    }

    return 0;
}