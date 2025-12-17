#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Lab-D.h"

void TestGraphBoundaryCases_no1() {
    Graph* TestGraph1 = CreateGraph(0, 0);
    assert(TestGraph1 == NULL);

    Graph* TestGraph2 = CreateGraph(1000, 5);
    assert(TestGraph2 == NULL);

    Graph* TestGraph3 = CreateGraph(5, -7);
    assert(TestGraph3 == NULL);

    Graph* TestGraph4 = CreateGraph(5, 10);
    assert(TestGraph4 != NULL);
    DestroyGraph(TestGraph4);
    printf("Test 1 PASSED\n");
}

void TestGraphMemory_no2() {
    Graph* TestGraph = CreateGraph(10, 15);
    assert(TestGraph != NULL);
    assert(TestGraph->vertice == 10);
    assert(TestGraph->edge == 15);

    DestroyGraph(TestGraph);
    printf("Test 2 PASSED\n");
}

void TestReadGraph_no3() {
    FILE* file = fopen("test_input.txt", "w");
    assert(file != NULL);
    fprintf(file, "5 6\n");
    fprintf(file, "1 2\n");
    fprintf(file, "1 3\n");
    fprintf(file, "2 3\n");
    fprintf(file, "2 4\n");
    fprintf(file, "3 4\n");
    fprintf(file, "4 5\n");
    fclose(file);

    Graph* graph = ReadGraph("test_input.txt", NULL, 3);
    assert(graph != NULL);
    assert(graph->vertice == 5);
    assert(graph->edge == 6);

    Graph* graph2 = ReadGraph("nonexistent.txt", NULL, 3);
    assert(graph2 == NULL);

    DestroyGraph(graph);
    remove("test_input.txt");
    printf("Test 3 PASSED\n");
}

void TestWriteGraph_no4() {
    Graph* graph = CreateGraph(5, 6);
    assert(graph != NULL);

    WriteGraph("test_output.txt", graph, 3);
    FILE* file = fopen("test_output.txt", "r");
    assert(file != NULL);
    fclose(file);

    WriteGraph("test_invalid.txt", NULL, 3);
    WriteGraph("test_invalid2.txt", graph, 0);
    WriteGraph("test_invalid3.txt", graph, 10);

    DestroyGraph(graph);
    remove("test_output.txt");
    printf("Test 4 PASSED\n");
}

void TestCountEdges_no5() {
    Graph* graph = CreateGraph(5, 0);
    assert(graph != NULL);

    graph->adjacency = (int**)calloc(5, sizeof(int*));
    for (int i = 0; i < 5; i++) {
        graph->adjacency[i] = (int*)calloc(5, sizeof(int));
    }

    //add edges
    graph->adjacency[0][1] = 1;
    graph->adjacency[1][0] = 1;
    graph->adjacency[1][2] = 1;
    graph->adjacency[2][1] = 1;

    int edge_count = CountEdges(graph);
    assert(edge_count == 2); // (0,1), (1,2)

    for (int i = 0; i < 5; i++) {
        free(graph->adjacency[i]);
    }
    free(graph->adjacency);
    DestroyGraph(graph);

    edge_count = CountEdges(NULL);
    assert(edge_count == 0);
    printf("Test 5 PASSED\n");
}

void TestGetEdges_no6() {
    Graph* graph = CreateGraph(4, 0);
    assert(graph != NULL);

    graph->adjacency = (int**)calloc(4, sizeof(int*));
    for (int i = 0; i < 4; i++) {
        graph->adjacency[i] = (int*)calloc(4, sizeof(int));
    }

    graph->adjacency[0][1] = 1; graph->adjacency[1][0] = 1;
    graph->adjacency[0][2] = 1; graph->adjacency[2][0] = 1;
    graph->adjacency[1][3] = 1; graph->adjacency[3][1] = 1;

    int edges_u[10], edges_v[10];
    int edge_count = 0;

    GetEdges(graph, edges_u, edges_v, &edge_count);
    assert(edge_count == 3);

    int found_01 = 0, found_02 = 0, found_13 = 0;
    for (int i = 0; i < edge_count; i++) {
        if ((edges_u[i] == 0 && edges_v[i] == 1) || (edges_u[i] == 1 && edges_v[i] == 0)) found_01 = 1;
        if ((edges_u[i] == 0 && edges_v[i] == 2) || (edges_u[i] == 2 && edges_v[i] == 0)) found_02 = 1;
        if ((edges_u[i] == 1 && edges_v[i] == 3) || (edges_u[i] == 3 && edges_v[i] == 1)) found_13 = 1;
    }
    assert(found_01 && found_02 && found_13);

    for (int i = 0; i < 4; i++) {
        free(graph->adjacency[i]);
    }
    free(graph->adjacency);
    DestroyGraph(graph);
    printf("Test 6 PASSED\n");
}

