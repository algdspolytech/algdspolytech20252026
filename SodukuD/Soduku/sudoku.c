#include<stdlib.h>
#include<stdio.h>
#include"sudoku.h"
typedef struct Sudoku {
	int N;
	int S;
	int* grid;
	unsigned char* row_used;
	unsigned char* col_used;
	unsigned char* box_used;
	int is_valid;
} Sudoku;
static int box_id(Sudoku* sudoku, int row, int col) {
	return (row / sudoku->N) * sudoku->N + (col / sudoku->N);
}
static int index_used(Sudoku* sudoku, int a, int value) {
	return a * (sudoku->S + 1) + value;
}
static int can_place(Sudoku* sudoku, int row, int col, int value) {
	int b = box_id(sudoku, row, col);
	return !sudoku->row_used[index_used(sudoku, row, value)] &&
		!sudoku->col_used[index_used(sudoku, col, value)] &&
		!sudoku->box_used[index_used(sudoku, b, value)];
}
static void place_value(Sudoku* sudoku, int row, int col, int value) {
	int b = box_id(sudoku, row, col);
	sudoku->grid[row * sudoku->S + col] = value;
	sudoku->row_used[index_used(sudoku, row, value)] = 1;
	sudoku->col_used[index_used(sudoku, col, value)] = 1;
	sudoku->box_used[index_used(sudoku, b, value)] = 1;
}
static void unplace_value(Sudoku* sudoku, int row, int col, int value) {
	int b = box_id(sudoku, row, col);
	sudoku->grid[row * sudoku->S + col] = 0;
	sudoku->row_used[index_used(sudoku, row, value)] = 0;
	sudoku->col_used[index_used(sudoku, col, value)] = 0;
	sudoku->box_used[index_used(sudoku, b, value)] = 0;
}
static int count_candidates(Sudoku* sudoku, int row, int col) {
	int count = 0;
	for (int value = 1; value <= sudoku->S; value++) {
		if (can_place(sudoku, row, col, value)) {
			count++;
		}
	}
	return count;
}
static int find_best_cell(Sudoku* sudoku, int* out_row, int* out_col) {
	int best_count = 1000000;
	int found = 0;
	for (int row = 0; row < sudoku->S; row++) {
		for (int col = 0; col < sudoku->S; col++) {
			if (sudoku->grid[row * sudoku->S + col] != 0) {
				continue;
			}
			int c = count_candidates(sudoku, row, col);
			if (c == 0) {
				return -1;
			}
			if (!found || c < best_count) {
				best_count = c;
				*out_row = row;
				*out_col = col;
				found = 1;
				if (best_count == 1) {
					return 1;
				}
			}
		}
	}
	return found ? 1 : 0;
}
static int solve_recursive(Sudoku* sudoku) {
	int row = 0;
	int col = 0;
	int pick = find_best_cell(sudoku, &row, &col);
	if (pick == 0) {
		return 1;
	}
	if (pick == -1) {
		return 0;
	}
	for (int value = 1; value <= sudoku->S; value++) {
		if (!can_place(sudoku, row, col, value)) {
			continue;
		}
		place_value(sudoku, row, col, value);
		if (solve_recursive(sudoku)) {
			return 1;
		}
		unplace_value(sudoku, row, col, value);
	}
	return 0;
}
Sudoku* create_sudoku(int N) {
	if (N <= 2 || N >= 10) {
		return NULL;
	}
	Sudoku* sudoku = malloc(sizeof(Sudoku));
	if (!sudoku) {
		return NULL;
	}
	sudoku->N = N;
	sudoku->S = N * N;
	sudoku->is_valid = 1;
	int S = sudoku->S;
	sudoku->grid = (int*)calloc(S * S, sizeof(int));
	if (!sudoku->grid) {
		free(sudoku);
		return NULL;
	}
	int used_size = S * (S + 1);
	sudoku->row_used = (unsigned char*)calloc(used_size, sizeof(unsigned char));
	sudoku->col_used = (unsigned char*)calloc(used_size, sizeof(unsigned char));
	sudoku->box_used = (unsigned char*)calloc(used_size, sizeof(unsigned char));
	if (!sudoku->row_used || !sudoku->col_used || !sudoku->box_used) {
		destroy_sudoku(sudoku);
		return NULL;
	}
	return sudoku;
}
void destroy_sudoku(Sudoku* sudoku) {
	if (!sudoku) {
		return;
	}
	free(sudoku->grid);
	free(sudoku->row_used);
	free(sudoku->col_used);
	free(sudoku->box_used);
	free(sudoku);
}
void set_initial_value(Sudoku* sudoku, int row, int col, int value, int* status) {
	if (!sudoku || !status) {
		return;
	}
	if (!sudoku->is_valid) {
		*status = 0;
		return;
	}
	if (row < 0 || col < 0 || row >= sudoku->S || col >= sudoku->S) {
		sudoku->is_valid = 0;
		*status = 0;
		return;
	}
	if (value < 0 || value > sudoku->S) {
		sudoku->is_valid = 0;
		*status = 0;
		return;
	}
	if (value == 0) {
		sudoku->grid[row * sudoku->S + col] = 0;
		*status = 1;
		return;
	}
	if (!can_place(sudoku, row, col, value)) {
		sudoku->is_valid = 0;
		*status = 0;
		return;
	}
	place_value(sudoku, row, col, value);
	*status = 1;
}
int solve_sudoku(Sudoku* sudoku) {
	if (!sudoku || !sudoku->is_valid) {
		return 0;
	}
	return solve_recursive(sudoku);
}
void print_sudoku(Sudoku* sudoku, FILE* out) {
	if (!sudoku || !out) {
		return;
	}
	for (int row = 0; row < sudoku->S; row++) {
		for (int col = 0; col < sudoku->S; col++) {
			if (col > 0) {
				fprintf(out, " ");
			}
			fprintf(out, "%d", sudoku->grid[row * sudoku->S + col]);
		}
		fprintf(out, "\n");
	}
}