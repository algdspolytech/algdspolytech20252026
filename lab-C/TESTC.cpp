#include "pch.h"
#include <gtest/gtest.h>
extern "C" {
#include "Ch.h"
}

TEST(Queue_Test, Createqueue_queue_returnvoid) {
    queue q;
    Createqueue(&q);
    EXPECT_EQ(q.head, -1);
    EXPECT_EQ(q.back, -1);
}

TEST(Queue_Test, isqueueempty_emptyqueue_returntrue) {
    queue q;
    Createqueue(&q);
    EXPECT_EQ(isqueueempty(&q), 1);
}

TEST(Queue_Test, isqueueempty_nonemptyqueue_returnfalse) {
    queue q;
    Createqueue(&q);
    point p = { 1, 2 };
    Addinqueue(&q, p);
    EXPECT_EQ(isqueueempty(&q), 0);
}

TEST(Queue_Test, Addinqueue_queue_returnvoid) {
    queue q;
    Createqueue(&q);
    point p = { 3, 4 };
    Addinqueue(&q, p);
    EXPECT_EQ(q.head, 0);
    EXPECT_EQ(q.back, 0);
    EXPECT_EQ(q.info[0].x, 3);
    EXPECT_EQ(q.info[0].y, 4);
}

TEST(Queue_Test, Addinqueue_multipleelements_returnvoid) {
    queue q;
    Createqueue(&q);
    point p1 = { 1, 1 };
    point p2 = { 2, 2 };
    Addinqueue(&q, p1);
    Addinqueue(&q, p2);
    EXPECT_EQ(q.head, 0);
    EXPECT_EQ(q.back, 1);
    EXPECT_EQ(q.info[0].x, 1);
    EXPECT_EQ(q.info[0].y, 1);
    EXPECT_EQ(q.info[1].x, 2);
    EXPECT_EQ(q.info[1].y, 2);
}

TEST(Queue_Test, Removefromqueue_emptyqueue_returnerrorpoint) {
    queue q;
    Createqueue(&q);
    point result = Removefromqueue(&q);
    EXPECT_EQ(result.x, -1);
    EXPECT_EQ(result.y, -1);
}

TEST(Queue_Test, Removefromqueue_nonemptyqueue_returncorrectpoints) {
    queue q;
    Createqueue(&q);
    point p1 = { 1, 2 };
    point p2 = { 3, 4 };
    point p3 = { 5, 6 };
    Addinqueue(&q, p1);
    Addinqueue(&q, p2);
    Addinqueue(&q, p3);
    point result1 = Removefromqueue(&q);
    EXPECT_EQ(result1.x, 1);
    EXPECT_EQ(result1.y, 2);
    point result2 = Removefromqueue(&q);
    EXPECT_EQ(result2.x, 3);
    EXPECT_EQ(result2.y, 4);
    point result3 = Removefromqueue(&q);
    EXPECT_EQ(result3.x, 5);
    EXPECT_EQ(result3.y, 6);
    EXPECT_EQ(isqueueempty(&q), 1);
}

TEST(SheetSeparation_Test, SheetSeparation_EmptySheet_returnZero) {
    int matrix[MAX][MAX] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    EXPECT_EQ(SheetSeparation(3, 3, matrix), 0);
}

TEST(SheetSeparation_Test, SheetSeparation_FullSheet_returnOne) {
    int matrix[MAX][MAX] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    EXPECT_EQ(SheetSeparation(3, 3, matrix), 1);
}

TEST(SheetSeparation_Test, SheetSeparation_IsolatedCells_returnFour) {
    int matrix[MAX][MAX] = {
        {1, 0, 1},
        {0, 0, 0},
        {1, 0, 1}
    };
    EXPECT_EQ(SheetSeparation(3, 3, matrix), 4);
}

TEST(SheetSeparation_Test, SheetSeparation_TwoDiagonalComponents_returnTwo) {
    int matrix[MAX][MAX] = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    EXPECT_EQ(SheetSeparation(3, 3, matrix), 2);
}

TEST(SheetSeparation_Test, SheetSeparation_Zigzag_returnTwo) {
    int matrix[MAX][MAX] = {
        {1, 1, 0},
        {0, 1, 1},
        {1, 0, 1}
    };
    EXPECT_EQ(SheetSeparation(3, 3, matrix), 2);
}

TEST(SheetSeparation_Test, SheetSeparation_SingleCell_returnOne) {
    int matrix[MAX][MAX] = {
        {1}
    };
    EXPECT_EQ(SheetSeparation(1, 1, matrix), 1);
}

TEST(SheetSeparation_Test, SheetSeparation_Chess_returnMultiple) {
    int matrix[MAX][MAX] = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    EXPECT_EQ(SheetSeparation(3, 4, matrix), 6);
}

TEST(SheetSeparation_Test, SheetSeparation_LinePattern_returnOne) {
    int matrix[MAX][MAX] = {
        {1, 1, 1, 1}
    };
    EXPECT_EQ(SheetSeparation(1, 4, matrix), 1);
}

TEST(SheetSeparation_Test, SheetSeparation_OneCenterCell_returnOne) {
    int matrix[MAX][MAX] = {
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
    };
    EXPECT_EQ(SheetSeparation(3, 3, matrix), 1);
}

TEST(SheetSeparation_Test, SheetSeparation_BorderCellsOnly_returnTwo) {
    int matrix[MAX][MAX] = { 0 };
    for (int i = 0; i < 5; i++) {
        matrix[i][0] = 1;
        matrix[i][4] = 1;
        matrix[0][i] = 1;
        matrix[4][i] = 1;
    }
    EXPECT_EQ(SheetSeparation(5, 5, matrix), 1);
}
