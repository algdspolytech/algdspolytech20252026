#ifndef GRAPH_LIB_H
#define GRAPH_LIB_H

// Стркутура-граф
typedef struct grapt_t {
  int n;              // вершины
  int m;              // ребра
  double **adjacency; // таблица смежностей
} graph_t;

// Структура-информация о пути до каждой вершины
typedef struct path_t {
  double *pi; // предшественник
  double *d;  // кратчайший путь до заданной вершины
} path_t;

// Считывание графа из файла в формате матрицы смежностей
graph_t *read_graph(const char *filename);

// Очистка памяти, занимаемой графом
void free_graph(graph_t *graph);

// Вывод графа в консоль
void print_graph(graph_t *graph);

// Создание структуры-путей
path_t *make_path(int n, int s);

// Очистка структуры-путей
void free_path(path_t *path);

// Метод релаксации для вершин u, v
void relax(graph_t *graph, int u, int v, double *d, double *pi);

// Алгоритм Беллмана-Форда: сохраняет в path параметры кратчайших путей
// Возвращает отсутствие петель с отрицательным весом
bool bellman_ford(graph_t *graph, path_t *path, int s, int e);

// Возвращает длину кратчайшего пути из вершины s в e по графу из файла
// Выводит в консоль граф и длину кратчайшего пути
double nodes_distance(int s, int e, const char *filename);

#endif