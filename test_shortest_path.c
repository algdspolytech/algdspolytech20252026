#include "shortest_path.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


// Вспомогательная функция для создания матрицы из массива
int** create_matrix_from_array(int* arr, int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = arr[i * n + j];
        }
    }
    return matrix;
}

void free_matrix_wrapper(int** matrix, int n) {
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
}

// Тест 1: Путь из вершины в себя shortestPath_StartEqualsEnd_no1
void test_shortestPath_StartEqualsEnd_no1() {
    int arr[] = {
        0,1,
        1,0
    };
    int n = 2;
    int** matrix = create_matrix_from_array(arr, n);
    PathResult res = find_shortest_path(matrix, n, 0, 0);
    assert(res.length == 1 && res.path[0] == 0);
    free_path_result(res);
    free_matrix_wrapper(matrix, n);
}

// Тест 2: Граф с одним ребром shortestPath_OneEdge_no2
void test_shortestPath_OneEdge_no2() {
    int arr[] = {
        0,1,
        1,0
    };
    int n = 2;
    int** matrix = create_matrix_from_array(arr, n);
    PathResult expected = { (int[]) { 0,1 }, 2 };
    PathResult res = find_shortest_path(matrix, n, 0, 1);
    assert(compare_paths(&res, &expected));
    free_path_result(res);
    free_matrix_wrapper(matrix, n);
}

// Тест 3: Нет пути shortestPath_NoPath_no3
void test_shortestPath_NoPath_no3() {
    int arr[] = {
        0,0,0,
        0,0,0,
        0,0,0
    };
    int n = 3;
    int** matrix = create_matrix_from_array(arr, n);
    PathResult res = find_shortest_path(matrix, n, 0, 2);
    assert(res.length == 0);
    free_path_result(res);
    free_matrix_wrapper(matrix, n);
}

// Тест 4: Путь длины 3 shortestPath_LengthThree_no4
void test_shortestPath_LengthThree_no4() {
    int arr[] = {
        0,1,0,0,
        1,0,1,0,
        0,1,0,1,
        0,0,1,0
    };
    int n = 4;
    int** matrix = create_matrix_from_array(arr, n);
    int expected_path[] = { 0,1,2,3 };
    PathResult expected = { expected_path, 4 };
    PathResult res = find_shortest_path(matrix, n, 0, 3);
    assert(compare_paths(&res, &expected));
    free_path_result(res);
    free_matrix_wrapper(matrix, n);
}

// Тест 5: Путь через несколько вариантов shortestPath_MultiplePaths_no5
void test_shortestPath_MultiplePaths_no5() {
    int arr[] = {
        0,1,1,0,
        1,0,0,1,
        1,0,0,1,
        0,1,1,0
    };
    int n = 4;
    int** matrix = create_matrix_from_array(arr, n);
    int exp_path[] = { 0,1,3 };
    PathResult expected = { exp_path, 3 };
    PathResult res = find_shortest_path(matrix, n, 0, 3);
    assert(compare_paths(&res, &expected));
    free_path_result(res);
    free_matrix_wrapper(matrix, n);
}

// Тест 6: Старт или конец вне диапазона shortestPath_OutOfRange_no6
void test_shortestPath_OutOfRange_no6() {
    int arr[] = {
        0,1,
        1,0
    };
    int n = 2;
    int** matrix = create_matrix_from_array(arr, n);
    PathResult res1 = find_shortest_path(matrix, n, -1, 1);
    assert(res1.length == 0);
    PathResult res2 = find_shortest_path(matrix, n, 0, 3);
    assert(res2.length == 0);
    free_path_result(res1);
    free_path_result(res2);
    free_matrix_wrapper(matrix, n);
}

// Тест 7: Граф с петлей shortestPath_Loop_no7
void test_shortestPath_Loop_no7() {
    int arr[] = {
        1,1,
        1,1
    };
    int n = 2;
    int** matrix = create_matrix_from_array(arr, n);
    int exp_path[] = { 0,1 };
    PathResult expected = { exp_path, 2 };
    PathResult res = find_shortest_path(matrix, n, 0, 1);
    assert(compare_paths(&res, &expected));
    free_path_result(res);
    free_matrix_wrapper(matrix, n);
}

// Тест 8: Граф с неориентированными ребрами shortestPath_Undirected_no8
void test_shortestPath_Undirected_no8() {
    int arr[] = {
        0,1,0,
        1,0,1,
        0,1,0
    };
    int n = 3;
    int** matrix = create_matrix_from_array(arr, n);
    int expected_path[] = { 0,1,2 };
    PathResult expected = { expected_path, 3 };
    PathResult res = find_shortest_path(matrix, n, 0, 2);
    assert(compare_paths(&res, &expected));
    free_path_result(res);
    free_matrix_wrapper(matrix, n);
}

// Тест 9: Путь отсутствует shortestPath_NoConnection_no9
void test_shortestPath_NoConnection_no9() {
    int arr[] = {
        0,0,
        0,0
    };
    int n = 2;
    int** matrix = create_matrix_from_array(arr, n);
    PathResult res = find_shortest_path(matrix, n, 0, 1);
    assert(res.length == 0);
    free_path_result(res);
    free_matrix_wrapper(matrix, n);
}

// Тест 10: Путь длины 1 shortestPath_LengthOne_no10
void test_shortestPath_LengthOne_no10() {
    int arr[] = {
        0,1,
        1,0
    };
    int n = 2;
    int** matrix = create_matrix_from_array(arr, n);
    int expected_path[] = { 0,1 };
    PathResult expected = { expected_path, 2 };
    PathResult res = find_shortest_path(matrix, n, 0, 1);
    assert(compare_paths(&res, &expected));
    free_path_result(res);
    free_matrix_wrapper(matrix, n);
}


int main(void) {
    test_shortestPath_StartEqualsEnd_no1();
    test_shortestPath_OneEdge_no2();
    test_shortestPath_NoPath_no3();
    test_shortestPath_LengthThree_no4();
    test_shortestPath_MultiplePaths_no5();
    test_shortestPath_OutOfRange_no6();
    test_shortestPath_Loop_no7();
    test_shortestPath_Undirected_no8();
    test_shortestPath_NoConnection_no9();
    test_shortestPath_LengthOne_no10();
    return 0;
}
