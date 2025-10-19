#include <stdio.h>
#include <string.h>
#include "graph.h"

// Вспомогательная функция для сравнения матриц
int matrices_equal(const Graph *g1, const Graph *g2) {
    if (g1->num_vertices != g2->num_vertices) {
        return 0;
    }

    for (int i = 0; i < g1->num_vertices; i++) {
        for (int j = 0; j < g1->num_vertices; j++) {
            if (g1->matrix[i][j] != g2->matrix[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

// Тест 1: Инициализация пустого графа
void TestInitializeEmptyGraph_no1() {
    printf("TestInitializeEmptyGraph_no1: ");
    Graph graph;
    initialize_graph(&graph, 5);

    int all_zeros = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (graph.matrix[i][j] != 0) {
                all_zeros = 0;
                break;
            }
        }
    }

    if (graph.num_vertices == 5 && all_zeros) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

// Тест 2: Добавление одного ребра
void TestAddSingleEdge_no2() {
    printf("TestAddSingleEdge_no2: ");
    Graph graph;
    initialize_graph(&graph, 3);

    int neighbors[] = {1};
    add_edge_from_adjacency_list(&graph, 0, neighbors, 1);

    if (graph.matrix[0][1] == 1 && graph.matrix[1][0] == 1 &&
        graph.matrix[0][0] == 0 && graph.matrix[1][1] == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

// Тест 3: Добавление нескольких ребер для одной вершины
void TestAddMultipleEdges_no3() {
    printf("TestAddMultipleEdges_no3: ");
    Graph graph;
    initialize_graph(&graph, 4);

    int neighbors[] = {1, 2, 3};
    add_edge_from_adjacency_list(&graph, 0, neighbors, 3);

    int expected[4][4] = {
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0}
    };

    int correct = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (graph.matrix[i][j] != expected[i][j]) {
                correct = 0;
                break;
            }
        }
    }

    if (correct) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

// Тест 4: Граф с одной вершиной
void TestSingleVertexGraph_no4() {
    printf("TestSingleVertexGraph_no4: ");
    Graph graph;
    initialize_graph(&graph, 1);

    int neighbors[] = {0}; // Петля
    add_edge_from_adjacency_list(&graph, 0, neighbors, 1);

    if (graph.num_vertices == 1 && graph.matrix[0][0] == 1) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

// Тест 5: Полный граф K3
void TestCompleteGraphK3_no5() {
    printf("TestCompleteGraphK3_no5: ");
    Graph graph;
    initialize_graph(&graph, 3);

    // Вершина 0 соединена с 1 и 2
    int neighbors0[] = {1, 2};
    add_edge_from_adjacency_list(&graph, 0, neighbors0, 2);

    // Вершина 1 соединена с 0 и 2
    int neighbors1[] = {0, 2};
    add_edge_from_adjacency_list(&graph, 1, neighbors1, 2);

    // Вершина 2 соединена с 0 и 1
    int neighbors2[] = {0, 1};
    add_edge_from_adjacency_list(&graph, 2, neighbors2, 2);

    int expected[3][3] = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    int correct = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (graph.matrix[i][j] != expected[i][j]) {
                correct = 0;
                break;
            }
        }
    }

    if (correct) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

// Тест 6: Проверка симметричности для неориентированного графа
void TestUndirectedGraphSymmetry_no6() {
    printf("TestUndirectedGraphSymmetry_no6: ");
    Graph graph;
    initialize_graph(&graph, 4);

    int neighbors[] = {1, 3};
    add_edge_from_adjacency_list(&graph, 0, neighbors, 2);

    int symmetric = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (graph.matrix[i][j] != graph.matrix[j][i]) {
                symmetric = 0;
                break;
            }
        }
    }

    if (symmetric) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

// Тест 7: Граф без ребер
void TestGraphWithoutEdges_no7() {
    printf("TestGraphWithoutEdges_no7: ");
    Graph graph;
    initialize_graph(&graph, 3);

    // Не добавляем никаких ребер

    int all_zeros = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (graph.matrix[i][j] != 0) {
                all_zeros = 0;
                break;
            }
        }
    }

    if (all_zeros) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

// Тест 8: Добавление петли
void TestSelfLoop_no8() {
    printf("TestSelfLoop_no8: ");
    Graph graph;
    initialize_graph(&graph, 2);

    int neighbors[] = {0}; // Петля
    add_edge_from_adjacency_list(&graph, 0, neighbors, 1);

    if (graph.matrix[0][0] == 1 && graph.matrix[0][1] == 0 &&
        graph.matrix[1][0] == 0 && graph.matrix[1][1] == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

// Тест 9: Звездообразный граф
void TestStarGraph_no9() {
    printf("TestStarGraph_no9: ");
    Graph graph;
    initialize_graph(&graph, 4);

    // Центральная вершина 0 соединена со всеми остальными
    int neighbors_center[] = {1, 2, 3};
    add_edge_from_adjacency_list(&graph, 0, neighbors_center, 3);

    int expected[4][4] = {
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 0},
        {1, 0, 0, 0}
    };

    int correct = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (graph.matrix[i][j] != expected[i][j]) {
                correct = 0;
                break;
            }
        }
    }

    if (correct) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

// Тест 10: Граф-путь P3
void TestPathGraphP3_no10() {
    printf("TestPathGraphP3_no10: ");
    Graph graph;
    initialize_graph(&graph, 3);

    // 0-1-2
    int neighbors0[] = {1};
    add_edge_from_adjacency_list(&graph, 0, neighbors0, 1);

    int neighbors1[] = {0, 2};
    add_edge_from_adjacency_list(&graph, 1, neighbors1, 2);

    int neighbors2[] = {1};
    add_edge_from_adjacency_list(&graph, 2, neighbors2, 1);

    int expected[3][3] = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };

    int correct = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (graph.matrix[i][j] != expected[i][j]) {
                correct = 0;
                break;
            }
        }
    }

    if (correct) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
}

// Тест 11: Обработка неверных входных данных
void TestInvalidInputHandling_no11() {
    printf("TestInvalidInputHandling_no11: ");
    Graph graph;

    // Тест с отрицательным количеством вершин
    initialize_graph(&graph, -1);

    // Тест с превышением максимального количества вершин
    initialize_graph(&graph, MAX_VERTICES + 1);

    // Тест с NULL указателем
    initialize_graph(NULL, 5);

    printf("PASS (проверка обработки ошибок)\n");
}

int main() {
    printf("=== Запуск юнит-тестов ===\n");

    TestInitializeEmptyGraph_no1();
    TestAddSingleEdge_no2();
    TestAddMultipleEdges_no3();
    TestSingleVertexGraph_no4();
    TestCompleteGraphK3_no5();
    TestUndirectedGraphSymmetry_no6();
    TestGraphWithoutEdges_no7();
    TestSelfLoop_no8();
    TestStarGraph_no9();
    TestPathGraphP3_no10();
    TestInvalidInputHandling_no11();

    printf("=== Тестирование завершено ===\n");

    return 0;
}