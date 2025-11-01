#include "func.h"
#include <string.h>

// Узел списка смежности
 struct Node{
    int vertex;
    struct Node* next;
 };

// Список смежности
 struct Graph{
    int numVertices;
    struct Node** node_list;
 };

// Создание узла
 struct Node* create_node(int v){
    struct Node* new_node=(struct Node*)malloc(sizeof(struct Node));
    new_node->vertex=v;
    new_node->next=NULL;
    return new_node;
 }
 // Создание списка смежности
 struct Graph* create_graph(int vertuces){
    struct Graph* new_graph=(struct Graph*)malloc(sizeof(struct Graph));
    new_graph->numVertices=vertuces;

    new_graph->node_list=(struct Node**)malloc(vertuces*sizeof(struct Node*));
    for(int i=0;i<vertuces;i++){
        new_graph->node_list[i]=NULL;
    }
    return new_graph;
 }
// Добавление ребра в список
void addEdge(struct Graph* graph, int i, int j){
    // Проверяем нет ли уже такого ребра
    struct Node* current = graph->node_list[i];
    while (current != NULL) {
        if (current->vertex == j) {
            return; // ребро уже существует, выходим
        }
        current = current->next;
    }
    
    // Добавляем новое ребро
    struct Node* newNode = create_node(j);
    newNode->next = graph->node_list[i];
    graph->node_list[i] = newNode;
}


// Функция для чтения списка смежностей из файла
struct Graph* readAdjacencyList(const char* filename, int* n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return NULL;
    }
    
    // Читаем количество вершин
    fscanf(file, "%d", n);
    
    struct Graph* graph = create_graph(*n);
    
    // Читаем каждую строку
    for (int i = 0; i < *n; i++) {
        int vertex;
        fscanf(file, "%d:", &vertex);  // Читаем "число:"
        
        // Читаем смежные вершины до конца строки
        char line[100];
        fgets(line, sizeof(line), file);  // читаем всю остальную строку
        
        char* ptr = line;
        int adjVertex;
        // Парсим числа из строки
        while (sscanf(ptr, "%d", &adjVertex) == 1) {
            addEdge(graph, vertex, adjVertex);
            // Перемещаем указатель на следующее число
            while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '\n') ptr++;
            while (*ptr == ' ' || *ptr == '\t') ptr++;
        }
    }
    
    fclose(file);
    return graph;
}

// Функция для построения матрицы смежности из списка смежностей
int** buildAdjacencyMatrix(struct Graph* graph) {
    int n = graph->numVertices;
    
    // Создаем матрицу n x n, заполненную нулями
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));  // calloc заполняет нулями
    }
    
    // Заполняем матрицу на основе списка смежностей
    for (int i = 0; i < n; i++) {
        struct Node* current = graph->node_list[i];
        while (current != NULL) {
            int j = current->vertex;
            matrix[i][j] = 1;
            current = current->next;
        }
    }
    
    return matrix;
}

// Функция для печати списка смежностей
void printAdjacencyList(struct Graph* graph) {
    printf("List:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->node_list[i];
        printf("Vertex %d: ", i);
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Функция для печати матрицы смежности
void printAdjacencyMatrix(int** matrix, int n) {
    printf("Matrix: (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для освобождения памяти графа
void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->node_list[i];
        while (temp) {
            struct Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(graph->node_list);
    free(graph);
}

// Функция для освобождения памяти матрицы
void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

