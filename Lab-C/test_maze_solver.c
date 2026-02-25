#include <stdio.h>
#include <assert.h>
#include "maze_solver.h"

void test_no1() {
    printf("TestSimpleMaze_no1: ");
    char maze[MAX_ROWS][MAX_COLS] = { {'S', '0', 'E'} };
    Point start = { 0, 0 };
    Point exit = { 0, 2 };
    Path path;

    solve_maze_right_hand(maze, 1, 3, start, exit, &path);
    assert(path.length > 1);
    printf("OK\n");
}

void test_no2() {
    printf("TestMazeWithWall_no2: ");
    char maze[MAX_ROWS][MAX_COLS] = {
        {'S', '1', '0'},
        {'0', '0', '0'},
        {'0', '0', 'E'}
    };

    Point start = { 0, 0 };
    Point exit = { 2, 2 };
    Path path;

    solve_maze_right_hand(maze, 3, 3, start, exit, &path);
    assert(path.length > 1);
    printf("OK\n");
}

void test_no3() {
    printf("TestSmallMaze_no3: ");
    char maze[MAX_ROWS][MAX_COLS] = {
        {'S', '0'},
        {'0', 'E'}
    };

    Point start = { 0, 0 };
    Point exit = { 1, 1 };
    Path path;

    solve_maze_right_hand(maze, 2, 2, start, exit, &path);
    assert(path.length > 1);
    printf("OK\n");
}

void test_no4() {
    printf("TestStartAtExit_no4: ");
    char maze[MAX_ROWS][MAX_COLS] = { {'S'} };

    Point start = { 0, 0 };
    Point exit = { 0, 0 };
    Path path;

    solve_maze_right_hand(maze, 1, 1, start, exit, &path);
    assert(path.length >= 1);
    printf("OK\n");
}

void test_no5() {
    printf("TestDeadEndMaze_no5: ");
    char maze[MAX_ROWS][MAX_COLS] = {
        {'S', '0', '1'},
        {'1', '0', '1'},
        {'0', '0', 'E'}
    };

    Point start = { 0, 0 };
    Point exit = { 2, 2 };
    Path path;

    solve_maze_right_hand(maze, 3, 3, start, exit, &path);
    assert(path.length > 1);
    printf("OK\n");
}

void test_no6() {
    printf("TestVerticalCorridor_no6: ");
    char maze[MAX_ROWS][MAX_COLS] = {
        {'S'},
        {'0'},
        {'0'},
        {'E'}
    };

    Point start = { 0, 0 };
    Point exit = { 3, 0 };
    Path path;

    solve_maze_right_hand(maze, 4, 1, start, exit, &path);
    assert(path.length > 1);
    printf("OK\n");
}
    
void test_no7() {
    printf("TestCorridorMaze_no7: ");
    char maze[MAX_ROWS][MAX_COLS] = {
        {'S', '0', '0', '0'},
        {'1', '1', 'E', '1'},
        {'0', '0', '0', '0'},
        {'0', '1', '1', '0'}
    };

    Point start = { 0, 0 };
    Point exit = { 1, 2 };
    Path path;

    solve_maze_right_hand(maze, 4, 4, start, exit, &path);
    assert(path.length > 1);
    printf("OK\n");
}

void test_no8() {
    printf("TestLMaze_no8: ");
    char maze[MAX_ROWS][MAX_COLS] = {
        {'S', '1'},
        {'0', '1'},
        {'0', '1'},
        {'0', 'E'}
    };

    Point start = { 0, 0 };
    Point exit = { 3, 1 };
    Path path;

    solve_maze_right_hand(maze, 4, 2, start, exit, &path);
    assert(path.length > 1);
    printf("OK\n");
}

void test_no9() {
    printf("TestLargeEmptyMaze_no9: ");
    char maze[MAX_ROWS][MAX_COLS];

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            maze[i][j] = '0';
        }
    }

    maze[0][0] = 'S';
    maze[9][9] = 'E';

    Point start = { 0, 0 };
    Point exit = { 9, 9 };
    Path path;

    solve_maze_right_hand(maze, 10, 10, start, exit, &path);
    assert(path.length > 1);
    printf("OK\n");
}

void test_no10() {
    printf("TestMultiPathMaze_no10: ");
    char maze[MAX_ROWS][MAX_COLS] = {
        {'S', '0', '0', '0'},
        {'1', '1', '0', '1'},
        {'0', '0', '0', '0'},
        {'0', '1', '1', 'E'}
    };

    Point start = { 0, 0 };
    Point exit = { 3, 3 };
    Path path;

    solve_maze_right_hand(maze, 4, 4, start, exit, &path);
    assert(path.length > 1);
    printf("OK\n");
}

void test_no11() {
    printf("TestIsValidCell_no11: ");
    char maze[MAX_ROWS][MAX_COLS] = { {'S', '0', '1'} };

    assert(is_valid_cell(maze, 1, 3, 0, 0) == true);  
    assert(is_valid_cell(maze, 1, 3, 0, 1) == true);  

    assert(is_valid_cell(maze, 1, 3, 0, 2) == false); 
    assert(is_valid_cell(maze, 1, 3, -1, 0) == false); 
    assert(is_valid_cell(maze, 1, 3, 0, 3) == false);  
    assert(is_valid_cell(maze, 1, 3, 1, 0) == false);  

    printf("OK\n");
}

void run_all_tests() {
    printf("=== Maze Solver Unit Tests ===\n\n");

    test_no1();
    test_no2();
    test_no3();
    test_no4();
    test_no5();
    test_no6();
    test_no7();
    test_no8();
    test_no9();
    test_no10();
    test_no11();

    printf("\nAll tests passed successfully!\n");
}