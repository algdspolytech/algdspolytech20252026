#include <gtest/gtest.h>
extern "C" {
#include "longest_path.h"
}

static void build(int **&adj, int *&deg, int v) {
    adj = (int**)malloc(v * sizeof(int*));
    deg = (int*)calloc(v, sizeof(int));
    for (int i = 0; i < v; i++)
        adj[i] = (int*)malloc(v * sizeof(int));
}

TEST(LongestPath, Triangle_K2_no1) {
    int **adj, *deg;
    build(adj, deg, 3);
    adj[0][deg[0]++] = 1; adj[0][deg[0]++] = 2;
    adj[1][deg[1]++] = 0; adj[1][deg[1]++] = 2;
    adj[2][deg[2]++] = 0; adj[2][deg[2]++] = 1;

    int res[10], len = 0;
    ASSERT_TRUE(find_path(3, adj, deg, 0, 2, 2, res, &len));
}

TEST(LongestPath, NoPath_no2) {
    int **adj, *deg;
    build(adj, deg, 2);
    int res[10], len = 0;
    ASSERT_FALSE(find_path(2, adj, deg, 0, 1, 1, res, &len));
}

TEST(LongestPath, LineGraph_no3) {
    int **adj, *deg;
    build(adj, deg, 4);
    adj[0][deg[0]++] = 1;
    adj[1][deg[1]++] = 0; adj[1][deg[1]++] = 2;
    adj[2][deg[2]++] = 1; adj[2][deg[2]++] = 3;
    adj[3][deg[3]++] = 2;

    int res[10], len = 0;
    ASSERT_TRUE(find_path(4, adj, deg, 0, 3, 3, res, &len));
}

TEST(LongestPath, KTooLarge_no4) {
    int **adj, *deg;
    build(adj, deg, 3);
    adj[0][deg[0]++] = 1;
    adj[1][deg[1]++] = 0; adj[1][deg[1]++] = 2;
    adj[2][deg[2]++] = 1;

    int res[10], len = 0;
    ASSERT_FALSE(find_path(3, adj, deg, 0, 2, 5, res, &len));
}

TEST(LongestPath, StartEqualsEnd_no5) {
    int **adj, *deg;
    build(adj, deg, 1);
    int res[10], len = 0;
    ASSERT_TRUE(find_path(1, adj, deg, 0, 0, 0, res, &len));
}

TEST(LongestPath, SquareGraph_no6) {
    int **adj, *deg;
    build(adj, deg, 4);
    adj[0][deg[0]++] = 1; adj[0][deg[0]++] = 3;
    adj[1][deg[1]++] = 0; adj[1][deg[1]++] = 2;
    adj[2][deg[2]++] = 1; adj[2][deg[2]++] = 3;
    adj[3][deg[3]++] = 0; adj[3][deg[3]++] = 2;

    int res[10], len = 0;
    ASSERT_TRUE(find_path(4, adj, deg, 0, 2, 2, res, &len));
}

TEST(LongestPath, Disconnected_no7) {
    int **adj, *deg;
    build(adj, deg, 3);
    adj[0][deg[0]++] = 1;
    adj[1][deg[1]++] = 0;

    int res[10], len = 0;
    ASSERT_FALSE(find_path(3, adj, deg, 0, 2, 1, res, &len));
}

TEST(LongestPath, KZero_no8) {
    int **adj, *deg;
    build(adj, deg, 2);
    int res[10], len = 0;
    ASSERT_TRUE(find_path(2, adj, deg, 0, 0, 0, res, &len));
}

TEST(LongestPath, BranchGraph_no9) {
    int **adj, *deg;
    build(adj, deg, 5);
    adj[0][deg[0]++] = 1; adj[1][deg[1]++] = 0;
    adj[1][deg[1]++] = 2; adj[2][deg[2]++] = 1;
    adj[1][deg[1]++] = 3; adj[3][deg[3]++] = 1;
    adj[3][deg[3]++] = 4; adj[4][deg[4]++] = 3;

    int res[10], len = 0;
    ASSERT_TRUE(find_path(5, adj, deg, 0, 4, 3, res, &len));
}

TEST(LongestPath, SingleEdge_no10) {
    int **adj, *deg;
    build(adj, deg, 2);
    adj[0][deg[0]++] = 1;
    adj[1][deg[1]++] = 0;

    int res[10], len = 0;
    ASSERT_TRUE(find_path(2, adj, deg, 0, 1, 1, res, &len));
}
