#pragma once
#include<stdlib.h>
#include<stdio.h>
typedef struct Sudoku Sudoku;
Sudoku* create_sudoku(int N);
void destroy_sudoku(Sudoku* sudoku);
void set_initial_value(Sudoku* sudoku, int row, int col, int value, int* status);
int solve_sudoku(Sudoku* sudoku);
void print_sudoku(Sudoku* sudoku, FILE* out);