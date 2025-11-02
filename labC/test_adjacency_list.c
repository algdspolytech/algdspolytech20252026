#include <stdio.h>
#include <stdlib.h>
#include "graph_utils.h"

static int tests_passed = 0;
static int tests_failed = 0;

#define ASSERT(condition, message) \
    if (!(condition)) { \
        printf("FAIL: %s\n", message); \
        tests_failed++; \
        return; \
    }

void test_create_adjacency_list_no1(void) {
    Graph* g = create_adjacency_list(5);
    ASSERT(g != NULL, "Graph should not be NULL");
    ASSERT(g->nodes == 5, "Graph should have 5 nodes");
    for (int i = 0; i < 5; i++) {
        ASSERT(g->connections[i] == NULL, "All adjacency lists should be NULL");
    }
    free_adjacency_list(g);
    tests_passed++;
    printf("PASS: test_create_adjacency_list_no1\n");
}

void test_add_edge_to_list_no2(void) {
    Graph* g = create_adjacency_list(3);
    add_edge_to_list(g, 0, 1);
    ASSERT(g->connections[0] != NULL, "Edge should exist");
    ASSERT(g->connections[0]->target == 1, "Edge should point to 1");
    ASSERT(g->connections[0]->link == NULL, "No further edges");
    free_adjacency_list(g);
    tests_passed++;
    printf("PASS: test_add_edge_to_list_no2\n");
}

void test_add_multiple_edges_no3(void) {
    Graph* g = create_adjacency_list(3);
    add_edge_to_list(g, 0, 1);
    add_edge_to_list(g, 0, 2);
    ASSERT(g->connections[0] != NULL, "Edges should exist");
    ASSERT(g->connections[0]->target == 2, "First edge should be 2");
    ASSERT(g->connections[0]->link->target == 1, "Second edge should be 1");
    ASSERT(g->connections[0]->link->link == NULL, "No more edges");
    free_adjacency_list(g);
    tests_passed++;
    printf("PASS: test_add_multiple_edges_no3\n");
}

void test_convert_empty_matrix_no4(void) {
    Grid* grid = malloc(sizeof(Grid));
    grid->grid = NULL;
    grid->dimension = 0;
    Graph* g = convert_matrix_to_list(grid);
    ASSERT(g == NULL, "Should return NULL for empty matrix");
    free(grid);
    tests_passed++;
    printf("PASS: test_convert_empty_matrix_no4\n");
}

void test_convert_single_vertex_no5(void) {
    Grid* grid = malloc(sizeof(Grid));
    grid->dimension = 1;
    grid->grid = malloc(sizeof(int*));
    grid->grid[0] = malloc(sizeof(int));
    grid->grid[0][0] = 0;
    Graph* g = convert_matrix_to_list(grid);
    ASSERT(g != NULL, "Graph should not be NULL");
    ASSERT(g->nodes == 1, "Graph should have 1 node");
    ASSERT(g->connections[0] == NULL, "Node should have no edges");
    free_adjacency_list(g);
    free_matrix_data(grid);
    tests_passed++;
    printf("PASS: test_convert_single_vertex_no5\n");
}

void test_convert_simple_graph_no6(void) {
    Grid* grid = malloc(sizeof(Grid));
    grid->dimension = 2;
    grid->grid = malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) grid->grid[i] = malloc(2 * sizeof(int));
    grid->grid[0][0] = 0; grid->grid[0][1] = 1;
    grid->grid[1][0] = 1; grid->grid[1][1] = 0;
    Graph* g = convert_matrix_to_list(grid);
    ASSERT(g->connections[0]->target == 1, "Node 0 should connect to 1");
    ASSERT(g->connections[1]->target == 0, "Node 1 should connect to 0");
    free_adjacency_list(g);
    free_matrix_data(grid);
    tests_passed++;
    printf("PASS: test_convert_simple_graph_no6\n");
}

void test_convert_no_edges_no7(void) {
    Grid* grid = malloc(sizeof(Grid));
    grid->dimension = 3;
    grid->grid = malloc(3 * sizeof(int*));
    for (int i = 0; i < 3; i++) {
        grid->grid[i] = malloc(3 * sizeof(int));
        for (int j = 0; j < 3; j++) grid->grid[i][j] = 0;
    }
    Graph* g = convert_matrix_to_list(grid);
    for (int i = 0; i < 3; i++) ASSERT(g->connections[i] == NULL, "All nodes should have no edges");
    free_adjacency_list(g);
    free_matrix_data(grid);
    tests_passed++;
    printf("PASS: test_convert_no_edges_no7\n");
}

void test_convert_full_graph_no8(void) {
    Grid* grid = malloc(sizeof(Grid));
    grid->dimension = 2;
    grid->grid = malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++) {
        grid->grid[i] = malloc(2 * sizeof(int));
        for (int j = 0; j < 2; j++) grid->grid[i][j] = 1;
    }
    Graph* g = convert_matrix_to_list(grid);
    ASSERT(g->connections[0]->target == 1, "Node 0 first edge");
    ASSERT(g->connections[0]->link->target == 0, "Node 0 second edge");
    ASSERT(g->connections[1]->target == 1, "Node 1 first edge");
    ASSERT(g->connections[1]->link->target == 0, "Node 1 second edge");
    free_adjacency_list(g);
    free_matrix_data(grid);
    tests_passed++;
    printf("PASS: test_convert_full_graph_no8\n");
}

void test_free_functions_no9(void) {
    free_adjacency_list(NULL);
    free_matrix_data(NULL);
    tests_passed++;
    printf("PASS: test_free_functions_no9\n");
}

void test_read_invalid_file_no10(void) {
    Grid* grid = read_matrix_from_file("nonexistent_file.txt");
    ASSERT(grid == NULL, "Should return NULL for invalid file");
    tests_passed++;
    printf("PASS: test_read_invalid_file_no10\n");
}

void run_all_tests(void) {
    printf("Running unit tests...\n\n");
    test_create_adjacency_list_no1();
    test_add_edge_to_list_no2();
    test_add_multiple_edges_no3();
    test_convert_empty_matrix_no4();
    test_convert_single_vertex_no5();
    test_convert_simple_graph_no6();
    test_convert_no_edges_no7();
    test_convert_full_graph_no8();
    test_free_functions_no9();
    test_read_invalid_file_no10();
    printf("\n=== TEST RESULTS ===\n");
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    printf("Total:  %d\n", tests_passed + tests_failed);
}