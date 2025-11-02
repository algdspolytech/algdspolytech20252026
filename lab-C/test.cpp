#include <gtest/gtest.h>
#include "header.h"
#include <stdio.h>
#include <string.h>

class MazeSolverTest : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                testMaze[i][j] = 0;
            }
        }
    }

    int testMaze[x][y];
    char path[x][y];
};

// Тест 1: Нахождение старта и финиша
TEST_F(MazeSolverTest, FindStartAndEnd) {
    testMaze[0][0] = -1;
    testMaze[9][9] = -2;

    int sx, sy, ex, ey;
    FindStart(testMaze, &sx, &sy, &ex, &ey);

    EXPECT_EQ(sx, 0);
    EXPECT_EQ(sy, 0);
    EXPECT_EQ(ex, 9);
    EXPECT_EQ(ey, 9);
}

// Тест 2: Лабиринт без старта
TEST_F(MazeSolverTest, NoStartPoint) {
    testMaze[9][9] = -2;

    int sx = -1, sy = -1, ex = -1, ey = -1;
    FindStart(testMaze, &sx, &sy, &ex, &ey);

    EXPECT_EQ(sx, -1);
    EXPECT_EQ(ex, 9);
}

// Тест 3: Лабиринт без финиша
TEST_F(MazeSolverTest, NoEndPoint) {
    testMaze[0][0] = -1;

    int sx, sy, ex, ey;
    FindStart(testMaze, &sx, &sy, &ex, &ey);

    EXPECT_EQ(sx, 0);
    EXPECT_EQ(sy, 0);
    EXPECT_EQ(ex, -1);
}

// Тест 4: Инициализация массива
TEST_F(MazeSolverTest, ArrayInitialization) {
    FullArr(path, 'X');

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            EXPECT_EQ(path[i][j], 'X');
        }
    }
}

// Тест 5: Восстановление пути
TEST_F(MazeSolverTest, PathRestoration) {
    int solvedMaze[x][y] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 11},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 12},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 13},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 14},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 15},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 16},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 17},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 18},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 19}
    };

    FullArr(path, '#');
    path[9][9] = '1';
    Way(solvedMaze, 9, 9, 19, path);

    EXPECT_EQ(path[0][0], '1');
}

// Тест 6: Старт и финиш рядом друг с другом
TEST_F(MazeSolverTest, StartAndEndAdjacent) {
    int adjacentMaze[x][y] = { 0 };
    adjacentMaze[0][0] = -1;
    adjacentMaze[0][1] = -2;

    int sx, sy, ex, ey;
    FindStart(adjacentMaze, &sx, &sy, &ex, &ey);

    adjacentMaze[sx][sy] = 1;
    FindWay(adjacentMaze, sx, sy);

    // Финиш должен быть достижим
    EXPECT_NE(adjacentMaze[ex][ey], -2);
    EXPECT_GT(adjacentMaze[ex][ey], 0);
}

// Тест 7: Лабиринт с непроходимыми стенами
TEST_F(MazeSolverTest, ImpossibleMaze) {
    int impossibleMaze[x][y] = {
        {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, -2}
    };

    int sx, sy, ex, ey;
    FindStart(impossibleMaze, &sx, &sy, &ex, &ey);

    impossibleMaze[sx][sy] = 1;
    FindWay(impossibleMaze, sx, sy);

    // Финиш должен остаться недостижимым
    EXPECT_EQ(impossibleMaze[ex][ey], -2);
}

// Тест 8: Лабиринт с единственным путем
TEST_F(MazeSolverTest, SinglePathMaze) {
    int singlePathMaze[x][y] = {
        {-1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, -2}
    };

    int sx, sy, ex, ey;
    FindStart(singlePathMaze, &sx, &sy, &ex, &ey);

    int workMaze[x][y];
    memcpy(workMaze, singlePathMaze, sizeof(singlePathMaze));

    workMaze[sx][sy] = 1;
    FindWay(workMaze, sx, sy);

    EXPECT_NE(workMaze[ex][ey], -2);
    EXPECT_GT(workMaze[ex][ey], 0);
}

// Тест 9: Комплексный лабиринт (оригинальный из кода)
TEST_F(MazeSolverTest, ComplexMaze) {
    int complexMaze[x][y] = {
        {-1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, -2}
    };

    int sx, sy, ex, ey;
    FindStart(complexMaze, &sx, &sy, &ex, &ey);

    EXPECT_EQ(sx, 0);
    EXPECT_EQ(sy, 0);
    EXPECT_EQ(ex, 9);
    EXPECT_EQ(ey, 9);

    int workMaze[x][y];
    memcpy(workMaze, complexMaze, sizeof(complexMaze));

    workMaze[sx][sy] = 1;
    FindWay(workMaze, sx, sy);

    // Проверяем, что путь найден
    EXPECT_NE(workMaze[ex][ey], -2);
    EXPECT_GT(workMaze[ex][ey], 0);
}

// Тест 10: Старт и финиш в одном месте
TEST_F(MazeSolverTest, StartAndEndSamePosition) {
    testMaze[5][5] = -1;
    testMaze[5][5] = -2; // Перезаписываем старт финишем

    int sx, sy, ex, ey;
    FindStart(testMaze, &sx, &sy, &ex, &ey);

    EXPECT_EQ(ex, 5);
    EXPECT_EQ(ey, 5);
}

#ifdef RUN_TESTS
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif