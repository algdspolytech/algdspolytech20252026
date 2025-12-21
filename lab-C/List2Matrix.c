// List2Matrix.c
/**
 * @file List2Matrix.c
 * @brief Реализация функций для преобразования списка смежности в матрицу смежности
 *
 * @version 1.0
 * @date 2025.12.21
 * @author Д.Смирнов
 */

#pragma warning(disable:4996)

#include "List2Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


 /**
  * @brief Поиск максимальной вершины в файле
  *
  * @param[in] file - указатель на открытый файл с данными графа
  * 
  * @return Номер максимальной вершины (индекс последней вершины)
  */
int FindMaxVertex(FILE* file) {
    int maxVert = -1;
    int current_vertex;
    char buffer[BUF];

    rewind(file);

    while (fgets(buffer, sizeof(buffer), file)) {
        char* ptr = buffer;
        while (*ptr && *ptr != ':') ptr++;

        if (*ptr == ':') {
            *ptr = '\0';
            current_vertex = atoi(buffer);
            *ptr = ':';

            if (current_vertex > maxVert) {
                maxVert = current_vertex;
            }

            ptr++;
            while (*ptr && *ptr != '[') ptr++;

            if (*ptr == '[') {
                ptr++;
                while (*ptr && *ptr != ']') {
                    if (isdigit(*ptr)) {
                        int neighbor = atoi(ptr);
                        if (neighbor > maxVert) {
                            maxVert = neighbor;
                        }
                        while (isdigit(*ptr)) ptr++;
                    }
                    if (*ptr == ',') ptr++;
                    ptr++;
                }
            }
        }
    }

    return maxVert;
}


/**
 * @brief Чтение списка смежности из файла
 * 
 * @param[in] file - указатель на открытый файл с данными графа
 * @param[out] adjList - двойной указатель для возврата массива массивов соседей
 * @param[out] sizes - указатель для возврата массива размеров каждого списка соседей
 * @param[in] VertexCount - общее количество вершин графа
 */
void ReadAdjacencyList(FILE* file, int*** adjList, int** sizes, int VertexCount) {
    rewind(file);
    char line[1000];

    *adjList = malloc(VertexCount * sizeof(int*));
    *sizes = calloc(VertexCount, sizeof(int));

    for (int i = 0; i < VertexCount; i++) {
        (*adjList)[i] = NULL;
    }

    while (fgets(line, sizeof(line), file)) {
        int i = 0;
        while (line[i] != ':' && line[i] != '\0') i++;

        if (line[i] == ':') {
            line[i] = '\0';
            int vertex = atoi(line);
            line[i] = ':';

            while (line[i] != '[' && line[i] != '\0') i++;

            if (line[i] == '[') {
                i++;
                int capacity = 2;
                (*adjList)[vertex] = malloc(capacity * sizeof(int));
                int count = 0;

                while (line[i] != ']' && line[i] != '\0') {
                    while (line[i] && (line[i] < '0' || line[i] > '9')) i++;

                    if (line[i] >= '0' && line[i] <= '9') {
                        int num = 0;
                        while (line[i] >= '0' && line[i] <= '9') {
                            num = num * 10 + (line[i] - '0');
                            i++;
                        }

                        if (count >= capacity) {
                            capacity *= 2;
                            (*adjList)[vertex] = realloc((*adjList)[vertex], capacity * sizeof(int));
                        }
                        (*adjList)[vertex][count++] = num;
                    }

                    while (line[i] && (line[i] == ',' || line[i] == ' ')) i++;
                }

                (*sizes)[vertex] = count;
            }
        }
    }
}


/**
 * @brief Создание матрицы смежности по списку смежности
 *
 * @param[in] adjList - массив массивов соседей (список смежности)
 * @param[in] sizes - массив размеров каждого списка соседей
 * @param[in] VertexCount - общее количество вершин графа
 * 
 * @return Двойной указатель на созданную матрицу смежности
 */
int** CreateAdjacencyMatrix(int** adjList, int* sizes, int VertexCount) {
    int** matrix = malloc(VertexCount * sizeof(int*));
    for (int i = 0; i < VertexCount; i++) {
        matrix[i] = calloc(VertexCount, sizeof(int));
    }

    for (int i = 0; i < VertexCount; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            int neighbor = adjList[i][j];
            if (neighbor < VertexCount) {
                matrix[i][neighbor] = 1;
            }
        }
    }

    return matrix;
}


/**
 * @brief Вывод матрицы смежности в консоль
 *
 * @param[in] matrix - матрица смежности для вывода
 * @param[in] VertexCount - размер матрицы (количество вершин)
 */
void PrintMatrix(int** matrix, int VertexCount) {
    printf("Матрица смежности:\n");
    printf("    ");
    for (int i = 0; i < VertexCount; i++) {
        printf("%2d ", i);
    }
    printf("\n");

    for (int i = 0; i < VertexCount; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < VertexCount; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
}


/**
 * @brief Освобождение выделенной динамической памяти
 *
 * @param[in] adjList - массив массивов соседей
 * @param[in] sizes - массив размеров списков соседей
 * @param[in] matrix - матрица смежности
 * @param[in] VertexCount - количество вершин (размер массивов)
 */
void FreeMemory(int** adjList, int* sizes, int** matrix, int VertexCount) {
    if (adjList) {
        for (int i = 0; i < VertexCount; i++) {
            if (adjList[i]) free(adjList[i]);
        }
        free(adjList);
    }

    if (sizes) free(sizes);

    if (matrix) {
        for (int i = 0; i < VertexCount; i++) {
            if (matrix[i]) free(matrix[i]);
        }
        free(matrix);
    }
}


/**
 * @brief Основная функция преобразования списка смежности в матрицу смежности
 *
 * @note Функция предполагает наличие файла "Data.txt" в текущей директории
 * @note В случае ошибки открытия файла выводит сообщение об ошибке и завершает работу
 */
void List2Matrix() {
    setlocale(LC_CTYPE, "Russian");

    const char* ptrFile = "Data.txt";

    FILE* file = fopen(ptrFile, "r");
    if (!file) {
        printf("Ошибка открытия файла %s\n", ptrFile);
        return 1;
    }

    int maxVert = FindMaxVertex(file);
    int VertexCount = maxVert + 1;
    printf("Найдено вершин: %d\n", VertexCount);

    int** adjList = NULL;
    int* sizes = NULL;
    ReadAdjacencyList(file, &adjList, &sizes, VertexCount);

    int** matrix = CreateAdjacencyMatrix(adjList, sizes, VertexCount);

    PrintMatrix(matrix, VertexCount);

    FreeMemory(adjList, sizes, matrix, VertexCount);
    fclose(file);
}