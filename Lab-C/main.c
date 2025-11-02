#include "lab.h"

int main() {

    Graph graph;
    init_graph(&graph);

    int start, end;

    printf("Enter the starting vertex: ");
    scanf("%d", &start);

    printf("Enter the ending vertex: ");
    scanf("%d", &end);

    if (!read_graph("graph.txt", &graph)) {
        return 1;
    }

    if (path_exists(&graph, start, end)) {
        printf("A path exists between vertices %d and %d\n", start, end);
    }
    else {
        printf("No path exists between vertices %d and %d\n", start, end);
    }

    run_all_tests();

    return 0;
}
