#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include <cstring>

extern "C" {
    #include "graph.h"
}

class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::ofstream f("test_input.txt");
        f << "4\n";
        f << "1:2 4\n";
        f << "2:1 3\n";
        f << "3:2 4\n";
        f << "4:1 3\n";
        f.close();
    }

    void TearDown() override {
        remove("test_input.txt");
        remove("test_output.txt");
        remove("test_graph.txt");
    }

    Graph g;
};

TEST_F(GraphTest, GraphInit_ZeroVertices_NoCrash_no1) {
    graph_init(&g, 0);
}

TEST_F(GraphTest, GraphInit_MaxVertices_Success_no2) {
    graph_init(&g, MAX_NODES);
    EXPECT_EQ(g.n, MAX_NODES);
}

TEST_F(GraphTest, GraphAddEdge_SelfLoop_NotAllowed_no3) {
    graph_init(&g, 3);
    EXPECT_EQ(graph_add_edge(&g, 1, 1), 0);
    EXPECT_EQ(graph_has_edge(&g, 1, 1), 0);
}

TEST_F(GraphTest, GraphLoadFromFile_VertexWithoutNeighbors_HandlesCorrectly_no4) {
    std::ofstream f("isolated.txt");
    f << "3\n";
    f << "1:2\n";
    f << "2:1\n";
    f << "3:\n";
    f.close();
    
    EXPECT_EQ(graph_load_from_file(&g, "isolated.txt"), 1);
    EXPECT_EQ(graph_edge_count(&g), 1);
    
    remove("isolated.txt");
}

TEST_F(GraphTest, GraphEdgeCount_CompleteGraph_CalculatesCorrectly_no5) {
    graph_init(&g, 5);
    for (int i = 1; i <= 5; i++) {
        for (int j = i + 1; j <= 5; j++) {
            graph_add_edge(&g, i, j);
        }
    }
    EXPECT_EQ(graph_edge_count(&g), 10);
}

TEST_F(GraphTest, GraphSaveMatrix_ReadBack_Consistent_no6) {
    graph_init(&g, 3);
    graph_add_edge(&g, 1, 2);
    graph_add_edge(&g, 2, 3);
    
    EXPECT_EQ(graph_save_matrix(&g, "test_graph.txt"), 1);
    
    Graph g2;
    EXPECT_EQ(graph_load_from_file(&g2, "test_graph.txt"), 1);
    
    EXPECT_EQ(g2.n, g.n);
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            EXPECT_EQ(g2.adj[i][j], g.adj[i][j]);
        }
    }
}

TEST_F(GraphTest, GraphPrintMatrix_EmptyGraph_OutputsHeader_no7) {
    graph_init(&g, 0);
    
    testing::internal::CaptureStdout();
    graph_print_matrix(&g);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.empty());
}

TEST_F(GraphTest, GraphLoadFromFile_ExtraSpaces_ParsesCorrectly_no8) {
    std::ofstream f("spaces.txt");
    f << "   3   \n";
    f << "1:   2    3   \n";
    f << "2:1     \n";
    f << "3:1\n";
    f.close();
    
    EXPECT_EQ(graph_load_from_file(&g, "spaces.txt"), 1);
    EXPECT_EQ(g.n, 3);
    EXPECT_EQ(graph_has_edge(&g, 1, 2), 1);
    EXPECT_EQ(graph_has_edge(&g, 1, 3), 1);
    
    remove("spaces.txt");
}

TEST_F(GraphTest, GraphHasEdge_InvalidOrder_ReturnsError_no9) {
    graph_init(&g, 3);
    EXPECT_EQ(graph_has_edge(&g, 3, 1), 0);
    graph_add_edge(&g, 1, 3);
    EXPECT_EQ(graph_has_edge(&g, 3, 1), 1);
}

TEST_F(GraphTest, GraphLoadFromFile_DuplicateEdgesInFile_HandlesGracefully_no10) {
    std::ofstream f("duplicate.txt");
    f << "3\n";
    f << "1:2 2 3 2\n";
    f << "2:1 3 1\n";
    f << "3:1 2\n";
    f.close();
    
    EXPECT_EQ(graph_load_from_file(&g, "duplicate.txt"), 1);
    EXPECT_EQ(graph_edge_count(&g), 3);
    
    remove("duplicate.txt");
}

TEST_F(GraphTest, GraphInit_NegativeVertices_NoCrash_no11) {
    graph_init(&g, -5);
}

TEST_F(GraphTest, GraphAddEdge_ReverseOrder_Symmetric_no12) {
    graph_init(&g, 4);
    graph_add_edge(&g, 2, 4);
    EXPECT_EQ(graph_has_edge(&g, 4, 2), 1);
    EXPECT_EQ(graph_has_edge(&g, 2, 4), 1);
}

TEST_F(GraphTest, GraphLoadFromFile_MissingColon_SkipsLine_no13) {
    std::ofstream f("nocolon.txt");
    f << "3\n";
    f << "1 2 3\n";
    f << "2:1\n";
    f << "3:1\n";
    f.close();
    
    EXPECT_EQ(graph_load_from_file(&g, "nocolon.txt"), 1);
    EXPECT_EQ(graph_edge_count(&g), 2);
    
    remove("nocolon.txt");
}

