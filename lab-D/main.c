#include <stdio.h>
#include <stdlib.h>
#include "subset_sum_solver.h"

int main(int argc, char* argv[]) {
    const char* input_file = "input.txt";
    const char* output_file = "output.txt";

    // Чтение входных данных
    int target, count;
    int* numbers = load_data_from_file(input_file, &target, &count);

    if (!numbers) {
        printf("Ошибка: не удалось прочитать файл %s\n", input_file);
        return 1;
    }

    // Решение задачи
    SubsetSolution result = solve_subset_sum_problem(target, numbers, count);

    // Сохранение результата
    store_result_to_file(output_file, &result);

    // Вывод на экран
    if (result.found) {
        printf("Найдено подмножество с суммой %d:\n", target);
        for (int i = 0; i < result.length; i++) {
            printf("%d ", result.items[i]);
        }
        printf("\n");
    }
    else {
        printf("Подмножество с суммой %d не найдено\n", target);
    }

    // Очистка памяти
    free(numbers);
    release_solution(&result);

    return 0;
}