#define _CRT_SECURE_NO_WARNINGS
#include "sudoku_dlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 9
#define MAX_ROWS (MAX_N * MAX_N * MAX_N)
#define MAX_COLS (4 * MAX_N * MAX_N)
#define INITIAL_SOLUTION_CAPACITY 100

DLX* dlx_create(int cols) {
    DLX* dlx = (DLX*)malloc(sizeof(DLX));
    if (!dlx) return NULL;

    dlx->solution_size = 0;
    dlx->solution_capacity = INITIAL_SOLUTION_CAPACITY;
    dlx->solution = (Node**)malloc(dlx->solution_capacity * sizeof(Node*));
    if (!dlx->solution) {
        free(dlx);
        return NULL;
    }

    dlx->header = (ColumnHeader*)malloc(sizeof(ColumnHeader));
    if (!dlx->header) {
        free(dlx->solution);
        free(dlx);
        return NULL;
    }

    Node* head = &(dlx->header->base);
    head->left = head->right = head;
    head->up = head->down = head;
    dlx->header->size = 0;
    dlx->header->id = -1;

    ColumnHeader* prev = dlx->header;
    for (int i = 0; i < cols; i++) {
        ColumnHeader* col = (ColumnHeader*)malloc(sizeof(ColumnHeader));
        if (!col) {
            // Освобождаем уже выделенные ресурсы
            while (prev != dlx->header) {
                ColumnHeader* temp = (ColumnHeader*)prev->base.left;
                free(prev);
                prev = temp;
            }
            free(dlx->header);
            free(dlx->solution);
            free(dlx);
            return NULL;
        }

        Node* node = &col->base;
        node->left = &prev->base;
        node->right = &dlx->header->base;
        prev->base.right = node;
        dlx->header->base.left = node;
        node->up = node->down = node;
        col->size = 0;
        col->id = i;
        col->base.col = col;
        prev = col;
    }
    return dlx;
}

void cover_column(ColumnHeader* col) {
    if (!col) return;

    col->base.right->left = col->base.left;
    col->base.left->right = col->base.right;
    Node* i = col->base.down;
    while (i != &col->base) {
        Node* j = i->right;
        while (j != i) {
            j->down->up = j->up;
            j->up->down = j->down;
            if (j->col) j->col->size--;
            j = j->right;
        }
        i = i->down;
    }
}

void uncover_column(ColumnHeader* col) {
    if (!col) return;

    Node* i = col->base.up;
    while (i != &col->base) {
        Node* j = i->left;
        while (j != i) {
            if (j->col) {
                j->col->size++;
                j->down->up = j;
                j->up->down = j;
            }
            j = j->left;
        }
        i = i->up;
    }
    col->base.right->left = &col->base;
    col->base.left->right = &col->base;
}

ColumnHeader* choose_column(DLX* dlx) {
    if (!dlx || !dlx->header) return NULL;

    int min_size = 1 << 30;
    ColumnHeader* chosen = NULL;
    ColumnHeader* col = (ColumnHeader*)dlx->header->base.right;
    while (col != dlx->header) {
        if (col->size < min_size) {
            min_size = col->size;
            chosen = col;
        }
        col = (ColumnHeader*)col->base.right;
    }
    return chosen;
}

void dlx_add_row(DLX* dlx, int row_id, int cols[], int count) {
    if (!dlx || !cols || count <= 0) return;

    Node* prev = NULL;
    Node* first = NULL;

    for (int i = 0; i < count; i++) {
        ColumnHeader* col = (ColumnHeader*)dlx->header->base.right;
        while (col != dlx->header && col->id != cols[i]) {
            col = (ColumnHeader*)col->base.right;
        }
        if (col == dlx->header) continue;

        Node* node = (Node*)malloc(sizeof(Node));
        if (!node) continue;

        node->row_id = row_id;
        node->col = col;

        node->up = col->base.up;
        node->down = &col->base;
        col->base.up->down = node;
        col->base.up = node;

        if (!prev) {
            node->left = node->right = node;
            first = node;
        }
        else {
            node->left = prev;
            node->right = first;
            prev->right = node;
            first->left = node;
        }
        prev = node;
        col->size++;
    }
}