TEST_F(GraphTest, GraphEdgeCount_SingleEdgeGraph_ReturnsOne_no14) {
    graph_init(&g, 2);
    graph_add_edge(&g, 1, 2);
    EXPECT_EQ(graph_edge_count(&g), 1);
}

TEST_F(GraphTest, GraphSaveMatrix_PermissionDenied_ReturnsFalse_no15) {
    graph_init(&g, 3);
    
    EXPECT_EQ(graph_save_matrix(&g, "/root/test.txt"), 0);
}

TEST_F(GraphTest, GraphLoadFromFile_NonNumericVertex_SkipsValue_no16) {
    std::ofstream f("nonnumeric.txt");
    f << "3\n";
    f << "1:2 abc 3\n";
    f << "2:1\n";
    f << "3:1\n";
    f.close();
    
    EXPECT_EQ(graph_load_from_file(&g, "nonnumeric.txt"), 1);
    EXPECT_EQ(graph_has_edge(&g, 1, 2), 1);
    EXPECT_EQ(graph_has_edge(&g, 1, 3), 1);
    
    remove("nonnumeric.txt");
}

TEST_F(GraphTest, GraphAddEdge_AfterMultipleOperations_MatrixConsistent_no17) {
    graph_init(&g, 5);
    
    graph_add_edge(&g, 1, 2);
    graph_add_edge(&g, 3, 4);
    graph_add_edge(&g, 2, 5);
    graph_add_edge(&g, 1, 4);
    
    EXPECT_EQ(graph_has_edge(&g, 2, 1), 1);
    EXPECT_EQ(graph_has_edge(&g, 4, 3), 1);
    EXPECT_EQ(graph_has_edge(&g, 5, 2), 1);
    EXPECT_EQ(graph_has_edge(&g, 4, 1), 1);
    EXPECT_EQ(graph_has_edge(&g, 1, 5), 0);
}

TEST_F(GraphTest, GraphVertexValid_NullGraph_ReturnsFalse_no18) {
    EXPECT_EQ(graph_vertex_valid(nullptr, 1), 0);
    EXPECT_EQ(graph_vertex_valid(nullptr, 0), 0);
    EXPECT_EQ(graph_vertex_valid(nullptr, -1), 0);
}

TEST_F(GraphTest, GraphLoadFromFile_LargeVertexNumbers_HandlesCorrectly_no19) {
    std::ofstream f("large.txt");
    f << "100\n";
    f << "1:100\n";
    f << "50:51\n";
    f << "100:1\n";
    f.close();
    
    EXPECT_EQ(graph_load_from_file(&g, "large.txt"), 1);
    EXPECT_EQ(g.n, 100);
    EXPECT_EQ(graph_has_edge(&g, 1, 100), 1);
    EXPECT_EQ(graph_has_edge(&g, 50, 51), 1);
    
    remove("large.txt");
}

TEST_F(GraphTest, GraphPrintMatrix_SingleVertex_OutputsCorrectly_no20) {
    graph_init(&g, 1);
    
    testing::internal::CaptureStdout();
    graph_print_matrix(&g);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("1 вершин"), std::string::npos);
    EXPECT_NE(output.find("1:"), std::string::npos);
}

TEST_F(GraphTest, GraphLoadFromFile_TabSeparators_ParsesCorrectly_no21) {
    std::ofstream f("tabs.txt");
    f << "3\n";
    f << "1:\t2\t3\n";
    f << "2:\t1\n";
    f << "3:\t1\n";
    f.close();
    
    EXPECT_EQ(graph_load_from_file(&g, "tabs.txt"), 1);
    EXPECT_EQ(graph_has_edge(&g, 1, 2), 1);
    EXPECT_EQ(graph_has_edge(&g, 1, 3), 1);
    
    remove("tabs.txt");
}

TEST_F(GraphTest, GraphHasEdge_OutOfRange_ReturnsError_no22) {
    graph_init(&g, 3);
    EXPECT_EQ(graph_has_edge(&g, 1, 100), -1);
    EXPECT_EQ(graph_has_edge(&g, 100, 1), -1);
    EXPECT_EQ(graph_has_edge(&g, 0, 2), -1);
}

TEST_F(GraphTest, GraphAddEdge_MultipleCalls_SameResult_no23) {
    graph_init(&g, 4);
    
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(graph_add_edge(&g, 1, 2), 1);
    }
    
    EXPECT_EQ(graph_edge_count(&g), 1);
}

TEST_F(GraphTest, GraphLoadFromFile_FileWithComments_HandlesCorrectly_no24) {
    std::ofstream f("comments.txt");
    f << "# Graph with 3 vertices\n";
    f << "3\n";
    f << "1:2  # connected to 2\n";
    f << "2:1 3\n";
    f << "# Vertex 3 connections\n";
    f << "3:2\n";
    f.close();
    
    EXPECT_EQ(graph_load_from_file(&g, "comments.txt"), 0);
    
    remove("comments.txt");
}

TEST_F(GraphTest, GraphSaveMatrix_EmptyGraph_SavesZeros_no25) {
    graph_init(&g, 4);
    
    EXPECT_EQ(graph_save_matrix(&g, "empty_graph.txt"), 1);
    
    std::ifstream f("empty_graph.txt");
    int n;
    f >> n;
    
    int matrix[4][4];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            f >> matrix[i][j];
            EXPECT_EQ(matrix[i][j], 0);
        }
    }
    
    f.close();
    remove("empty_graph.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    
    return result;
}
