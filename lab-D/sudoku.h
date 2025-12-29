#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#define MAX_N 9

typedef struct DancingNode {
    struct DancingNode* left, * right, * up, * down;
    struct DancingNode* column;
    int row_id;
    int size;
} DancingNode;

typedef struct {
    int N;
    int board[MAX_N][MAX_N];
    DancingNode* header;
    DancingNode* nodes;
    int node_count;
    int* solution;
    int solution_size;
} SudokuPuzzle;

DancingNode* create_node(SudokuPuzzle* puzzle);
void initialize_solver(SudokuPuzzle* puzzle, int N);
void link_node_to_column(DancingNode* col, DancingNode* node);
void build_exact_cover(SudokuPuzzle* puzzle);
void hide_column(DancingNode* col);
void reveal_column(DancingNode* col);
DancingNode* select_column(SudokuPuzzle* puzzle);
int algorithm_x(SudokuPuzzle* puzzle, int level);
void decode_solution(SudokuPuzzle* puzzle);
int validate_sudoku(SudokuPuzzle* puzzle);
int solve_puzzle(SudokuPuzzle* puzzle);
int load_puzzle(const char* filename, SudokuPuzzle* puzzle);
void save_result(const char* filename, SudokuPuzzle* puzzle, int solved);

#endif#pragma once
