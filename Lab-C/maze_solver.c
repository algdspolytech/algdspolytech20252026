#include <stdio.h>
#include "maze_solver.h"

bool is_valid_cell(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != '1');
}

void solve_maze_right_hand(char maze[MAX_ROWS][MAX_COLS], int rows, int cols,
    Point start, Point exit, Path* path) {
    int x = start.x;
    int y = start.y;
    int dir = 1; 

    path->length = 0;
    path->points[0].x = x;
    path->points[0].y = y;
    path->length = 1;

    int max_steps = rows * cols * 10;
    int steps = 0;

    while (steps < max_steps) {
        steps++;

        if (x == exit.x && y == exit.y) {
            printf("Exit found in %d steps!\n", steps);
            return;
        }

        int rx = x, ry = y;
        switch ((dir + 1) % 4) {
        case 0: rx--; break;
        case 1: ry++; break;
        case 2: rx++; break;
        case 3: ry--; break;
        }

        int fx = x, fy = y;
        switch (dir) {
        case 0: fx--; break;
        case 1: fy++; break;
        case 2: fx++; break;
        case 3: fy--; break;
        }

        if (is_valid_cell(maze, rows, cols, rx, ry)) {
            dir = (dir + 1) % 4;
            x = rx;
            y = ry;
        }
        else if (is_valid_cell(maze, rows, cols, fx, fy)) {
            x = fx;
            y = fy;
        }
        else {
            dir = (dir + 3) % 4;
            continue;
        }

        if (path->length == 0 ||
            path->points[path->length - 1].x != x ||
            path->points[path->length - 1].y != y) {
            path->points[path->length].x = x;
            path->points[path->length].y = y;
            path->length++;
        }
    }

    printf("Could not find exit\n");
}

void print_maze_with_path(char maze[MAX_ROWS][MAX_COLS], int rows, int cols, Path* path) {
    char display[MAX_ROWS][MAX_COLS];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            display[i][j] = maze[i][j];
        }
    }

    for (int i = 0; i < path->length; i++) {
        int x = path->points[i].x;
        int y = path->points[i].y;

        if (display[x][y] != 'S' && display[x][y] != 'E') {
            display[x][y] = '*';
        }
    }

    printf("\nMaze with path:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", display[i][j]);
        }
        printf("\n");
    }
}