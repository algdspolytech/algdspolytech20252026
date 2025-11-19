#include <gtest/gtest.h>
#include <fstream>
#include "graph.h"

void writeGraphFile(const char* filename, const std::vector<std::vector<int>>& matrix) {
    std::ofstream file(filename);
    file << matrix.size() << "\n";
    for (auto& row : matrix) {
        for (int value : row) file << value << " ";
        file << "\n";
    }
}

//несвязный граф
TEST(GraphTest, DisconnectedGraph_no5) {
    Graph graph;
    writeGraphFile("g5.txt", {
        {0,1,0,0},
        {1,0,0,0},
        {0,0,0,1},
        {0,0,1,0}
        });
    ASSERT_TRUE(readGraphFromFile(&graph, "g5.txt"));
    EXPECT_EQ(dfsHasPath(&graph, 0, 3), 0);
}

//граф с петлёй
TEST(GraphTest, LoopGraph_no4) {
    Graph graph;
    writeGraphFile("g4.txt", { {1} });
    ASSERT_TRUE(readGraphFromFile(&graph, "g4.txt"));
    EXPECT_EQ(dfsHasPath(&graph, 0, 0), 1);
}

//некорректный ввод (файл не существует)
TEST(GraphTest, FileNotFound_Edge_no9) {
    Graph graph;
    EXPECT_EQ(readGraphFromFile(&graph, "nofile.txt"), 0);
}

//путь по диагонали (если 1 на диагонали не означает связь)
TEST(GraphTest, DiagonalOnes_no6) {
    Graph graph;
    writeGraphFile("g6.txt", {
        {1,0,0},
        {0,1,0},
        {0,0,1}
        });
    ASSERT_TRUE(readGraphFromFile(&graph, "g6.txt"));
    EXPECT_EQ(dfsHasPath(&graph, 0, 2), 0);
}

//отсутствует путь
TEST(GraphTest, NoPath_Edge_no2) {
    Graph graph;
    writeGraphFile("g2.txt", { {0,0},{0,0} });
    ASSERT_TRUE(readGraphFromFile(&graph, "g2.txt"));
    EXPECT_EQ(dfsHasPath(&graph, 0, 1), 0);
}

//выход за границы вершин
TEST(GraphTest, OutOfRangeVertices_Edge_no10) {
    Graph graph;
    writeGraphFile("g10.txt", {
        {0,1},
        {1,0}
        });
    ASSERT_TRUE(readGraphFromFile(&graph, "g10.txt"));
    EXPECT_EQ(dfsHasPath(&graph, -1, 0), 0);
    EXPECT_EQ(dfsHasPath(&graph, 0, 10), 0);
}

//полный граф
TEST(GraphTest, CompleteGraph_no7) {
    Graph graph;
    writeGraphFile("g7.txt", {
        {0,1,1},
        {1,0,1},
        {1,1,0}
        });
    ASSERT_TRUE(readGraphFromFile(&graph, "g7.txt"));
    EXPECT_EQ(dfsHasPath(&graph, 0, 2), 1);
}

//простой путь из A в B
TEST(GraphTest, SimplePath_HappyPath_no1) {
    Graph graph;
    writeGraphFile("g1.txt", { {0,1},{1,0} });
    ASSERT_TRUE(readGraphFromFile(&graph, "g1.txt"));
    EXPECT_EQ(dfsHasPath(&graph, 0, 1), 1);
}

//путь длиной > 1
TEST(GraphTest, MultiStepPath_HappyPath_no3) {
    Graph graph;
    writeGraphFile("g3.txt", {
        {0,1,0},
        {1,0,1},
        {0,1,0}
        });
    ASSERT_TRUE(readGraphFromFile(&graph, "g3.txt"));
    EXPECT_EQ(dfsHasPath(&graph, 0, 2), 1);
}

//направленный граф (путь только в одну сторону)
TEST(GraphTest, DirectedGraph_no8) {
    Graph graph;
    writeGraphFile("g8.txt", {
        {0,1,0},
        {0,0,1},
        {0,0,0}
        });
    ASSERT_TRUE(readGraphFromFile(&graph, "g8.txt"));
    EXPECT_EQ(dfsHasPath(&graph, 0, 2), 1);
    EXPECT_EQ(dfsHasPath(&graph, 2, 0), 0);
}