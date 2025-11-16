



#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_SIZE 52
typedef struct {
    int x;
    int y;
}Point;
int readMaze(char maze[MAX_SIZE][MAX_SIZE], int* startX, int* startY, int* endX, int* endY) 
{
    FILE* file = fopen("maze.txt", "r");
    if (!file)
    {
        printf("fail open maze.txt!\n");
        return -1;
    }
    int rows = 0;
    char line[MAX_SIZE];
    while (fgets(line, sizeof(line), file) && rows < MAX_SIZE)
    {
        int i = 0;
        while (line[i] != '\n' && line[i] != '\0' && i < MAX_SIZE)
        {
            maze[rows][i] = line[i];

            if (line[i] == 'S')
            {
                *startX = rows;
                *startY = i;
            }
            else if (line[i] == 'E')
            {
                *endX = rows;
                *endY = i;
            }
            i++;
        }
        rows++;
    }
    fclose(file);
    return rows;
}
int getCols(char maze[MAX_SIZE][MAX_SIZE], int rows)
{
    int maxCols = 0;
    for (int i = 0; i < rows; i++) {
        int cols = 0;
        while (maze[i][cols] != '\0' && maze[i][cols] != '\n') 
        {
            cols++;
        }
        if (cols > maxCols) {
            maxCols = cols;
        }
    }
    return maxCols;
}

void printMaze(char maze[MAX_SIZE][MAX_SIZE], int rows, int cols)
{
    printf("labirint (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool findPathDFS(char maze[MAX_SIZE][MAX_SIZE], int x, int y, int endX, int endY,
    int rows, int cols, bool visited[MAX_SIZE][MAX_SIZE],
    Point path[MAX_SIZE * MAX_SIZE], int* pathLength)
{


    if (x < 0||  y < 0||  x >= rows || y >= cols)
    {
        return false;
    }

    if (maze[x][y] == '#' || visited[x][y]) 
    {
        return false;
    }

    visited[x][y] = true;

    path[*pathLength] = (Point){ x, y };
    (*pathLength)++;

    if (x == endX && y == endY)
    {
        return true;
    }

    if (findPathDFS(maze, x, y + 1, endX, endY, rows, cols, visited, path, pathLength) ||
        findPathDFS(maze, x + 1, y, endX, endY, rows, cols, visited, path, pathLength) ||
        findPathDFS(maze, x, y - 1, endX, endY, rows, cols, visited, path, pathLength) ||
        findPathDFS(maze, x - 1, y, endX, endY, rows, cols, visited, path, pathLength))
    {
        return true;
    }

    (*pathLength)--;
    return false;
}

void visualizePath(char maze[MAX_SIZE][MAX_SIZE], Point path[MAX_SIZE * MAX_SIZE],
    int pathLength, int startX, int startY, int endX, int endY,
    int rows, int cols) {

    char visualMaze[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visualMaze[i][j] = maze[i][j];
        }
    }

    for (int i = 1; i < pathLength - 1; i++)
    {
        int x = path[i].x;
        int y = path[i].y;
        if (visualMaze[x][y] != 'S' && visualMaze[x][y] != 'E')
        {
            visualMaze[x][y] = '*';
        }
    }

    printf("find path:\n");
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            printf("%c", visualMaze[i][j]);
        }
        printf("\n");
    }
}

int orig_main() {
    char maze[MAX_SIZE][MAX_SIZE] = { 0 };
    int startX, startY, endX, endY;

    int rows = readMaze(maze, &startX, &startY, &endX, &endY);
    if (rows == -1) 
    {
        return -1;
    }

    int cols = getCols(maze, rows);
    printMaze(maze, rows, cols);
    bool visited[MAX_SIZE][MAX_SIZE] = { false };

    Point path[MAX_SIZE * MAX_SIZE];
    int pathLength = 0;

    if (findPathDFS(maze, startX, startY, endX, endY, rows, cols, visited, path, &pathLength)) 
    {
        visualizePath(maze, path, pathLength, startX, startY, endX, endY, rows, cols);
    }
    else
    {
        printf("where is no path(((!\n");
    }
    return 0;
}