#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sudoku.h"

DancingNode* create_node(SudokuPuzzle* puzzle) {
    if (!puzzle->nodes) {
        printf("ERROR: puzzle->nodes is NULL!\n");
        return NULL;
    }
    DancingNode* node = &puzzle->nodes[puzzle->node_count++];
    node->left = node->right = node->up = node->down = NULL;
    node->column = NULL;
    node->row_id = -1;
    node->size = 0;
    return node;
}

void initialize_solver(SudokuPuzzle* puzzle, int N) {
    puzzle->N = N;
    puzzle->node_count = 0;

    int dimension = N * N;
    int max_nodes = 4 * dimension * dimension * dimension;
    puzzle->nodes = (DancingNode*)malloc(max_nodes * sizeof(DancingNode));
    if (!puzzle->nodes) {
        printf("ERROR: Memory allocation failed for nodes!\n");
        return;
    }

    puzzle->solution = (int*)malloc(dimension * dimension * sizeof(int));
    if (!puzzle->solution) {
        printf("ERROR: Memory allocation failed for solution!\n");
        free(puzzle->nodes);
        puzzle->nodes = NULL;
        return;
    }
    puzzle->solution_size = 0;

    puzzle->header = create_node(puzzle);
    puzzle->header->left = puzzle->header;
    puzzle->header->right = puzzle->header;
    puzzle->header->up = puzzle->header;
    puzzle->header->down = puzzle->header;
    puzzle->header->size = 0;
}

void link_node_to_column(DancingNode* col, DancingNode* node) {
    node->column = col;
    node->up = col->up;
    node->down = col;
    col->up->down = node;
    col->up = node;
    col->size++;
}

void build_exact_cover(SudokuPuzzle* puzzle) {
    int N = puzzle->N;
    int dimension = N * N;
    int constraints = 4 * dimension * dimension;
    DancingNode** columns = (DancingNode**)malloc(constraints * sizeof(DancingNode*));
    if (!columns) {
        printf("ERROR: malloc columns failed\n");
        return;
    }

    for (int i = 0; i < constraints; i++) {
        columns[i] = create_node(puzzle);
        if (!columns[i]) {
            free(columns);
            return;
        }

        columns[i]->left = puzzle->header->left;
        columns[i]->right = puzzle->header;
        puzzle->header->left->right = columns[i];
        puzzle->header->left = columns[i];
        columns[i]->up = columns[i];
        columns[i]->down = columns[i];
        columns[i]->size = 0;
    }

    for (int row = 0; row < dimension; row++) {
        for (int col = 0; col < dimension; col++) {
            int block = (row / N) * N + (col / N);
            for (int num = 1; num <= dimension; num++) {
                if (puzzle->board[row][col] != 0 && puzzle->board[row][col] != num) continue;

                int cell_constraint = row * dimension + col;
                int row_constraint = dimension * dimension + row * dimension + (num - 1);
                int col_constraint = 2 * dimension * dimension + col * dimension + (num - 1);
                int block_constraint = 3 * dimension * dimension + block * dimension + (num - 1);

                DancingNode* node1 = create_node(puzzle);
                DancingNode* node2 = create_node(puzzle);
                DancingNode* node3 = create_node(puzzle);
                DancingNode* node4 = create_node(puzzle);
                if (!node1 || !node2 || !node3 || !node4) {
                    free(columns);
                    return;
                }

                int encoded = row * dimension * dimension + col * dimension + (num - 1);
                node1->row_id = encoded;
                node2->row_id = encoded;
                node3->row_id = encoded;
                node4->row_id = encoded;

                link_node_to_column(columns[cell_constraint], node1);
                link_node_to_column(columns[row_constraint], node2);
                link_node_to_column(columns[col_constraint], node3);
                link_node_to_column(columns[block_constraint], node4);

                node1->right = node2;
                node2->right = node3;
                node3->right = node4;
                node4->right = node1;
                node1->left = node4;
                node2->left = node1;
                node3->left = node2;
                node4->left = node3;
            }
        }
    }
    free(columns);
}

void hide_column(DancingNode* col) {
    col->right->left = col->left;
    col->left->right = col->right;
    for (DancingNode* row = col->down; row != col; row = row->down) {
        for (DancingNode* node = row->right; node != row; node = node->right) {
            node->down->up = node->up;
            node->up->down = node->down;
            node->column->size--;
        }
    }
}

