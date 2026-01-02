#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#pragma warning(disable: 4996)

#define MAX_VERTICES 1000

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjacencyList[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int numVertices;
} Graph;

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}


void initGraph(Graph* graph, int numVertices) {
    if (numVertices > MAX_VERTICES) {
        printf("Слишком много вершин! Максимум: %d\n", MAX_VERTICES);
        exit(1);
    }

    graph->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }
}


void addEdge(Graph* graph, int src, int dest) {
    if (src < 0 || src >= graph->numVertices || dest < 0 || dest >= graph->numVertices) {
        printf("Ошибка: неверные вершины %d или %d\n", src, dest);
        return;
    }

    Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}


int DFS(Graph* graph, int current, int target) {
    if (current == target) {
        return 1;
    }

    graph->visited[current] = 1;

    Node* temp = graph->adjacencyList[current];
    while (temp != NULL) {
        int neighbor = temp->vertex;
        if (!graph->visited[neighbor]) {
            if (DFS(graph, neighbor, target)) {
                return 1;
            }
        }
        temp = temp->next;
    }

    return 0;
}

int pathExists(Graph* graph, int start, int target) {
    if (start < 0 || start >= graph->numVertices ||
        target < 0 || target >= graph->numVertices) {
        return 0;
    }

    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }

    return DFS(graph, start, target);
}

void readGraph(Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла %s!\n", filename);
        exit(1);
    }

    int numVertices;
    if (fscanf(file, "%d", &numVertices) != 1) {
        printf("Ошибка чтения количества вершин из файла!\n");
        fclose(file);
        exit(1);
    }

    initGraph(graph, numVertices);

    char line[1024];
    fgets(line, sizeof(line), file);

    for (int i = 0; i < numVertices; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            break;
        }

        line[strcspn(line, "\n")] = 0;

        char* token = strtok(line, " ");
        if (token == NULL) {
            continue;
        }

        int src = atoi(token);

        while ((token = strtok(NULL, " ")) != NULL) {
            int dest = atoi(token);
            if (dest != src) {
                addEdge(graph, src, dest);
            }
        }
    }

    fclose(file);
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* current = graph->adjacencyList[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
        graph->adjacencyList[i] = NULL;
    }
}

// ==================== ТЕСТЫ ====================

void testCreateNode_n1() {
    printf("Тест 1: ");
    Node* node = createNode(5);

    if (node != NULL && node->vertex == 5 && node->next == NULL) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }

    free(node);
}

void testInitGraph_n2() {
    printf("Тест 2:");
    Graph graph;
    initGraph(&graph, 10);

    int passed = 1;
    if (graph.numVertices != 10) {
        passed = 0;
    }

    for (int i = 0; i < 10 && passed; i++) {
        if (graph.adjacencyList[i] != NULL || graph.visited[i] != 0) {
            passed = 0;
        }
    }

    freeGraph(&graph);

    if (passed) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
}

void testAddEdge_n3() {
    printf("Тест 3:");
    Graph graph;
    initGraph(&graph, 5);
    addEdge(&graph, 0, 1);

    int edge1 = 0, edge2 = 0;

    Node* temp = graph.adjacencyList[0];
    while (temp != NULL) {
        if (temp->vertex == 1) {
            edge1 = 1;
            break;
        }
        temp = temp->next;
    }

    temp = graph.adjacencyList[1];
    while (temp != NULL) {
        if (temp->vertex == 0) {
            edge2 = 1;
            break;
        }
        temp = temp->next;
    }

    freeGraph(&graph);

    if (edge1 && edge2) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
}


void testDFSPathExists_n4() {
    printf("Тест 4:");
    Graph graph;
    initGraph(&graph, 3);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);

    for (int i = 0; i < graph.numVertices; i++) {
        graph.visited[i] = 0;
    }

    int result = DFS(&graph, 0, 2);
    freeGraph(&graph);

    if (result) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
}

