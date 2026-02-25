#pragma once
#include <stdio.h>

typedef struct Puzzle Puzzle;

Puzzle* create_puzzle(int size);
void free_puzzle(Puzzle* puzzle);
void set_cell(Puzzle* puzzle, int row, int col, int val, int* success);
int solve_puzzle(Puzzle* puzzle);
void display_puzzle(Puzzle* puzzle, FILE* output);