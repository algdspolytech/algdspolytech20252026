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

void test_create_adjacency_list_ValidSize_no1(void) {
    AdjacencyList* list = create_adjacency_list(5);
    ASSERT(list != NULL, "List should not be NULL");
    ASSERT(list->vertex_count == 5, "Vertex count should be 5");

    for (int i = 0; i < 5; i++) {
        ASSERT(list->lists[i] == NULL, "All lists should be initialized as NULL");
    }

    free_adjacency_list(list);
    tests_passed++;
    printf("PASS: test_create_adjacency_list_ValidSize_no1\n");
}

void test_add_edge_to_list_ValidEdge_no2(void) {
    AdjacencyList* list = create_adjacency_list(3);

    add_edge_to_list(list, 0, 1);
    ASSERT(list->lists[0] != NULL, "Edge should be added");
    ASSERT(list->lists[0]->vertex == 1, "Destination vertex should be 1");
    ASSERT(list->lists[0]->next == NULL, "Next should be NULL");

    free_adjacency_list(list);
    tests_passed++;
    printf("PASS: test_add_edge_to_list_ValidEdge_no2\n");
}

void test_add_edge_to_list_MultipleEdges_no3(void) {
    AdjacencyList* list = create_adjacency_list(3);

    add_edge_to_list(list, 0, 1);
    add_edge_to_list(list, 0, 2);

    ASSERT(list->lists[0] != NULL, "First edge should exist");
    ASSERT(list->lists[0]->vertex == 2, "First in list should be vertex 2");
    ASSERT(list->lists[0]->next != NULL, "Should have next node");
    ASSERT(list->lists[0]->next->vertex == 1, "Second should be vertex 1");

    free_adjacency_list(list);
    tests_passed++;
    printf("PASS: test_add_edge_to_list_MultipleEdges_no3\n");
}

void test_convert_matrix_to_list_EmptyMatrix_no4(void) {
    MatrixData* matrix_data = malloc(sizeof(MatrixData));
    matrix_data->matrix = NULL;
    matrix_data->size = 0;

    AdjacencyList* list = convert_matrix_to_list(matrix_data);
    ASSERT(list == NULL, "Should return NULL for empty matrix");

    free(matrix_data);
    tests_passed++;
    printf("PASS: test_convert_matrix_to_list_EmptyMatrix_no4\n");
}

void test_convert_matrix_to_list_SingleVertex_no5(void) {
    MatrixData* matrix_data = malloc(sizeof(MatrixData));
    matrix_data->size = 1;
    matrix_data->matrix = malloc(sizeof(int*));
    matrix_data->matrix[0] = malloc(sizeof(int));
    matrix_data->matrix[0][0] = 0;

    AdjacencyList* list = convert_matrix_to_list(matrix_data);
    ASSERT(list != NULL, "List should not be NULL");
    ASSERT(list->vertex_count == 1, "Should have 1 vertex");
    ASSERT(list->lists[0] == NULL, "Should have no edges");

    free_adjacency_list(list);
    free_matrix_data(matrix_data);
    tests_passed++;
    printf("PASS: test_convert_matrix_to_list_SingleVertex_no5\n");
}

void test_convert_matrix_to_list_SimpleGraph_no6(void) {
    MatrixData* matrix_data = malloc(sizeof(MatrixData));
    matrix_data->size = 2;
    matrix_data->matrix = malloc(2 * sizeof(int*));
    matrix_data->matrix[0] = malloc(2 * sizeof(int));
    matrix_data->matrix[1] = malloc(2 * sizeof(int));

    matrix_data->matrix[0][0] = 0;
    matrix_data->matrix[0][1] = 1;
    matrix_data->matrix[1][0] = 1;
    matrix_data->matrix[1][1] = 0;

    AdjacencyList* list = convert_matrix_to_list(matrix_data);
    ASSERT(list != NULL, "List should not be NULL");
    ASSERT(list->lists[0] != NULL, "Vertex 0 should have edges");
    ASSERT(list->lists[0]->vertex == 1, "Vertex 0 should connect to vertex 1");
    ASSERT(list->lists[1] != NULL, "Vertex 1 should have edges");
    ASSERT(list->lists[1]->vertex == 0, "Vertex 1 should connect to vertex 0");

    free_adjacency_list(list);
    free_matrix_data(matrix_data);
    tests_passed++;
    printf("PASS: test_convert_matrix_to_list_SimpleGraph_no6\n");
}

