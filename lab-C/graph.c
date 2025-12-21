#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void graph_init(Graph* g, int n) {
    if (!g || n <= 0 || n > MAX_NODES) return;
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->adj[i][j] = 0;
        }
    }
}

int graph_vertex_valid(const Graph* g, int v) {
    return g && v >= 1 && v <= g->n;
}

int graph_add_edge(Graph* g, int u, int v) {
    if (!g || !graph_vertex_valid(g, u) || !graph_vertex_valid(g, v)) return 0;
    
    u--;
    v--;
    
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
    
    return 1;
}

int graph_has_edge(const Graph* g, int u, int v) {
    if (!g || !graph_vertex_valid(g, u) || !graph_vertex_valid(g, v)) return -1;
    
    return g->adj[u-1][v-1];
}

int graph_edge_count(const Graph* g) {
    if (!g) return 0;
    
    int edges = 0;
    for (int i = 0; i < g->n; i++) {
        for (int j = i + 1; j < g->n; j++) {
            if (g->adj[i][j]) edges++;
        }
    }
    return edges;
}

int graph_load_from_file(Graph* g, const char* filename) {
    if (!filename || !g) return 0;
    
    FILE* f = fopen(filename, "r");
    if (!f) return 0;
    
    int n;
    if (fscanf(f, "%d", &n) != 1 || n <= 0 || n > MAX_NODES) {
        fclose(f);
        return 0;
    }
    
    while (fgetc(f) != '\n' && !feof(f));
    
    graph_init(g, n);
    
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {
        char* colon = strchr(buffer, ':');
        if (!colon) continue;
        
        *colon = '\0';
        int vertex = atoi(buffer);
        
        if (!graph_vertex_valid(g, vertex)) continue;
        
        char* neighbors = colon + 1;
        char* token = strtok(neighbors, " \t\n");
        
        while (token) {
            int neighbor = atoi(token);
            if (graph_vertex_valid(g, neighbor)) {
                graph_add_edge(g, vertex, neighbor);
            }
            token = strtok(NULL, " \t\n");
        }
    }
    
    fclose(f);
    return 1;
}

void graph_print_matrix(const Graph* g) {
    if (!g) return;
    
    printf("Матрица смежности (граф с %d вершинами):\n", g->n);
    
    printf("    ");
    for (int j = 0; j < g->n; j++) {
        printf("%3d", j + 1);
    }
    printf("\n");
    
    for (int i = 0; i < g->n; i++) {
        printf("%3d:", i + 1);
        for (int j = 0; j < g->n; j++) {
            printf("%3d", g->adj[i][j]);
        }
        printf("\n");
    }
}

int graph_save_matrix(const Graph* g, const char* filename) {
    if (!g || !filename) return 0;
    
    FILE* f = fopen(filename, "w");
    if (!f) return 0;
    
    fprintf(f, "%d\n", g->n);
    
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            fprintf(f, "%d ", g->adj[i][j]);
        }
        fprintf(f, "\n");
    }
    
    fclose(f);
    return 1;
}
