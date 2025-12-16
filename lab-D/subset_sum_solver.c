#include "subset_sum_solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Загрузка данных из файла
int* load_data_from_file(const char* filename, int* target, int* count) {
    FILE* input_file = fopen(filename, "r");
    if (!input_file) {
        return NULL;
    }

    fscanf(input_file, "%d", target);
    fscanf(input_file, "%d", count);

    int* numbers = (int*)malloc(*count * sizeof(int));
    if (!numbers) {
        fclose(input_file);
        return NULL;
    }

    for (int i = 0; i < *count; i++) {
        fscanf(input_file, "%d", &numbers[i]);
    }

    fclose(input_file);
    return numbers;
}

// Сохранение результата в файл
void store_result_to_file(const char* filename, const SubsetSolution* result) {
    FILE* output_file = fopen(filename, "w");
    if (!output_file) {
        return;
    }

    if (result->found && result->length > 0) {
        for (int i = 0; i < result->length; i++) {
            fprintf(output_file, "%d ", result->items[i]);
        }
        fprintf(output_file, "\n");
    }
    else {
        fprintf(output_file, "0\n");
    }

    fclose(output_file);
}

// Сортировка по убыванию
void arrange_descending(int* array, int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (array[j] < array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// Вычисление суммы элементов
int compute_subset_total(const int* subset, int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += subset[i];
    }
    return total;
}

// Освобождение памяти решения
void release_solution(SubsetSolution* solution) {
    if (solution->items) {
        free(solution->items);
        solution->items = NULL;
    }
    solution->length = 0;
    solution->found = false;
}

// Рекурсивный поиск подмножества (основной алгоритм)
static bool recursive_search(int target, int* numbers, int count,
    int* current_subset, int current_size,
    int start_idx, int* result, int* result_size) {
    // Нашли решение
    if (target == 0) {
        *result_size = current_size;
        for (int i = 0; i < current_size; i++) {
            result[i] = current_subset[i];
        }
        return true;
    }

    // Невалидное состояние
    if (target < 0 || start_idx >= count) {
        return false;
    }

    // Пробуем включить текущий элемент
    current_subset[current_size] = numbers[start_idx];
    if (recursive_search(target - numbers[start_idx], numbers, count,
        current_subset, current_size + 1,
        start_idx + 1, result, result_size)) {
        return true;
    }

    // Пробуем исключить текущий элемент
    return recursive_search(target, numbers, count,
        current_subset, current_size,
        start_idx + 1, result, result_size);
}

// Поиск индексов элементов подмножества
bool* find_subset_indices(int target, int* numbers, int count, int* subset_size) {
    bool* selected = (bool*)calloc(count, sizeof(bool));
    if (!selected) return NULL;

    int* temp_subset = (int*)malloc(count * sizeof(int));
    int* result_subset = (int*)malloc(count * sizeof(int));
    int result_count = 0;

    if (!temp_subset || !result_subset) {
        free(selected);
        free(temp_subset);
        free(result_subset);
        return NULL;
    }

    // Копируем и сортируем массив
    int* sorted_numbers = (int*)malloc(count * sizeof(int));
    memcpy(sorted_numbers, numbers, count * sizeof(int));
    arrange_descending(sorted_numbers, count);

    // Ищем подмножество
    if (recursive_search(target, sorted_numbers, count,
        temp_subset, 0, 0,
        result_subset, &result_count)) {
        // Восстанавливаем индексы в оригинальном массиве
        for (int i = 0; i < result_count; i++) {
            for (int j = 0; j < count; j++) {
                if (numbers[j] == result_subset[i] && !selected[j]) {
                    selected[j] = true;
                    break;
                }
            }
        }
        *subset_size = result_count;
    }
    else {
        free(selected);
        selected = NULL;
        *subset_size = 0;
    }

    free(sorted_numbers);
    free(temp_subset);
    free(result_subset);
    return selected;
}

// Основная функция решения
SubsetSolution solve_subset_sum_problem(int target, int* numbers, int count) {
    SubsetSolution solution = { NULL, 0, false };

    // Проверка базовых случаев
    if (target == 0) {
        solution.found = true;
        solution.items = (int*)malloc(sizeof(int));
        solution.length = 0;
        return solution;
    }

    if (count == 0 || !numbers) {
        return solution;
    }

    // Вычисляем общую сумму
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += numbers[i];
    }

    if (total < target) {
        return solution;
    }

    // Ищем подмножество
    int subset_count;
    bool* indices = find_subset_indices(target, numbers, count, &subset_count);

    if (indices) {
        solution.found = true;
        solution.length = subset_count;
        solution.items = (int*)malloc(subset_count * sizeof(int));

        if (solution.items) {
            int idx = 0;
            for (int i = 0; i < count; i++) {
                if (indices[i]) {
                    solution.items[idx++] = numbers[i];
                }
            }
        }
        free(indices);
    }

    return solution;
}