#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* left, * right, * up, * down, * column;
    int row_id, size;
} Node;

typedef struct {
    Node head, ** columns, ** rows, ** column_nodes;
    int* solution, solution_count, row_count, col_count, board_size, box_size;
} DLX;

typedef struct {
    int N, board_size, box_size, ** board;
} Sudoku;

int* row_to_r, * row_to_c, * row_to_num, total_rows;

void init_dlx(DLX* dlx, int cols, int board_size, int box_size) {
    dlx->head.left = dlx->head.right = dlx->head.up = dlx->head.down = &dlx->head;
    dlx->col_count = cols; dlx->row_count = dlx->solution_count = 0;
    dlx->board_size = board_size; dlx->box_size = box_size;

    dlx->columns = malloc(sizeof(Node*) * cols);
    dlx->rows = malloc(sizeof(Node*) * (board_size * board_size * board_size));
    dlx->column_nodes = malloc(sizeof(Node*) * cols);
    dlx->solution = malloc(sizeof(int) * board_size * board_size);

    row_to_r = malloc(sizeof(int) * (board_size * board_size * board_size));
    row_to_c = malloc(sizeof(int) * (board_size * board_size * board_size));
    row_to_num = malloc(sizeof(int) * (board_size * board_size * board_size));
    total_rows = 0;

    for (int i = 0; i < cols; i++) {
        Node* col_node = malloc(sizeof(Node));
        col_node->left = &dlx->head; col_node->right = dlx->head.right;
        dlx->head.right->left = col_node; dlx->head.right = col_node;
        col_node->up = col_node->down = col_node->column = col_node;
        col_node->row_id = -1; col_node->size = 0;
        dlx->column_nodes[i] = col_node;
    }
}

void add_row(DLX* dlx, int* cols, int col_count, int r, int c, int num) {
    Node* first = NULL, * prev = NULL;
    for (int i = 0; i < col_count; i++) {
        Node* col_node = dlx->column_nodes[cols[i]];
        Node* new_node = malloc(sizeof(Node));
        new_node->column = col_node; new_node->row_id = total_rows;
        new_node->up = col_node->up; new_node->down = col_node;
        col_node->up->down = new_node; col_node->up = new_node;
        col_node->size++;

        if (!first) first = new_node->left = new_node->right = new_node;
        else {
            new_node->left = prev; new_node->right = first;
            prev->right = new_node; first->left = new_node;
        }
        prev = new_node;
    }
    if (first) {
        row_to_r[total_rows] = r; row_to_c[total_rows] = c;
        row_to_num[total_rows] = num; dlx->rows[dlx->row_count++] = first; total_rows++;
    }
}

void cover(Node* col) {
    col->right->left = col->left; col->left->right = col->right;
    for (Node* i = col->down; i != col; i = i->down)
        for (Node* j = i->right; j != i; j = j->right) {
            j->down->up = j->up; j->up->down = j->down; j->column->size--;
        }
}

void uncover(Node* col) {
    for (Node* i = col->up; i != col; i = i->up)
        for (Node* j = i->left; j != i; j = j->left) {
            j->column->size++; j->down->up = j; j->up->down = j;
        }
    col->right->left = col; col->left->right = col;
}

int search(DLX* dlx, int depth) {
    if (dlx->head.right == &dlx->head) { dlx->solution_count = depth; return 1; }

    Node* min_col = dlx->head.right;
    for (Node* j = min_col->right; j != &dlx->head; j = j->right)
        if (j->size < min_col->size) min_col = j;

    if (min_col->size == 0) return 0;

    cover(min_col);
    for (Node* r = min_col->down; r != min_col; r = r->down) {
        dlx->solution[depth] = r->row_id;
        for (Node* j = r->right; j != r; j = j->right) cover(j->column);
        if (search(dlx, depth + 1)) return 1;
        for (Node* j = r->left; j != r; j = j->left) uncover(j->column);
    }
    uncover(min_col);
    return 0;
}

void sudoku_to_exact_cover(DLX* dlx, Sudoku* sudoku) {
    int constraints[4], bs = sudoku->board_size, bx = sudoku->box_size;
    for (int r = 0; r < bs; r++) for (int c = 0; c < bs; c++) {
        if (sudoku->board[r][c]) {
            int n = sudoku->board[r][c] - 1;
            constraints[0] = r * bs + c;
            constraints[1] = bs * bs + r * bs + n;
            constraints[2] = 2 * bs * bs + c * bs + n;
            constraints[3] = 3 * bs * bs + ((r / bx) * bx + (c / bx)) * bs + n;
            add_row(dlx, constraints, 4, r, c, n);
        }
        else for (int n = 0; n < bs; n++) {
            constraints[0] = r * bs + c;
            constraints[1] = bs * bs + r * bs + n;
            constraints[2] = 2 * bs * bs + c * bs + n;
            constraints[3] = 3 * bs * bs + ((r / bx) * bx + (c / bx)) * bs + n;
            add_row(dlx, constraints, 4, r, c, n);
        }
    }
}

void solution_to_sudoku(DLX* dlx, Sudoku* sudoku) {
    for (int i = 0; i < dlx->solution_count; i++) {
        int id = dlx->solution[i];
        sudoku->board[row_to_r[id]][row_to_c[id]] = row_to_num[id] + 1;
    }
}

void read_sudoku(const char* filename, Sudoku* sudoku) {
    FILE* file = fopen(filename, "r");
    fscanf(file, "%d", &sudoku->N);
    sudoku->board_size = sudoku->N * sudoku->N;
    sudoku->box_size = sudoku->N;
    sudoku->board = malloc(sizeof(int*) * sudoku->board_size);
    for (int i = 0; i < sudoku->board_size; i++) {
        sudoku->board[i] = malloc(sizeof(int) * sudoku->board_size);
        for (int j = 0; j < sudoku->board_size; j++)
            fscanf(file, "%d", &sudoku->board[i][j]);
    }
    fclose(file);
}

void write_sudoku(const char* filename, Sudoku* sudoku) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < sudoku->board_size; i++) {
        for (int j = 0; j < sudoku->board_size; j++)
            fprintf(file, "%d ", sudoku->board[i][j]);
        fprintf(file, "\n");
    }
    fclose(file);
}

void write_no_solution(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;
    fprintf(file, "0\n");
    fclose(file);
}

void free_dlx(DLX* dlx) {
    if (!dlx) return;
    for (int i = 0; i < dlx->row_count; i++) {
        if (dlx->rows[i]) {
            Node* node = dlx->rows[i];
            Node* current = node->right;
            while (current != node) {
                Node* temp = current;
                current = current->right;
                free(temp);
            }
            free(node);
        }
    }
    for (int i = 0; i < dlx->col_count; i++) {
        if (dlx->column_nodes[i]) free(dlx->column_nodes[i]);
    }
    if (dlx->columns) free(dlx->columns);
    if (dlx->rows) free(dlx->rows);
    if (dlx->column_nodes) free(dlx->column_nodes);
    if (dlx->solution) free(dlx->solution);
}

void free_sudoku(Sudoku* sudoku) {
    if (!sudoku) return;
    for (int i = 0; i < sudoku->board_size; i++) {
        if (sudoku->board[i]) free(sudoku->board[i]);
    }
    if (sudoku->board) free(sudoku->board);
}

