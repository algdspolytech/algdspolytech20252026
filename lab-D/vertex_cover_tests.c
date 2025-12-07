#include "vertex_cover.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Тест 1: Пустой граф
void test_empty_graph_no1() {
    printf("Test 1: Empty graph\n");
    Graph g;
    init_graph(&g, 5);

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 2;

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == true);
    assert(cover_size == 0);
    printf("Passed!\n\n");
}

// Тест 2: Граф с одним ребром
void test_single_edge_no2() {
    printf("Test 2: Single edge graph\n");
    Graph g;
    init_graph(&g, 2);
    add_edge(&g, 1, 2);

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 1;

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == true);
    assert(cover_size == 1);
    assert(cover[0] == 1 || cover[0] == 2);
    printf("Passed!\n\n");
}

// Тест 3: Граф треугольник
void test_triangle_graph_no3() {
    printf("Test 3: Triangle graph\n");
    Graph g;
    init_graph(&g, 3);
    add_edge(&g, 1, 2);
    add_edge(&g, 2, 3);
    add_edge(&g, 3, 1);

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 2;

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == true);
    assert(cover_size == 2);

    // Проверяем, что это действительно покрытие
    bool covered[4] = { false };
    for (int i = 0; i < cover_size; i++) {
        covered[cover[i]] = true;
    }
    assert(covered[1] || covered[2]); // Ребро 1-2 покрыто
    assert(covered[2] || covered[3]); // Ребро 2-3 покрыто
    assert(covered[3] || covered[1]); // Ребро 3-1 покрыто
    printf("Passed!\n\n");
}

// Тест 4: Граф звезда
void test_star_graph_no4() {
    printf("Test 4: Star graph\n");
    Graph g;
    init_graph(&g, 5);
    add_edge(&g, 1, 2);
    add_edge(&g, 1, 3);
    add_edge(&g, 1, 4);
    add_edge(&g, 1, 5);

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 1;

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == true);
    assert(cover_size == 1);
    assert(cover[0] == 1); // Центр звезды должен быть в покрытии
    printf("Passed!\n\n");
}

// Тест 5: Граф путь из 4 вершин
void test_path_graph_no5() {
    printf("Test 5: Path graph (4 vertices)\n");
    Graph g;
    init_graph(&g, 4);
    add_edge(&g, 1, 2);
    add_edge(&g, 2, 3);
    add_edge(&g, 3, 4);

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 2;

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == true);
    assert(cover_size == 2);

    bool covered[5] = { false };
    for (int i = 0; i < cover_size; i++) {
        covered[cover[i]] = true;
    }
    assert(covered[1] || covered[2]); // Ребро 1-2
    assert(covered[2] || covered[3]); // Ребро 2-3
    assert(covered[3] || covered[4]); // Ребро 3-4
    printf("Passed!\n\n");
}

// Тест 6: K слишком маленькое
void test_k_too_small_no6() {
    printf("Test 6: K too small\n");
    Graph g;
    init_graph(&g, 4);
    add_edge(&g, 1, 2);
    add_edge(&g, 2, 3);
    add_edge(&g, 3, 4);
    add_edge(&g, 4, 1);

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 1; // Слишком маленькое для цикла

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == false);
    printf("Passed!\n\n");
}

// Тест 7: Полный граф K5
void test_complete_graph_no7() {
    printf("Test 7: Complete graph K5\n");
    Graph g;
    init_graph(&g, 5);

    // Создаем полный граф
    for (int i = 1; i <= 5; i++) {
        for (int j = i + 1; j <= 5; j++) {
            add_edge(&g, i, j);
        }
    }

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 4; // В полном графе минимальное покрытие - n-1 вершин

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == true);
    assert(cover_size == 4);
    printf("Passed!\n\n");
}

// Тест 8: Граф без ребер
void test_no_edges_no8() {
    printf("Test 8: Graph without edges\n");
    Graph g;
    init_graph(&g, 10);

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 0;

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == true);
    assert(cover_size == 0);
    printf("Passed!\n\n");
}

// Тест 9: Граф с изолированными вершинами
void test_isolated_vertices_no9() {
    printf("Test 9: Graph with isolated vertices and edges\n");
    Graph g;
    init_graph(&g, 6);
    add_edge(&g, 1, 2);
    add_edge(&g, 3, 4);
    // Вершины 5 и 6 изолированы

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 2;

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == true);
    assert(cover_size == 2);

    bool covered[7] = { false };
    for (int i = 0; i < cover_size; i++) {
        covered[cover[i]] = true;
    }
    assert(covered[1] || covered[2]);
    assert(covered[3] || covered[4]);
    printf("Passed!\n\n");
}

// Тест 10: Большой K (все вершины)
void test_large_k_no10() {
    printf("Test 10: Large K (all vertices)\n");
    Graph g;
    init_graph(&g, 5);
    add_edge(&g, 1, 2);
    add_edge(&g, 2, 3);
    add_edge(&g, 3, 4);
    add_edge(&g, 4, 5);

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 5;

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == true);
    assert(cover_size <= 5);
    printf("Passed!\n\n");
}

// Тест 11: Проверка функции is_vertex_cover
void test_is_vertex_cover_function_no11() {
    printf("Test 11: is_vertex_cover function\n");
    Graph g;
    init_graph(&g, 3);
    add_edge(&g, 1, 2);
    add_edge(&g, 2, 3);

    bool covered1[4] = { false, true, true, false }; // Вершины 1 и 2
    assert(is_vertex_cover(&g, covered1) == true);

    bool covered2[4] = { false, true, false, true }; // Вершины 1 и 3
    assert(is_vertex_cover(&g, covered2) == false); // Ребро 2-3 не покрыто

    printf("Passed!\n\n");
}

// Тест 12: Граф с петлями (должны игнорироваться)
void test_self_loops_no12() {
    printf("Test 12: Graph with self-loops (should be ignored)\n");
    // Этот тест проверяет, что петли не мешают работе алгоритма
    Graph g;
    init_graph(&g, 3);
    add_edge(&g, 1, 2);
    add_edge(&g, 2, 3);

    int cover[MAX_VERTICES];
    int cover_size;
    int K = 1;

    bool result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == false); // K=1 недостаточно для пути из 3 вершин

    K = 2;
    result = find_vertex_cover(&g, K, cover, &cover_size);
    assert(result == true);
    assert(cover_size == 2);
    printf("Passed!\n\n");
}

int main() {
    printf("Running Vertex Cover Tests\n");
    printf("==========================\n\n");

    test_empty_graph_no1();
    test_single_edge_no2();
    test_triangle_graph_no3();
    test_star_graph_no4();
    test_path_graph_no5();
    test_k_too_small_no6();
    test_complete_graph_no7();
    test_no_edges_no8();
    test_isolated_vertices_no9();
    test_large_k_no10();
    test_is_vertex_cover_function_no11();
    test_self_loops_no12();

    printf("All tests passed!\n");
    return 0;
}