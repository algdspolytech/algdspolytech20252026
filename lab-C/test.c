// test.c
/**
 * @file test.c
 * @brief Файл тестирования функций преобразования списка смежности в матрицу смежности
 *
 * @version 1.0
 * @date 2025.12.21
 * @author Д.Смирнов
 */

#pragma warning(disable:4996)

#include <assert.h> 
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "List2Matrix.h"

 // Вспомогательная функция для создания тестового файла
void CreateTestFile(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s", content);
        fclose(file);
    }
}

// Вспомогательная функция для удаления тестового файла
void DeleteTestFile(const char* filename) {
    remove(filename);
}

// Вспомогательная функция для проверки равенства двух матриц
int MatricesAreEqual(int** matrix1, int** matrix2, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}


/**
 * @brief Тест функции FindMaxVertex с нормальными данными
 *
 * Проверяет корректность определения максимальной вершины
 * в файле со стандартным форматом данных
 */
void Test_FindMaxVertex_NormalData_ReturnsCorrectMax_N1() {
    printf("Test 1: FindMaxVertex with normal data\n");

    const char* testFile = "test_findmax.txt";
    const char* content =
        "0: [1, 2, 3]\n"
        "1: [0, 4, 5]\n"
        "2: [0, 6, 7]\n"
        "3: [0, 8]\n"
        "9: [4, 5, 8]\n";

    CreateTestFile(testFile, content);

    FILE* file = fopen(testFile, "r");
    assert(file != NULL);

    int maxVertex = FindMaxVertex(file);
    assert(maxVertex == 9);

    fclose(file);
    DeleteTestFile(testFile);
    printf("Success\n");
}

/**
 * @brief Тест функции FindMaxVertex с одной вершиной
 *
 * Проверяет обработку файла, содержащего только одну вершину
 */
void Test_FindMaxVertex_SingleVertex_ReturnsCorrectMax_N2() {
    printf("Test 2: FindMaxVertex with single vertex\n");

    const char* testFile = "test_single.txt";
    const char* content = "5: [1, 2, 3]\n";

    CreateTestFile(testFile, content);

    FILE* file = fopen(testFile, "r");
    assert(file != NULL);

    int maxVertex = FindMaxVertex(file);
    assert(maxVertex == 5);

    fclose(file);
    DeleteTestFile(testFile);
    printf("Success\n");
}

/**
 * @brief Тест функции FindMaxVertex с пустым файлом
 *
 * Проверяет поведение функции при обработке пустого файла
 */
void Test_FindMaxVertex_EmptyFile_ReturnsMinusOne_N3() {
    printf("Test 3: FindMaxVertex with empty file\n");

    const char* testFile = "test_empty.txt";
    CreateTestFile(testFile, "");

    FILE* file = fopen(testFile, "r");
    assert(file != NULL);

    int maxVertex = FindMaxVertex(file);
    assert(maxVertex == -1);

    fclose(file);
    DeleteTestFile(testFile);
    printf("Success\n");
}

/**
 * @brief Тест функции ReadAdjacencyList с нормальными данными
 *
 * Проверяет корректность чтения списка смежности из файла
 */
void Test_ReadAdjacencyList_NormalData_ReturnsCorrectLists_N4() {
    printf("Test 4: ReadAdjacencyList with normal data\n");

    const char* testFile = "test_readlist.txt";
    const char* content =
        "0: [1, 2]\n"
        "1: [0, 3]\n"
        "2: [0]\n"
        "3: [1]\n";

    CreateTestFile(testFile, content);

    FILE* file = fopen(testFile, "r");
    assert(file != NULL);

    // Находим максимальную вершину
    int maxVertex = FindMaxVertex(file);
    int vertexCount = maxVertex + 1;

    // Читаем список смежности
    int** adjList = NULL;
    int* sizes = NULL;
    ReadAdjacencyList(file, &adjList, &sizes, vertexCount);

    // Проверяем результаты
    assert(adjList != NULL);
    assert(sizes != NULL);

    // Проверяем вершину 0
    assert(sizes[0] == 2);
    assert(adjList[0][0] == 1);
    assert(adjList[0][1] == 2);

    // Проверяем вершину 1
    assert(sizes[1] == 2);
    assert(adjList[1][0] == 0);
    assert(adjList[1][1] == 3);

    // Проверяем вершину 2
    assert(sizes[2] == 1);
    assert(adjList[2][0] == 0);

    // Проверяем вершину 3
    assert(sizes[3] == 1);
    assert(adjList[3][0] == 1);

    // Освобождаем память
    FreeMemory(adjList, sizes, NULL, vertexCount);
    fclose(file);
    DeleteTestFile(testFile);
    printf("Success\n");
}

/**
 * @brief Тест функции ReadAdjacencyList с отсутствующими вершинами
 *
 * Проверяет обработку случая, когда некоторые вершины отсутствуют в файле
 */
