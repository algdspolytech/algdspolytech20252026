#include "Adj_Graph_to_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FILENAME
#define FILENAME "adjacency_matrix.txt"
#endif

AdjListNode* newAdjListNode(int dest) {
  AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
  if (newNode == NULL) {
    perror("Ошибка выделения памяти для узла");
    exit(EXIT_FAILURE);
  }
  newNode->dest = dest;
  newNode->next = NULL;
  return newNode;
}

Graph* createGraph(int V) {
  Graph* graph = (Graph*)malloc(sizeof(Graph));
  if (graph == NULL) {
    perror("Ошибка выделения памяти для графа");
    exit(EXIT_FAILURE);
  }
  graph->V = V;

  graph->head = (AdjListNode**)malloc(V * sizeof(AdjListNode*));
  if (graph->head == NULL) {
    perror("Ошибка выделения памяти для массива head");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < V; ++i) {
    graph->head[i] = NULL;
  }
  return graph;
}

void addEdge(Graph* graph, int src, int dest) {
  // Добавляем ребро src -> dest
  AdjListNode* newNode = newAdjListNode(dest);
  newNode->next = graph->head[src];
  graph->head[src] = newNode;

  // Граф неориентированный: добавляем ребро dest -> src
  newNode = newAdjListNode(src);
  newNode->next = graph->head[dest];
  graph->head[dest] = newNode;
}

Graph* matrixToList() {
  FILE* file = fopen(FILENAME, "r");
  if (file == NULL) {
    perror("Ошибка открытия файла adjacency_matrix.txt");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  if (ftell(file) == 0) {
    fclose(file);
    return NULL;
  }
  fseek(file, 0, SEEK_SET);

  int matrix[MAX_VERTICES][MAX_VERTICES];
  int V = 0;
  int temp_val;
  int cols = 0;

  while (V < MAX_VERTICES && fscanf(file, "%d", &temp_val) == 1) {
    matrix[V][cols] = temp_val;
    cols++;

    // Проверяем конец строки или конец файла
    int c = fgetc(file);
    if (c == '\n' || c == EOF) {
      V++;
      cols = 0;
    } else {
      ungetc(c, file);
    }
  }
  fclose(file);

  if (V == 0) {
    return NULL;
  }

  if (cols > 0) {
  }

  Graph* graph = createGraph(V);

  // Преобразование матрицы смежности в список смежности
  for (int i = 0; i < V; i++) {
    for (int j_inner = 0; j_inner < V; j_inner++) {
      // Убеждаемся, что мы в границах и значение равно 1, и это не петля
      if (i < V && j_inner < V && matrix[i][j_inner] == 1 && i != j_inner) {
        // Добавляем ребро только один раз для неориентированного графа
        if (j_inner > i) {
          addEdge(graph, i, j_inner);
        }
      }
    }
  }

  return graph;
}

void printGraph(Graph* graph) {
  int v;
  for (v = 0; v < graph->V; ++v) {
    AdjListNode* current = graph->head[v];
    printf("\nСписок смежности вершины %d:\n head ", v);
    while (current) {
      printf("-> %d", current->dest);
      current = current->next;
    }
    printf("\n");
  }
}
