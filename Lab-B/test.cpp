#include <gtest/gtest.h>
#include "Adj_Graph_to_list.h"

// ---------- Фикстура ----------
class GraphTest : public ::testing::Test {
protected:
    Graph* graph;

    void SetUp() override {
        graph = nullptr;
    }

    void TearDown() override {
        if (graph)
            free_graph(graph);
    }
};

// ---------- Тесты ----------

// 1️ Тест на создание графа с нормальным количеством вершин
TEST_F(GraphTest, create_graph_NormalCount_returnValidVal) {
    graph = create_graph(4);
    ASSERT_NE(graph, nullptr);
    ASSERT_EQ(graph->num_vertices, 4);
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(graph->adj_lists[i], nullptr);
    }
}

// 2️ Тест на создание пустого графа
TEST_F(GraphTest, create_graph_ZeroCount_returnValidVal) {
    graph = create_graph(0);
    ASSERT_NE(graph, nullptr);
    ASSERT_EQ(graph->num_vertices, 0);
}

// 3️ Тест на создание графа с большим количеством вершин
TEST_F(GraphTest, create_graph_LargeCount_returnValidVal) {
    graph = create_graph(10);
    ASSERT_NE(graph, nullptr);
    ASSERT_EQ(graph->num_vertices, 10);
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(graph->adj_lists[i], nullptr);
    }
}

// 4️ Тест на добавление одного ребра
TEST_F(GraphTest, add_edge_SingleEdge_returnValidVal) {
    graph = create_graph(2);
    add_edge(graph, 0, 1);
    ASSERT_NE(graph->adj_lists[0], nullptr);
    ASSERT_EQ(graph->adj_lists[0]->vertex, 1);
    ASSERT_EQ(graph->adj_lists[0]->next, nullptr);
    ASSERT_EQ(graph->adj_lists[1], nullptr);
}

// 5️ Тест на добавление дублирующегося ребра
TEST_F(GraphTest, add_edge_DuplicateEdge_returnValidVal) {
    graph = create_graph(2);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 1); // дубликат
    Node* head = graph->adj_lists[0];
    ASSERT_NE(head, nullptr);
    ASSERT_EQ(head->vertex, 1);
    ASSERT_NE(head->next, nullptr);
    ASSERT_EQ(head->next->vertex, 1);
    ASSERT_EQ(head->next->next, nullptr);
}

// 6️ Тест на добавление несимметричного ребра
TEST_F(GraphTest, add_edge_AsymmetricEdge_returnValidVal) {
    graph = create_graph(2);
    add_edge(graph, 0, 1);
    ASSERT_NE(graph->adj_lists[0], nullptr);
    ASSERT_EQ(graph->adj_lists[0]->vertex, 1);
    ASSERT_EQ(graph->adj_lists[0]->next, nullptr);
    ASSERT_EQ(graph->adj_lists[1], nullptr);
}

// 7️ Тест на добавление нескольких ребер
TEST_F(GraphTest, add_edge_MultipleEdges_returnValidVal) {
    graph = create_graph(3);
    add_edge(graph, 0, 1);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 0);
    add_edge(graph, 2, 1);

    // Проверка списков смежности
    ASSERT_EQ(graph->adj_lists[0]->vertex, 1);
    ASSERT_EQ(graph->adj_lists[0]->next, nullptr);

    ASSERT_EQ(graph->adj_lists[1]->vertex, 0);
    ASSERT_EQ(graph->adj_lists[1]->next->vertex, 2);
    ASSERT_EQ(graph->adj_lists[1]->next->next, nullptr);

    ASSERT_EQ(graph->adj_lists[2]->vertex, 1);
    ASSERT_EQ(graph->adj_lists[2]->next, nullptr);
}

// 8️ Тест на граф без ребер
TEST_F(GraphTest, add_edge_NoEdges_returnValidVal) {
    graph = create_graph(2);
    ASSERT_EQ(graph->adj_lists[0], nullptr);
    ASSERT_EQ(graph->adj_lists[1], nullptr);
}

// 9️ Тест на освобождение памяти нормального графа
TEST_F(GraphTest, free_graph_NormalGraph_returnSuccess) {
    graph = create_graph(2);
    add_edge(graph, 0, 1);
    free_graph(graph);
    graph = nullptr;
    SUCCEED();
}

// 10️ Тест на освобождение памяти пустого графа
TEST_F(GraphTest, free_graph_EmptyGraph_returnSuccess) {
    graph = create_graph(0);
    free_graph(graph);
    graph = nullptr;
    SUCCEED();
}