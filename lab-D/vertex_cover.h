#ifndef VERTEX_COVER_H
#define VERTEX_COVER_H

#include <stdbool.h>

#define MAX_VERTICES 1000

// Структура графа
typedef struct {
    int adj[MAX_VERTICES + 1][MAX_VERTICES + 1]; // Матрица смежности (индексы с 1)
    int degree[MAX_VERTICES + 1]; // Степени вершин
    int vertex_count; // Количество вершин
} Graph;

// Функции для работы с графом
void init_graph(Graph* g, int vertex_count);
void add_edge(Graph* g, int u, int v);
bool read_graph_from_file(const char* filename, Graph* g, int* K);

// Алгоритм вершинного покрытия
bool find_vertex_cover(Graph* g, int K, int cover[], int* cover_size);
void find_vertex_cover_recursive(Graph* g, int K, int cover[], int* cover_size,
    int current_vertex, int current_size,
    bool visited[]);

// Вспомогательные функции
void remove_vertex(Graph* g, int v, bool visited[]);
void restore_vertex(Graph* g, int v, int saved_degree, int saved_adj[]);
bool is_vertex_cover(Graph* g, bool covered[]);

// Основная функция для файлового ввода/вывода
void solve_vertex_cover(const char* input_file, const char* output_file);

#endif // VERTEX_COVER_H