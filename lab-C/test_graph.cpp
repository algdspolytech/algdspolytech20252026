#include <gtest/gtest.h>
#include <fstream>
#include "graph.h"

// Вспомогательная функция для записи временного файла с матрицей
void writeGraphFile(const char* filename, const std::vector<std::vector<int>>& matrix) {
    std::ofstream f(filename);
    f << matrix.size() << "\n";
    for (auto& row : matrix) {
        for (int val : row) f << val << " ";
        f << "\n";
    }
}

// Тест №1 — простой путь из A в B
TEST(GraphTest, SimplePath_HappyPath_no1) {
    Graph g;
    writeGraphFile("g1.txt", {{0,1},{1,0}});
    ASSERT_TRUE(readGraphFromFile(&g, "g1.txt"));
    EXPECT_EQ(dfsHasPath(&g, 0, 1), 1);
}

// Тест №2 — отсутствует путь
TEST(GraphTest, NoPath_Edge_no2) {
    Graph g;
    writeGraphFile("g2.txt", {{0,0},{0,0}});
    ASSERT_TRUE(readGraphFromFile(&g, "g2.txt"));
    EXPECT_EQ(dfsHasPath(&g, 0, 1), 0);
}

// Тест №3 — путь длиной > 1
TEST(GraphTest, MultiStepPath_HappyPath_no3) {
    Graph g;
    writeGraphFile("g3.txt", {
        {0,1,0},
        {1,0,1},
        {0,1,0}
    });
    ASSERT_TRUE(readGraphFromFile(&g, "g3.txt"));
    EXPECT_EQ(dfsHasPath(&g, 0, 2), 1);
}

// Тест №4 — граф с петлёй
TEST(GraphTest, LoopGraph_no4) {
    Graph g;
    writeGraphFile("g4.txt", {{1}});
    ASSERT_TRUE(readGraphFromFile(&g, "g4.txt"));
    EXPECT_EQ(dfsHasPath(&g, 0, 0), 1);
}

// Тест №5 — несвязный граф
TEST(GraphTest, DisconnectedGraph_no5) {
    Graph g;
    writeGraphFile("g5.txt", {
        {0,1,0,0},
        {1,0,0,0},
        {0,0,0,1},
        {0,0,1,0}
    });
    ASSERT_TRUE(readGraphFromFile(&g, "g5.txt"));
    EXPECT_EQ(dfsHasPath(&g, 0, 3), 0);
}

// Тест №6 — путь по диагонали (если 1 на диагонали не означает связь)
TEST(GraphTest, DiagonalOnes_no6) {
    Graph g;
    writeGraphFile("g6.txt", {
        {1,0,0},
        {0,1,0},
        {0,0,1}
    });
    ASSERT_TRUE(readGraphFromFile(&g, "g6.txt"));
    EXPECT_EQ(dfsHasPath(&g, 0, 2), 0);
}

// Тест №7 — полный граф
TEST(GraphTest, CompleteGraph_no7) {
    Graph g;
    writeGraphFile("g7.txt", {
        {0,1,1},
        {1,0,1},
        {1,1,0}
    });
    ASSERT_TRUE(readGraphFromFile(&g, "g7.txt"));
    EXPECT_EQ(dfsHasPath(&g, 0, 2), 1);
}

// Тест №8 — направленный граф (путь только в одну сторону)
TEST(GraphTest, DirectedGraph_no8) {
    Graph g;
    writeGraphFile("g8.txt", {
        {0,1,0},
        {0,0,1},
        {0,0,0}
    });
    ASSERT_TRUE(readGraphFromFile(&g, "g8.txt"));
    EXPECT_EQ(dfsHasPath(&g, 0, 2), 1);
    EXPECT_EQ(dfsHasPath(&g, 2, 0), 0);
}

// Тест №9 — некорректный ввод (файл не существует)
TEST(GraphTest, FileNotFound_Edge_no9) {
    Graph g;
    EXPECT_EQ(readGraphFromFile(&g, "nofile.txt"), 0);
}

// Тест №10 — выход за границы вершин
TEST(GraphTest, OutOfRangeVertices_Edge_no10) {
    Graph g;
    writeGraphFile("g10.txt", {
        {0,1},
        {1,0}
    });
    ASSERT_TRUE(readGraphFromFile(&g, "g10.txt"));
    EXPECT_EQ(dfsHasPath(&g, -1, 0), 0);
    EXPECT_EQ(dfsHasPath(&g, 0, 10), 0);
}