void Test_ReadAdjacencyList_MissingVertices_HandlesCorrectly_N5() {
    printf("Test 5: ReadAdjacencyList with missing vertices\n");

    const char* testFile = "test_missing.txt";
    const char* content =
        "0: [1, 3]\n"
        "3: [0, 2]\n"
        "5: [1, 4]\n";

    CreateTestFile(testFile, content);

    FILE* file = fopen(testFile, "r");
    assert(file != NULL);

    // Находим максимальную вершину
    int maxVertex = FindMaxVertex(file);
    int vertexCount = maxVertex + 1;

    // Читаем список смежности
    int** adjList = NULL;
    int* sizes = NULL;
    ReadAdjacencyList(file, &adjList, &sizes, vertexCount);

    // Проверяем, что для отсутствующих вершин размер равен 0
    assert(sizes[1] == 0);
    assert(sizes[2] == 0);
    assert(sizes[4] == 0);

    // Проверяем существующие вершины
    assert(sizes[0] == 2);
    assert(sizes[3] == 2);
    assert(sizes[5] == 2);

    // Освобождаем память
    FreeMemory(adjList, sizes, NULL, vertexCount);
    fclose(file);
    DeleteTestFile(testFile);
    printf("Success\n");
}

/**
 * @brief Тест функции CreateAdjacencyMatrix с нормальными данными
 *
 * Проверяет корректность преобразования списка смежности в матрицу
 */
void Test_CreateAdjacencyMatrix_NormalData_ReturnsCorrectMatrix_N6() {
    printf("Test 6: CreateAdjacencyMatrix with normal data\n");

    // Создаем тестовый список смежности вручную
    int vertexCount = 4;

    // Выделяем память для списка смежности
    int** adjList = malloc(vertexCount * sizeof(int*));
    int* sizes = malloc(vertexCount * sizeof(int));

    // Заполняем данные для графа:
    // 0: [1, 2]
    // 1: [0, 3]
    // 2: [0]
    // 3: [1]

    sizes[0] = 2;
    adjList[0] = malloc(2 * sizeof(int));
    adjList[0][0] = 1;
    adjList[0][1] = 2;

    sizes[1] = 2;
    adjList[1] = malloc(2 * sizeof(int));
    adjList[1][0] = 0;
    adjList[1][1] = 3;

    sizes[2] = 1;
    adjList[2] = malloc(1 * sizeof(int));
    adjList[2][0] = 0;

    sizes[3] = 1;
    adjList[3] = malloc(1 * sizeof(int));
    adjList[3][0] = 1;

    // Создаем матрицу смежности
    int** matrix = CreateAdjacencyMatrix(adjList, sizes, vertexCount);

    // Проверяем правильность матрицы
    // Ожидаемая матрица 4x4:
    //   0 1 2 3
    // 0:0 1 1 0
    // 1:1 0 0 1
    // 2:1 0 0 0
    // 3:0 1 0 0

    int expected[4][4] = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 0},
        {0, 1, 0, 0}
    };

    // Сравниваем полученную матрицу с ожидаемой
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            assert(matrix[i][j] == expected[i][j]);
        }
    }

    // Освобождаем память
    FreeMemory(adjList, sizes, matrix, vertexCount);
    printf("Success\n");
}

/**
 * @brief Тест функции CreateAdjacencyMatrix с неориентированным графом
 *
 * Проверяет создание симметричной матрицы для неориентированного графа
 */
void Test_CreateAdjacencyMatrix_UndirectedGraph_ReturnsSymmetricMatrix_N7() {
    printf("Test 7: CreateAdjacencyMatrix with undirected graph\n");

    // Создаем тестовый список смежности для треугольника
    int vertexCount = 3;

    int** adjList = malloc(vertexCount * sizeof(int*));
    int* sizes = malloc(vertexCount * sizeof(int));

    // Треугольник: 0-1-2-0
    sizes[0] = 2;
    adjList[0] = malloc(2 * sizeof(int));
    adjList[0][0] = 1;
    adjList[0][1] = 2;

    sizes[1] = 2;
    adjList[1] = malloc(2 * sizeof(int));
    adjList[1][0] = 0;
    adjList[1][1] = 2;

    sizes[2] = 2;
    adjList[2] = malloc(2 * sizeof(int));
    adjList[2][0] = 0;
    adjList[2][1] = 1;

    // Создаем матрицу
    int** matrix = CreateAdjacencyMatrix(adjList, sizes, vertexCount);

    // Проверяем симметричность матрицы
    assert(matrix[0][1] == 1 && matrix[1][0] == 1);
    assert(matrix[0][2] == 1 && matrix[2][0] == 1);
    assert(matrix[1][2] == 1 && matrix[2][1] == 1);

    // Проверяем отсутствие петель
    assert(matrix[0][0] == 0);
    assert(matrix[1][1] == 0);
    assert(matrix[2][2] == 0);

    FreeMemory(adjList, sizes, matrix, vertexCount);
    printf("Success\n");
}