void test_convert_matrix_to_list_NoEdges_no7(void) {
    MatrixData* matrix_data = malloc(sizeof(MatrixData));
    matrix_data->size = 3;
    matrix_data->matrix = malloc(3 * sizeof(int*));

    for (int i = 0; i < 3; i++) {
        matrix_data->matrix[i] = malloc(3 * sizeof(int));
        for (int j = 0; j < 3; j++) {
            matrix_data->matrix[i][j] = 0;
        }
    }

    AdjacencyList* list = convert_matrix_to_list(matrix_data);
    ASSERT(list != NULL, "List should not be NULL");

    for (int i = 0; i < 3; i++) {
        ASSERT(list->lists[i] == NULL, "All lists should be empty");
    }

    free_adjacency_list(list);
    free_matrix_data(matrix_data);
    tests_passed++;
    printf("PASS: test_convert_matrix_to_list_NoEdges_no7\n");
}

void test_convert_matrix_to_list_FullGraph_no8(void) {
    MatrixData* matrix_data = malloc(sizeof(MatrixData));
    matrix_data->size = 2;
    matrix_data->matrix = malloc(2 * sizeof(int*));
    matrix_data->matrix[0] = malloc(2 * sizeof(int));
    matrix_data->matrix[1] = malloc(2 * sizeof(int));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrix_data->matrix[i][j] = 1;
        }
    }

    AdjacencyList* list = convert_matrix_to_list(matrix_data);
    ASSERT(list != NULL, "List should not be NULL");

    ASSERT(list->lists[0] != NULL, "Vertex 0 first edge");
    ASSERT(list->lists[0]->vertex == 1, "Vertex 0 first to vertex 1");
    ASSERT(list->lists[0]->next != NULL, "Vertex 0 second edge");
    ASSERT(list->lists[0]->next->vertex == 0, "Vertex 0 second to vertex 0");
    ASSERT(list->lists[0]->next->next == NULL, "Vertex 0 exactly two edges");

    ASSERT(list->lists[1] != NULL, "Vertex 1 first edge");
    ASSERT(list->lists[1]->vertex == 1, "Vertex 1 first to vertex 1");
    ASSERT(list->lists[1]->next != NULL, "Vertex 1 second edge");
    ASSERT(list->lists[1]->next->vertex == 0, "Vertex 1 second to vertex 0");
    ASSERT(list->lists[1]->next->next == NULL, "Vertex 1 exactly two edges");

    free_adjacency_list(list);
    free_matrix_data(matrix_data);
    tests_passed++;
    printf("PASS: test_convert_matrix_to_list_FullGraph_no8\n");
}

void test_free_functions_NullInput_no9(void) {
    free_adjacency_list(NULL);
    free_matrix_data(NULL);

    tests_passed++;
    printf("PASS: test_free_functions_NullInput_no9\n");
}

void test_read_matrix_from_file_InvalidFile_no10(void) {
    MatrixData* data = read_matrix_from_file("nonexistent_file.txt");
    ASSERT(data == NULL, "Should return NULL for invalid file");

    tests_passed++;
    printf("PASS: test_read_matrix_from_file_InvalidFile_no10\n");
}

void run_all_tests(void) {
    printf("Running unit tests...\n\n");

    test_create_adjacency_list_ValidSize_no1();
    test_add_edge_to_list_ValidEdge_no2();
    test_add_edge_to_list_MultipleEdges_no3();
    test_convert_matrix_to_list_EmptyMatrix_no4();
    test_convert_matrix_to_list_SingleVertex_no5();
    test_convert_matrix_to_list_SimpleGraph_no6();
    test_convert_matrix_to_list_NoEdges_no7();
    test_convert_matrix_to_list_FullGraph_no8();
    test_free_functions_NullInput_no9();
    test_read_matrix_from_file_InvalidFile_no10();

    printf("\n=== TEST RESULTS ===\n");
    printf("Passed: %d\n", tests_passed);
    printf("Failed: %d\n", tests_failed);
    printf("Total:  %d\n", tests_passed + tests_failed);
}