#include <stdio.h>
#define SIZE 100

// 1.1 Описание структуры графа
typedef struct {
    int n;
    int matrix[SIZE][SIZE];
} Graph;

// 1.2 Инициализация графа и заполнение нулями
void init_graph(Graph* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->matrix[i][j] = 0;
        }
    }
}

// 1.3 Чтение из списка смежностей
void read_from_list(Graph* g, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error\n");
        return;
    }

    int n;
    fscanf(f, "%d", &n);
    init_graph(g, n);

    for (int i = 0; i < n; i++) {
        int k, v;
        fscanf(f, "%d", &k);
        for (int j = 0; j < k; j++) {
            fscanf(f, "%d", &v);
            g->matrix[i][v - 1] = 1;
            g->matrix[v - 1][i] = 1;
        }
    }
    fclose(f);
}

// 1.4 Чтение графа из матрицы смежности
void read_from_matrix(Graph* g, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error!\n");
        return;
    }
    int n;
    fscanf(f, "%d", &n);
    init_graph(g, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(f, "%d", &g->matrix[i][j]);
        }
    }
    fclose(f);
}

// 1.5 Сравнение двух графов
int compare_graphs(const Graph* a, const Graph* b) {
    if (a->n != b->n) return 0;

    for (int i = 0; i < a->n; i++)
        for (int j = 0; j < a->n; j++)
            if (a->matrix[i][j] != b->matrix[i][j]) return 0;

    return 1;
}

// 1.6 Вывод матрицы
void print_graph(const Graph* g) {
    printf("Adjacency matrix (%d nodes):\n", g->n);
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) printf("%d ", g->matrix[i][j]);
        printf("\n");
    }
}