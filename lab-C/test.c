#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Вспомогательная функция для проверки матрицы */
int matrices_equal(int** m1, int** m2, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (m1[i][j] != m2[i][j])
                return 0;
    return 1;
}


void TestGraphCreateEmpty_no1() {
    Graph* g = graph_create(0);
    assert(g != NULL);
    assert(g->vertexCount == 0);
    graph_destroy(g);
    printf("Тест 1 пройден: Создание пустого графа\n");
}

void TestGraphCreateSingleVertex_no2() {
    Graph* g = graph_create(1);
    assert(g != NULL);
    assert(g->vertexCount == 1);
    assert(g->adjacencyLists[0] == NULL);
    graph_destroy(g);
    printf("Тест 2 пройден: Создание графа с одной вершиной\n");
}

void TestGraphAddEdgeSimple_no3() {
    Graph* g = graph_create(2);
    assert(graph_add_edge(g, 0, 1) == 1);
    assert(g->adjacencyLists[0]->toVertex == 1);
    assert(g->adjacencyLists[0]->next == NULL);
    graph_destroy(g);
    printf("Тест 3 пройден: Добавление одного ребра\n");
}

void TestGraphAddEdgeDuplicate_no4() {
    Graph* g = graph_create(2);
    graph_add_edge(g, 0, 1);
    assert(graph_add_edge(g, 0, 1) == 0);
    graph_destroy(g);
    printf("Тест 4 пройден: Добавление дубликата ребра\n");
}

void TestGraphAddEdgeInvalidIndices_no5() {
    Graph* g = graph_create(3);
    assert(graph_add_edge(g, -1, 0) == 0);
    assert(graph_add_edge(g, 0, 5) == 0);
    assert(graph_add_edge(g, 3, 1) == 0);
    graph_destroy(g);
    printf("Тест 5 пройден: Добавление ребра с неверными индексами\n");
}

void TestGraphMatrixEmpty_no6() {
    Graph* g = graph_create(2);
    int** m = graph_to_matrix(g);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            assert(m[i][j] == 0);
    matrix_destroy(m, 2);
    graph_destroy(g);
    printf("Тест 6 пройден: Матрица пустого графа\n");
}

void TestGraphMatrixSingleEdge_no7() {
    Graph* g = graph_create(2);
    graph_add_edge(g, 0, 1);
    int** m = graph_to_matrix(g);
    assert(m[0][1] == 1);
    assert(m[1][0] == 0);
    matrix_destroy(m, 2);
    graph_destroy(g);
    printf("Тест 7 пройден: Матрица графа с одним ребром\n");
}

void TestGraphMatrixSelfLoop_no8() {
    Graph* g = graph_create(1);
    graph_add_edge(g, 0, 0);
    int** m = graph_to_matrix(g);
    assert(m[0][0] == 1);
    matrix_destroy(m, 1);
    graph_destroy(g);
    printf("Тест 8 пройден: Матрица графа с петлей\n");
}

void TestGraphMatrixCompleteK3_no9() {
    Graph* g = graph_create(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (i != j) graph_add_edge(g, i, j);

    int** m = graph_to_matrix(g);
    int expected[3][3] = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            assert(m[i][j] == expected[i][j]);

    matrix_destroy(m, 3);
    graph_destroy(g);
    printf("Тест 9 пройден: Полная матрица K3\n");
}

void TestGraphDestroyEmpty_no10() {
    Graph* g = graph_create(0);
    graph_destroy(g); // проверка, что функция не ломается
    printf("Тест 10 пройден: Уничтожение пустого графа\n");
}

void TestGraphMatrixIsolated_no11() {
    Graph* g = graph_create(4);
    int** m = graph_to_matrix(g);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            assert(m[i][j] == 0);
    matrix_destroy(m, 4);
    graph_destroy(g);
    printf("Тест 11 пройден: Изолированные вершины\n");
}

void TestGraphMatrixNull_no12() {
    assert(graph_to_matrix(NULL) == NULL);
    printf("Тест 12 пройден: Матрица для NULL-графа\n");
}


int main() {
    printf("Запуск юнит-тестов...\n\n");

    TestGraphCreateEmpty_no1();
    TestGraphCreateSingleVertex_no2();
    TestGraphAddEdgeSimple_no3();
    TestGraphAddEdgeDuplicate_no4();
    TestGraphAddEdgeInvalidIndices_no5();
    TestGraphMatrixEmpty_no6();
    TestGraphMatrixSingleEdge_no7();
    TestGraphMatrixSelfLoop_no8();
    TestGraphMatrixCompleteK3_no9();
    TestGraphDestroyEmpty_no10();
    TestGraphMatrixIsolated_no11();
    TestGraphMatrixNull_no12();

    printf("\nВсе тесты пройдены успешно!\n");
    return 0;
}
