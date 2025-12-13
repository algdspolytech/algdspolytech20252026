#include <gtest/gtest.h>
#include "main.h"

class GraphTest : public ::testing::Test
{
protected:
    Graph graph;
    GraphMatrix graph_matrix;

    void SetUp() override
    {
        create_graph_list(&graph, 5);
        create_matrix_graph(&graph_matrix, 5);
    }

    void TearDown() override
    {
        free_graph_matrix(&graph_matrix);
        free_graph_list(&graph);
    }
};

TEST_F(GraphTest, ListCreateEmptyGraph_no1)
{
    ASSERT_NE(&graph, nullptr);
    ASSERT_EQ(graph.vertices, 5);

    for (int i = 0; i < 5; i++)
    {
        ASSERT_EQ(graph.array[i].head, nullptr);
    }
}

TEST_F(GraphTest, ListAddSingleEdge_no2)
{
    add_edge_list(&graph, 0, 1);

    ASSERT_NE(graph.array[0].head, nullptr);
    ASSERT_EQ(graph.array[0].head->destination, 1);
    ASSERT_NE(graph.array[1].head, nullptr);
    ASSERT_EQ(graph.array[1].head->destination, 0);
    ASSERT_EQ(graph.array[2].head, nullptr);
}

TEST_F(GraphTest, MatrixMemoryManagement_no3)
{
    for (int i = 0; i < 4; i++)
    {
        add_edge_matrix(&graph_matrix, i, i + 1);
    }

    ASSERT_EQ(graph_matrix.matrix[0][1], 1);
}

TEST_F(GraphTest, ListSingleVertexGraph_no4)
{
    ASSERT_EQ(graph.array[0].head, nullptr);

    add_edge_list(&graph, 0, 0);
    ASSERT_NE(graph.array[0].head, nullptr);
    ASSERT_EQ(graph.array[0].head->destination, 0);
}

TEST_F(GraphTest, ListEdgeOrderPreservation_no5)
{
    add_edge_list(&graph, 0, 1);
    add_edge_list(&graph, 0, 2);
    add_edge_list(&graph, 0, 3);

    struct AdjListNode* current = graph.array[0].head;
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->destination, 3);

    current = current->next;
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->destination, 2);

    current = current->next;
    ASSERT_NE(current, nullptr);
    ASSERT_EQ(current->destination, 1);

    ASSERT_EQ(current->next, nullptr);
}

TEST_F(GraphTest, ListDuplicateEdges_no6) {

    add_edge_list(&graph, 0, 1);
    add_edge_list(&graph, 0, 1);
    add_edge_list(&graph, 0, 1);

    int neighbor_count = 0;
    struct AdjListNode* current = graph.array[0].head;
    while (current != nullptr)
    {
        ASSERT_EQ(current->destination, 1);
        neighbor_count++;
        current = current->next;
    }
    ASSERT_EQ(neighbor_count, 3);
}

TEST_F(GraphTest, MatrixDuplicateEdges_no7)
{
    add_edge_matrix(&graph_matrix, 0, 1);
    add_edge_matrix(&graph_matrix, 0, 1);
    add_edge_matrix(&graph_matrix, 0, 1);

    ASSERT_EQ(graph_matrix.matrix[0][1], 1);

    ASSERT_EQ(graph_matrix.matrix[0][0], 0);
    ASSERT_EQ(graph_matrix.matrix[1][1], 0);
}

TEST_F(GraphTest, Matrix_IsolatedVertices) {
    add_edge_matrix(&graph_matrix, 1, 2);

    for (int i : {0, 3, 4})
    {
        for (int j = 0; j < graph_matrix.vertices; j++) {
            ASSERT_EQ(graph_matrix.matrix[i][j], 0);
            ASSERT_EQ(graph_matrix.matrix[j][i], 0);
        }
    }
}

TEST_F(GraphTest, StructureConsistencySingleEdge_no9)
{

    add_edge_list(&graph, 0, 1);
    add_edge_matrix(&graph_matrix, 0, 1);

    ASSERT_NE(graph.array[0].head, nullptr);
    ASSERT_EQ(graph.array[0].head->destination, 1);

    ASSERT_EQ(graph_matrix.matrix[0][1], 1);
}

TEST_F(GraphTest, StructureConsistencyMultipleEdges_no10)
{
    add_edge_list(&graph, 0, 1);
    add_edge_list(&graph, 1, 2);
    add_edge_list(&graph, 2, 3);
    add_edge_list(&graph, 3, 4);
    add_edge_list(&graph, 4, 0);

    add_edge_matrix(&graph_matrix, 0, 1);
    add_edge_matrix(&graph_matrix, 1, 2);
    add_edge_matrix(&graph_matrix, 2, 3);
    add_edge_matrix(&graph_matrix, 3, 4);
    add_edge_matrix(&graph_matrix, 4, 0);

    int listNeighborCount = 0;
    int matrixNeighborCount = 0;

    for (int i = 0; i < 5; i++)
    {
        AdjListNode* current = graph.array[i].head;
        while (current != nullptr)
        {
            listNeighborCount++;
            current = current->next;
        }

        for (int j = 0; j < 5; j++)
        {
            if (graph_matrix.matrix[i][j] == 1)
            {
                matrixNeighborCount++;
            }
        }
        int listNeighborCount = 0;
        int matrixNeighborCount = 0;
    }
    ASSERT_EQ(listNeighborCount, matrixNeighborCount);
}

TEST_F(GraphTest, StructureConsistencyEmptyGraph_no11)
{
    for (int i = 0; i < 5; i++)
    {
        ASSERT_EQ(graph.array[i].head, nullptr);

        for (int j = 0; j < 5; j++)
        {
            ASSERT_EQ(graph_matrix.matrix[i][j], 0);
        }
    }
}