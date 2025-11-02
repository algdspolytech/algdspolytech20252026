#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
extern "C" {
#include "adj.h"
}

TEST(VecTest, InitPushFree) {
    Vec v;
    init_vec(&v);
    EXPECT_EQ(v.size, 0);
    vec_push(&v, 7);
    vec_push(&v, 42);
    ASSERT_EQ(v.size, 2);
    EXPECT_EQ(v.data[0], 7);
    EXPECT_EQ(v.data[1], 42);
    vec_free(&v);
    EXPECT_EQ(v.size, 0);
    EXPECT_EQ(v.data, nullptr);
}

TEST(GraphTest, AddAdjToGraph) {
    Graph g;
    init_graph(&g);
    add_adj_to_graph(&g, 3);
    ASSERT_EQ(g.size, 3);
    for (int i = 0; i < g.size; ++i) {
        EXPECT_EQ(g.adj[i].size, 0);
        EXPECT_EQ(g.adj[i].data, nullptr);
    }
    graph_free(&g);
}

TEST(GraphTest, ReadAdjListFile) {
    Graph g;
    init_graph(&g);
    ASSERT_TRUE(read_adjlist_file("adjlist.txt", &g));
    ASSERT_EQ(g.size, 4);
    ASSERT_GE(g.adj[0].size, 2);
    bool has1 = false, has2 = false;
    for (int k = 0; k < g.adj[0].size; ++k) {
        if (g.adj[0].data[k] == 1) has1 = true;
        if (g.adj[0].data[k] == 2) has2 = true;
    }
    EXPECT_TRUE(has1 && has2);
    graph_free(&g);
}


TEST(AdjMatrixTest, ReadAdjMatrixFile) {
    Graph g;
    init_graph(&g);
    ASSERT_TRUE(read_adjmatrix_file("adjmatrix.txt", &g));
    ASSERT_EQ(g.size, 4);
    bool has1 = false, has2 = false;
    for (int k = 0; k < g.adj[0].size; ++k) {
        if (g.adj[0].data[k] == 1) has1 = true;
        if (g.adj[0].data[k] == 2) has2 = true;
    }
    EXPECT_TRUE(has1 && has2);
    graph_free(&g);
}

TEST(EqualTest, ListVsMatrixEqual) {
    Graph a, b;
    init_graph(&a);
    init_graph(&b);
    ASSERT_TRUE(read_adjlist_file("adjlist.txt", &a));
    ASSERT_TRUE(read_adjmatrix_file("adjmatrix.txt", &b));
    EXPECT_TRUE(graphs_equal(&a, &b));
    graph_free(&a);
    graph_free(&b);
}

TEST(EqualTest, ListVsMatrixNotEqual) {
    Graph a, b;
    init_graph(&a);
    init_graph(&b);
    ASSERT_TRUE(read_adjlist_file("adjlist.txt", &a));
    ASSERT_TRUE(read_adjmatrix_file("adjmatrix_not_equal.txt", &b));
    EXPECT_FALSE(graphs_equal(&a, &b));
    graph_free(&a);
    graph_free(&b);
}

TEST(FileTest, ReadMissingListFile) {
    Graph g;
    init_graph(&g);
    EXPECT_FALSE(read_adjlist_file("labawaba.txt", &g));
    graph_free(&g);
}

TEST(MatrixTest, ReadMalformedMatrixFile) {
    Graph g;
    init_graph(&g);
    EXPECT_FALSE(read_adjmatrix_file("bad_matrix.txt", &g));
    graph_free(&g);
}

TEST(EqualTest, SelfLoopEqual) {
    Graph a, b;
    init_graph(&a);
    init_graph(&b);
    ASSERT_TRUE(read_adjmatrix_file("badmatrix2.txt", &a));
    ASSERT_TRUE(read_adjlist_file("badloop.txt", &b));
    EXPECT_TRUE(graphs_equal(&a, &b));
    graph_free(&a);
    graph_free(&b);
}