void reveal_column(DancingNode* col) {
    for (DancingNode* row = col->up; row != col; row = row->up) {
        for (DancingNode* node = row->left; node != row; node = node->left) {
            node->column->size++;
            node->down->up = node;
            node->up->down = node;
        }
    }
    col->right->left = col;
    col->left->right = col;
}

DancingNode* select_column(SudokuPuzzle* puzzle) {
    DancingNode* best = puzzle->header->right;
    for (DancingNode* col = puzzle->header->right; col != puzzle->header; col = col->right) {
        if (col->size < best->size) best = col;
    }
    return best;
}

int algorithm_x(SudokuPuzzle* puzzle, int level) {
    if (puzzle->header->right == puzzle->header) return 1;

    DancingNode* col = select_column(puzzle);
    if (!col || col->size == 0) return 0;

    hide_column(col);

    for (DancingNode* row = col->down; row != col; row = row->down) {
        puzzle->solution[puzzle->solution_size++] = row->row_id;

        for (DancingNode* node = row->right; node != row; node = node->right) {
            hide_column(node->column);
        }

        if (algorithm_x(puzzle, level + 1)) return 1;

        puzzle->solution_size--;

        for (DancingNode* node = row->left; node != row; node = node->left) {
            reveal_column(node->column);
        }
    }

    reveal_column(col);
    return 0;
}

void decode_solution(SudokuPuzzle* puzzle) {
    int dimension = puzzle->N * puzzle->N;
    for (int i = 0; i < puzzle->solution_size; i++) {
        int encoded = puzzle->solution[i];
        int num = encoded % dimension + 1;
        encoded /= dimension;
        int col = encoded % dimension;
        int row = encoded / dimension;
        puzzle->board[row][col] = num;
    }
}

int validate_sudoku(SudokuPuzzle* puzzle) {
    int dimension = puzzle->N * puzzle->N;

    for (int row = 0; row < dimension; row++) {
        int used[MAX_N * MAX_N + 1] = { 0 };
        for (int col = 0; col < dimension; col++) {
            int num = puzzle->board[row][col];
            if (num == 0) continue;
            if (num < 1 || num > dimension || used[num]) return 0;
            used[num] = 1;
        }
    }

    for (int col = 0; col < dimension; col++) {
        int used[MAX_N * MAX_N + 1] = { 0 };
        for (int row = 0; row < dimension; row++) {
            int num = puzzle->board[row][col];
            if (num == 0) continue;
            if (used[num]) return 0;
            used[num] = 1;
        }
    }

    for (int block_row = 0; block_row < puzzle->N; block_row++) {
        for (int block_col = 0; block_col < puzzle->N; block_col++) {
            int used[MAX_N * MAX_N + 1] = { 0 };
            for (int row = block_row * puzzle->N; row < (block_row + 1) * puzzle->N; row++) {
                for (int col = block_col * puzzle->N; col < (block_col + 1) * puzzle->N; col++) {
                    int num = puzzle->board[row][col];
                    if (num == 0) continue;
                    if (used[num]) return 0;
                    used[num] = 1;
                }
            }
        }
    }
    return 1;
}

int solve_puzzle(SudokuPuzzle* puzzle) {
    build_exact_cover(puzzle);
    int solved = algorithm_x(puzzle, 0);
    if (solved) {
        decode_solution(puzzle);
        if (!validate_sudoku(puzzle)) return 0;
    }
    return solved;
}

int load_puzzle(const char* filename, SudokuPuzzle* puzzle) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open input file\n");
        return 0;
    }

    if (fscanf(file, "%d", &puzzle->N) != 1) {
        fclose(file);
        return 0;
    }

    int dimension = puzzle->N * puzzle->N;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (fscanf(file, "%d", &puzzle->board[i][j]) != 1) {
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    return 1;
}

void save_result(const char* filename, SudokuPuzzle* puzzle, int solved) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Cannot open output file\n");
        return;
    }

    if (!solved) {
        fprintf(file, "0\n");
    }
    else {
        int dimension = puzzle->N * puzzle->N;
        fprintf(file, "%d\n", puzzle->N);
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                fprintf(file, "%d", puzzle->board[i][j]);
                if (j < dimension - 1) fprintf(file, " ");
            }
            fprintf(file, "\n");
        }
    }
    fclose(file);
}