#include "gtest/gtest.h"
#include "graph.h"
#pragma warning(disable: 4996)


TEST(SimpleTests, NumInMas_Found_no1) {
    int mas[] = { 1, 2, 3, -1 };
    EXPECT_EQ(Num_In_Mas(mas, 2), 0);
}

TEST(SimpleTests, NumInMas_NotFound_no2) {
    int mas[] = { 1, 2, 3, -1 };
    EXPECT_EQ(Num_In_Mas(mas, 5), 1);
}

TEST(SimpleTests, NumInMas_EmptyArray_no3) {
    int mas[] = { -1 };
    EXPECT_EQ(Num_In_Mas(mas, 1), 1);
}

TEST(AddToListTests, AddToEmpty_no4) {
    int* mas = (int*)malloc(sizeof(int));
    mas[0] = -1;

    mas = Add_To_List(mas, 42);

    EXPECT_EQ(mas[0], 42);
    EXPECT_EQ(mas[1], -1);
}

TEST(AddToListTests, AddMultiple_no5) {
    int* mas = (int*)malloc(sizeof(int));
    mas[0] = -1;

    mas = Add_To_List(mas, 1);
    mas = Add_To_List(mas, 2);
    mas = Add_To_List(mas, 3);

    EXPECT_EQ(mas[0], 1);
    EXPECT_EQ(mas[1], 2);
    EXPECT_EQ(mas[2], 3);
    EXPECT_EQ(mas[3], -1);
}

TEST(GraphTests, WayExistsDirect_no6) {

    int** graph = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }
    graph[0][1] = 1;
    graph[1][0] = 1;

    const char* result = Way_Between_Graph_Node(graph, 0, 1);
    EXPECT_STREQ(result, "There is a way:)");
}

TEST(GraphTests, WayNotExists_no7) {
    int** graph = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    const char* result = Way_Between_Graph_Node(graph, 0, 5);
    EXPECT_STREQ(result, "There is no way:(");
}

TEST(GraphTests, WaySameNode_no8) {
    int** graph = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    const char* result = Way_Between_Graph_Node(graph, 3, 3);
    EXPECT_STREQ(result, "There is a way:)");
}

TEST(ComplexGraphTest, MultipleConnections_no9) {
    int** graph = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    graph[0][1] = graph[1][0] = 1;
    graph[1][2] = graph[2][1] = 1;

    const char* result1 = Way_Between_Graph_Node(graph, 0, 2);
    EXPECT_STREQ(result1, "There is a way:)");

    const char* result2 = Way_Between_Graph_Node(graph, 0, 8);
    EXPECT_STREQ(result2, "There is no way:(");

}

TEST(DFSTest, BasicTraversal_no10) {
    int** graph = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    graph[0][1] = graph[1][0] = 1;
    graph[1][2] = graph[2][1] = 1;

    int* marked = (int*)malloc(sizeof(int));
    marked[0] = -1;

    marked = DFS(graph, marked, 0);

    EXPECT_EQ(Num_In_Mas(marked, 0), 0);
    EXPECT_EQ(Num_In_Mas(marked, 1), 0);
    EXPECT_EQ(Num_In_Mas(marked, 2), 0);

}

TEST(DFSTest, EmptyGraph_no11) {
    int** graph = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        graph[i] = (int*)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    int* marked = (int*)malloc(sizeof(int));
    marked[0] = -1;

    marked = DFS(graph, marked, 0);

    EXPECT_EQ(Num_In_Mas(marked, 0), 0);
    EXPECT_EQ(Num_In_Mas(marked, 1), 1);
    EXPECT_EQ(Num_In_Mas(marked, 2), 1);

}

TEST(CreateGraphTest, FromFileSimple_no12) {
    FILE* file = fopen("test_graph.txt", "w");
    fprintf(file, "0100000000\n");
    fprintf(file, "1010000000\n");
    fprintf(file, "0100000000\n");
    fprintf(file, "0000000000\n");
    fprintf(file, "0000000000\n");
    fprintf(file, "0000000000\n");
    fprintf(file, "0000000000\n");
    fprintf(file, "0000000000\n");
    fprintf(file, "0000000000\n");
    fprintf(file, "0000000000\n");
    fclose(file);

    file = fopen("test_graph.txt", "r");
    int** graph = Create_Graph_Matrix(file);
    fclose(file);

    EXPECT_EQ(graph[0][1], 1);
    EXPECT_EQ(graph[1][0], 1);
    EXPECT_EQ(graph[1][2], 1);
    EXPECT_EQ(graph[2][1], 1);

    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
    remove("test_graph.txt");
}

TEST(CreateGraphTest, FromFileEmptyno13) {
    FILE* file = fopen("test_graph.txt", "w");
    fclose(file);

    file = fopen("test_graph.txt", "r");
    int** graph = Create_Graph_Matrix(file);
    fclose(file);

    EXPECT_EQ(graph, nullptr);

    free(graph);
    remove("test_graph.txt");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}