void testDFSNoPath_n5() {
    printf("Тест 5:");
    Graph graph;
    initGraph(&graph, 3);
    addEdge(&graph, 0, 1);

    for (int i = 0; i < graph.numVertices; i++) {
        graph.visited[i] = 0;
    }

    int result = DFS(&graph, 0, 2);
    freeGraph(&graph);

    if (!result) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
}


void testPathExistsFunction_n6() {
    printf("Тест 6:");
    Graph graph;
    initGraph(&graph, 4);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);

    int test1 = pathExists(&graph, 0, 3);
    int test2 = pathExists(&graph, 0, 0);

    freeGraph(&graph);

    if (test1 && test2) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
}

void testDisconnectedGraph_n7() {
    printf("Тест 7:");
    Graph graph;
    initGraph(&graph, 4);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 2, 3);

    int result = pathExists(&graph, 0, 3);
    freeGraph(&graph);

    if (!result) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
}

void testGraphWithCycle_n8() {
    printf("Тест 8:");
    Graph graph;
    initGraph(&graph, 4);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 0);

    int result = pathExists(&graph, 0, 3);
    freeGraph(&graph);

    if (result) {
        printf("1\n");
    }
    else {
        printf("0\n");
    }
}

void testInvalidVertices_n9() {
    printf("Тест 9:");
    Graph graph;
    initGraph(&graph, 5);
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);

    int test1 = pathExists(&graph, 0, 6);
    int test2 = pathExists(&graph, -1, 2);
    int test3 = pathExists(&graph, 0, 5);

    freeGraph(&graph);

    if (!test1 && !test2 && !test3) {
        printf("1\n");
    }
    else {
        printf("0 (test1=%d, test2=%d, test3=%d)\n", test1, test2, test3);
    }
}

void testReadFromFileAndMainFunction_n10() {
    printf("Тест 10:");

    const char* test_filename = "test_graph.txt";
    FILE* testFile = fopen(test_filename, "w");
    if (testFile == NULL) {
        printf("0 (не удалось создать файл)\n");
        return;
    }

    fprintf(testFile, "3\n");
    fprintf(testFile, "0 1 2\n");
    fprintf(testFile, "1 0\n");
    fprintf(testFile, "2 0\n");
    fclose(testFile);

    Graph graph;
    readGraph(&graph, test_filename);

    int test1 = pathExists(&graph, 0, 2);
    int test2 = pathExists(&graph, 1, 2);
    int test3 = pathExists(&graph, 0, 0);
    int test4 = pathExists(&graph, 2, 1);
    freeGraph(&graph);
    remove(test_filename);

    if (test1 && test2 && test3 && test4) {
        printf("1\n");
    }
    else {
        printf("0 (0->2=%d, 1->2=%d, 0->0=%d, 2->1=%d)\n",
            test1, test2, test3, test4);
    }
}


void runAllTests() {
    printf("\n\n=====ТЕСТЫ=====\n\n");

    testCreateNode();
    testInitGraph();
    testAddEdge();
    testDFSPathExists();
    testDFSNoPath();
    testPathExistsFunction();
    testDisconnectedGraph();
    testGraphWithCycle();
    testInvalidVertices();
    testReadFromFileAndMainFunction();

    printf("\n=== Тестирование завершено ===\n");
}


int main() {
 
    setlocale(LC_CTYPE, "Russian");


    Graph graph;
    const char* filename = "graph.txt";

    printf("Чтение графа из файла '%s'...\n", filename);
    readGraph(&graph, filename);
    printf("Граф успешно загружен. Количество вершин: %d\n", graph.numVertices);


    int start, target;
    printf("Введите начальную вершину (0-%d): ", graph.numVertices - 1);
    scanf("%d", &start);
    printf("Введите целевую вершину (0-%d): ", graph.numVertices - 1);
    scanf("%d", &target);


    if (pathExists(&graph, start, target)) {
        printf("Путь между вершинами %d и %d СУЩЕСТВУЕТ.\n", start, target);
    }
    else {
        printf("Путь между вершинами %d и %d НЕ СУЩЕСТВУЕТ.\n", start, target);
    }

    freeGraph(&graph);

    runAllTests();

    return 0;
}