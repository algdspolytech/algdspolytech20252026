#include "dfs.h"
#include <assert.h>

void TestPathExistsInConnectedGraph_no1() {
    Graph graph;
    initialize_graph(&graph);

    add_edge(&graph, 0, 1);
    add_edge(&graph, 1, 2);

    assert(path_exists(&graph, 0, 2) == 1);
    printf("Test 1 passed: Path exists in connected graph\n");

    destroy_graph(&graph);
}

void TestNoPathBetweenDisconnectedComponents_no2() {
    Graph graph;
    initialize_graph(&graph);

    add_edge(&graph, 0, 1);
    add_edge(&graph, 2, 3);

    assert(path_exists(&graph, 0, 2) == 0);
    printf("Test 2 passed: No path between disconnected components\n");

    destroy_graph(&graph);
}

void TestPathToSelf_no3() {
    Graph graph;
    initialize_graph(&graph);

    add_edge(&graph, 0, 1);
    add_edge(&graph, 1, 2);

    assert(path_exists(&graph, 0, 0) == 1);
    assert(path_exists(&graph, 1, 1) == 1);
    assert(path_exists(&graph, 2, 2) == 1);
    printf("Test 3 passed: Path to self always exists\n");

    destroy_graph(&graph);
}

void TestLargeGraph_no4() {
    Graph graph;
    initialize_graph(&graph);

    for (int i = 0; i < 19; i++) {
        add_edge(&graph, i, i + 1);
    }

    assert(path_exists(&graph, 0, 19) == 1);
    assert(path_exists(&graph, 0, 10) == 1);
    printf("Test 4 passed: Large graph handled correctly\n");

    destroy_graph(&graph);
}

void TestLargeVertexNumbers_no5() {
    Graph graph;
    initialize_graph(&graph);

    add_edge(&graph, 100, 200);
    add_edge(&graph, 200, 300);

    assert(path_exists(&graph, 100, 300) == 1);
    assert(path_exists(&graph, 100, 500) == 0);
    printf("Test 5 passed: Large vertex numbers handled correctly\n");

    destroy_graph(&graph);
}

void TestInitializedGraphWithoutEdges_no6() {
    Graph graph;
    initialize_graph(&graph);

    assert(path_exists(&graph, 0, 0) == 0);
    assert(path_exists(&graph, 1, 1) == 0);
    printf("Test 6 passed: Initialized graph without edges handled correctly\n");

    destroy_graph(&graph);
}

void TestNegativeVertices_no7() {
    Graph graph;
    initialize_graph(&graph);

    assert(add_edge(&graph, -1, 0) == 0);
    assert(path_exists(&graph, -1, 0) == 0);
    printf("Test 7 passed: Negative vertices handled correctly\n");

    destroy_graph(&graph);
}

void TestMultipleComponents_no8() {
    Graph graph;
    initialize_graph(&graph);

    add_edge(&graph, 0, 1);
    add_edge(&graph, 1, 2);

    add_edge(&graph, 10, 11);
    add_edge(&graph, 11, 12);

    assert(path_exists(&graph, 0, 2) == 1);
    assert(path_exists(&graph, 10, 12) == 1);
    assert(path_exists(&graph, 0, 10) == 0);
    printf("Test 8 passed: Multiple components handled correctly\n");

    destroy_graph(&graph);
}

void TestReadFromFile_no9() {
    Graph graph;

    int result = read_graph_from_file(&graph, "graph.txt");

    if (result) {
        printf("Test 9 passed: Graph read from file successfully\n");
        assert(graph.vertices_count > 0);
    }
    else {
        printf("Test 9 passed: File reading failed gracefully\n");
    }

    destroy_graph(&graph);
}

void TestMemoryCleanup_no10() {
    Graph graph;
    initialize_graph(&graph);

    for (int i = 0; i < 10; i++) {
        add_edge(&graph, i, i + 1);
    }

    destroy_graph(&graph);

    assert(graph.vertices_count == 0);
    assert(graph.capacity == 0);
    assert(graph.adjacency_list == NULL);

    printf("Test 10 passed: Memory cleanup working correctly\n");
}

void TestSingleVertexGraph_no11() {
    Graph graph;
    initialize_graph(&graph);

    graph.vertices_count = 1;

    assert(path_exists(&graph, 0, 0) == 1);
    assert(path_exists(&graph, 0, 1) == 0);
    printf("Test 11 passed: Single vertex graph handled correctly\n");

    destroy_graph(&graph);
}

void TestIsolatedVertices_no12() {
    Graph graph;
    initialize_graph(&graph);

    graph.vertices_count = 5;

    assert(path_exists(&graph, 0, 0) == 1);
    assert(path_exists(&graph, 0, 1) == 0);
    assert(path_exists(&graph, 1, 2) == 0);
    printf("Test 12 passed: Isolated vertices handled correctly\n");

    destroy_graph(&graph);
}

int main() {
    printf("Running Universal DFS tests...\n\n");

    TestPathExistsInConnectedGraph_no1();
    TestNoPathBetweenDisconnectedComponents_no2();
    TestPathToSelf_no3();
    TestLargeGraph_no4();
    TestLargeVertexNumbers_no5();
    TestInitializedGraphWithoutEdges_no6();
    TestNegativeVertices_no7();
    TestMultipleComponents_no8();
    TestReadFromFile_no9();
    TestMemoryCleanup_no10();
    TestSingleVertexGraph_no11();
    TestIsolatedVertices_no12();

    printf("\nAll universal tests passed successfully!\n");
    return 0;
}