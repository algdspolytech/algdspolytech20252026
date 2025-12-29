#include "graph.h"

/* Создание узла */
GraphNode* node_create(int toVertex) {
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    if (!node) return NULL;
    node->toVertex = toVertex;
    node->next = NULL;
    return node;
}

/* Создание графа */
Graph* graph_create(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;

    graph->vertexCount = vertices;
    graph->adjacencyLists = (GraphNode**)calloc(vertices, sizeof(GraphNode*));
    return graph;
}

/* Добавление ребра (без дубликатов) */
int graph_add_edge(Graph* graph, int from, int to) {
    if (!graph || from < 0 || to < 0 ||
        from >= graph->vertexCount || to >= graph->vertexCount)
        return 0;

    GraphNode* cur = graph->adjacencyLists[from];
    while (cur) {
        if (cur->toVertex == to)
            return 0; // уже существует
        cur = cur->next;
    }

    GraphNode* newNode = node_create(to);
    newNode->next = graph->adjacencyLists[from];
    graph->adjacencyLists[from] = newNode;
    return 1;
}

/* Чтение графа из файла */
Graph* graph_read_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    int n;
    fscanf(file, "%d", &n);
    Graph* graph = graph_create(n);

    for (int i = 0; i < n; i++) {
        int v;
        fscanf(file, "%d:", &v);

        char buffer[256];
        fgets(buffer, sizeof(buffer), file);

        char* p = buffer;
        int to;
        while (sscanf(p, "%d", &to) == 1) {
            graph_add_edge(graph, v, to);
            while (*p && *p != ' ') p++;
            while (*p == ' ') p++;
        }
    }

    fclose(file);
    return graph;
}

/* Построение матрицы смежности */
int** graph_to_matrix(const Graph* graph) {
    if (!graph) return NULL;

    int n = graph->vertexCount;
    int** matrix = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++)
        matrix[i] = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        GraphNode* cur = graph->adjacencyLists[i];
        while (cur) {
            matrix[i][cur->toVertex] = 1;
            cur = cur->next;
        }
    }
    return matrix;
}

/* Очистка памяти */
void graph_destroy(Graph* graph) {
    if (!graph) return;

    for (int i = 0; i < graph->vertexCount; i++) {
        GraphNode* cur = graph->adjacencyLists[i];
        while (cur) {
            GraphNode* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(graph->adjacencyLists);
    free(graph);
}

void matrix_destroy(int** matrix, int size) {
    if (!matrix) return;
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}
#include "graph.h"

/* Создание узла */
GraphNode* node_create(int toVertex) {
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    if (!node) return NULL;
    node->toVertex = toVertex;
    node->next = NULL;
    return node;
}

/* Создание графа */
Graph* graph_create(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) return NULL;

    graph->vertexCount = vertices;
    graph->adjacencyLists = (GraphNode**)calloc(vertices, sizeof(GraphNode*));
    return graph;
}

/* Добавление ребра (без дубликатов) */
int graph_add_edge(Graph* graph, int from, int to) {
    if (!graph || from < 0 || to < 0 ||
        from >= graph->vertexCount || to >= graph->vertexCount)
        return 0;

    GraphNode* cur = graph->adjacencyLists[from];
    while (cur) {
        if (cur->toVertex == to)
            return 0; // уже существует
        cur = cur->next;
    }

    GraphNode* newNode = node_create(to);
    newNode->next = graph->adjacencyLists[from];
    graph->adjacencyLists[from] = newNode;
    return 1;
}

/* Чтение графа из файла */
Graph* graph_read_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    int n;
    fscanf(file, "%d", &n);
    Graph* graph = graph_create(n);

    for (int i = 0; i < n; i++) {
        int v;
        fscanf(file, "%d:", &v);

        char buffer[256];
        fgets(buffer, sizeof(buffer), file);

        char* p = buffer;
        int to;
        while (sscanf(p, "%d", &to) == 1) {
            graph_add_edge(graph, v, to);
            while (*p && *p != ' ') p++;
            while (*p == ' ') p++;
        }
    }

    fclose(file);
    return graph;
}

/* Построение матрицы смежности */
int** graph_to_matrix(const Graph* graph) {
    if (!graph) return NULL;

    int n = graph->vertexCount;
    int** matrix = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++)
        matrix[i] = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        GraphNode* cur = graph->adjacencyLists[i];
        while (cur) {
            matrix[i][cur->toVertex] = 1;
            cur = cur->next;
        }
    }
    return matrix;
}

/* Очистка памяти */
void graph_destroy(Graph* graph) {
    if (!graph) return;

    for (int i = 0; i < graph->vertexCount; i++) {
        GraphNode* cur = graph->adjacencyLists[i];
        while (cur) {
            GraphNode* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(graph->adjacencyLists);
    free(graph);
}

void matrix_destroy(int** matrix, int size) {
    if (!matrix) return;
    for (int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);
}
