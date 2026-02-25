#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include <stdbool.h>

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point points[MAX_ROWS * MAX_COLS];
    int length;
} Path;

void solve_maze_right_hand(char maze[MAX_ROWS][MAX_COLS], int rows, int cols,
    Point start, Point exit, Path* path);
void print_maze_with_path(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Path* path);
bool is_valid_cell(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int x, int y);

#endif