bool dlx_solve(DLX* dlx) {
    if (!dlx || !dlx->header) return false;

    if (dlx->header->base.right == &dlx->header->base) {
        return true;
    }

    ColumnHeader* col = choose_column(dlx);
    if (!col || col->size == 0) return false;

    cover_column(col);

    Node* row_node = col->base.down;
    while (row_node != &col->base) {
        // Увеличиваем capacity при необходимости
        if (dlx->solution_size >= dlx->solution_capacity) {
            dlx->solution_capacity *= 2;
            Node** new_solution = (Node**)realloc(dlx->solution,
                dlx->solution_capacity * sizeof(Node*));
            if (!new_solution) {
                uncover_column(col);
                return false;
            }
            dlx->solution = new_solution;
        }

        dlx->solution[dlx->solution_size++] = row_node;

        // Cover все столбцы в строке
        Node* j = row_node->right;
        while (j != row_node) {
            if (j->col) cover_column(j->col);
            j = j->right;
        }

        if (dlx_solve(dlx)) {
            uncover_column(col);
            return true;
        }

        // Backtrack
        dlx->solution_size--;

        j = row_node->left;
        while (j != row_node) {
            if (j->col) uncover_column(j->col);
            j = j->left;
        }

        row_node = row_node->down;
    }

    uncover_column(col);
    return false;
}

void dlx_free(DLX* dlx) {
    if (!dlx) return;

    if (dlx->header) {
        ColumnHeader* col = (ColumnHeader*)dlx->header->base.right;
        while (col != dlx->header) {
            Node* node = col->base.down;
            while (node != &col->base) {
                Node* next = node->down;
                free(node);
                node = next;
            }
            ColumnHeader* next_col = (ColumnHeader*)col->base.right;
            free(col);
            col = next_col;
        }
        free(dlx->header);
    }

    if (dlx->solution) free(dlx->solution);
    free(dlx);
}

int** read_sudoku(const char* filename, int* N) {
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;

    if (fscanf(f, "%d", N) != 1) {
        fclose(f);
        return NULL;
    }

    int size = (*N) * (*N);
    int** grid = (int**)malloc(size * sizeof(int*));
    if (!grid) {
        fclose(f);
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        grid[i] = (int*)malloc(size * sizeof(int));
        if (!grid[i]) {
            for (int j = 0; j < i; j++) free(grid[j]);
            free(grid);
            fclose(f);
            return NULL;
        }

        for (int j = 0; j < size; j++) {
            if (fscanf(f, "%d", &grid[i][j]) != 1) {
                for (int k = 0; k <= i; k++) free(grid[k]);
                free(grid);
                fclose(f);
                return NULL;
            }
        }
    }
    fclose(f);
    return grid;
}

void free_sudoku(int** grid, int N) {
    if (!grid) return;

    int size = N * N;
    for (int i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);
}

DLX* sudoku_to_exact_cover(int** grid, int N) {
    if (!grid || N <= 0) return NULL;

    int size = N * N;
    int cols = 4 * size * size;
    DLX* dlx = dlx_create(cols);
    if (!dlx) return NULL;

    int row_index = 0;
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            int block = (r / N) * N + (c / N);
            for (int num = 1; num <= size; num++) {
                if (grid[r][c] == 0 || grid[r][c] == num) {
                    int constraint[4];
                    constraint[0] = r * size + c;
                    constraint[1] = size * size + r * size + (num - 1);
                    constraint[2] = 2 * size * size + c * size + (num - 1);
                    constraint[3] = 3 * size * size + block * size + (num - 1);
                    dlx_add_row(dlx, row_index, constraint, 4);
                    row_index++;
                }
            }
        }
    }
    return dlx;
}

void save_solution(DLX* dlx, int** grid, int N) {
    if (!dlx || !grid || N <= 0) return;

    int size = N * N;
    for (int i = 0; i < dlx->solution_size; i++) {
        Node* node = dlx->solution[i];
        if (!node) continue;

        int row_id = node->row_id;
        int num = (row_id % size) + 1;
        int pos = row_id / size;
        int r = pos / size;
        int c = pos % size;
        grid[r][c] = num;
    }
}

bool solve_sudoku_dlx(const char* input_file, const char* output_file) {
    if (!input_file || !output_file) return false;

    int N = 0;
    int** grid = read_sudoku(input_file, &N);
    if (!grid || N <= 0) {
        FILE* f = fopen(output_file, "w");
        if (f) {
            fprintf(f, "0\n");
            fclose(f);
        }
        return false;
    }

    DLX* dlx = sudoku_to_exact_cover(grid, N);
    if (!dlx) {
        free_sudoku(grid, N);
        FILE* f = fopen(output_file, "w");
        if (f) {
            fprintf(f, "0\n");
            fclose(f);
        }
        return false;
    }

    bool solved = dlx_solve(dlx);

    FILE* f = fopen(output_file, "w");
    if (f) {
        if (solved) {
            save_solution(dlx, grid, N);
            int size = N * N;
            fprintf(f, "%d\n", N);
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    fprintf(f, "%d ", grid[i][j]);
                }
                fprintf(f, "\n");
            }
        }
        else {
            fprintf(f, "0\n");
        }
        fclose(f);
    }

    dlx_free(dlx);
    free_sudoku(grid, N);
    return solved;
}