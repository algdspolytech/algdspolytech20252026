#include "VertexCover.h"

Graph *init_graph() {
    Graph *g = (Graph *) malloc(sizeof(Graph));
    g->edges = NULL;
    g->edge_count = 0;
    g->vertex_count = 0;
    return g;
}


void free_graph(Graph *g) {
    if (g != NULL) {
        free(g->edges);
        free(g);
    }
}


Graph* load_graph(char* filename, int* k) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    int verts;
    if (fscanf(file, "%d %d", &verts, k) != 2) {
        fclose(file);
        return NULL;
    }

    Graph* g = init_graph();
    g->vertex_count = verts;

    int u, v;
    while (fscanf(file, "%d %d", &u, &v) == 2) {
        g->edges = (Edge *) realloc(g->edges, (g->edge_count + 1) * sizeof(Edge));
        if (g->edges == NULL)
            exit(-1);

        g->edges[g->edge_count].u = u;
        g->edges[g->edge_count].v = v;
        g->edge_count++;
    }

    fclose(file);
    return g;
}


VertexCover *init_vertex_cover() {
    VertexCover *cov = (VertexCover *) malloc(sizeof(VertexCover));
    cov->vertices = NULL;
    cov->count = 0;
    return cov;
}


void free_vertex_cover(VertexCover *cov) {
    if (cov) {
        free(cov->vertices);
        free(cov);
    }
}


void add_vertex(VertexCover *cov, int vertex) {
    if (vertex > 0 && vertex < 1000) {
        cov->vertices = (int *) realloc(cov->vertices, (cov->count + 1) * sizeof(int));
        if (cov->vertices == NULL)
            exit(-1);
        cov->vertices[cov->count++] = vertex;
    }
}

int check_cover(Graph *g, VertexCover *cov) {
    int *in_cover = (int*)calloc(g->vertex_count + 1, sizeof(int));

    for (int i = 0; i < cov->count; i++) {
        int v = cov->vertices[i];
        in_cover[v] = 1;

        for (int j = 0; j < g->edge_count; j++) {
            if (g->edges[j].u == v) in_cover[g->edges[j].v] = 1;
            if (g->edges[j].v == v) in_cover[g->edges[j].u] = 1;
        }
    }

    for (int i = 1; i <= g->vertex_count; i++) {
        if (!in_cover[i]) {
            free(in_cover);
            return 0;
        }
    }

    free(in_cover);
    return 1;
}


VertexCover *find_vertex_cover(Graph *g, int k, int current_vertex) {

    if (k < 0) return NULL;

    VertexCover *current_ds = init_vertex_cover();

    if (current_vertex > g->vertex_count) {
        if (k == 0 && check_cover(g, current_ds)) {
            return current_ds;
        }
        free_vertex_cover(current_ds);
        return NULL;
    }

    VertexCover *result = find_vertex_cover(g, k, current_vertex + 1);
    if (result != NULL) {
        free_vertex_cover(current_ds);
        return result;
    }

    add_vertex(current_ds, current_vertex);
    if (check_cover(g, current_ds)) {
        return current_ds;
    }

    result = find_vertex_cover(g, k - 1, current_vertex + 1);
    if (result != NULL) {
        add_vertex(result, current_vertex);
        free_vertex_cover(current_ds);
        return result;
    }

    free_vertex_cover(current_ds);
    return NULL;
}


void write_vertex_cover(VertexCover *cov, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) return;

    if (cov == NULL)
        fprintf(file, "0\n");
    else {
        for (int i = 0; i < cov->count; i++)
            fprintf(file, "%d ", cov->vertices[i]);
        fprintf(file, "\n");
    }

    fclose(file);
}
