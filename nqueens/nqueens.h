#pragma once

#ifndef NQUEENS_H
#define NQUEENS_H

// Доска в формате двумерного массива
typedef struct board_t {
  int n;
  int **squares;
} board_t;

// Доска в формате расположения ферзей
typedef struct placement_t {
  int n, *x; // n - размер доски; x[k] - расположение ферзя в k-м столбце
  bool *a;   // a[k] - отсутствие ферзя в k-й строке
  bool *b;   // b[k] - отсутствие ферзя на k-й диагонали  \ (с суммой i+j = k)
  bool *c; // c[k] - отсутствие ферзя на k-й диагонали  / (c разностью i-j+n-1)
} placement_t;

// Создание пустой доски nxn
board_t *make_board(int n);

// Очистка памяти, занимаемой доской
void free_board(board_t *);

// Вывод доски в консоль
void print_board(board_t *);

// Создание пустого набора расположений
placement_t *make_placement(int n);

// Очистка памяти, занимаемой набором расположений
void free_placement(placement_t *);

// Установка ферзя в позицию: столбец i строка j
void place_queen(int i, int j, placement_t *p);

// Удаление ферзя с позиции: столбец i строка j
void remove_queen(int i, int j, placement_t *p);

// Проверка возможности расположения ферзя на столбце i, строке j
bool check_square(int i, int j, placement_t *p);

// Попытка расположить ферзи, начиная с i-го столбца
void try_placement(int i, bool *q, placement_t *p);

// Расстановка ферзей на доске
int queen_placement(board_t *board);

// Перенос расстановки из формального расположения в матрицу
void place_to_board(board_t *board, placement_t *p);

// Считывание числа из текстового файла
int read_number(char *filename);

// Запись ответа в файл
int output(char *filename);

#endif