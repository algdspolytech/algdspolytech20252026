#include <gtest/gtest.h>

#pragma warning(disable: 4996)

#define _CRT_SECURE_NO_WARNINGS

extern "C" {
#include "Header.h"
}

TEST(Graph_Test, Createqueue_queue_returnvoid) {
    queue q;
    Createqueue(&q);
    EXPECT_EQ(q.head, -1);
    EXPECT_EQ(q.back, -1);
}

TEST(Graph_Test, isqueueempty_queue_returnbool) {
    queue q;
    Createqueue(&q);
    EXPECT_EQ(isqueueempty(&q), 1);
    Addinqueue(&q, 5);
    EXPECT_EQ(isqueueempty(&q), 0);
}

TEST(Graph_Test, Addinqueue_queueint_returnvoid) {
    queue q;
    Createqueue(&q);
    Addinqueue(&q, 10);
    EXPECT_EQ(q.head, 0);
    EXPECT_EQ(q.back, 0);
    EXPECT_EQ(q.vertices[0], 10);
    Addinqueue(&q, 20);
    EXPECT_EQ(q.head, 0);
    EXPECT_EQ(q.back, 1);
    EXPECT_EQ(q.vertices[1], 20);
}

TEST(Graph_Test, Removefromqueue_queue_returnint) {
    queue q;
    Createqueue(&q);
    EXPECT_EQ(Removefromqueue(&q), -1);
    Addinqueue(&q, 10);
    Addinqueue(&q, 20);
    Addinqueue(&q, 30);
    EXPECT_EQ(Removefromqueue(&q), 10);
    EXPECT_EQ(Removefromqueue(&q), 20);
    EXPECT_EQ(Removefromqueue(&q), 30);
    EXPECT_EQ(isqueueempty(&q), 1);
}

TEST(Graph_Test, Createstack_stack_returnvoid) {
    stack s;
    Createstack(&s);
    EXPECT_EQ(s.top, -1);
}

TEST(Graph_Test, isstackempty_stack_returnbool) {
    stack s;
    Createstack(&s);
    EXPECT_EQ(isstackempty(&s), 1);
    Addinstack(&s, 5);
    EXPECT_EQ(isstackempty(&s), 0);
}

TEST(Graph_Test, Addinstack_stackint_returnvoid) {
    stack s;
    Createstack(&s);
    Addinstack(&s, 10);
    EXPECT_EQ(s.top, 0);
    EXPECT_EQ(s.vertices[0], 10);
    Addinstack(&s, 20);
    EXPECT_EQ(s.top, 1);
    EXPECT_EQ(s.vertices[1], 20);
}

TEST(Graph_Test, Removefromstack_stack_returnint) {
    stack s;
    Createstack(&s);
    EXPECT_EQ(Removefromstack(&s), -1);
    Addinstack(&s, 10);
    Addinstack(&s, 20);
    Addinstack(&s, 30);
    EXPECT_EQ(Removefromstack(&s), 30);
    EXPECT_EQ(Removefromstack(&s), 20);
    EXPECT_EQ(Removefromstack(&s), 10);
    EXPECT_EQ(isstackempty(&s), 1);
}

TEST(Graph_Test, pathfinder_ValidPath_ShouldFindPath) {
    int matrix[MAX][MAX];
    int n = 4;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    matrix[1][2] = 1;
    matrix[2][1] = 1;
    matrix[2][3] = 1;
    matrix[3][2] = 1;
    PathResult result;
    pathfinder(matrix, n, 0, 3, &result);
    EXPECT_EQ(result.found, 1);
    EXPECT_EQ(result.length, 4);
    EXPECT_EQ(result.path[0], 0);
    EXPECT_EQ(result.path[1], 1);
    EXPECT_EQ(result.path[2], 2);
    EXPECT_EQ(result.path[3], 3);
}

TEST(Graph_Test, pathfinder_NoPath_ShouldReturnNotFound) {
    int matrix[MAX][MAX];
    int n = 3;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    PathResult result;
    pathfinder(matrix, n, 0, 2, &result);
    EXPECT_EQ(result.found, 0);
    EXPECT_EQ(result.length, 0);
}

TEST(Graph_Test, pathfinder_SameVertex_ShouldFindPathLengthZero) {
    int matrix[MAX][MAX];
    int n = 3;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    matrix[1][2] = 1;
    matrix[2][1] = 1;
    PathResult result;
    pathfinder(matrix, n, 1, 1, &result);
    EXPECT_EQ(result.found, 1);
    EXPECT_EQ(result.length, 1);
    EXPECT_EQ(result.path[0], 1);
}

TEST(Graph_Test, pathfinder_MultiplePaths_ShouldFindShortest) {
    int matrix[MAX][MAX];
    int n = 5;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    matrix[0][1] = 1;
    matrix[1][0] = 1;
    matrix[1][2] = 1;
    matrix[2][1] = 1;
    matrix[2][4] = 1;
    matrix[4][2] = 1;
    matrix[0][3] = 1;
    matrix[3][0] = 1;
    matrix[3][4] = 1;
    matrix[4][3] = 1;
    PathResult result;
    pathfinder(matrix, n, 0, 4, &result);
    EXPECT_EQ(result.found, 1);
    EXPECT_EQ(result.length, 3);
    EXPECT_EQ(result.path[0], 0);
    EXPECT_EQ(result.path[1], 3);
    EXPECT_EQ(result.path[2], 4);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}