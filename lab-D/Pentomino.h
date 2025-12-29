#pragma once
#include <stdio.h>
#include <stdlib.h>

#ifndef PENTOMINO_H
#define PENTOMINO_H

#define MAX_CELLS 5
#define FIELD_SIZE 10

typedef struct {
    int x;
    int y;
} Cell;

typedef struct {
    Cell cells[MAX_CELLS];
    int count;
} Pentomino;

typedef struct {
    int width;
    int height;
    int field[FIELD_SIZE][FIELD_SIZE];
} Field;

/* Pentomino functions */
Pentomino* init_pentomino();
void free_pentomino(Pentomino* p);
Pentomino* load_pentomino(const char* filename);
int is_valid_pentomino(Pentomino* p);
void rotate_pentomino(Pentomino* p);

/* Field functions */
Field* init_field(int width, int height);
void free_field(Field* f);
int can_place(Field* f, Pentomino* p, int offset_x, int offset_y);

/* Output */
void write_pentomino(Pentomino* p, const char* filename);

#endif

