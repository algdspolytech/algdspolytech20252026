#include <gtest/gtest.h>

extern "C" {
#include "graph.h"
}

// Тест 1: Путь в графе с одной вершиной (к самому себе)
TEST(GraphTest, SingleVertexGraphPathExists_no1) {
    int graph[MAX_VERTICES][MAX_VERTICES] = { {0} };
    int result = has_path(graph, 1, 0, 0);
    EXPECT_EQ(result, 1);
}

// Тест 2: Путь в несвязном графе (нет пути)
TEST(GraphTest, DisconnectedGraphNoPath_no2) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int result = has_path(graph, 3, 0, 2);
    EXPECT_EQ(result, 0);
}

// Тест 3: Путь в полносвязном графе (путь должен быть)
TEST(GraphTest, FullyConnectedGraphPathExists_no3) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    int result = has_path(graph, 3, 0, 2);
    EXPECT_EQ(result, 1);
}

// Тест 4: Проверка на некорректные входные данные (отрицательная начальная вершина)
TEST(GraphTest, InvalidNegativeStartVertex_no4) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1},
        {1, 0}
    };
    int result = has_path(graph, 2, -1, 1);
    EXPECT_EQ(result, -1);
}

// Тест 5: Проверка на некорректные входные данные (отрицательная конечная вершина)
TEST(GraphTest, InvalidNegativeEndVertex_no5) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1},
        {1, 0}
    };
    int result = has_path(graph, 2, 0, -1);
    EXPECT_EQ(result, -1);
}

// Тест 6: Путь через несколько вершин (цепочка)
TEST(GraphTest, MultiVertexChainPathExists_no6) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    int result = has_path(graph, 4, 0, 3);
    EXPECT_EQ(result, 1);
}

// Тест 7: Обратный путь в ориентированном графе (нет пути)
TEST(GraphTest, DirectedGraphNoReversePath_no7) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}
    };
    int result = has_path(graph, 3, 2, 0);
    EXPECT_EQ(result, 0);
}

// Тест 8: Путь в графе с циклом
TEST(GraphTest, CyclicGraphPathExists_no8) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };
    int result = has_path(graph, 4, 0, 3);
    EXPECT_EQ(result, 1);
}

// Тест 9: Нет пути в графе с "островами"
TEST(GraphTest, TwoIslandsNoPath_no9) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}
    };
    int result = has_path(graph, 4, 0, 3);
    EXPECT_EQ(result, 0);
}

// Тест 10: Большой граф с максимальным количеством вершин
TEST(GraphTest, LargeGraphPathExists_no10) {
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };
    // Создаем линейную цепочку из всех вершин
    for (int i = 0; i < MAX_VERTICES - 1; i++) {
        graph[i][i + 1] = 1;
    }
    int result = has_path(graph, MAX_VERTICES, 0, MAX_VERTICES - 1);
    EXPECT_EQ(result, 1);
}

// Тест 11: Тест сброса массива visited
TEST(GraphTest, ResetVisitedArray_no11) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    // Первый поиск
    int result1 = has_path(graph, 3, 0, 2);
    EXPECT_EQ(result1, 1);

    // Второй поиск (должен работать корректно после сброса)
    int result2 = has_path(graph, 3, 2, 0);
    EXPECT_EQ(result2, 1);
}

// Тест 12: Тест с вершиной вне диапазона (слишком большая)
TEST(GraphTest, VertexBeyondMax_no12) {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1},
        {1, 0}
    };
    int result = has_path(graph, 2, 0, MAX_VERTICES);
    EXPECT_EQ(result, -1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}