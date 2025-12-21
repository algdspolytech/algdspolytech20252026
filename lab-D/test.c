// test.c
/**
 * @file test.c
 * @brief Тестирование алгоритма поиска гамильтонова пути
 *
 * @version 1.0
 * @date 2025.12.20
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hamiltonian.h"


// Вспомогательная функция для создания тестового файла
void CreateTestFile(const char* filename, const char* content) {
    FILE* f = fopen(filename, "w");
    if (f) {
        fprintf(f, "%s", content);
        fclose(f);
    }
}

void Test_ReadGraphFromFile_ValidFile_ReadsCorrectly_N1() {
    printf("Test 1: Read valid graph from file\n");

    CreateTestFile("test1.txt", "3\n1 2\n2 3\n");

    initializeData();
    int result = readGraphFromFile("test1.txt");

    assert(result == 1);
    assert(n == 3);
    assert(adj[1][2] == 1);
    assert(adj[2][1] == 1);
    assert(adj[2][3] == 1);
    assert(adj[3][2] == 1);
    assert(adj[1][3] == 0);
    assert(adj[3][1] == 0);

    remove("test1.txt");
    printf("Success\n");
}

void Test_ReadGraphFromFile_NonExistentFile_ReturnsZero_N2() {
    printf("Test 2: Read from non-existent file\n");

    initializeData();
    int result = readGraphFromFile("nonexistent.txt");

    assert(result == 0);
    printf("Success\n");
}

void Test_ReadGraphFromFile_InvalidFormat_ReturnsZero_N3() {
    printf("Test 3: Read file with invalid format\n");

    CreateTestFile("test3.txt", "not_a_number\n");

    initializeData();
    int result = readGraphFromFile("test3.txt");

    assert(result == 0);

    remove("test3.txt");
    printf("Success\n");
}

void Test_HamiltonianFromAnyVertex_SingleVertex_ReturnsOne_N4() {
    printf("Test 4: Hamiltonian path in single vertex graph\n");

    initializeData();
    n = 1;

    int found = HamiltonianFromAnyVertex();

    assert(found == 1);
    assert(path[0] == 1);
    printf("Success\n");
}

void Test_HamiltonianFromAnyVertex_TwoVerticesWithEdge_ReturnsOne_N5() {
    printf("Test 5: Hamiltonian path in two vertices with edge\n");

    initializeData();
    n = 2;
    adj[1][2] = adj[2][1] = 1;

    int found = HamiltonianFromAnyVertex();

    assert(found == 1);
    assert((path[0] == 1 && path[1] == 2) || (path[0] == 2 && path[1] == 1));
    printf("Success\n");
}

void Test_HamiltonianFromAnyVertex_TwoVerticesWithoutEdge_ReturnsZero_N6() {
    printf("Test 6: Hamiltonian path in two vertices without edge\n");

    initializeData();
    n = 2;
    // No edges

    int found = HamiltonianFromAnyVertex();

    assert(found == 0);
    printf("Success\n");
}

void Test_HamiltonianFromAnyVertex_ChainGraph_ReturnsOne_N7() {
    printf("Test 7: Hamiltonian path in chain graph of 3 vertices\n");

    initializeData();
    n = 3;
    adj[1][2] = adj[2][1] = 1;
    adj[2][3] = adj[3][2] = 1;
    // 1-2-3 chain

    int found = HamiltonianFromAnyVertex();

    assert(found == 1);
    // Check that all vertices are in path
    int vertices[4] = { 0 };
    for (int i = 0; i < n; i++) {
        vertices[path[i]] = 1;
    }
    assert(vertices[1] == 1 && vertices[2] == 1 && vertices[3] == 1);
    printf("Success\n");
}

void Test_HamiltonianFromAnyVertex_IsolatedVertices_ReturnsZero_N8() {
    printf("Test 8: Hamiltonian path in graph with isolated vertices\n");

    initializeData();
    n = 3;
    // No edges - all vertices isolated

    int found = HamiltonianFromAnyVertex();

    assert(found == 0);
    printf("Success\n");
}

void Test_HamiltonianFromAnyVertex_CompleteGraph_ReturnsOne_N9() {
    printf("Test 9: Hamiltonian path in complete graph of 3 vertices\n");

    initializeData();
    n = 3;
    // Complete graph K3
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            adj[i][j] = adj[j][i] = 1;
        }
    }

    int found = HamiltonianFromAnyVertex();

    assert(found == 1);
    printf("Success\n");
}

void Test_HamiltonianFromAnyVertex_TriangleWithExtraVertex_ReturnsOne_N10() {
    printf("Test 10: Hamiltonian path in triangle with extra vertex\n");

    initializeData();
    n = 4;
    // Triangle 1-2-3-1
    adj[1][2] = adj[2][1] = 1;
    adj[2][3] = adj[3][2] = 1;
    adj[3][1] = adj[1][3] = 1;
    // Extra vertex 4 connected to 3
    adj[3][4] = adj[4][3] = 1;

    int found = HamiltonianFromAnyVertex();

    assert(found == 1);
    printf("Success\n");
}

void Test_WriteResultToFile_ValidPath_WritesCorrectly_N11() {
    printf("Test 11: Write valid path to file\n");

    initializeData();
    n = 3;
    path[0] = 1;
    path[1] = 2;
    path[2] = 3;

    writeResultToFile("test_output.txt", 1);

    FILE* f = fopen("test_output.txt", "r");
    assert(f != NULL);

    int a, b, c;
    int result = fscanf(f, "%d %d %d", &a, &b, &c);
    fclose(f);

    assert(result == 3);
    assert(a == 1 && b == 2 && c == 3);

    remove("test_output.txt");
    printf("Success\n");
}

void Test_WriteResultToFile_NoPath_WritesMinusOne_N12() {
    printf("Test 12: Write 0 when no path found\n");

    initializeData();

    writeResultToFile("test_output2.txt", 0);

    FILE* f = fopen("test_output2.txt", "r");
    assert(f != NULL);

    int value;
    int result = fscanf(f, "%d", &value);
    fclose(f);

    assert(result == 1);
    assert(value == 0);

    remove("test_output2.txt");
    printf("Success\n");
}

void Test_HamiltonianFunction_ValidPath_ReturnsOne_N13() {
    printf("Test 13: Hamiltonian recursive function finds path\n");

    initializeData();
    n = 3;
    adj[1][2] = adj[2][1] = 1;
    adj[2][3] = adj[3][2] = 1;

    visited[1] = 1;
    int result = Hamiltonian(1, 1);

    assert(result == 1);
    printf("Success\n");
}

void Test_HamiltonianFunction_InvalidPath_ReturnsZero_N14() {
    printf("Test 14: Hamiltonian recursive function returns 0 for no path\n");

    initializeData();
    n = 3;
    // Only edge 1-2 exists
    adj[1][2] = adj[2][1] = 1;
    // Vertex 3 is isolated

    visited[1] = 1;
    int result = Hamiltonian(1, 1);

    assert(result == 0);
    printf("Success\n");
}

void Test_GraphWithCycle_ReturnsOne_N15() {
    printf("Test 15: Hamiltonian path in cycle graph (C4)\n");

    initializeData();
    n = 4;
    // Cycle 1-2-3-4-1
    adj[1][2] = adj[2][1] = 1;
    adj[2][3] = adj[3][2] = 1;
    adj[3][4] = adj[4][3] = 1;
    adj[4][1] = adj[1][4] = 1;

    int found = HamiltonianFromAnyVertex();

    assert(found == 1);
    printf("Success\n");
}

void UnitTests() {
    printf("=== Тестирование алгоритма поиска гамильтонова пути ===\n\n");

    Test_ReadGraphFromFile_ValidFile_ReadsCorrectly_N1();
    Test_ReadGraphFromFile_NonExistentFile_ReturnsZero_N2();
    Test_ReadGraphFromFile_InvalidFormat_ReturnsZero_N3();
    Test_HamiltonianFromAnyVertex_SingleVertex_ReturnsOne_N4();
    Test_HamiltonianFromAnyVertex_TwoVerticesWithEdge_ReturnsOne_N5();
    Test_HamiltonianFromAnyVertex_TwoVerticesWithoutEdge_ReturnsZero_N6();
    Test_HamiltonianFromAnyVertex_ChainGraph_ReturnsOne_N7();
    Test_HamiltonianFromAnyVertex_IsolatedVertices_ReturnsZero_N8();
    Test_HamiltonianFromAnyVertex_CompleteGraph_ReturnsOne_N9();
    Test_HamiltonianFromAnyVertex_TriangleWithExtraVertex_ReturnsOne_N10();
    Test_WriteResultToFile_ValidPath_WritesCorrectly_N11();
    Test_WriteResultToFile_NoPath_WritesMinusOne_N12();
    Test_HamiltonianFunction_ValidPath_ReturnsOne_N13();
    Test_HamiltonianFunction_InvalidPath_ReturnsZero_N14();
    Test_GraphWithCycle_ReturnsOne_N15();

    printf("\n=== Все тесты успешно пройдены! ===\n\n");
}