#include "hamilton.h"
#include <string.h>

Graph* create_graph_from_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;

    int n;
    if (fscanf(f, "%d", &n) != 1 || n <= 0 || n >= MAX_V) {
        fclose(f);
        return NULL;
    }

    Graph* g = (Graph*)malloc(sizeof(Graph));
    if (!g) {
        fclose(f);
        return NULL;
    }

    g->n = n;
    memset(g->adj, 0, sizeof(g->adj));
    memset(g->degree, 0, sizeof(g->degree));

    for (int i = 0; i < n; i++) {
        int v;
        while (fscanf(f, "%d", &v) == 1 && v != 0) { 
            v--;  
            if (v >= 0 && v < n) {
                g->adj[i][v] = 1;
                g->adj[v][i] = 1;  
                g->degree[i]++;
            }
        }
        
        int c;
        while ((c = fgetc(f)) != EOF && c != '\n');
    }

    fclose(f);
    return g;
}

void free_graph(Graph* g) {
    free(g);
}


bool is_safe(int v, Graph* g, int path[], int pos) {
    if (pos == 0) return true;
    return g->adj[path[pos - 1]][v];
}


bool hamiltonian_util(Graph* g, int path[], bool visited[], int pos) {
    if (pos == g->n) return true;

    for (int v = 0; v < g->n; v++) {
        if (!visited[v] && is_safe(v, g, path, pos)) {
            visited[v] = true;
            path[pos] = v;

            if (hamiltonian_util(g, path, visited, pos + 1))
                return true;

            visited[v] = false;
        }
    }
    return false;
}


bool find_hamiltonian_path(Graph* g, int path[], int start) {
    bool visited[MAX_V] = { false };
    path[0] = start;
    visited[start] = true;

    if (hamiltonian_util(g, path, visited, 1))
        return true;

    return false;
}


void print_path_to_file(const char* filename, int path[], int n) {
    FILE* f = fopen(filename, "w");
    if (!f) return;

    if (n == 0) {
        fprintf(f, "0\n");
    }
    else {
        for (int i = 0; i < n; i++) {
            fprintf(f, "%d ", path[i] + 1);  
        }
        fprintf(f, "\n");
    }
    fclose(f);
}


bool is_valid_hamiltonian_path(Graph* g, int path[]) {
    if (!path) return false;
    bool visited[MAX_V] = { false };

    for (int i = 0; i < g->n; i++) {
        int u = path[i];
        if (u < 0 || u >= g->n || visited[u]) return false;
        visited[u] = true;

        if (i > 0 && !g->adj[path[i - 1]][u]) return false;
    }

    for (int i = 0; i < g->n; i++)
        if (!visited[i]) return false;

    return true;
}