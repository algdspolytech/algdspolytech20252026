#include "vertex_cover.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Инициализация графа
void init_graph(Graph* g, int vertex_count) {
    g->vertex_count = vertex_count;
    for (int i = 1; i <= vertex_count; i++) {
        g->degree[i] = 0;
        for (int j = 1; j <= vertex_count; j++) {
            g->adj[i][j] = 0;
        }
    }
}

// Добавление ребра
void add_edge(Graph* g, int u, int v) {
    if (u < 1 || u > g->vertex_count || v < 1 || v > g->vertex_count) {
        return;
    }

    // Проверяем, нет ли уже такого ребра
    for (int i = 1; i <= g->degree[u]; i++) {
        if (g->adj[u][i] == v) {
            return;
        }
    }

    // Добавляем ребро в обе стороны
    g->adj[u][++g->degree[u]] = v;
    g->adj[v][++g->degree[v]] = u;
}

// Чтение графа из файла
bool read_graph_from_file(const char* filename, Graph* g, int* K) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return false;
    }

    int vertex_count;
    if (fscanf(file, "%d %d", &vertex_count, K) != 2) {
        fclose(file);
        return false;
    }

    if (vertex_count > MAX_VERTICES || *K <= 0 || *K > vertex_count) {
        fclose(file);
        return false;
    }

    init_graph(g, vertex_count);

    char line[4096];
    fgets(line, sizeof(line), file); // Читаем остаток строки

    for (int i = 1; i <= vertex_count; i++) {
        if (!fgets(line, sizeof(line), file)) {
            break;
        }

        char* token = strtok(line, " \t\n");
        while (token != NULL) {
            int neighbor = atoi(token);
            if (neighbor >= 1 && neighbor <= vertex_count && neighbor != i) {
                add_edge(g, i, neighbor);
            }
            token = strtok(NULL, " \t\n");
        }
    }

    fclose(file);
    return true;
}

// Проверка, является ли множество вершин покрытием
bool is_vertex_cover(Graph* g, bool covered[]) {
    for (int u = 1; u <= g->vertex_count; u++) {
        for (int i = 1; i <= g->degree[u]; i++) {
            int v = g->adj[u][i];
            if (u < v) { // Проверяем каждое ребро один раз
                if (!covered[u] && !covered[v]) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Удаление вершины (временное для алгоритма)
void remove_vertex(Graph* g, int v, bool visited[]) {
    visited[v] = true;
}

// Восстановление вершины
void restore_vertex(Graph* g, int v, int saved_degree, int saved_adj[]) {
    // Восстанавливаем смежные вершины
    for (int i = 1; i <= saved_degree; i++) {
        g->adj[v][i] = saved_adj[i];
    }
    g->degree[v] = saved_degree;
}

// Рекурсивный поиск вершинного покрытия
void find_vertex_cover_recursive(Graph* g, int K, int cover[], int* cover_size,
    int current_vertex, int current_size,
    bool visited[]) {

    // Базовые случаи
    if (current_size > K) {
        return;
    }

    if (current_vertex > g->vertex_count) {
        // Проверяем, является ли текущее множество покрытием
        bool covered[MAX_VERTICES + 1] = { false };
        for (int i = 0; i < current_size; i++) {
            covered[cover[i]] = true;
        }

        if (is_vertex_cover(g, covered)) {
            *cover_size = current_size;
            for (int i = 0; i < current_size; i++) {
                cover[i] = cover[i]; // Копируем результат
            }
        }
        return;
    }

    // Пропускаем уже удаленные вершины
    if (visited[current_vertex]) {
        find_vertex_cover_recursive(g, K, cover, cover_size,
            current_vertex + 1, current_size, visited);
        return;
    }

    // Случай 1: не включаем текущую вершину
    // Но тогда должны включить всех ее соседей
    bool temp_visited[MAX_VERTICES + 1];
    memcpy(temp_visited, visited, sizeof(temp_visited));

    int saved_adj[MAX_VERTICES + 1];
    int saved_degree = g->degree[current_vertex];
    memcpy(saved_adj, g->adj[current_vertex], sizeof(saved_adj));

    // Включаем всех соседей
    int neighbor_count = 0;
    int neighbors[MAX_VERTICES];
    for (int i = 1; i <= g->degree[current_vertex]; i++) {
        int neighbor = g->adj[current_vertex][i];
        if (!temp_visited[neighbor]) {
            neighbors[neighbor_count++] = neighbor;
            remove_vertex(g, neighbor, temp_visited);
        }
    }

    if (current_size + neighbor_count <= K) {
        int new_cover[MAX_VERTICES];
        memcpy(new_cover, cover, current_size * sizeof(int));
        for (int i = 0; i < neighbor_count; i++) {
            new_cover[current_size + i] = neighbors[i];
        }

        find_vertex_cover_recursive(g, K, new_cover, cover_size,
            current_vertex + 1, current_size + neighbor_count,
            temp_visited);

        if (*cover_size > 0 && *cover_size <= K) {
            memcpy(cover, new_cover, (*cover_size) * sizeof(int));
            return;
        }
    }

    // Восстанавливаем граф
    restore_vertex(g, current_vertex, saved_degree, saved_adj);
    for (int i = 1; i <= g->degree[current_vertex]; i++) {
        int neighbor = g->adj[current_vertex][i];
        temp_visited[neighbor] = visited[neighbor];
    }

    // Случай 2: включаем текущую вершину
    int new_cover[MAX_VERTICES];
    memcpy(new_cover, cover, current_size * sizeof(int));
    new_cover[current_size] = current_vertex;
    remove_vertex(g, current_vertex, temp_visited);

    find_vertex_cover_recursive(g, K, new_cover, cover_size,
        current_vertex + 1, current_size + 1,
        temp_visited);

    if (*cover_size > 0 && *cover_size <= K) {
        memcpy(cover, new_cover, (*cover_size) * sizeof(int));
    }
}

// Основная функция поиска вершинного покрытия
bool find_vertex_cover(Graph* g, int K, int cover[], int* cover_size) {
    *cover_size = 0;
    bool visited[MAX_VERTICES + 1] = { false };
    int temp_cover[MAX_VERTICES];

    find_vertex_cover_recursive(g, K, temp_cover, cover_size, 1, 0, visited);

    if (*cover_size > 0 && *cover_size <= K) {
        memcpy(cover, temp_cover, (*cover_size) * sizeof(int));
        return true;
    }

    return false;
}

// Решение задачи с файловым вводом/выводом
void solve_vertex_cover(const char* input_file, const char* output_file) {
    Graph g;
    int K;

    if (!read_graph_from_file(input_file, &g, &K)) {
        FILE* out = fopen(output_file, "w");
        if (out) {
            fprintf(out, "0\n");
            fclose(out);
        }
        return;
    }

    int cover[MAX_VERTICES];
    int cover_size;

    if (find_vertex_cover(&g, K, cover, &cover_size)) {
        FILE* out = fopen(output_file, "w");
        if (out) {
            for (int i = 0; i < cover_size; i++) {
                fprintf(out, "%d", cover[i]);
                if (i < cover_size - 1) {
                    fprintf(out, " ");
                }
            }
            if (cover_size == 0) {
                fprintf(out, "0");
            }
            fprintf(out, "\n");
            fclose(out);
        }
    }
    else {
        FILE* out = fopen(output_file, "w");
        if (out) {
            fprintf(out, "0\n");
            fclose(out);
        }
    }
}