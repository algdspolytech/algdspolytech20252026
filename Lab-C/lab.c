#include "lab.h"

void init_graph(Graph* graph) {
    graph->vertex_count = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->size[i] = 0;
    }
}

void add_edge(Graph* graph, int from, int to) {
    if (graph->size[from] < MAX_VERTICES) {
        graph->adjacency_list[from][graph->size[from]++] = to;
    }
}

int dfs(Graph* graph, int current, int target, int visited[]) {
    if (current == target) {
        return 1;
    }

    visited[current] = 1;

    for (int i = 0; i < graph->size[current]; i++) {
        int neighbor = graph->adjacency_list[current][i];
        if (!visited[neighbor]) {
            if (dfs(graph, neighbor, target, visited)) {
                return 1;
            }
        }
    }

    return 0;
}

int path_exists(Graph* graph, int start, int end) {
    int visited[MAX_VERTICES] = { 0 };
    return dfs(graph, start, end, visited);
}

int read_graph(const char* filename, Graph* graph) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int max_vertex = -1;

    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) <= 1)
            continue;

        char* colon_pos = strchr(line, ':');
        if (colon_pos == NULL)
            continue;

        *colon_pos = '\0';
        char* vertex_part = line;
        char* neighbors_part = colon_pos + 1;

        int from = atoi(vertex_part);
        if (from > max_vertex)
            max_vertex = from;

        char* token = strtok(neighbors_part, ", \t\n");
        while (token != NULL) {
            int to = atoi(token);
            add_edge(graph, from, to);
            if (to > max_vertex)
                max_vertex = to;
            token = strtok(NULL, ", \t\n");
        }
    }

    graph->vertex_count = max_vertex + 1;
    fclose(file);
    return 1;
}
