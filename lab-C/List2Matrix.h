// List2Matrix.h
/**
 * @file List2Matrix.h
 * @brief Заголовочный файл для преобразования списка смежности в матрицу смежности
 *
 * @version 1.0
 * @date 2025.12.21
 * @author Д.Смирнов
 */

#pragma once

#include <stdio.h>

 // Константы
#define BUF 1000

// Прототипы функций

int FindMaxVertex(FILE* file);
void ReadAdjacencyList(FILE* file, int*** adjList, int** sizes, int VertexCount);
int** CreateAdjacencyMatrix(int** adjList, int* sizes, int VertexCount);
void PrintMatrix(int** matrix, int VertexCount);
void FreeMemory(int** adjList, int* sizes, int** matrix, int VertexCount);
void List2Matrix(void);

void UnitTests(void);