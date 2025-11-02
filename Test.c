#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Lab-C.h"

void TestCreateGraph_ZeroVertices_no1() {
    Graph* graph = createGraph(0);
    assert(graph == NULL);
    printf("TestCreateGraph_ZeroVertices_no1\n");
}

void TestCreateGraph_NegativeVertices_no2() {
    Graph* graph = createGraph(-5);
    assert(graph == NULL);
    printf("TestCreateGraph_NegativeVertices_no2\n");
}

void TestAddEdge_ValidUndirected_no3() {
    Graph* graph = createGraph(3);
    assert(graph != NULL);

    addEdge(graph, 0, 1);
    assert(hasEdge(graph, 0, 1) == 1);
    assert(hasEdge(graph, 1, 0) == 1);

    destroyGraph(graph);
    printf("TestAddEdge_ValidUndirected_no3\n");
}

void TestAddEdge_MultipleEdges_no4() {
    Graph* graph = createGraph(4);
    assert(graph != NULL);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);

    assert(hasEdge(graph, 0, 1) == 1);
    assert(hasEdge(graph, 0, 2) == 1);
    assert(hasEdge(graph, 1, 3) == 1);
    assert(hasEdge(graph, 2, 3) == 0);

    destroyGraph(graph);
    printf("TestAddEdge_MultipleEdges_no4\n");
}

void TestAddEdge_SelfLoop_no5() {
    Graph* graph = createGraph(3);
    assert(graph != NULL);

    addEdge(graph, 1, 1);
    assert(hasEdge(graph, 1, 1) == 1);
    assert(hasEdge(graph, 0, 0) == 0);

    destroyGraph(graph);
    printf("TestAddEdge_SelfLoop_no5\n");
}

void TestAddEdge_OutOfBoundsVertices_no6() {
    Graph* graph = createGraph(3);
    assert(graph != NULL);

    addEdge(graph, -1, 2);
    addEdge(graph, 0, 5);
    addEdge(graph, 10, 10);

    assert(hasEdge(graph, -1, 2) == 0);
    assert(hasEdge(graph, 0, 5) == 0);
    assert(hasEdge(graph, 10, 10) == 0);

    addEdge(graph, 0, 2);
    assert(hasEdge(graph, 0, 2) == 1);

    destroyGraph(graph);
    printf("TestAddEdge_OutOfBoundsVertices_no6\n");
}

void TestAddEdge_BoundaryVertices_no7() {
    Graph* graph = createGraph(5);
    assert(graph != NULL);

    addEdge(graph, 0, 4);
    addEdge(graph, 0, 0);

    assert(hasEdge(graph, 0, 4) == 1);
    assert(hasEdge(graph, 4, 0) == 1);
    assert(hasEdge(graph, 0, 0) == 1);

    destroyGraph(graph);
    printf("TestAddEdge_BoundaryVertices_no7\n");
}

void TestReadGraphFromFile_ValidFile_no8() {
    FILE* file = fopen("test_valid.txt", "w");
    assert(file != NULL);
    fprintf(file, "0 1 2\n1 0 3\n2 0 3\n3 1 2\n");
    fclose(file);

    Graph* graph = readGraphFromFile("test_valid.txt");
    assert(graph != NULL);
    assert(getVertexCount(graph) == 4);
    assert(hasEdge(graph, 0, 1) == 1);
    assert(hasEdge(graph, 2, 3) == 1);

    destroyGraph(graph);
    remove("test_valid.txt");
    printf("TestReadGraphFromFile_ValidFile_no8\n");
}

void TestReadGraphFromFile_SingleVertexFile_no9() {
    FILE* file = fopen("test_single.txt", "w");
    assert(file != NULL);
    fprintf(file, "0\n");
    fclose(file);

    Graph* graph = readGraphFromFile("test_single.txt");
    assert(graph != NULL);
    assert(getVertexCount(graph) == 1);
    assert(hasEdge(graph, 0, 0) == 0);

    destroyGraph(graph);
    remove("test_single.txt");
    printf("TestReadGraphFromFile_SingleVertexFile_no9\n");
}

void TestGraph_CompleteGraph_no10() {
    Graph* graph = createGraph(3);
    assert(graph != NULL);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i != j) {
                addEdge(graph, i, j);
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i != j) {
                assert(hasEdge(graph, i, j) == 1);
            }
        }
    }

    destroyGraph(graph);
    printf("TestGraph_CompleteGraph_no10\n");
}

void TestGraph_IsolatedVertices_no11() {
    Graph* graph = createGraph(4);
    assert(graph != NULL);

    addEdge(graph, 0, 1);

    assert(hasEdge(graph, 0, 1) == 1);
    assert(hasEdge(graph, 2, 3) == 0);
    assert(hasEdge(graph, 2, 0) == 0);
    assert(hasEdge(graph, 3, 1) == 0);

    destroyGraph(graph);
    printf("TestGraph_IsolatedVertices_no11\n");
}

void TestGraph_DuplicateEdges_no12() {
    Graph* graph = createGraph(3);
    assert(graph != NULL);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 0);

    assert(hasEdge(graph, 0, 1) == 1);
    assert(hasEdge(graph, 1, 0) == 1);

    destroyGraph(graph);
    printf("TestGraph_DuplicateEdges_no12\n");
}

int main() {
    printf("Unit Tests for Graph Adjacency Matrix Library\n");
    printf("=============================================\n\n");

    int test_count = 0;

    TestCreateGraph_ZeroVertices_no1(); test_count++;
    TestCreateGraph_NegativeVertices_no2(); test_count++;
    TestAddEdge_ValidUndirected_no3(); test_count++;
    TestAddEdge_MultipleEdges_no4(); test_count++;
    TestAddEdge_SelfLoop_no5(); test_count++;
    TestAddEdge_OutOfBoundsVertices_no6(); test_count++;
    TestAddEdge_BoundaryVertices_no7(); test_count++;
    TestReadGraphFromFile_ValidFile_no8(); test_count++;
    TestReadGraphFromFile_SingleVertexFile_no9(); test_count++;
    TestGraph_CompleteGraph_no10(); test_count++;
    TestGraph_IsolatedVertices_no11(); test_count++;
    TestGraph_DuplicateEdges_no12();
    printf("\n");

    printf("All %d tests passed successfully!\n", test_count);
    return 0;
}