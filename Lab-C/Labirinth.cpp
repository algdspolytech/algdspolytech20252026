



#include <gtest/gtest.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
extern "C" 
{
#define MAX_SIZE 52
    typedef struct
    {
        int x;
        int y;
    } Point;
    int readMaze(char maze[MAX_SIZE][MAX_SIZE], int* startX, int* startY, int* endX, int* endY);
    int getCols(char maze[MAX_SIZE][MAX_SIZE], int rows);
    bool findPathDFS(char maze[MAX_SIZE][MAX_SIZE], int x, int y, int endX, int endY,int rows, int cols, bool visited[MAX_SIZE][MAX_SIZE],Point path[MAX_SIZE * MAX_SIZE], int* pathLength);
}
void createTestFile(const char* filename, const char* content)
{
    FILE* f;
    errno_t err = fopen_s(&f, filename, "w");
    if (err == 0 && f)
    {
        fprintf(f, "%s", content);
        fclose(f);
    }
}
TEST(MazeTest, GetColsRectangular) {
    char maze[MAX_SIZE][MAX_SIZE] = {
        "S.#",
        "..#",
        ".#E"
    };

    int cols = getCols(maze, 3);

    EXPECT_EQ(cols, 3);
}


TEST(MazeTest, GetColsJagged) {
    char maze[MAX_SIZE][MAX_SIZE] = {
        "S.#",
        "..",
        ".#E."
    };

    int cols = getCols(maze, 3);

    EXPECT_EQ(cols, 4);
}


TEST(MazeTest, SimplePathNoWalls) 
{
    char maze[MAX_SIZE][MAX_SIZE] ={"S...E"};
    bool visited[MAX_SIZE][MAX_SIZE] = { false };
    Point path[MAX_SIZE * MAX_SIZE];
    int pathLength = 0;
    bool result = findPathDFS(maze, 0, 0, 0, 4, 1, 5, visited, path, &pathLength);
    EXPECT_TRUE(result);
    EXPECT_GT(pathLength, 0);
    EXPECT_EQ(path[0].x, 0);
    EXPECT_EQ(path[0].y, 0);
    EXPECT_EQ(path[pathLength - 1].x, 0);
    EXPECT_EQ(path[pathLength - 1].y, 4);
}
TEST(MazeTest, NoPathDueToWalls)
{
    char maze[MAX_SIZE][MAX_SIZE] = {
        "S#E"
    };
    bool visited[MAX_SIZE][MAX_SIZE] = { false };
    Point path[MAX_SIZE * MAX_SIZE];
    int pathLength = 0;

    bool result = findPathDFS(maze, 0, 0, 0, 2, 1, 3, visited, path, &pathLength);

    EXPECT_FALSE(result);
}


TEST(MazeTest, StartEqualsEnd) {
    char maze[MAX_SIZE][MAX_SIZE] = {
        "S"
    };
    bool visited[MAX_SIZE][MAX_SIZE] = { false };
    Point path[MAX_SIZE * MAX_SIZE];
    int pathLength = 0;

    bool result = findPathDFS(maze, 0, 0, 0, 0, 1, 1, visited, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_EQ(pathLength, 1);
}


TEST(MazeTest, OutOfBoundsCoordinates) {
    char maze[MAX_SIZE][MAX_SIZE] = {
        "S.E"
    };
    bool visited[MAX_SIZE][MAX_SIZE] = { false };
    Point path[MAX_SIZE * MAX_SIZE];
    int pathLength = 0;

    bool result = findPathDFS(maze, -1, 0, 0, 2, 1, 3, visited, path, &pathLength);

    EXPECT_FALSE(result);
}


TEST(MazeTest, ComplexMazeWithPath) {
    char maze[MAX_SIZE][MAX_SIZE] = {
        "S.#...",
        "....#.",
        ".#.#..",
        ".#..#.",
        "....#E"
    };
    bool visited[MAX_SIZE][MAX_SIZE] = { false };
    Point path[MAX_SIZE * MAX_SIZE];
    int pathLength = 0;

    bool result = findPathDFS(maze, 0, 0, 4, 5, 5, 6, visited, path, &pathLength);

    EXPECT_TRUE(result);
}


TEST(MazeTest, PathThroughVisitedCells) {
    char maze[MAX_SIZE][MAX_SIZE] = {
        "S.E"
    };
    bool visited[MAX_SIZE][MAX_SIZE] = { false };
    visited[0][1] = true;
    Point path[MAX_SIZE * MAX_SIZE];
    int pathLength = 0;

    bool result = findPathDFS(maze, 0, 0, 0, 2, 1, 3, visited, path, &pathLength);

    EXPECT_FALSE(result);
}

TEST(MazeTest, SinglePossiblePath) {
    char maze[MAX_SIZE][MAX_SIZE] = {
        "S###",
        "..##",
        "#..#",
        "##E#"
    };

    bool visited[MAX_SIZE][MAX_SIZE] = { false };
    Point path[MAX_SIZE * MAX_SIZE];
    int pathLength = 0;

    bool result = findPathDFS(maze, 0, 0, 3, 2, 4, 4, visited, path, &pathLength);

    EXPECT_TRUE(result);
    EXPECT_GT(pathLength, 0);

    // Проверяем что путь начинается и заканчивается в правильных точках
    EXPECT_EQ(path[0].x, 0);
    EXPECT_EQ(path[0].y, 0);
    EXPECT_EQ(path[pathLength - 1].x, 3);
    EXPECT_EQ(path[pathLength - 1].y, 2);

    printf("Найден путь длиной %d:\n", pathLength);
    for (int i = 0; i < pathLength;
        i++) {
        printf("(%d,%d) ", path[i].x, path[i].y);
    }
    printf("\n");
}


TEST(MazeTest, MazeWithDeadEnds) {
    char maze[MAX_SIZE][MAX_SIZE] = {
        "S.#...",
        ".#.#..",
        ".#....",
        ".#.#..",
        "....#E"
    };
    bool visited[MAX_SIZE][MAX_SIZE] = { false };
    Point path[MAX_SIZE * MAX_SIZE];
    int pathLength = 0;

    bool result = findPathDFS(maze, 0, 0, 4, 5, 5, 6, visited, path, &pathLength);


    EXPECT_TRUE(result);
}

int main(int argc, char** argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}