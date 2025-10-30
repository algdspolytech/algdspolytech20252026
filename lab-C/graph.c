#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "graph.h"

#define MAX_VERTICES 100
#define INF INT_MAX

// Полное определение структуры Queue
struct Queue {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
};

// Функции для работы с очередью
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

void enqueue(Queue* queue, int value) {
    if (queue->size < queue->capacity) {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->data[queue->rear] = value;
        queue->size++;
    }
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return -1;
    }
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return value;
}

void freeQueue(Queue* queue) {
    free(queue->data);
    free(queue);
}

// Функции для работы с графом
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->matrix = (int**)malloc(vertices * sizeof(int*));

    for (int i = 0; i < vertices; i++) {
        graph->matrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }
    return graph;
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph);
}

Graph* readGraphFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return NULL;
    }

    int vertices;
    fscanf(file, "%d", &vertices);

    Graph* graph = createGraph(vertices);

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            fscanf(file, "%d", &graph->matrix[i][j]);
        }
    }

    fclose(file);
    return graph;
}

// Функция поиска кратчайшего пути (BFS)
int* findShortestPath(Graph* graph, int start, int end, int* pathLength) {
    if (start < 0 || start >= graph->vertices || end < 0 || end >= graph->vertices) {
        *pathLength = 0;
        return NULL;
    }

    if (start == end) {
        int* path = (int*)malloc(sizeof(int));
        path[0] = start;
        *pathLength = 1;
        return path;
    }

    int* visited = (int*)calloc(graph->vertices, sizeof(int));
    int* parent = (int*)malloc(graph->vertices * sizeof(int));
    int* distance = (int*)malloc(graph->vertices * sizeof(int));

    for (int i = 0; i < graph->vertices; i++) {
        parent[i] = -1;
        distance[i] = -1;
    }

    Queue* queue = createQueue(graph->vertices);

    visited[start] = 1;
    distance[start] = 0;
    enqueue(queue, start);

    int found = 0;

    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);

        if (current == end) {
            found = 1;
            break;
        }

        for (int neighbor = 0; neighbor < graph->vertices; neighbor++) {
            if (graph->matrix[current][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = 1;
                parent[neighbor] = current;
                distance[neighbor] = distance[current] + 1;
                enqueue(queue, neighbor);
            }
        }
    }

    freeQueue(queue);
    free(visited);
    free(distance);

    if (!found) {
        free(parent);
        *pathLength = 0;
        return NULL;
    }

    // Восстановление пути
    int* path = NULL;
    *pathLength = 0;

    // Подсчет длины пути
    int temp = end;
    while (temp != -1) {
        (*pathLength)++;
        temp = parent[temp];
    }

    path = (int*)malloc((*pathLength) * sizeof(int));
    temp = end;
    for (int i = *pathLength - 1; i >= 0; i--) {
        path[i] = temp;
        temp = parent[temp];
    }

    free(parent);
    return path;
}

void printPath(int* path, int pathLength) {
    if (path == NULL || pathLength == 0) {
        printf("No path exists\n");
        return;
    }

    printf("Shortest path: ");
    for (int i = 0; i < pathLength; i++) {
        printf("%d", path[i]);
        if (i < pathLength - 1) {
            printf(" -> ");
        }
    }
    printf("\nPath length: %d edges\n", pathLength - 1);
}