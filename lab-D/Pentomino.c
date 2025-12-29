#include "Pentomino.h"

Pentomino* init_pentomino() {
    Pentomino* p = (Pentomino*)malloc(sizeof(Pentomino));
    p->count = 0;
    return p;
}

void free_pentomino(Pentomino* p) {
    if (p) free(p);
}

Pentomino* load_pentomino(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    Pentomino* p = init_pentomino();
    int x, y;

    while (fscanf(file, "%d %d", &x, &y) == 2) {
        if (p->count >= MAX_CELLS) {
            fclose(file);
            free_pentomino(p);
            return NULL;
        }
        p->cells[p->count].x = x;
        p->cells[p->count].y = y;
        p->count++;
    }

    fclose(file);
    return p;
}

int is_valid_pentomino(Pentomino* p) {
    if (!p || p->count != MAX_CELLS) return 0;

    for (int i = 0; i < MAX_CELLS; i++) {
        for (int j = i + 1; j < MAX_CELLS; j++) {
            if (p->cells[i].x == p->cells[j].x &&
                p->cells[i].y == p->cells[j].y)
                return 0;
        }
    }
    return 1;
}

void rotate_pentomino(Pentomino* p) {
    if (!p) return;

    for (int i = 0; i < p->count; i++) {
        int x = p->cells[i].x;
        p->cells[i].x = -p->cells[i].y;
        p->cells[i].y = x;
    }
}

Field* init_field(int width, int height) {
    Field* f = (Field*)malloc(sizeof(Field));
    f->width = width;
    f->height = height;

    for (int i = 0; i < FIELD_SIZE; i++)
        for (int j = 0; j < FIELD_SIZE; j++)
            f->field[i][j] = 0;

    return f;
}

void free_field(Field* f) {
    if (f) free(f);
}

int can_place(Field* f, Pentomino* p, int offset_x, int offset_y) {
    if (!f || !p) return 0;

    for (int i = 0; i < p->count; i++) {
        int x = p->cells[i].x + offset_x;
        int y = p->cells[i].y + offset_y;

        if (x < 0 || y < 0 || x >= f->width || y >= f->height)
            return 0;

        if (f->field[y][x] != 0)
            return 0;
    }
    return 1;
}

void write_pentomino(Pentomino* p, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;

    if (!p) {
        fprintf(file, "0\n");
    }
    else {
        for (int i = 0; i < p->count; i++) {
            fprintf(file, "%d %d\n", p->cells[i].x, p->cells[i].y);
        }
    }

    fclose(file);
}
