#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph_coloring.h"

// Всомогательный static функции
// Создание графа
static Graph* createTestGraph(int n) {
    return createGraph(n);
}

// Добавление неориентированного ребра u - v
static void addEdge(Graph* g, int u, int v) {
    g->adj[u][v] = true;
    g->adj[v][u] = true;
}

// Удаление графа
static void destroyTestGraph(Graph* g) {
    freeGraph(g);
}


void TestEmptyGraph_K1_ReturnTrue_no1() {
    Graph* g = createTestGraph(5);
    int colors[5] = {0};
    bool result = graphColoring(g, 1, colors);
    assert(result == true);
    // все вершины должны получить цвет 1
    for (int i = 0; i < 5; ++i) {
        assert(colors[i] == 1);
    }
    destroyTestGraph(g);
}

void TestTwoVerticesEdge_K1_ReturnFalse_no2() {
    Graph* g = createTestGraph(2);
    addEdge(g, 0, 1);
    int colors[2] = {0};
    bool result = graphColoring(g, 1, colors);
    assert(result == false);   // раскраски нет
    destroyTestGraph(g);
}

void TestTwoVerticesEdge_K2_ReturnTrueValidColors_no3() {
    Graph* g = createTestGraph(2);
    addEdge(g, 0, 1);
    int colors[2] = {0};
    bool result = graphColoring(g, 2, colors);
    assert(result == true);
    assert(colors[0] != colors[1]);
    assert(colors[0] >= 1 && colors[0] <= 2);
    assert(colors[1] >= 1 && colors[1] <= 2);
    destroyTestGraph(g);
}

void TestTriangle_K2_ReturnFalse_no4() {
    Graph* g = createTestGraph(3);
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    int colors[3] = {0};
    bool result = graphColoring(g, 2, colors);
    assert(result == false);
    destroyTestGraph(g);
}

void TestTriangle_K3_ReturnTrue_no5() {
    Graph* g = createTestGraph(3);
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    int colors[3] = {0};
    bool result = graphColoring(g, 3, colors);
    assert(result == true);
    for (int i = 0; i < 3; ++i)
        for (int j = i+1; j < 3; ++j)
            if (g->adj[i][j])
                assert(colors[i] != colors[j]);
    destroyTestGraph(g);
}

void TestSquareCycle_K2_ReturnTrue_no6() {
    Graph* g = createTestGraph(4);
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 3);
    addEdge(g, 3, 0);
    int colors[4] = {0};
    bool result = graphColoring(g, 2, colors);
    assert(result == true);
    for (int i = 0; i < 4; ++i) {
        if (g->adj[i][(i+1)%4])
            assert(colors[i] != colors[(i+1)%4]);
    }
    destroyTestGraph(g);
}

void TestStar_K2_ReturnTrue_no7() {
    Graph* g = createTestGraph(4);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 0, 3);
    int colors[4] = {0};
    bool result = graphColoring(g, 2, colors);
    assert(result == true);
    assert(colors[1] == colors[2] && colors[2] == colors[3]);
    assert(colors[0] != colors[1]);
    destroyTestGraph(g);
}

void TestK4_K3_ReturnFalse_no8() {
    Graph* g = createTestGraph(4);
    for (int i = 0; i < 4; ++i)
        for (int j = i+1; j < 4; ++j)
            addEdge(g, i, j);
    int colors[4] = {0};
    bool result = graphColoring(g, 3, colors);
    assert(result == false);
    destroyTestGraph(g);
}

void TestK4_K4_ReturnTrue_no9() {
    Graph* g = createTestGraph(4);
    for (int i = 0; i < 4; ++i)
        for (int j = i+1; j < 4; ++j)
            addEdge(g, i, j);
    int colors[4] = {0};
    bool result = graphColoring(g, 4, colors);
    assert(result == true);
    for (int i = 0; i < 4; ++i)
        for (int j = i+1; j < 4; ++j)
            assert(colors[i] != colors[j]);
    destroyTestGraph(g);
}

void TestSingleVertex_K1_ReturnTrue_no10() {
    Graph* g = createTestGraph(1);
    int colors[1] = {0};
    bool result = graphColoring(g, 1, colors);
    assert(result == true);
    assert(colors[0] == 1);
    destroyTestGraph(g);
}


void TestSingleVertex_K3_ReturnTrue_no11() {
    Graph* g = createTestGraph(1);
    int colors[1] = {0};
    bool result = graphColoring(g, 3, colors);
    assert(result == true);
    assert(colors[0] == 1);
    destroyTestGraph(g);
}

void TestTrianglePlusIsolated_K3_ReturnTrue_no12() {
    Graph* g = createTestGraph(4);
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    // вершина 3 изолирована
    int colors[4] = {0};
    bool result = graphColoring(g, 3, colors);
    assert(result == true);
    assert(colors[0] != colors[1] && colors[1] != colors[2] && colors[2] != colors[0]);
    assert(colors[3] >= 1 && colors[3] <= 3);
    destroyTestGraph(g);
}

int main() {
    TestEmptyGraph_K1_ReturnTrue_no1();
    TestTwoVerticesEdge_K1_ReturnFalse_no2();
    TestTwoVerticesEdge_K2_ReturnTrueValidColors_no3();
    TestTriangle_K2_ReturnFalse_no4();
    TestTriangle_K3_ReturnTrue_no5();
    TestSquareCycle_K2_ReturnTrue_no6();
    TestStar_K2_ReturnTrue_no7();
    TestK4_K3_ReturnFalse_no8();
    TestK4_K4_ReturnTrue_no9();
    TestSingleVertex_K1_ReturnTrue_no10();
    TestSingleVertex_K3_ReturnTrue_no11();
    TestTrianglePlusIsolated_K3_ReturnTrue_no12();

    printf("All tests passed successfully!\n");
    return 0;    
}