/**
 * @brief Тест функции FreeMemory с NULL параметрами
 *
 * Проверяет, что функция корректно обрабатывает NULL указатели
 */
void Test_FreeMemory_NULLParameters_DoesNothing_N8() {
    printf("Test 8: FreeMemory with NULL parameters\n");

    // Должно выполняться без ошибок
    FreeMemory(NULL, NULL, NULL, 0);
    FreeMemory(NULL, NULL, NULL, 10);

    printf("Success\n");
}

/**
 * @brief Тест функции FreeMemory с валидными данными
 *
 * Проверяет корректное освобождение памяти
 */
void Test_FreeMemory_ValidData_FreesMemory_N9() {
    printf("Test 9: FreeMemory with valid data\n");

    int vertexCount = 3;

    // Создаем тестовые данные
    int** adjList = malloc(vertexCount * sizeof(int*));
    int* sizes = malloc(vertexCount * sizeof(int));
    int** matrix = malloc(vertexCount * sizeof(int*));

    for (int i = 0; i < vertexCount; i++) {
        adjList[i] = malloc(2 * sizeof(int));
        sizes[i] = 2;
        matrix[i] = malloc(vertexCount * sizeof(int));
    }

    // Должно выполняться без ошибок
    FreeMemory(adjList, sizes, matrix, vertexCount);

    printf("Success\n");
}

/**
 * @brief Тест полного преобразования списка в матрицу
 *
 * Интеграционный тест полного процесса преобразования
 */
void Test_CompleteConversion_ReturnsCorrectResult_N10() {
    printf("Test 10: Complete conversion from list to matrix\n");

    const char* testFile = "test_complete.txt";
    const char* content =
        "0: [1, 2]\n"
        "1: [0, 2]\n"
        "2: [0, 1]\n";

    CreateTestFile(testFile, content);

    FILE* file = fopen(testFile, "r");
    assert(file != NULL);

    // Шаг 1: Определяем количество вершин
    int maxVertex = FindMaxVertex(file);
    int vertexCount = maxVertex + 1;
    assert(vertexCount == 3);

    // Шаг 2: Читаем список смежности
    int** adjList = NULL;
    int* sizes = NULL;
    ReadAdjacencyList(file, &adjList, &sizes, vertexCount);

    // Шаг 3: Создаем матрицу смежности
    int** matrix = CreateAdjacencyMatrix(adjList, sizes, vertexCount);

    // Проверяем результат
    int expected[3][3] = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            assert(matrix[i][j] == expected[i][j]);
        }
    }

    // Шаг 4: Освобождаем память
    FreeMemory(adjList, sizes, matrix, vertexCount);
    fclose(file);
    DeleteTestFile(testFile);
    printf("Success\n");
}

/**
 * @brief Тест обработки некорректного формата файла
 *
 * Проверяет устойчивость функций к нестандартному формату данных
 */
void Test_InvalidFileFormat_HandlesGracefully_N11() {
    printf("Test 11: Invalid file format handling\n");

    const char* testFile = "test_invalid.txt";
    const char* content =
        "0: 1, 2, 3\n"           // Нет скобок
        "1: [abc, def]\n"        // Нечисловые данные
        "not a number: [1, 2]\n" // Некорректный номер вершины
        "2: [1]\n";

    CreateTestFile(testFile, content);

    FILE* file = fopen(testFile, "r");
    assert(file != NULL);

    // Функция должна корректно обработать такой файл
    int maxVertex = FindMaxVertex(file);

    // В данном случае максимум должен быть 2 (из последней строки)
    assert(maxVertex == 2);

    fclose(file);
    DeleteTestFile(testFile);
    printf("Success\n");
}

void UnitTests(void) {
    setlocale(LC_CTYPE, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    Test_FindMaxVertex_NormalData_ReturnsCorrectMax_N1();
    Test_FindMaxVertex_SingleVertex_ReturnsCorrectMax_N2();
    Test_FindMaxVertex_EmptyFile_ReturnsMinusOne_N3();
    Test_ReadAdjacencyList_NormalData_ReturnsCorrectLists_N4();
    Test_ReadAdjacencyList_MissingVertices_HandlesCorrectly_N5();
    Test_CreateAdjacencyMatrix_NormalData_ReturnsCorrectMatrix_N6();
    Test_CreateAdjacencyMatrix_UndirectedGraph_ReturnsSymmetricMatrix_N7();
    Test_FreeMemory_NULLParameters_DoesNothing_N8();
    Test_FreeMemory_ValidData_FreesMemory_N9();
    Test_CompleteConversion_ReturnsCorrectResult_N10();
    Test_InvalidFileFormat_HandlesGracefully_N11();

    printf("\nAll tests passed successfully!\n\n\n");
}