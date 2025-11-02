#define _CRT_SECURE_NO_WARNINGS
#include "gtest/gtest.h"
#include "Header.h"
TEST(GraphTest, CreateGraph) {
    struct Graph* graph = createGraph(5);
    EXPECT_NE(graph, nullptr);
    EXPECT_EQ(graph->numVertices, 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(graph->adjLists[i], nullptr);
        EXPECT_EQ(graph->visited[i], 0);
    }
    freeGraph(graph);
}

TEST(GraphTest, AddEdge) {
    struct Graph* graph = createGraph(3);
    addEdge(graph, 0, 1);

    EXPECT_NE(graph->adjLists[0], nullptr);
    EXPECT_EQ(graph->adjLists[0]->vertex, 1);
    EXPECT_NE(graph->adjLists[1], nullptr);
    EXPECT_EQ(graph->adjLists[1]->vertex, 0);

    freeGraph(graph);
}

TEST(GraphTest, PathExistsSameVertex) {
    struct Graph* graph = createGraph(3);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);

    EXPECT_TRUE(pathExists(graph, 0, 0));

    freeGraph(graph);
}

TEST(GraphTest, PathExistsDirectConnection) {
    struct Graph* graph = createGraph(3);
    addEdge(graph, 0, 1);

    EXPECT_TRUE(pathExists(graph, 0, 1));
    EXPECT_TRUE(pathExists(graph, 1, 0));

    freeGraph(graph);
}

TEST(GraphTest, PathExistsIndirectConnection) {
    struct Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);

    EXPECT_TRUE(pathExists(graph, 0, 3));

    freeGraph(graph);
}

TEST(GraphTest, PathNotExists) {
    struct Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 2, 3);

    EXPECT_FALSE(pathExists(graph, 0, 2));
    EXPECT_FALSE(pathExists(graph, 1, 3));

    freeGraph(graph);
}

TEST(GraphTest, PathExistsComplexGraph) {
    struct Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    EXPECT_TRUE(pathExists(graph, 0, 5));
    EXPECT_TRUE(pathExists(graph, 1, 4));

    freeGraph(graph);
}

TEST(GraphTest, IsolatedVertex) {
    struct Graph* graph = createGraph(3);
    addEdge(graph, 0, 1);

    EXPECT_FALSE(pathExists(graph, 0, 2));
    EXPECT_FALSE(pathExists(graph, 1, 2));
    EXPECT_TRUE(pathExists(graph, 2, 2));

    freeGraph(graph);
}

TEST(GraphTest, MultipleEdges) {
    struct Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);

    EXPECT_TRUE(pathExists(graph, 1, 3));

    freeGraph(graph);
}

TEST(GraphTest, SingleVertexGraph) {
    struct Graph* graph = createGraph(1);

    EXPECT_TRUE(pathExists(graph, 0, 0));

    freeGraph(graph);
}

TEST(GraphTest, CreateNode) {
    struct Node* node = createNode(5);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(node->vertex, 5);
    EXPECT_EQ(node->next, nullptr);
    free(node);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}