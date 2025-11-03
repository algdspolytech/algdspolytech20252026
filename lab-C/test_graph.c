#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int vertex; struct Node* next; } Node;
typedef struct { int vertices; Node** adjLists; } Graph;

Graph* createGraph(int vertices);
void addEdgeList(Graph* graph, int src, int dest);
void freeGraph(Graph* graph);
int** listToMatrix(const Graph* graph);
int compareGraphs(const Graph* listGraph, int** matrixGraph, int size);

int tests_passed = 0;
int tests_failed = 0;

void assert_int(int a, int b, const char* test_name) {
    if (a == b) {
        printf("[PASS] %s\n", test_name);
        tests_passed++;
    } else {
        printf("[FAIL] %s: expected %d, got %d\n", test_name, b, a);
        tests_failed++;
    }
}

// ---------------- TESTS ------------------

// 1. createGraph нормальный граф
void createGraph_NormalVertices_returnNonNull_num1() {
    Graph* g = createGraph(3);
    assert_int(g != NULL, 1, "createGraph_NormalVertices_returnNonNull_num1");
    freeGraph(g);
}

// 2. createGraph количество вершин
void createGraph_NormalVertices_countCorrect_num2() {
    Graph* g = createGraph(3);
    assert_int(g->vertices, 3, "createGraph_NormalVertices_countCorrect_num2");
    freeGraph(g);
}

// 3. createGraph 0 вершин
void createGraph_ZeroVertices_returnNull_num3() {
    Graph* g = createGraph(0);
    assert_int(g == NULL, 1, "createGraph_ZeroVertices_returnNull_num3");
}

// 4. createGraph большой граф
void createGraph_Large_returnNonNull_num4() {
    Graph* g = createGraph(10);
    assert_int(g != NULL, 1, "createGraph_Large_returnNonNull_num4");
    freeGraph(g);
}

// 5. addEdgeList нормальный
void addEdgeList_Normal_returnCorrect_num5() {
    Graph* g = createGraph(2);
    addEdgeList(g, 0, 1);
    assert_int(g->adjLists[0]->vertex, 1, "addEdgeList_Normal_returnCorrect_num5");
    freeGraph(g);
}

// 6. addEdgeList NULL граф
void addEdgeList_NullGraph_returnNoCrash_num6() {
    addEdgeList(NULL, 0, 1);
    assert_int(1, 1, "addEdgeList_NullGraph_returnNoCrash_num6");
}

// 7. listToMatrix одиночное ребро
void listToMatrix_SingleEdge_returnValid_num7() {
    Graph* g = createGraph(2);
    addEdgeList(g, 0, 1);
    int** m = listToMatrix(g);
    assert_int(m[0][1], 1, "listToMatrix_SingleEdge_returnValid_num7");
    for(int i=0;i<2;i++) free(m[i]);
    free(m);
    freeGraph(g);
}

// 8. listToMatrix множественные ребра (ребро 0->1)
void listToMatrix_MultipleEdges_returnEdge01_num8() {
    Graph* g = createGraph(3);
    addEdgeList(g, 0, 1);
    addEdgeList(g, 0, 2);
    int** m = listToMatrix(g);
    assert_int(m[0][1], 1, "listToMatrix_MultipleEdges_returnEdge01_num8");
    for(int i=0;i<3;i++) free(m[i]);
    free(m);
    freeGraph(g);
}

// 9. listToMatrix множественные ребра (ребро 0->2)
void listToMatrix_MultipleEdges_returnEdge02_num9() {
    Graph* g = createGraph(3);
    addEdgeList(g, 0, 1);
    addEdgeList(g, 0, 2);
    int** m = listToMatrix(g);
    assert_int(m[0][2], 1, "listToMatrix_MultipleEdges_returnEdge02_num9");
    for(int i=0;i<3;i++) free(m[i]);
    free(m);
    freeGraph(g);
}

// 10. compareGraphs равные
void compareGraphs_Equal_returnTrue_num10() {
    Graph* g = createGraph(2);
    addEdgeList(g, 0, 1);
    int** m = (int**)malloc(2 * sizeof(int*));
    for(int i=0;i<2;i++) m[i]=(int*)calloc(2,sizeof(int));
    m[0][1] = 1;
    assert_int(compareGraphs(g, m, 2), 1, "compareGraphs_Equal_returnTrue_num10");
    for(int i=0;i<2;i++) free(m[i]);
    free(m);
    freeGraph(g);
}

// ---------------- MAIN ------------------

int main() {
    printf("Running tests...\n");

    createGraph_NormalVertices_returnNonNull_num1();
    createGraph_NormalVertices_countCorrect_num2();
    createGraph_ZeroVertices_returnNull_num3();
    createGraph_Large_returnNonNull_num4();
    addEdgeList_Normal_returnCorrect_num5();
    addEdgeList_NullGraph_returnNoCrash_num6();
    listToMatrix_SingleEdge_returnValid_num7();
    listToMatrix_MultipleEdges_returnEdge01_num8();
    listToMatrix_MultipleEdges_returnEdge02_num9();
    compareGraphs_Equal_returnTrue_num10();

    printf("\nTests passed: %d\nTests failed: %d\n", tests_passed, tests_failed);
    return tests_failed > 0 ? 1 : 0;
}
