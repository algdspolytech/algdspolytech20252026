#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "maze_solver.h"

void run_all_tests();

int main() {
    int choice;

    printf("Maze Solver Laboratory\n");
    printf("======================\n");
    printf("1. Run demo\n");
    printf("2. Run all tests\n");
    printf("Enter choice (1 or 2): ");

    scanf("%d", &choice);

    if (choice == 1) {
        printf("=== Maze Path Finder Demo ===\n");

        char maze[MAX_ROWS][MAX_COLS] = {
            {'S', '0', '1', '0', '0'},
            {'0', '0', '1', '0', '1'},
            {'0', '1', '0', '0', '0'},
            {'0', '0', '0', '1', '0'},
            {'1', '0', '0', '0', 'E'}
        };

        int rows = 5;
        int cols = 5;

        Point start = { 0, 0 };
        Point exit = { 4, 4 };
        Path path;

        printf("\nOriginal maze:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%c ", maze[i][j]);
            }
            printf("\n");
        }

        solve_maze_right_hand(maze, rows, cols, start, exit, &path);
        print_maze_with_path(maze, rows, cols, &path);
    }
    else if (choice == 2) {
        run_all_tests();
    }
    else {
        printf("Invalid choice\n");
    }

    printf("\nPress Enter to exit...");
    getchar(); 
    getchar();  

    return 0;
}