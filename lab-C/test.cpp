#include "gtest/gtest.h"
#include "pch.h"

extern "C" {
#include "graph.h"
}

// 1 Проверяем, что пустые графы совпадают
TEST(GraphTest, EmptyGraphs_no1) {
    Graph a, b;
    init_graph(&a, 0);
    init_graph(&b, 0);
    EXPECT_EQ(compare_graphs(&a, &b), 1);
}

// 2 Проверка одинаковых графов
TEST(GraphTest, IdenticalGraphs_no2) {
    Graph a, b;
    init_graph(&a, 3);
    init_graph(&b, 3);
    a.matrix[0][1] = b.matrix[0][1] = 1;
    a.matrix[1][0] = b.matrix[1][0] = 1;
    EXPECT_EQ(compare_graphs(&a, &b), 1);
}

// 3 Проверка разных графов
TEST(GraphTest, DifferentGraphs_no3) {
    Graph a, b;
    init_graph(&a, 3);
    init_graph(&b, 3);
    a.matrix[0][1] = 1;
    b.matrix[0][2] = 1;
    EXPECT_EQ(compare_graphs(&a, &b), 0);
}

// 4 Проверка графов с разным количеством вершин
TEST(GraphTest, DifferentSizes_no4) {
    Graph a, b;
    init_graph(&a, 3);
    init_graph(&b, 4);
    EXPECT_EQ(compare_graphs(&a, &b), 0);
}

// 5 Проверка симметрии графа
TEST(GraphTest, SymmetricGraph_no5) {
    Graph a, b;
    init_graph(&a, 3);
    init_graph(&b, 3);
    a.matrix[0][1] = 1;
    a.matrix[1][0] = 1;
    b.matrix[0][1] = 1;
    b.matrix[1][0] = 1;
    EXPECT_EQ(compare_graphs(&a, &b), 1);
}

// 6 Проверка несоответствия по диагонали
TEST(GraphTest, DiagonalDifference_no6) {
    Graph a, b;
    init_graph(&a, 3);
    init_graph(&b, 3);
    a.matrix[0][0] = 1;
    b.matrix[0][0] = 0;
    EXPECT_EQ(compare_graphs(&a, &b), 0);
}

// 7 Проверка соответствия с диагональю
TEST(GraphTest, SameLoops_no7) {
    Graph a, b;
    init_graph(&a, 2);
    init_graph(&b, 2);
    a.matrix[0][0] = b.matrix[0][0] = 1;
    EXPECT_EQ(compare_graphs(&a, &b), 1);
}

// 8 Проверка полноты графа
TEST(GraphTest, CompleteGraph_no8) {
    Graph a, b;
    init_graph(&a, 4);
    init_graph(&b, 4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) a.matrix[i][j] = b.matrix[i][j] = 1;
    EXPECT_EQ(compare_graphs(&a, &b), 1);
}

// 9 Проверка совпадения несвязных графов
TEST(GraphTest, AllZeros_no9) {
    Graph a, b;
    init_graph(&a, 5);
    init_graph(&b, 5);
    EXPECT_EQ(compare_graphs(&a, &b), 1);
}

// 10 Проверка графов, отличающихся одной связью
TEST(GraphTest, OneEdgeDiff_no10) {
    Graph a, b;
    init_graph(&a, 3);
    init_graph(&b, 3);
    a.matrix[1][2] = 1;
    b.matrix[1][2] = b.matrix[2][1] = 1;  // b симметричный, a нет
    EXPECT_EQ(compare_graphs(&a, &b), 0);
}

// 11 Проверка графа с "изолированной" вершиной
TEST(GraphTest, IsolatedVertex_no11) {
    Graph a, b;
    init_graph(&a, 4);
    init_graph(&b, 4);

    // Ребра между 1–2 и 2–3
    a.matrix[0][1] = a.matrix[1][0] = 1;
    a.matrix[1][2] = a.matrix[2][1] = 1;

    b.matrix[0][1] = b.matrix[1][0] = 1;
    b.matrix[1][2] = b.matrix[2][1] = 1;
    // вершина 4 изолирована
    EXPECT_EQ(compare_graphs(&a, &b), 1);
}

// 12 Проверка сравнения по позициям в матрице
TEST(GraphTest, SameStructureDifferentLabels_no12) {
    Graph a, b;
    init_graph(&a, 3);
    init_graph(&b, 3);

    a.matrix[0][1] = a.matrix[1][0] = 1;
    a.matrix[1][2] = a.matrix[2][1] = 1;

    b.matrix[0][1] = b.matrix[1][0] = 1;
    b.matrix[0][2] = b.matrix[2][0] = 0;  // перестановка вершин

    EXPECT_EQ(compare_graphs(&a, &b), 0);
}