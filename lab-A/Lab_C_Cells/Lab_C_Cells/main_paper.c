#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include "paper.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    int m, n, k;

    printf("Введите размеры листа (M N): ");
    if (scanf("%d %d", &m, &n) != 2) {
        fprintf(stderr, "Ошибка ввода M и N.\n");
        return 1;
    }

    printf("Введите количество удаленных клеток K: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Ошибка ввода K.\n");
        return 1;
    }

    if (k < 0) {
        fprintf(stderr, "K не может быть отрицательным.\n");
        return 1;
    }

    // если K=0, нет смысла выделять память
    int* x_coords = NULL;
    int* y_coords = NULL;

    if (k > 0) {
        x_coords = (int*)malloc(k * sizeof(int));
        y_coords = (int*)malloc(k * sizeof(int));

        if (!x_coords || !y_coords) {
            fprintf(stderr, "Ошибка выделения памяти для координат.\n");
            free(x_coords);
            free(y_coords);
            return 1;
        }

        printf("Введите координаты удаленных клеток (x y), начиная с 1:\n");
        for (int i = 0; i < k; i++) {
            if (scanf("%d %d", &x_coords[i], &y_coords[i]) != 2) {
                fprintf(stderr, "Ошибка ввода координат клетки %d.\n", i + 1);
                free(x_coords);
                free(y_coords);
                return 1;
            }

            // преобр 1-индексации (пользовательский ввод) в 0-индексацию (массив C)
            x_coords[i] = x_coords[i] - 1;
            y_coords[i] = y_coords[i] - 1;
        }
    }

    Paper* paper = create_paper(m, n);
    if (!paper) {
        fprintf(stderr, "Ошибка создания листа (неверные размеры или память).\n");
        free(x_coords);
        free(y_coords);
        return 1;
    }

    remove_cells(paper, k, x_coords, y_coords);

    int components = count_connected_components(paper);

    printf("Количество связных кусков: %d\n", components);

    // освобождение ресурсов
    destroy_paper(paper);
    free(x_coords);
    free(y_coords);

    return 0;
}