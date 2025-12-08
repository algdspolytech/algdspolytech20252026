#include "pch.h"

extern "C" {
#include "Header.h"
}
    // Вспомогательная функция для создания графа
    void SetupGraph1(Graf* G) {
        // Граф: 0 - 1 - 2 - 3 (линейный)
        Create_Graf(G, 4);
        Add_Edge(G, 0, 1);
        Add_Edge(G, 1, 2);
        Add_Edge(G, 2, 3);
    }

    void SetupGraph2(Graf* G) {
        // Разветвленный граф:
        // 0
        // |\
        // 1 2
        //     \
        //      3
        Create_Graf(G, 4);
        Add_Edge(G, 0, 1);
        Add_Edge(G, 0, 2);
        Add_Edge(G, 2, 3);
    }

    void SetupGraph3(Graf* G) {
        // Разобщенные компоненты:
        // 0 - 1   2 - 3
        Create_Graf(G, 4);
        Add_Edge(G, 0, 1);
        Add_Edge(G, 2, 3);
    }

    void SetupGraph4(Graf* G) {
        // Цикл 0-1-2-0
        Create_Graf(G, 3);
        Add_Edge(G, 0, 1);
        Add_Edge(G, 1, 2);
        Add_Edge(G, 2, 0);
    }

    void SetupGraph5(Graf* G) {
        // Один узел без связей
        Create_Graf(G, 1);
    }

    void SetupGraph6(Graf* G) {
        // Полностью связанный граф (круг)
        Create_Graf(G, 4);
        Add_Edge(G, 0, 1);
        Add_Edge(G, 0, 2);
        Add_Edge(G, 0, 3);
        Add_Edge(G, 1, 2);
        Add_Edge(G, 1, 3);
        Add_Edge(G, 2, 3);
    }

    void SetupGraph7(Graf* G) {
        // Граф из 5 вершин с разными связями
        Create_Graf(G, 5);
        Add_Edge(G, 0, 1);
        Add_Edge(G, 1, 2);
        Add_Edge(G, 3, 4);
    }

    void SetupGraph8(Graf* G) {
        // Линейный граф из 5 вершин
        Create_Graf(G, 5);
        Add_Edge(G, 0, 1);
        Add_Edge(G, 1, 2);
        Add_Edge(G, 2, 3);
        Add_Edge(G, 3, 4);
    }

    void SetupGraph9(Graf* G) {
        // Граф с петлей
        Create_Graf(G, 3);
        Add_Edge(G, 0, 1);
        Add_Edge(G, 1, 2);
        Add_Edge(G, 2, 0);
    }

    void SetupGraph10(Graf* G) {
        // Разобщенные вершины без связей
        Create_Graf(G, 3);
        // Нет добавленных рёбер
    }

    // Тесты

    TEST(IsWay, PathExistsLinear) {
        Graf G;
        SetupGraph1(&G);
        EXPECT_TRUE(IsWay(&G, 0, 3));
        FreeGraf(&G);
    }

    TEST(IsWay, PathExistsBranching) {
        Graf G;
        SetupGraph2(&G);
        EXPECT_TRUE(IsWay(&G, 0, 3));
        EXPECT_TRUE(IsWay(&G, 0, 1));
        FreeGraf(&G);
    }

    TEST(IsWay, NoPathDifferentComponents) {
        Graf G;
        SetupGraph3(&G);
        EXPECT_FALSE(IsWay(&G, 0, 3));
        EXPECT_FALSE(IsWay(&G, 2, 1));
        FreeGraf(&G);
    }

    TEST(IsWay, CyclePath) {
        Graf G;
        SetupGraph4(&G);
        EXPECT_TRUE(IsWay(&G, 0, 2));
        EXPECT_TRUE(IsWay(&G, 2, 0));
        FreeGraf(&G);
    }

    TEST(IsWay, SingleNodeNoEdges) {
        Graf G;
        SetupGraph5(&G);
        EXPECT_TRUE(IsWay(&G, 0, 0));
        EXPECT_FALSE(IsWay(&G, 0, 1));
        FreeGraf(&G);
    }

    TEST(IsWay, CompleteGraph) {
        Graf G;
        SetupGraph6(&G);
        EXPECT_TRUE(IsWay(&G, 0, 3));
        EXPECT_TRUE(IsWay(&G, 1, 2));
        FreeGraf(&G);
    }

    TEST(IsWay, DisconnectedSubgraphs) {
        Graf G;
        SetupGraph7(&G);
        EXPECT_TRUE(IsWay(&G, 0, 2));
        EXPECT_FALSE(IsWay(&G, 0, 4));
        FreeGraf(&G);
    }

    TEST(IsWay, LinearChain) {
        Graf G;
        SetupGraph8(&G);
        EXPECT_TRUE(IsWay(&G, 0, 4));
        EXPECT_FALSE(IsWay(&G, 4, 0)); // так как граф ориентированный? Нет, не ориентированный
        FreeGraf(&G);
    }

    TEST(IsWay, CycleGraph) {
        Graf G;
        SetupGraph9(&G);
        EXPECT_TRUE(IsWay(&G, 0, 2));
        EXPECT_TRUE(IsWay(&G, 1, 0));
        FreeGraf(&G);
    }

    TEST(IsWay, NoEdges) {
        Graf G;
        SetupGraph10(&G);
        EXPECT_FALSE(IsWay(&G, 0, 1));
        EXPECT_FALSE(IsWay(&G, 1, 2));
        EXPECT_TRUE(IsWay(&G, 0, 0));
        FreeGraf(&G);
    }