#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// Вспомогательная функция для создания тестового графа
Graph* createTestGraph1() {
    Graph* graph = createGraph(5);
    // Граф: 0-1-2-3-4
    graph->matrix[0][1] = 1;
    graph->matrix[1][0] = 1;
    graph->matrix[1][2] = 1;
    graph->matrix[2][1] = 1;
    graph->matrix[2][3] = 1;
    graph->matrix[3][2] = 1;
    graph->matrix[3][4] = 1;
    graph->matrix[4][3] = 1;
    return graph;
}

Graph* createTestGraph2() {
    Graph* graph = createGraph(4);
    // Полный граф K4
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                graph->matrix[i][j] = 1;
            }
        }
    }
    return graph;
}

Graph* createTestGraph3() {
    Graph* graph = createGraph(6);
    // Граф с двумя компонентами связности
    // Компонента 1: 0-1-2
    graph->matrix[0][1] = 1;
    graph->matrix[1][0] = 1;
    graph->matrix[1][2] = 1;
    graph->matrix[2][1] = 1;
    // Компонента 2: 3-4-5
    graph->matrix[3][4] = 1;
    graph->matrix[4][3] = 1;
    graph->matrix[4][5] = 1;
    graph->matrix[5][4] = 1;
    return graph;
}

// Тест 1: Путь в линейном графе
void TestLinearGraphPath_no1() {
    printf("Test 1: Linear graph path\n");
    Graph* graph = createTestGraph1();
    int pathLength;
    int* path = findShortestPath(graph, 0, 4, &pathLength);

    if (pathLength == 5 && path[0] == 0 && path[4] == 4) {
        printf("PASS: Correct path found\n");
    }
    else {
        printf("FAIL: Incorrect path\n");
    }

    free(path);
    freeGraph(graph);
    printf("---\n");
}

// Тест 2: Путь в полном графе
void TestCompleteGraphPath_no2() {
    printf("Test 2: Complete graph path\n");
    Graph* graph = createTestGraph2();
    int pathLength;
    int* path = findShortestPath(graph, 0, 3, &pathLength);

    if (pathLength == 2 && path[0] == 0 && path[1] == 3) {
        printf("PASS: Direct path found\n");
    }
    else {
        printf("FAIL: Incorrect path\n");
    }

    free(path);
    freeGraph(graph);
    printf("---\n");
}

// Тест 3: Путь в несвязном графе
void TestDisconnectedGraph_no3() {
    printf("Test 3: Disconnected graph\n");
    Graph* graph = createTestGraph3();
    int pathLength;
    int* path = findShortestPath(graph, 0, 5, &pathLength);

    if (path == NULL && pathLength == 0) {
        printf("PASS: No path found as expected\n");
    }
    else {
        printf("FAIL: Path should not exist\n");
    }

    free(path);
    freeGraph(graph);
    printf("---\n");
}

// Тест 4: Путь от вершины к самой себе
void TestSameVertexPath_no4() {
    printf("Test 4: Same vertex path\n");
    Graph* graph = createTestGraph1();
    int pathLength;
    int* path = findShortestPath(graph, 2, 2, &pathLength);

    if (pathLength == 1 && path[0] == 2) {
        printf("PASS: Self-loop path correct\n");
    }
    else {
        printf("FAIL: Self-loop path incorrect\n");
    }

    free(path);
    freeGraph(graph);
    printf("---\n");
}

// Тест 5: Неверные индексы вершин
void TestInvalidVertices_no5() {
    printf("Test 5: Invalid vertices\n");
    Graph* graph = createTestGraph1();
    int pathLength;

    // Отрицательные индексы
    int* path1 = findShortestPath(graph, -1, 2, &pathLength);
    if (path1 == NULL && pathLength == 0) {
        printf("PASS: Negative start vertex handled\n");
    }
    else {
        printf("FAIL: Negative start vertex not handled\n");
    }

    // Индексы больше размера графа
    int* path2 = findShortestPath(graph, 0, 10, &pathLength);
    if (path2 == NULL && pathLength == 0) {
        printf("PASS: Large end vertex handled\n");
    }
    else {
        printf("FAIL: Large end vertex not handled\n");
    }

    freeGraph(graph);
    printf("---\n");
}