void TestCheckVertexCover_no7() {
    Graph* graph = CreateGraph(3, 0); //Triangle
    assert(graph != NULL);

    graph->adjacency = (int**)calloc(3, sizeof(int*));
    for (int i = 0; i < 3; i++) {
        graph->adjacency[i] = (int*)calloc(3, sizeof(int));
    }

    graph->adjacency[0][1] = 1; graph->adjacency[1][0] = 1;
    graph->adjacency[1][2] = 1; graph->adjacency[2][1] = 1;
    graph->adjacency[0][2] = 1; graph->adjacency[2][0] = 1;

    bool result = CheckVertexCover(graph, 2);
    assert(result == true);

    result = CheckVertexCover(graph, 1);
    assert(result == false);

    for (int i = 0; i < 3; i++) {
        free(graph->adjacency[i]);
    }
    free(graph->adjacency);
    DestroyGraph(graph);
    printf("Test 7 PASSED\n");
}

void TestFindVertexCover_no8() {
    Graph* graph = CreateGraph(5, 0);
    assert(graph != NULL);

    graph->adjacency = (int**)calloc(5, sizeof(int*));
    for (int i = 0; i < 5; i++) {
        graph->adjacency[i] = (int*)calloc(5, sizeof(int));
    }

    graph->adjacency[0][1] = 1; graph->adjacency[1][0] = 1;
    graph->adjacency[1][2] = 1; graph->adjacency[2][1] = 1;
    graph->adjacency[2][3] = 1; graph->adjacency[3][2] = 1;
    graph->adjacency[3][4] = 1; graph->adjacency[4][3] = 1;

    int cover[10];
    int cover_size = 0;

    FindVertexCover(graph, 3, cover, &cover_size);
    assert(cover_size <= 3);

    for (int i = 0; i < 5; i++) {
        free(graph->adjacency[i]);
    }
    free(graph->adjacency);
    DestroyGraph(graph);
    printf("Test 8 PASSED\n");
}

void TestRemoveIncidentEdges_no9() {
    Graph* graph = CreateGraph(4, 0);
    assert(graph != NULL);

    graph->adjacency = (int**)calloc(4, sizeof(int*));
    for (int i = 0; i < 4; i++) {
        graph->adjacency[i] = (int*)calloc(4, sizeof(int));
    }

    graph->adjacency[0][1] = 1; graph->adjacency[1][0] = 1;
    graph->adjacency[0][2] = 1; graph->adjacency[2][0] = 1;
    graph->adjacency[1][3] = 1; graph->adjacency[3][1] = 1;
    graph->adjacency[2][3] = 1; graph->adjacency[3][2] = 1;

    int edges_u[10], edges_v[10];
    int edge_count = 0;

    GetEdges(graph, edges_u, edges_v, &edge_count);
    assert(edge_count == 4);

    RemoveIncidentEdges(graph, 0, edges_u, edges_v, &edge_count);
    assert(edge_count == 2); //stay only (1,3) и (2,3)

    int has_edge_01 = 0, has_edge_02 = 0;
    for (int i = 0; i < edge_count; i++) {
        if ((edges_u[i] == 0 && edges_v[i] == 1) || (edges_u[i] == 1 && edges_v[i] == 0)) has_edge_01 = 1;
        if ((edges_u[i] == 0 && edges_v[i] == 2) || (edges_u[i] == 2 && edges_v[i] == 0)) has_edge_02 = 1;
    }
    assert(has_edge_01 == 0 && has_edge_02 == 0);

    for (int i = 0; i < 4; i++) {
        free(graph->adjacency[i]);
    }
    free(graph->adjacency);
    DestroyGraph(graph);
    printf("Test 9 PASSED\n");
}

void TestIsCoverValid_no10() {
    Graph* graph = CreateGraph(4, 0);
    assert(graph != NULL);

    graph->adjacency = (int**)calloc(4, sizeof(int*));
    for (int i = 0; i < 4; i++) {
        graph->adjacency[i] = (int*)calloc(4, sizeof(int));
    }

    //Square
    graph->adjacency[0][1] = 1; graph->adjacency[1][0] = 1;
    graph->adjacency[1][2] = 1; graph->adjacency[2][1] = 1;
    graph->adjacency[2][3] = 1; graph->adjacency[3][2] = 1;
    graph->adjacency[3][0] = 1; graph->adjacency[0][3] = 1;

    int cover1[] = { 0, 2 };
    bool valid1 = IsCoverValid(graph, cover1, 2);
    assert(valid1 == true);

    int cover2[] = { 0 };
    bool valid2 = IsCoverValid(graph, cover2, 1);
    assert(valid2 == false);

    int cover3[] = { 0, 1 };
    bool valid3 = IsCoverValid(graph, cover3, 2);
    assert(valid3 == false);

    for (int i = 0; i < 4; i++) {
        free(graph->adjacency[i]);
    }
    free(graph->adjacency);
    DestroyGraph(graph);

    bool valid4 = IsCoverValid(NULL, NULL, 0);
    assert(valid4 == false);
    printf("Test 10 PASSED\n");
}

