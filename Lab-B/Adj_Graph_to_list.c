#include "Adj_Graph_to_list.h"

// Создание графа с n вершинами
Graph* create_graph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = vertices;
    graph->adj_lists = (Node**)calloc(vertices, sizeof(Node*));
    return graph;
}

// Добавление ребра src → dest
void add_edge(Graph* graph, int src, int dest) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->vertex = dest;
    new_node->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node;
}

// Чтение графа из файла с матрицей смежности
Graph* read_graph_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Не удалось открыть файл");
        exit(1);
    }

    int size = 0;
    char ch;
    while ((ch = fgetc(file)) != '\n' && ch != EOF) {
        if (ch == ' ')
            continue;
        size++;
    }

    rewind(file);

    Graph* graph = create_graph(size);
    int value;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fscanf_s(file, "%d", &value) == 1 && value == 1) {
                add_edge(graph, i, j);
            }
        }
    }

    fclose(file);
    return graph;
}

// Печать списка смежности
void print_graph(const Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("%d:", i);
        Node* temp = graph->adj_lists[i];
        while (temp) {
            printf(" %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Освобождение памяти
void free_graph(Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        Node* temp = graph->adj_lists[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adj_lists);
    free(graph);
}