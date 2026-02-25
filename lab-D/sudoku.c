#include <stdlib.h>
#include <string.h>
#include "sudoku.h"

struct Puzzle {
    int size;
    int dimension;
    int* cells;
    unsigned char* rows;
    unsigned char* cols;
    unsigned char* boxes;
    int consistent;
};

static int get_box(struct Puzzle* p, int r, int c) {
    return (r / p->size) * p->size + (c / p->size);
}

static int get_index(int category, int val, int max) {
    return category * (max + 1) + val;
}

static int can_place(struct Puzzle* p, int r, int c, int val) {
    int b = get_box(p, r, c);
    int max = p->dimension;
    return !p->rows[get_index(r, val, max)] &&
        !p->cols[get_index(c, val, max)] &&
        !p->boxes[get_index(b, val, max)];
}

static void apply_move(struct Puzzle* p, int r, int c, int val) {
    int b = get_box(p, r, c);
    int max = p->dimension;
    p->cells[r * max + c] = val;
    p->rows[get_index(r, val, max)] = 1;
    p->cols[get_index(c, val, max)] = 1;
    p->boxes[get_index(b, val, max)] = 1;
}

static void undo_move(struct Puzzle* p, int r, int c, int val) {
    int b = get_box(p, r, c);
    int max = p->dimension;
    p->cells[r * max + c] = 0;
    p->rows[get_index(r, val, max)] = 0;
    p->cols[get_index(c, val, max)] = 0;
    p->boxes[get_index(b, val, max)] = 0;
}

static int count_options(struct Puzzle* p, int r, int c) {
    int cnt = 0;
    for (int v = 1; v <= p->dimension; v++) {
        if (can_place(p, r, c, v)) cnt++;
    }
    return cnt;
}

static int select_cell(struct Puzzle* p, int* r, int* c) {
    int min = 1000;
    int found = 0;
    int dim = p->dimension;

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (p->cells[i * dim + j] != 0) continue;

            int opts = count_options(p, i, j);
            if (opts == 0) return -1;

            if (!found || opts < min) {
                min = opts;
                *r = i;
                *c = j;
                found = 1;
                if (min == 1) return 1;
            }
        }
    }
    return found ? 1 : 0;
}

static int recursive_solve(struct Puzzle* p) {
    int row, col;
    int status = select_cell(p, &row, &col);

    if (status == 0) return 1;
    if (status == -1) return 0;

    for (int v = 1; v <= p->dimension; v++) {
        if (!can_place(p, row, col, v)) continue;

        apply_move(p, row, col, v);
        if (recursive_solve(p)) return 1;
        undo_move(p, row, col, v);
    }
    return 0;
}

Puzzle* create_puzzle(int size) {
    if (size <= 2 || size >= 10) return NULL;

    Puzzle* p = (Puzzle*)malloc(sizeof(Puzzle));
    if (!p) return NULL;

    p->size = size;
    p->dimension = size * size;
    p->consistent = 1;

    int dim = p->dimension;
    p->cells = (int*)calloc(dim * dim, sizeof(int));
    if (!p->cells) {
        free(p);
        return NULL;
    }

    int used = dim * (dim + 1);
    p->rows = (unsigned char*)calloc(used, sizeof(unsigned char));
    p->cols = (unsigned char*)calloc(used, sizeof(unsigned char));
    p->boxes = (unsigned char*)calloc(used, sizeof(unsigned char));

    if (!p->rows || !p->cols || !p->boxes) {
        free_puzzle(p);
        return NULL;
    }

    return p;
}

void free_puzzle(Puzzle* puzzle) {
    if (!puzzle) return;
    free(puzzle->cells);
    free(puzzle->rows);
    free(puzzle->cols);
    free(puzzle->boxes);
    free(puzzle);
}

void set_cell(Puzzle* puzzle, int row, int col, int val, int* success) {
    if (!puzzle || !success || !puzzle->consistent) {
        if (success) *success = 0;
        return;
    }

    int dim = puzzle->dimension;
    if (row < 0 || col < 0 || row >= dim || col >= dim || val < 0 || val > dim) {
        puzzle->consistent = 0;
        *success = 0;
        return;
    }

    if (val == 0) {
        puzzle->cells[row * dim + col] = 0;
        *success = 1;
        return;
    }

    if (!can_place(puzzle, row, col, val)) {
        puzzle->consistent = 0;
        *success = 0;
        return;
    }

    apply_move(puzzle, row, col, val);
    *success = 1;
}

int solve_puzzle(Puzzle* puzzle) {
    if (!puzzle || !puzzle->consistent) return 0;
    return recursive_solve(puzzle);
}

void display_puzzle(Puzzle* puzzle, FILE* output) {
    if (!puzzle || !output) return;

    int dim = puzzle->dimension;
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (j > 0) fprintf(output, " ");
            fprintf(output, "%d", puzzle->cells[i * dim + j]);
        }
        fprintf(output, "\n");
    }
}