void TestDestroyGraph_no11() {
    Graph* graph = CreateGraph(10, 15);
    assert(graph != NULL);
    DestroyGraph(graph);
    DestroyGraph(NULL);

    graph = CreateGraph(5, 0);
    graph->adjacency = (int**)calloc(5, sizeof(int*));
    for (int i = 0; i < 5; i++) {
        graph->adjacency[i] = (int*)calloc(5, sizeof(int));
    }
    DestroyGraph(graph);
    printf("Test 11 PASSED\n");
}

void TestEmptyVertexCover_no12() {
    //Case 1: Graph without edges
    Graph* graph1 = CreateGraph(5, 0);
    assert(graph1 != NULL);

    graph1->adjacency = (int**)calloc(5, sizeof(int*));
    for (int i = 0; i < 5; i++) {
        graph1->adjacency[i] = (int*)calloc(5, sizeof(int));
    }

    bool result1 = CheckVertexCover(graph1, 0);
    assert(result1 == true);

    bool result2 = CheckVertexCover(graph1, 1);
    assert(result2 == true);

    DestroyGraph(graph1);

    //Case 2: Graph with one edge, K=0
    Graph* graph2 = CreateGraph(2, 0);
    assert(graph2 != NULL);

    graph2->adjacency = (int**)calloc(2, sizeof(int*));
    for (int i = 0; i < 2; i++) {
        graph2->adjacency[i] = (int*)calloc(2, sizeof(int));
    }

    graph2->adjacency[0][1] = 1;
    graph2->adjacency[1][0] = 1;

    bool result3 = CheckVertexCover(graph2, 0);
    assert(result3 == false);

    bool result4 = CheckVertexCover(graph2, 1);
    assert(result4 == true);
    DestroyGraph(graph2);

    //Case 3: Triangle graph, finding minimal K
    Graph* graph3 = CreateGraph(3, 0);
    assert(graph3 != NULL);

    graph3->adjacency = (int**)calloc(3, sizeof(int*));
    for (int i = 0; i < 3; i++) {
        graph3->adjacency[i] = (int*)calloc(3, sizeof(int));
    }

    graph3->adjacency[0][1] = 1; graph3->adjacency[1][0] = 1;
    graph3->adjacency[1][2] = 1; graph3->adjacency[2][1] = 1;
    graph3->adjacency[0][2] = 1; graph3->adjacency[2][0] = 1;

    assert(CheckVertexCover(graph3, 0) == false);
    assert(CheckVertexCover(graph3, 1) == false);
    assert(CheckVertexCover(graph3, 2) == true);
    assert(CheckVertexCover(graph3, 3) == true);

    //Case 4: FindVertexCover with K=0
    int cover[10];
    int cover_size = 0;

    FindVertexCover(graph3, 0, cover, &cover_size);
    assert(cover_size == 0);

    //Case 5: IsCoverValid for empty cover
    bool valid_empty = IsCoverValid(graph3, NULL, 0);
    assert(valid_empty == false);

    int empty_cover[1] = { 0 };
    bool valid_empty2 = IsCoverValid(graph3, empty_cover, 0);
    assert(valid_empty2 == false);

    Graph* empty_graph = CreateGraph(5, 0);
    empty_graph->adjacency = (int**)calloc(5, sizeof(int*));
    for (int i = 0; i < 5; i++) {
        empty_graph->adjacency[i] = (int*)calloc(5, sizeof(int));
    }

    bool valid_empty3 = IsCoverValid(empty_graph, empty_cover, 0);
    assert(valid_empty3 == true);

    DestroyGraph(empty_graph);
    DestroyGraph(graph3);
    printf("Test 12 PASSED\n");
}

int main() {
    TestGraphBoundaryCases_no1();
    TestGraphMemory_no2();
    TestReadGraph_no3();
    TestWriteGraph_no4();
    TestCountEdges_no5();
    TestGetEdges_no6();
    TestCheckVertexCover_no7();
    TestFindVertexCover_no8();
    TestRemoveIncidentEdges_no9();
    TestIsCoverValid_no10();
    TestDestroyGraph_no11();
    TestEmptyVertexCover_no12();

    return 0;
}