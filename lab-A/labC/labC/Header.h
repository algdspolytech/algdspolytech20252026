#pragma once
#ifdef __cplusplus
extern "C" {
#endif

    struct Node {
        int vertex;
        struct Node* next;
    };

    struct Graph {
        int numVertices;
        struct Node** adjLists;
        int* visited;
    };

    struct Node* createNode(int v);
    struct Graph* createGraph(int vertices);
    void addEdge(struct Graph* graph, int src, int dest);
    int DFS(struct Graph* graph, int current, int target);
    int pathExists(struct Graph* graph, int start, int end);
    void printAdjacencyList(struct Graph* graph);
    void freeGraph(struct Graph* graph);

#ifdef __cplusplus
}
#endif