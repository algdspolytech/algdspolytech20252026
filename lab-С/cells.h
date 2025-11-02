#ifndef CELLS_H
#define CELLS_H

#include <stdbool.h>

// Структура для хранения координат удалённой клетки
typedef struct {
    int x, y;
} Cell;

// Основная функция: возвращает количество связных кусков
int count_connected_components(int M, int N, Cell* removed, int K);

#endif // CELLS_H