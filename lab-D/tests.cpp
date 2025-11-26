#include <gtest/gtest.h>
#include "graph_coloring.h"




// Вспомогательная проверка раскраски корректности
static bool check_coloring(Graph* g, int K, int *colors, int expect_ok) {
    if (!expect_ok) return true;
    for (int v = 0; v < g->V; ++v) {
        if (colors[v] < 1 || colors[v] > K) return false;
        for (int i = 0; i < g->deg[v]; ++i) {
            int nb = g->adj[v][i];
            if (colors[nb] == colors[v]) return false;
        }
    }
    return true;
}

// 1. Минимальный граф (одна вершина)
TEST(GraphColoringTest, SingleVertex_K1_no1) {
    Graph* g = graph_create(1);
    int colors[1];
    int res = graph_color(g, 1, colors);
    EXPECT_EQ(res, 1);
    EXPECT_TRUE(check_coloring(g, 1, colors, res));
    graph_free(g);
}

// 2. Два связанных вершины, K=1 -> нельзя 
TEST(GraphColoringTest, TwoVertices_Edge_K1_no2) {
    Graph* g = graph_create(2);
    graph_add_edge(g, 0, 1);
    int colors[2];
    int res = graph_color(g, 1, colors);
    EXPECT_EQ(res, 0);
    graph_free(g);
}

// 3. Два связанных вершины, K=2 -> можно 
TEST(GraphColoringTest, TwoVertices_Edge_K2_no3) {
    Graph* g = graph_create(2);
    graph_add_edge(g, 0, 1);
    int colors[2];
    int res = graph_color(g, 2, colors);
    EXPECT_EQ(res, 1);
    EXPECT_TRUE(check_coloring(g, 2, colors, res));
    graph_free(g);
}

// 4. Треугольник (K=2 impossible, K=3 possible) 
TEST(GraphColoringTest, Triangle_K2_no4) {
    Graph* g = graph_create(3);
    graph_add_edge(g,0,1); graph_add_edge(g,1,2); graph_add_edge(g,2,0);
    int colors[3];
    int res = graph_color(g, 2, colors);
    EXPECT_EQ(res, 0);
    graph_free(g);
}
TEST(GraphColoringTest, Triangle_K3_no5) {
    Graph* g = graph_create(3);
    graph_add_edge(g,0,1); graph_add_edge(g,1,2); graph_add_edge(g,2,0);
    int colors[3];
    int res = graph_color(g, 3, colors);
    EXPECT_EQ(res, 1);
    EXPECT_TRUE(check_coloring(g, 3, colors, res));
    graph_free(g);
}

// 5. Пустой граф (никаких рёбер): любой K>=1 подходит
TEST(GraphColoringTest, EmptyGraph_K1_no6) {
    Graph* g = graph_create(5);
    int colors[5];
    int res = graph_color(g, 1, colors);
    EXPECT_EQ(res, 1);
    EXPECT_TRUE(check_coloring(g, 1, colors, res));
    graph_free(g);
}

// 6. Двудольный (цепочка длины 5) — K=2 должно быть возможно 
TEST(GraphColoringTest, Path5_K2_no7) {
    Graph* g = graph_create(5);
    for (int i = 0; i+1 < 5; ++i) graph_add_edge(g, i, i+1);
    int colors[5];
    int res = graph_color(g, 2, colors);
    EXPECT_EQ(res, 1);
    EXPECT_TRUE(check_coloring(g, 2, colors, res));
    graph_free(g);
}

// 7. Полный граф K_n: n вершин, K = n-1 -> невозможно, K = n -> возможно
TEST(GraphColoringTest, CompleteGraph_KnMinus1_no8) {
    const int n = 4;
    Graph* g = graph_create(n);
    for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) graph_add_edge(g,i,j);
    int colors[n];
    int res = graph_color(g, n-1, colors);
    EXPECT_EQ(res, 0);
    graph_free(g);
}
TEST(GraphColoringTest, CompleteGraph_Kn_no9) {
    const int n = 4;
    Graph* g = graph_create(n);
    for (int i = 0; i < n; ++i) for (int j = i+1; j < n; ++j) graph_add_edge(g,i,j);
    int colors[n];
    int res = graph_color(g, n, colors);
    EXPECT_EQ(res, 1);
    EXPECT_TRUE(check_coloring(g, n, colors, res));
    graph_free(g);
}

// 8. Несвязный граф: одна компонента раскрашиваемая, другая нет 
TEST(GraphColoringTest, DisconnectedComponents_no10) {
    /* компонент A: треугольник (нужны 3 цвета)
       компонент B: одно ребро (нужны 2 цвета)
       всего вершин 5. K=2 -> общая раскраска невозможна. K=3 -> возможно. */
    Graph* g = graph_create(5);
    /* треугольник 0-1-2 */
    graph_add_edge(g,0,1); graph_add_edge(g,1,2); graph_add_edge(g,2,0);
    /* ребро 3-4 */
    graph_add_edge(g,3,4);
    int colors[5];
    int res2 = graph_color(g, 2, colors);
    EXPECT_EQ(res2, 0);
    int res3 = graph_color(g, 3, colors);
    EXPECT_EQ(res3, 1);
    EXPECT_TRUE(check_coloring(g, 3, colors, res3));
    graph_free(g);
}

// 9. Алгоритмический кейс: граф с высокими степенями, K small 
TEST(GraphColoringTest, StarGraph_K2_no11) {
    /* звезда из 6 вершин (центр 0) -> двуцветна */
    Graph* g = graph_create(6);
    for (int i = 1; i < 6; ++i) graph_add_edge(g, 0, i);
    int colors[6];
    int res = graph_color(g, 2, colors);
    EXPECT_EQ(res, 1);
    EXPECT_TRUE(check_coloring(g, 2, colors, res));
    graph_free(g);
}

// 10. Ещё один кейс: цикл нечетной длины (5) K=2 -> невозможно 
TEST(GraphColoringTest, OddCycle5_K2_no12) {
    Graph* g = graph_create(5);
    for (int i = 0; i < 5; ++i) graph_add_edge(g, i, (i+1)%5);
    int colors[5];
    int res = graph_color(g, 2, colors);
    EXPECT_EQ(res, 0);
    graph_free(g);
}
