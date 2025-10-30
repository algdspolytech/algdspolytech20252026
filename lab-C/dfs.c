#include "dfs.h"

void initialize_graph(Graph* graph) {
    graph->vertices_count = 0;
    graph->capacity = INITIAL_CAPACITY;
    graph->adjacency_list = (int**)malloc(graph->capacity * sizeof(int*));

    if (graph->adjacency_list) {
        for (int i = 0; i < graph->capacity; i++) {
            graph->adjacency_list[i] = (int*)calloc(graph->capacity, sizeof(int));
        }
    }
}

void destroy_graph(Graph* graph) {
    if (graph->adjacency_list) {
        for (int i = 0; i < graph->capacity; i++) {
            free(graph->adjacency_list[i]);
        }
        free(graph->adjacency_list);
    }
    graph->vertices_count = 0;
    graph->capacity = 0;
    graph->adjacency_list = NULL;
}

int resize_graph(Graph* graph, int new_size) {
    if (new_size <= graph->capacity) {
        return 1;
    }

    int new_capacity = new_size * 2;
    int** new_adjacency = (int**)malloc(new_capacity * sizeof(int*));

    if (!new_adjacency) return 0;

    for (int i = 0; i < new_capacity; i++) {
        new_adjacency[i] = (int*)calloc(new_capacity, sizeof(int));
        if (!new_adjacency[i]) {
            for (int j = 0; j < i; j++) {
                free(new_adjacency[j]);
            }
            free(new_adjacency);
            return 0;
        }

        if (i < graph->capacity && graph->adjacency_list) {
            for (int j = 0; j < graph->capacity; j++) {
                new_adjacency[i][j] = graph->adjacency_list[i][j];
            }
        }
    }

    if (graph->adjacency_list) {
        for (int i = 0; i < graph->capacity; i++) {
            free(graph->adjacency_list[i]);
        }
        free(graph->adjacency_list);
    }

    graph->adjacency_list = new_adjacency;
    graph->capacity = new_capacity;
    if (new_size > graph->vertices_count) {
        graph->vertices_count = new_size;
    }

    return 1;
}

int add_edge(Graph* graph, int src, int dest) {
    if (src < 0 || dest < 0) {
        return 0;
    }

    int required_size = (src > dest ? src : dest) + 1;
    if (required_size > graph->capacity) {
        if (!resize_graph(graph, required_size)) {
            return 0;
        }
    }

    if (required_size > graph->vertices_count) {
        graph->vertices_count = required_size;
    }

    graph->adjacency_list[src][dest] = 1;
    graph->adjacency_list[dest][src] = 1;

    return 1;
}

void parse_neighbors(Graph* graph, int vertex, const char* neighbors_str) {
    char buffer[MAX_LINE_LENGTH];
    strcpy(buffer, neighbors_str);

    char* token = strtok(buffer, " \t\n");
    while (token != NULL) {
        int neighbor = atoi(token);
        add_edge(graph, vertex, neighbor);
        token = strtok(NULL, " \t\n");
    }
}

int read_graph_from_file(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return 0;
    }

    initialize_graph(graph);

    char line[MAX_LINE_LENGTH];
    int max_vertex = -1;

    while (fgets(line, sizeof(line), file)) {
        if (strlen(line) <= 1 || line[0] == '#') continue;

        line[strcspn(line, "\n")] = 0;

        char* colon_pos = strchr(line, ':');
        if (!colon_pos) {
            int vertex = atoi(line);
            if (vertex >= 0 && vertex > max_vertex) {
                max_vertex = vertex;
            }
            continue;
        }

        *colon_pos = '\0';
        int vertex = atoi(line);

        if (vertex > max_vertex) max_vertex = vertex;

        char* neighbors_str = colon_pos + 1;
        while (*neighbors_str == ' ' || *neighbors_str == '\t') {
            neighbors_str++;
        }

        char buffer[MAX_LINE_LENGTH];
        strcpy(buffer, neighbors_str);
        char* token = strtok(buffer, " \t");

        while (token != NULL) {
            int neighbor = atoi(token);
            if (neighbor > max_vertex) max_vertex = neighbor;
            add_edge(graph, vertex, neighbor);
            token = strtok(NULL, " \t");
        }
    }

    if (max_vertex >= 0) {
        graph->vertices_count = max_vertex + 1;
    }
    else {
        graph->vertices_count = 0;
    }

    fclose(file);
    return 1;
}

void print_graph(const Graph* graph) {
    if (!graph || !graph->adjacency_list) {
        printf("Graph is empty or not initialized\n");
        return;
    }

    printf("Graph (adjacency list):\n");
    int printed_vertices = 0;

    for (int i = 0; i < graph->vertices_count; i++) {
        printf("%d: ", i);
        int has_neighbors = 0;

        for (int j = 0; j < graph->vertices_count; j++) {
            if (graph->adjacency_list[i][j]) {
                printf("%d ", j);
                has_neighbors = 1;
            }
        }

        if (!has_neighbors) {
            printf("no neighbors");
        }
        printf("\n");
        printed_vertices++;
    }

    if (printed_vertices == 0) {
        printf("No vertices found in graph\n");
    }
}

int dfs(const Graph* graph, int current, int end, int visited[]) {
    if (current == end) {
        return 1;
    }

    visited[current] = 1;

    for (int i = 0; i < graph->vertices_count; i++) {
        if (graph->adjacency_list[current][i] && !visited[i]) {
            if (dfs(graph, i, end, visited)) {
                return 1;
            }
        }
    }

    return 0;
}

int path_exists(const Graph* graph, int start, int end) {
    if (!graph || !graph->adjacency_list) {
        return 0;
    }

    if (graph->vertices_count == 0) {
        return 0;
    }

    if (start < 0 || start >= graph->vertices_count ||
        end < 0 || end >= graph->vertices_count) {
        return 0;
    }

    if (start == end) return 1;

    int* visited = (int*)calloc(graph->vertices_count, sizeof(int));
    if (!visited) return 0;

    int result = dfs(graph, start, end, visited);
    free(visited);

    return result;
}