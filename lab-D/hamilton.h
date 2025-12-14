#pragma once
#ifndef HAMILTON_H
#define HAMILTON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_V 1000


typedef struct {
    int n;                  
    int adj[MAX_V][MAX_V];  
    int degree[MAX_V];      
} Graph;


Graph* create_graph_from_file(const char* filename);
void free_graph(Graph* g);
bool find_hamiltonian_path(Graph* g, int path[], int start);
void print_path_to_file(const char* filename, int path[], int n);
bool is_valid_hamiltonian_path(Graph* g, int path[]);

#endif