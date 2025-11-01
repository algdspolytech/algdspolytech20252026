#include "func.h"
#include <assert.h>
#include <stdio.h>

// Вспомогательная функция для проверки матрицы
int matricesEqual(int** matrix1, int** matrix2, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// Тест 1: Создание узла
void TestCreateNode_ValidVertex_no1() {
    struct Node* node = create_node(5);
    assert(node != NULL);
    assert(node->vertex == 5);
    assert(node->next == NULL);
    free(node);
    printf("Test 1 passed: CreateNode with valid vertex\n");
}

// Тест 2: Создание графа с нулевым количеством вершин
void TestCreateGraph_ZeroVertices_no2() {
    struct Graph* graph = create_graph(0);
    assert(graph != NULL);
    assert(graph->numVertices == 0);
    assert(graph->node_list != NULL);
    freeGraph(graph);
    printf("Test 2 passed: CreateGraph with zero vertices\n");
}

// Тест 3: Создание графа с одним vertices
void TestCreateGraph_SingleVertex_no3() {
    struct Graph* graph = create_graph(1);
    assert(graph != NULL);
    assert(graph->numVertices == 1);
    assert(graph->node_list[0] == NULL);
    freeGraph(graph);
    printf("Test 3 passed: CreateGraph with single vertex\n");
}

// Тест 4: Добавление ребра в пустой граф
void TestAddEdge_ToEmptyGraph_no4() {
    struct Graph* graph = create_graph(3);
    addEdge(graph, 0, 1);
    
    assert(graph->node_list[0] != NULL);
    assert(graph->node_list[0]->vertex == 1);
    assert(graph->node_list[0]->next == NULL);
    assert(graph->node_list[1] == NULL);
    assert(graph->node_list[2] == NULL);
    
    freeGraph(graph);
    printf("Test 4 passed: AddEdge to empty graph\n");
}

// Тест 5: Добавление нескольких ребер в одну вершину
void TestAddEdge_MultipleEdgesSameVertex_no5() {
    struct Graph* graph = create_graph(3);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    
    assert(graph->node_list[0] != NULL);
    assert(graph->node_list[0]->vertex == 2); // последний добавленный
    assert(graph->node_list[0]->next != NULL);
    assert(graph->node_list[0]->next->vertex == 1); // предыдущий
    
    freeGraph(graph);
    printf("Test 5 passed: Add multiple edges to same vertex\n");
}

// Тест 6: Построение матрицы для пустого графа
void TestBuildAdjacencyMatrix_EmptyGraph_no6() {
    struct Graph* graph = create_graph(2);
    int** matrix = buildAdjacencyMatrix(graph);
    
    assert(matrix != NULL);
    assert(matrix[0][0] == 0);
    assert(matrix[0][1] == 0);
    assert(matrix[1][0] == 0);
    assert(matrix[1][1] == 0);
    
    freeMatrix(matrix, 2);
    freeGraph(graph);
    printf("Test 6 passed: Build matrix for empty graph\n");
}

// Тест 7: Построение матрицы для графа с одним ребром
void TestBuildAdjacencyMatrix_SingleEdge_no7() {
    struct Graph* graph = create_graph(2);
    addEdge(graph, 0, 1);
    int** matrix = buildAdjacencyMatrix(graph);
    
    int expected[2][2] = {{0, 1}, {0, 0}};
    
    assert(matrix != NULL);
    assert(matrix[0][0] == expected[0][0]);
    assert(matrix[0][1] == expected[0][1]);
    assert(matrix[1][0] == expected[1][0]);
    assert(matrix[1][1] == expected[1][1]);
    
    freeMatrix(matrix, 2);
    freeGraph(graph);
    printf("Test 7 passed: Build matrix for graph with single edge\n");
}

// Тест 8: Построение матрицы для полного графа K3
void TestBuildAdjacencyMatrix_CompleteGraphK3_no8() {
    struct Graph* graph = create_graph(3);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 0);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 1);
    
    int** matrix = buildAdjacencyMatrix(graph);
    
    int expected[3][3] = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    
    assert(matrix != NULL);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            assert(matrix[i][j] == expected[i][j]);
        }
    }
    
    freeMatrix(matrix, 3);
    freeGraph(graph);
    printf("Test 8 passed: Build matrix for complete graph K3\n");
}

// Тест 9: Освобождение пустого графа
void TestFreeGraph_EmptyGraph_no9() {
    struct Graph* graph = create_graph(0);
    freeGraph(graph); // Не должно быть ошибок
    printf("Test 9 passed: Free empty graph\n");
}

// Тест 10: Освобождение матрицы нулевого размера
void TestFreeMatrix_ZeroSize_no10() {
    int** matrix = (int**)malloc(0 * sizeof(int*));
    freeMatrix(matrix, 0); // Не должно быть ошибок
    printf("Test 10 passed: Free zero-size matrix\n");
}

// Тест 11: Граф с изолированными вершинами
void TestBuildAdjacencyMatrix_IsolatedVertices_no11() {
    struct Graph* graph = create_graph(4);
    // Никаких ребер не добавляем
    
    int** matrix = buildAdjacencyMatrix(graph);
    
    assert(matrix != NULL);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            assert(matrix[i][j] == 0);
        }
    }
    
    freeMatrix(matrix, 4);
    freeGraph(graph);
    printf("Test 11 passed: Build matrix for graph with isolated vertices\n");
}

// Тест 12: Граф с петлей (ребро в саму себя)
void TestAddEdge_SelfLoop_no12() {
    struct Graph* graph = create_graph(2);
    addEdge(graph, 0, 0); // Петля
    
    int** matrix = buildAdjacencyMatrix(graph);
    
    assert(matrix != NULL);
    assert(matrix[0][0] == 1); // Петля
    assert(matrix[0][1] == 0);
    assert(matrix[1][0] == 0);
    assert(matrix[1][1] == 0);
    
    freeMatrix(matrix, 2);
    freeGraph(graph);
    printf("Test 12 passed: Add self-loop edge\n");
}

// Запуск всех тестов
int main() {
    printf("Starting unit tests...\n\n");
    
    TestCreateNode_ValidVertex_no1();
    TestCreateGraph_ZeroVertices_no2();
    TestCreateGraph_SingleVertex_no3();
    TestAddEdge_ToEmptyGraph_no4();
    TestAddEdge_MultipleEdgesSameVertex_no5();
    TestBuildAdjacencyMatrix_EmptyGraph_no6();
    TestBuildAdjacencyMatrix_SingleEdge_no7();
    TestBuildAdjacencyMatrix_CompleteGraphK3_no8();
    TestFreeGraph_EmptyGraph_no9();
    TestFreeMatrix_ZeroSize_no10();
    TestBuildAdjacencyMatrix_IsolatedVertices_no11();
    TestAddEdge_SelfLoop_no12();
    
    printf("\nAll tests passed!\n");
    return 0;
}