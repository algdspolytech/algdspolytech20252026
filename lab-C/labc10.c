#include "labC10.h"

//Создание узла
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

//Создание графа
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVert = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));

    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

//Добавление ребра
void addEdge(Graph* graph, int st, int end) {
    Node* newNode = createNode(end);
    newNode->next = graph->adjLists[st];
    graph->adjLists[st] = newNode;
}

//Преобразование матрицы смежности в список
Graph* convertMatrixToList(int** matrix, int size) {
    Graph* graph = createGraph(size);

    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j >= 0; j--) {
            if (matrix[i][j] != 0) {
                addEdge(graph, i, j);
            }
        }
    }
    return graph;
}

//Печать графа
void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVert; v++) {
        Node* temp = graph->adjLists[v];
        printf("%d:", v);
        while (temp) {
            printf(" %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

//Освобождение памяти
void freeGraph(Graph* graph) {
    for (int v = 0; v < graph->numVert; v++) {
        Node* temp = graph->adjLists[v];
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(graph->adjLists);
    free(graph);
}

//Чтение матрицы смежности из файла
int** readMatrixFromFile(const char* filename, int* size) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        exit(1);
    }

    fscanf_s(file, "%d", size);
    int** matrix = (int**)malloc((*size) * sizeof(int*));
    for (int i = 0; i < *size; i++) {
        matrix[i] = (int*)malloc((*size) * sizeof(int));
        for (int j = 0; j < *size; j++) {
            fscanf_s(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
    return matrix;
}