#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cov.h"

// Функция для запуска теста и вывода результата
void run_test(const char* test_name, bool condition) {
    if (condition) {
        printf("%s: PASSED\n", test_name);
    }
    else {
        printf("%s: FAILED\n", test_name);
    }
}

// Тест 1: Одно ребро, K=0
void test_single_edge_K0_no1() {
    Graph graph;
    graph.vertices_count = 2;
    graph.edges_count = 1;
    graph.edges[0].u = 0;
    graph.edges[0].v = 1;
    int cover[MAX_VERTICES];
    int cover_size;

    bool result = find_vertex_cover(&graph, 0, cover, &cover_size);
    run_test("SingleEdgeK0_no1", result == false && cover_size == 0);
}

// Тест 2: Путь из 3 вершин, K=1
void test_path_3_vertices_K1_no2() {
    Graph graph;
    graph.vertices_count = 3;
    graph.edges_count = 2;
    graph.edges[0].u = 0; graph.edges[0].v = 1;
    graph.edges[1].u = 1; graph.edges[1].v = 2;
    int cover[MAX_VERTICES];
    int cover_size;

    bool result = find_vertex_cover(&graph, 1, cover, &cover_size);
    run_test("Path3VerticesK1_no2", result == true && cover_size == 1 && cover[0] == 1);
}

// Тест 3: Одно ребро, K=1
void test_single_edge_K1_no3() {
    Graph graph;
    graph.vertices_count = 2;
    graph.edges_count = 1;
    graph.edges[0].u = 0;
    graph.edges[0].v = 1;
    int cover[MAX_VERTICES];
    int cover_size;

    bool result = find_vertex_cover(&graph, 1, cover, &cover_size);
    run_test("SingleEdgeK1_no3", result == true && cover_size == 1);
}

// Тест 4: Треугольник, K=2
void test_triangle_graph_K2_no4() {
    Graph graph;
    graph.vertices_count = 3;
    graph.edges_count = 3;
    graph.edges[0].u = 0; graph.edges[0].v = 1;
    graph.edges[1].u = 1; graph.edges[1].v = 2;
    graph.edges[2].u = 2; graph.edges[2].v = 0;
    int cover[MAX_VERTICES];
    int cover_size;

    bool result = find_vertex_cover(&graph, 2, cover, &cover_size);
    run_test("TriangleGraphK2_no4", result == true && cover_size == 2);
}

// Тест 5: Пустой граф
void test_empty_graph_no5() {
    Graph graph;
    graph.vertices_count = 0;
    graph.edges_count = 0;
    int cover[MAX_VERTICES];
    int cover_size;

    bool result = find_vertex_cover(&graph, 0, cover, &cover_size);
    run_test("EmptyGraph_no5", result == true && cover_size == 0);
}

// Тест 6: Треугольник, K=1
void test_triangle_graph_K1_no6() {
    Graph graph;
    graph.vertices_count = 3;
    graph.edges_count = 3;
    graph.edges[0].u = 0; graph.edges[0].v = 1;
    graph.edges[1].u = 1; graph.edges[1].v = 2;
    graph.edges[2].u = 2; graph.edges[2].v = 0;
    int cover[MAX_VERTICES];
    int cover_size;

    bool result = find_vertex_cover(&graph, 1, cover, &cover_size);
    run_test("TriangleGraphK1_no6", result == false && cover_size == 0);
}

// Тест 7: Два несвязанных ребра, K=2
void test_two_disconnected_edges_K2_no7() {
    Graph graph;
    graph.vertices_count = 4;
    graph.edges_count = 2;
    graph.edges[0].u = 0; graph.edges[0].v = 1;
    graph.edges[1].u = 2; graph.edges[1].v = 3;
    int cover[MAX_VERTICES];
    int cover_size;

    bool result = find_vertex_cover(&graph, 2, cover, &cover_size);
    run_test("TwoDisconnectedEdgesK2_no7", result == true && cover_size == 2);
}

// Тест 8: Одна вершина без ребер
void test_single_vertex_no_edges_no8() {
    Graph graph;
    graph.vertices_count = 1;
    graph.edges_count = 0;
    int cover[MAX_VERTICES];
    int cover_size;

    bool result = find_vertex_cover(&graph, 0, cover, &cover_size);
    run_test("SingleVertexNoEdges_no8", result == true && cover_size == 0);
}

// Тест 9: Звезда с центром, K=1
void test_star_graph_center_K1_no9() {
    Graph graph;
    graph.vertices_count = 4;
    graph.edges_count = 3;
    graph.edges[0].u = 0; graph.edges[0].v = 1;
    graph.edges[1].u = 0; graph.edges[1].v = 2;
    graph.edges[2].u = 0; graph.edges[2].v = 3;
    int cover[MAX_VERTICES];
    int cover_size;

    bool result = find_vertex_cover(&graph, 1, cover, &cover_size);
    run_test("StarGraphCenterK1_no9", result == true && cover_size == 1 && cover[0] == 0);
}

// Тест 10: Изолированные вершины
void test_isolated_vertices_no10() {
    Graph graph;
    graph.vertices_count = 5;
    graph.edges_count = 0;
    int cover[MAX_VERTICES];
    int cover_size;

    bool result = find_vertex_cover(&graph, 0, cover, &cover_size);
    run_test("IsolatedVertices_no10", result == true && cover_size == 0);
}

int main() {
    printf("=== Running Vertex Cover Tests ===\n\n");

    // Запуск всех тестов
    test_single_edge_K0_no1();
    test_path_3_vertices_K1_no2();
    test_single_edge_K1_no3();
    test_triangle_graph_K2_no4();
    test_empty_graph_no5();
    test_triangle_graph_K1_no6();
    test_two_disconnected_edges_K2_no7();
    test_single_vertex_no_edges_no8();
    test_star_graph_center_K1_no9();
    test_isolated_vertices_no10();

    printf("\n=== Tests Completed ===\n");
    return 0;
}