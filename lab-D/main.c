#include "solution.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int B, N;
    int* A = NULL;

    // Читаем входные данные.
    if (!read_input(&B, &N, &A)) {
        printf("Ошибка при чтении входных данных.\n");
        return 1;
    }

    // Находим подмножество.
    SubsetResult result = find_subset_sum(A, N, B);

    // Записываем результат.
    if (!write_output(&result)) {
        printf("Ошибка при записи выходных данных.\n");
        free_subset_result(&result);
        free(A);
        return 1;
    }

    // Освобождаем память.
    free_subset_result(&result);
    free(A);

    printf("Результат записан в output.txt.\n");
    return 0;
}