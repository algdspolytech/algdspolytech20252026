#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cover.h"

bool read_graph(const char* filename, Graph* graph, int* K) {
    FILE* file = fopen(filename, "r");
    if (!file) return false;

    if (fscanf(file, "%d %d", &graph->vertices_count, K) != 2) {
        fclose(file);
        return false;
    }

    graph->edges_count = 0;
    int u, v;
    while (fscanf(file, "%d %d", &u, &v) == 2) {
        graph->edges[graph->edges_count].u = u - 1;
        graph->edges[graph->edges_count].v = v - 1;
        graph->edges_count++;
    }
    fclose(file);
    return true;
}

bool write_result(const char* filename, int* cover_vertices, int cover_size) {
    FILE* file = fopen(filename, "w");
    if (!file) return false;

    if (cover_size == 0) {
        fprintf(file, "0");
    }
    else {
        for (int i = 0; i < cover_size; i++) {
            fprintf(file, "%d", cover_vertices[i] + 1);
            if (i < cover_size - 1) fprintf(file, " ");
        }
    }
    fclose(file);
    return true;
}

// Простой перебор
bool find_vertex_cover(Graph* graph, int K, int* cover_vertices, int* cover_size) {
    // Если нет рёбер - пустое покрытие
    if (graph->edges_count == 0) {
        *cover_size = 0;
        return true;
    }

    // Перебираем все комбинации вершин
    int max_mask = 1 << graph->vertices_count;

    for (int mask = 0; mask < max_mask; mask++) {
        int count = 0;
        // Считаем количество выбранных вершин
        for (int i = 0; i < graph->vertices_count; i++) {
            if (mask & (1 << i)) count++;
        }

        if (count != K) continue;

        // Проверяем покрыты ли все рёбра
        bool all_covered = true;
        for (int e = 0; e < graph->edges_count; e++) {
            int u = graph->edges[e].u;
            int v = graph->edges[e].v;
            if (!(mask & (1 << u)) && !(mask & (1 << v))) {
                all_covered = false;
                break;
            }
        }

        if (all_covered) {
            *cover_size = 0;
            for (int i = 0; i < graph->vertices_count; i++) {
                if (mask & (1 << i)) {
                    cover_vertices[(*cover_size)++] = i;
                }
            }
            return true;
        }
    }

    *cover_size = 0;
    return false;
}