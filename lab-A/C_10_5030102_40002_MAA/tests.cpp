#include "googletest/googletest/include/gtest/gtest.h"
#include <fstream>
#include "list.h"

class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
    
    void CreateTestFile(const char* filename, const char* content) {
        std::ofstream file(filename);
        file << content;
        file.close();
    }
};

TEST_F(GraphTest, CreateGraphWithValidSize_no1) {
    struct Graph* graph = create_graph(5);
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertices, 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(graph->adj_list[i], nullptr);
    }
    free_graph(graph);
}

TEST_F(GraphTest, CreateGraphWithZeroVertices_no2) {
    struct Graph* graph = create_graph(0);
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertices, 0);
    free_graph(graph);
}

TEST_F(GraphTest, AddSingleEdgeToGraph_no3) {
    struct Graph* graph = create_graph(3);
    add_edge(graph, 0, 1);
    
    EXPECT_NE(graph->adj_list[0], nullptr);
    EXPECT_EQ(graph->adj_list[0]->vertex, 1);
    EXPECT_EQ(has_edge(graph, 0, 1), 1);
    EXPECT_EQ(has_edge(graph, 1, 0), 0);
    
    free_graph(graph);
}

TEST_F(GraphTest, AddMultipleEdgesFromSameVertex_no4) {
    struct Graph* graph = create_graph(3);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    
    EXPECT_EQ(has_edge(graph, 0, 1), 1);
    EXPECT_EQ(has_edge(graph, 0, 2), 1);
    EXPECT_EQ(has_edge(graph, 1, 0), 0);
    EXPECT_EQ(has_edge(graph, 2, 0), 0);
    
    free_graph(graph);
}

TEST_F(GraphTest, AddSelfLoopEdge_no5) {
    struct Graph* graph = create_graph(2);
    add_edge(graph, 0, 0);
    
    EXPECT_EQ(has_edge(graph, 0, 0), 1);
    free_graph(graph);
}

TEST_F(GraphTest, ReadValidMatrixFromFile_no6) {
    CreateTestFile("test_valid.txt", "3\n0 1 0\n1 0 1\n0 1 0");
    
    struct Graph* graph = read_matrix_file("test_valid.txt");
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertices, 3);
    
    EXPECT_EQ(has_edge(graph, 0, 1), 1);
    EXPECT_EQ(has_edge(graph, 1, 0), 1);
    EXPECT_EQ(has_edge(graph, 1, 2), 1);
    EXPECT_EQ(has_edge(graph, 2, 1), 1);
    EXPECT_EQ(has_edge(graph, 0, 0), 0);
    EXPECT_EQ(has_edge(graph, 0, 2), 0);
    
    free_graph(graph);
    remove("test_valid.txt");
}

TEST_F(GraphTest, ReadEmptyGraphFromFile_no7) {
    CreateTestFile("test_empty.txt", "2\n0 0\n0 0");
    
    struct Graph* graph = read_matrix_file("test_empty.txt");
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertices, 2);
    
    for (int i = 0; i < 2; i++) {
        EXPECT_EQ(graph->adj_list[i], nullptr);
    }
    
    free_graph(graph);
    remove("test_empty.txt");
}

TEST_F(GraphTest, ReadCompleteGraphFromFile_no8) {
    CreateTestFile("test_complete.txt", "3\n1 1 1\n1 1 1\n1 1 1");
    
    struct Graph* graph = read_matrix_file("test_complete.txt");
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertices, 3);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_EQ(has_edge(graph, i, j), 1);
        }
    }
    
    free_graph(graph);
    remove("test_complete.txt");
}

TEST_F(GraphTest, ReadNonExistentFile_no9) {
    struct Graph* graph = read_matrix_file("nonexistent_file.txt");
    EXPECT_EQ(graph, nullptr);
}

TEST_F(GraphTest, ReadSingleVertexGraph_no10) {
    CreateTestFile("test_single.txt", "1\n0");
    
    struct Graph* graph = read_matrix_file("test_single.txt");
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertices, 1);
    EXPECT_EQ(graph->adj_list[0], nullptr);
    
    free_graph(graph);
    remove("test_single.txt");
}

TEST_F(GraphTest, AddDuplicateEdges_no11) {
    struct Graph* graph = create_graph(2);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 1);
    
    EXPECT_EQ(has_edge(graph, 0, 1), 1);
    
    struct Node* node = graph->adj_list[0];
    int count = 0;
    while (node) {
        if (node->vertex == 1) count++;
        node = node->next;
    }
    EXPECT_EQ(count, 2);
    
    free_graph(graph);
}

TEST_F(GraphTest, ComplexGraphStructure_no12) {
    CreateTestFile("test_complex.txt", "4\n0 1 1 0\n1 0 1 1\n1 1 0 0\n0 1 0 0");
    
    struct Graph* graph = read_matrix_file("test_complex.txt");
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertices, 4);
    
    EXPECT_EQ(has_edge(graph, 0, 1), 1);
    EXPECT_EQ(has_edge(graph, 0, 2), 1);
    EXPECT_EQ(has_edge(graph, 1, 0), 1);
    EXPECT_EQ(has_edge(graph, 1, 2), 1);
    EXPECT_EQ(has_edge(graph, 1, 3), 1);
    EXPECT_EQ(has_edge(graph, 2, 0), 1);
    EXPECT_EQ(has_edge(graph, 2, 1), 1);
    EXPECT_EQ(has_edge(graph, 3, 1), 1);
    
    EXPECT_EQ(has_edge(graph, 0, 3), 0);
    EXPECT_EQ(has_edge(graph, 2, 3), 0);
    EXPECT_EQ(has_edge(graph, 3, 0), 0);
    EXPECT_EQ(has_edge(graph, 3, 2), 0);
    
    free_graph(graph);
    remove("test_complex.txt");
}