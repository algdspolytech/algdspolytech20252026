#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



typedef struct {
    int* data;
    int size;
}Vec;

 typedef struct {
     Vec* adj;
     int size;
 }Graph;

 void init_vec(Vec* v);
 void vec_add_to_data(Vec* v);
 void vec_push(Vec* v, int x);
 void vec_free(Vec* v);

 void init_graph(Graph* g);
 void add_adj_to_graph(Graph* g, int n);
 void graph_free(Graph* g);

 int read_adjlist_file(const char* path, Graph* g);
 void print_graph(const Graph* g);
 int read_adjmatrix_file(const char* path, Graph* g);
 int graphs_equal(const Graph* a, const Graph* b);
