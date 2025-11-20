#pragma once
#include <stdio.h>
#include <stdlib.h>

#ifndef VERTEX_COVER_H
#define VERTEX_COVER_H


// Структура для представления ребра графа
typedef struct {
    int u;  // первая вершина ребра
    int v;  // вторая вершина ребра
} Edge;

// Структура для представления графа
typedef struct {
    Edge* edges;       // массив ребер
    int edge_count;    // количество ребер
    int vertex_count;  // количество вершин
} Graph;

// Структура для представления доминирующего множества
typedef struct {
    int* vertices;    // массив вершин множества
    int count;        // количество вершин в множестве
} VertexCover;

// Функции для работы с графом
Graph* init_graph();
void free_graph(Graph* g);
Graph* load_graph(char* filename, int* k);

// Функции для работы с доминирующим множеством
VertexCover* init_vertex_cover(void);
void free_vertex_cover(VertexCover* ds);
void add_vertex(VertexCover* ds, int vertex);
int check_cover(Graph* g, VertexCover* ds);
VertexCover* find_vertex_cover(Graph* g, int k, int current_vertex);

// Вспомогательные функции
void write_vertex_cover(VertexCover* ds, char* filename);


#endif // VERTEX_COVER_H