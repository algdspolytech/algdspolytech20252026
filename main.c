#include <stdio.h>
#include <stdlib.h>

#include "graph_coloring.h"

int main() {
    Graph* g = NULL;
    int K;
    if (!readGraphFromFile("input.txt", &g, &K)) {
        printf("Error reading input file");
        return 1;
    }

    int* colors = (int*)malloc(g->n * sizeof(int));
    if (!colors) {
        freeGraph(g);
        return 1;
    }
    for (int i = 0; i < g->n; i++) {
        colors[i] = 0;
    }

    bool coloringSuccess = graphColoring(g, K, colors);

    if (!writeResultToFile("output.txt", colors, g->n, coloringSuccess)) {
        printf("Error writing into output file");
        free(colors);
        freeGraph(g);
        return 1;
    }

    free(colors);
    freeGraph(g);

    return 0;
}