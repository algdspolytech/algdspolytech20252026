#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 1000

typedef struct {
    int V, K;
    int** adj;
    int* deg;
    int* used;
    int* best;
    int found;
} GraphData;

// utility

void free_graph(GraphData* g) {
    if (!g) return;

    if (g->adj) {
        for (int i = 1; i <= g->V; i++)
            free(g->adj[i]);
        free(g->adj);
    }
    free(g->deg);
    free(g->used);
    free(g->best);

    memset(g, 0, sizeof(GraphData));
}

// read graph

int read_graph_from_file(const char* filename, GraphData* g) {
    if (!filename || !g) return 0;

    FILE* fin = fopen(filename, "r");
    if (!fin) return 0;

    memset(g, 0, sizeof(GraphData));

    // Чтение V и K
    if (fscanf(fin, "%d %d", &g->V, &g->K) != 2 ||
        g->V <= 0 || g->V > MAXV ||
        g->K <= 0 || g->K > g->V) {
        printf("Input format error\n");
        fclose(fin);
        return 0;
    }

    // Выделяем память
    g->adj = (int**)calloc(g->V + 1, sizeof(int*));
    g->deg = (int*)calloc(g->V + 1, sizeof(int));
    g->used = (int*)calloc(g->V + 1, sizeof(int));
    g->best = (int*)calloc(g->V + 1, sizeof(int));
    g->found = 0;

    if (!g->adj || !g->deg || !g->used || !g->best) {
        printf("Input format error\n");
        free_graph(g);
        fclose(fin);
        return 0;
    }

    char line[6000];
    fgets(line, sizeof(line), fin); // пропускаем остаток первой строки

    for (int i = 1; i <= g->V; i++) {
        g->adj[i] = (int*)malloc(sizeof(int) * g->V);
        if (!g->adj[i]) {
            printf("Input format error\n");
            free_graph(g);
            fclose(fin);
            return 0;
        }

        if (!fgets(line, sizeof(line), fin) || line[0] == '\n' || line[0] == '\0') {
            // Пустая строка считается ошибкой
            printf("Input format error\n");
            free_graph(g);
            fclose(fin);
            return 0;
        }

        char* p = line;
        int u;
        while (*p) {
            if (sscanf(p, "%d", &u) != 1 || u < 1 || u > g->V || u == i || g->deg[i] >= g->V) {
                printf("Input format error\n");
                free_graph(g);
                fclose(fin);
                return 0;
            }
            g->adj[i][g->deg[i]++] = u;

            // Пропускаем до следующего числа
            while (*p && *p != ' ') p++;
            while (*p == ' ') p++;
        }
    }

    fclose(fin);
    return 1; // успешное чтение
}


// algorithm

int all_edges_covered(GraphData* g) {
    for (int v = 1; v <= g->V; v++) {
        if (!g->used[v]) {
            for (int i = 0; i < g->deg[v]; i++) {
                int u = g->adj[v][i];
                if (!g->used[u])
                    return 0;
            }
        }
    }
    return 1;
}

void backtrack(GraphData* g, int vertex, int chosen) {
    if (g->found) return;
    if (chosen > g->K) return;

    if (vertex > g->V) {
        if (all_edges_covered(g)) {
            for (int i = 1; i <= g->V; i++)
                g->best[i] = g->used[i];
            g->found = 1;
        }
        return;
    }

    g->used[vertex] = 1;
    backtrack(g, vertex + 1, chosen + 1);

    if (g->found) return;

    g->used[vertex] = 0;
    backtrack(g, vertex + 1, chosen);
}

// main solver

int solve_vertex_cover(const char* input_file, const char* output_file) {
    GraphData g;
    if (!read_graph_from_file(input_file, &g))
        return -1;

    backtrack(&g, 1, 0);

    FILE* fout = fopen(output_file, "w");
    if (!fout) {
        printf("Cannot open output file\n");
        free_graph(&g);
        return -1;
    }

    if (!g.found) {
        fprintf(fout, "0\n");
        free_graph(&g);
        fclose(fout);
        return 0;
    }

    for (int i = 1; i <= g.V; i++)
        if (g.best[i])
            fprintf(fout, "%d ", i);
    fprintf(fout, "\n");

    free_graph(&g);
    fclose(fout);
    return 1;
}

/*

int main() {
    int res = solve_vertex_cover("input2.txt", "output.txt");
    if (res) {
        printf("Done.\n");
    } else {
        printf("No vertex cover found with given K.\n");
    }
    return 0;
}

*/