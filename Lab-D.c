#include <stdio.h>
#include <stdlib.h>
#include "Lab-D.h"
#pragma warning(disable:4996)

Graph* CreateGraph(int vertice, int edge) {
    if (vertice >= MAX_VERTICE || vertice <= 0) {
        return NULL;
    }

    if (edge < 0) {
        return NULL;
    }

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        return NULL;
    }

    graph->vertice = vertice;
    graph->edge = edge;

    return graph;
}

Graph* ReadGraph(const char* filename, Graph* graph, int K) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    int vertice, edge;
    if (fscanf(file, "%d %d", &vertice, &edge) != 2) {
        fclose(file);
        return NULL;
    }

    if (vertice >= MAX_VERTICE || vertice <= 0) {
        fclose(file);
        return NULL;
    }

    if (K > vertice || K <= 0) {
        fclose(file);
        return NULL;
    }

    if (graph == NULL) {
        graph = CreateGraph(vertice, edge);
    }
    else {
        graph->vertice = vertice;
        graph->edge = edge;
    }

    fclose(file);
    return graph;
}

void WriteGraph(const char* filename, Graph* graph, int K) {
    if (!graph || K <= 0 || K > graph->vertice) {
        return NULL;
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        return NULL;
    }

    fprintf(file, "%d %d\n", graph->vertice, graph->edge);
    fprintf(file, "K = %d\n", K);

    fclose(file);
}

void DestroyGraph(Graph* graph) {
    if (graph) {
        free(graph);
    }
}

int CountEdges(Graph* graph) {
    if (!graph) return 0;

    int count = 0;
    for (int i = 0; i < graph->vertice; i++) {
        for (int j = i + 1; j < graph->vertice; j++) {
            if (graph->adjacency[i][j]) {
                count++;
            }
        }
    }
    return count;
}

void GetEdges(Graph* graph, int* edges_u, int* edges_v, int* edge_count) {
    if (!graph || !edges_u || !edges_v || !edge_count) return;

    *edge_count = 0;
    for (int i = 0; i < graph->vertice; i++) {
        for (int j = i + 1; j < graph->vertice; j++) {
            if (graph->adjacency[i][j]) {
                edges_u[*edge_count] = i;
                edges_v[*edge_count] = j;
                (*edge_count)++;
            }
        }
    }
}

void RemoveIncidentEdges(Graph* graph, int vertex, int* edges_u, int* edges_v, int* edge_count) {
    if (!graph || !edges_u || !edges_v || !edge_count || vertex < 0 || vertex >= graph->vertice) {
        return;
    }

    int new_count = 0;
    for (int i = 0; i < *edge_count; i++) {
        if (edges_u[i] != vertex && edges_v[i] != vertex) {
            edges_u[new_count] = edges_u[i];
            edges_v[new_count] = edges_v[i];
            new_count++;
        }
    }
    *edge_count = new_count;
}

bool IsCoverValid(Graph* graph, int* cover, int cover_size) {
    if (!graph || !cover) return false;

    int** temp = (int**)malloc(graph->vertice * sizeof(int*));
    for (int i = 0; i < graph->vertice; i++) {
        temp[i] = (int*)malloc(graph->vertice * sizeof(int));
        memcpy(temp[i], graph->adjacency[i], graph->vertice * sizeof(int));
    }

    for (int c = 0; c < cover_size; c++) {
        int v = cover[c];
        for (int i = 0; i < graph->vertice; i++) {
            temp[v][i] = 0;
            temp[i][v] = 0;
        }
    }

    bool has_edges = false;
    for (int i = 0; i < graph->vertice && !has_edges; i++) {
        for (int j = 0; j < graph->vertice && !has_edges; j++) {
            if (temp[i][j]) {
                has_edges = true;
            }
        }
    }

    for (int i = 0; i < graph->vertice; i++) {
        free(temp[i]);
    }
    free(temp);

    return !has_edges;
}

bool VertexCoverUtil(Graph* graph, int* edges_u, int* edges_v, int edge_count, int K) {
    if (edge_count == 0) return true;
    if (K == 0) return false;

    int u = edges_u[0];
    int v = edges_v[0];

    int* new_edges_u = (int*)malloc(edge_count * sizeof(int));
    int* new_edges_v = (int*)malloc(edge_count * sizeof(int));

    int new_count = 0;
    for (int i = 0; i < edge_count; i++) {
        if (edges_u[i] != u && edges_v[i] != u) {
            new_edges_u[new_count] = edges_u[i];
            new_edges_v[new_count] = edges_v[i];
            new_count++;
        }
    }

    bool result = VertexCoverUtil(graph, new_edges_u, new_edges_v, new_count, K - 1);
    if (result) {
        free(new_edges_u);
        free(new_edges_v);
        return true;
    }

    return result;
}

bool CheckVertexCover(Graph* graph, int K) {
    if (!graph || K > graph->vertice || K < 0) {
        return false;
    }

    int edge_count = CountEdges(graph);
    if (edge_count == 0) return true;

    int* edges_u = (int*)malloc(edge_count * sizeof(int));
    int* edges_v = (int*)malloc(edge_count * sizeof(int));

    GetEdges(graph, edges_u, edges_v, &edge_count);

    bool result = VertexCoverUtil(graph, edges_u, edges_v, edge_count, K);

    free(edges_u);
    free(edges_v);

    return result;
}

void FindVertexCover(Graph* graph, int K, int* cover, int* cover_size) {
    *cover_size = 0;
    if (!graph || K <= 0 || !cover) {
        return;
    }

    int** temp_adj = (int**)malloc(graph->vertice * sizeof(int*));
    for (int i = 0; i < graph->vertice; i++) {
        temp_adj[i] = (int*)malloc(graph->vertice * sizeof(int));
        memcpy(temp_adj[i], graph->adjacency[i], graph->vertice * sizeof(int));
    }

    while (*cover_size < K) {
        int max_degree = -1;
        int max_vertex = -1;

        for (int i = 0; i < graph->vertice; i++) {
            int degree = 0;
            for (int j = 0; j < graph->vertice; j++) {
                if (temp_adj[i][j]) {
                    degree++;
                }
            }

            if (degree > max_degree) {
                max_degree = degree;
                max_vertex = i;
            }
        }

        if (max_degree == 0) {
            break;
        }
        cover[(*cover_size)++] = max_vertex;

        for (int i = 0; i < graph->vertice; i++) {
            temp_adj[max_vertex][i] = 0;
            temp_adj[i][max_vertex] = 0;
        }
    }
    for (int i = 0; i < graph->vertice; i++) {
        free(temp_adj[i]);
    }
    free(temp_adj);
}