// Тест 6: Граф с одним узлом
void TestSingleVertexGraph_no6() {
    printf("Test 6: Single vertex graph\n");
    Graph* graph = createGraph(1);
    int pathLength;
    int* path = findShortestPath(graph, 0, 0, &pathLength);

    if (pathLength == 1 && path[0] == 0) {
        printf("PASS: Single vertex path correct\n");
    }
    else {
        printf("FAIL: Single vertex path incorrect\n");
    }

    free(path);
    freeGraph(graph);
    printf("---\n");
}

// Тест 7: Граф без ребер
void TestGraphWithoutEdges_no7() {
    printf("Test 7: Graph without edges\n");
    Graph* graph = createGraph(3);
    int pathLength;
    int* path = findShortestPath(graph, 0, 2, &pathLength);

    if (path == NULL && pathLength == 0) {
        printf("PASS: No path in graph without edges\n");
    }
    else {
        printf("FAIL: Should not find path in graph without edges\n");
    }

    free(path);
    freeGraph(graph);
    printf("---\n");
}

// Тест 8: Прямое соединение
void TestDirectConnection_no8() {
    printf("Test 8: Direct connection\n");
    Graph* graph = createGraph(3);
    graph->matrix[0][1] = 1;
    graph->matrix[1][0] = 1;
    graph->matrix[1][2] = 1;
    graph->matrix[2][1] = 1;

    int pathLength;
    int* path = findShortestPath(graph, 0, 1, &pathLength);

    if (pathLength == 2 && path[0] == 0 && path[1] == 1) {
        printf("PASS: Direct connection found\n");
    }
    else {
        printf("FAIL: Direct connection not found\n");
    }

    free(path);
    freeGraph(graph);
    printf("---\n");
}

// Тест 9: Альтернативные пути
void TestAlternativePaths_no9() {
    printf("Test 9: Alternative paths\n");
    Graph* graph = createGraph(4);
    // 0-1-2
    //  \   /
    //   3
    graph->matrix[0][1] = 1;
    graph->matrix[1][0] = 1;
    graph->matrix[1][2] = 1;
    graph->matrix[2][1] = 1;
    graph->matrix[0][3] = 1;
    graph->matrix[3][0] = 1;
    graph->matrix[3][2] = 1;
    graph->matrix[2][3] = 1;

    int pathLength;
    int* path = findShortestPath(graph, 0, 2, &pathLength);

    // Должен найти путь 0-1-2 или 0-3-2 (длина 3)
    if (pathLength == 3 && path[0] == 0 && path[2] == 2) {
        printf("PASS: Shortest alternative path found\n");
    }
    else {
        printf("FAIL: Shortest alternative path not found\n");
    }

    free(path);
    freeGraph(graph);
    printf("---\n");
}

// Тест 10: Большой граф
void TestLargeGraph_no10() {
    printf("Test 10: Large graph\n");
    Graph* graph = createGraph(10);
    // Линейный граф 0-1-2-3-4-5-6-7-8-9
    for (int i = 0; i < 9; i++) {
        graph->matrix[i][i + 1] = 1;
        graph->matrix[i + 1][i] = 1;
    }

    int pathLength;
    int* path = findShortestPath(graph, 0, 9, &pathLength);

    if (pathLength == 10 && path[0] == 0 && path[9] == 9) {
        printf("PASS: Path in large graph found\n");
    }
    else {
        printf("FAIL: Path in large graph not found\n");
    }

    free(path);
    freeGraph(graph);
    printf("---\n");
}

int main() {
    printf("Running Graph Tests\n");
    printf("==================\n\n");

    TestLinearGraphPath_no1();
    TestCompleteGraphPath_no2();
    TestDisconnectedGraph_no3();
    TestSameVertexPath_no4();
    TestInvalidVertices_no5();
    TestSingleVertexGraph_no6();
    TestGraphWithoutEdges_no7();
    TestDirectConnection_no8();
    TestAlternativePaths_no9();
    TestLargeGraph_no10();

    printf("All tests completed!\n");
    return 0;
}