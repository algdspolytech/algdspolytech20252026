// hamiltonian.c
/**
 * @file hamiltonian.c
 * @brief Реализация функций для поиска гамильтонова пути
 *
 * @version 1.0
 * @date 2025.12.21
 * @author Д.Смирнов
 */

#pragma warning(disable:4996)

#include "hamiltonian.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int adj[MAX_VERTICES + 1][MAX_VERTICES + 1] = { 0 };
int visited[MAX_VERTICES + 1] = { 0 };
int path[MAX_VERTICES] = { 0 };
int n = 0;

/**
 * @brief Функция инициализации данных
 */ 
void initializeData() {
    memset(adj, 0, sizeof(adj));
    memset(visited, 0, sizeof(visited));
    memset(path, 0, sizeof(path));
    n = 0;
}


/**
 * @brief Чтение графа из файла
 *
 * @param[in] filename - имя открываемого файла
 *
 * @return Количество вершин
 */
int readGraphFromFile(const char* filename) {
    FILE* input = fopen(filename, "r");
    if (!input) {
        printf("Ошибка открытия файла %s.\n", filename);
        return 0;
    }

    // Чтение количества вершин
    if (fscanf(input, "%d", &n) != 1) {
        printf("Ошибка чтения количества вершин.\n");
        fclose(input);
        return 0;
    }

    // Чтение рёбер до конца файла
    int u, v;
    while (fscanf(input, "%d %d", &u, &v) == 2) {
        adj[u][v] = adj[v][u] = 1; // граф неориентированный
    }

    fclose(input);
    return 1;
}


/**
 * @brief Рекурсивная функция для поиска гамильтонова пути
 *
 * @param[in] current - текущая вершина
 * @param[in] step - путь
 *
 * @return Количество вершин
 */
int Hamiltonian(int current, int step) {
    path[step - 1] = current; // добавляем текущую вершину в путь

    // Если путь содержит все вершины — путь найден
    if (step == n) {
        return 1;
    }

    // Перебираем все возможные следующие вершины
    for (int next = 1; next <= n; next++) {
        // Проверяем, есть ли ребро и не посещена ли вершина
        if (adj[current][next] && !visited[next]) {
            visited[next] = 1;
            if (Hamiltonian(next, step + 1)) {
                return 1;
            }
            visited[next] = 0; // откат
        }
    }

    return 0;
}


/**
 * @brief Функция поиска гамильтонова пути с любой стартовой вершины
 *
 * @return Результат поиска
 */
int HamiltonianFromAnyVertex() {
    // Перебор всех вершин в качестве начальной
    for (int start = 1; start <= n; start++) {
        memset(visited, 0, sizeof(visited)); // сброс посещений
        visited[start] = 1; // отмечаем начальную вершину

        if (Hamiltonian(start, 1)) {
            return 1;
        }
    }

    return 0;
}


/**
 * @brief Функция записи результата в файл
 *
 * @param[in] filename - имя открываемого файла
 * @param[in] found - результат
 */
void writeResultToFile(const char* filename, int found) {
    FILE* output = fopen(filename, "w");
    if (!output) {
        printf("Ошибка открытия файла %s для записи.\n", filename);
        return;
    }

    // Вывод результата
    if (found) {
        for (int i = 0; i < n; i++) {
            fprintf(output, "%d ", path[i]);
        }
    }
    else {
        fprintf(output, "0");
    }

    fclose(output);
}


/**
 * @brief Основная функция
 */
void HumiltonianFinder() {
    initializeData();

    // Чтение графа из файла
    if (!readGraphFromFile("input.txt")) {
        return;
    }

    // Поиск гамильтонова пути
    int found = HamiltonianFromAnyVertex();

    // Запись результата в файл
    writeResultToFile("output.txt", found);
}