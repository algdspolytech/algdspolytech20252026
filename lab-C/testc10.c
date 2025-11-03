#include <stdio.h>
#include <string.h>
#include "labC10.h"

//Запись графа в строку 
void graphToString(Graph* graph, char* buffer, size_t size) {
    buffer[0] = '\0';
    for (int i = 0; i < graph->numVert; i++) {
        char line[128];
        sprintf_s(line, sizeof(line), "%d:", i);
        strcat_s(buffer, size, line);

        Node* t = graph->adjLists[i];
        while (t) {
            char vertex[16];
            sprintf_s(vertex, sizeof(vertex), " %d", t->vertex);
            strcat_s(buffer, size, vertex);
            t = t->next;
        }
        strcat_s(buffer, size, "\n");
    }
}

//Проверка равенства строк
void expectEq(const char* testName,
    const char* got,
    const char* expected) {
    if (strcmp(got, expected) == 0) {
        printf("OK %s\n", testName);
    }
    else {
        printf("FAIL %s\n", testName);
    }
}

//Проверка на пустоту графа
void expectNull(const char* testName, Graph* g) {
    if (g == NULL || g->numVert == 0) {
        printf("OK  %s\n", testName);
    }
    else {
        printf("FAIL %s\n", testName);
    }
}

//1 Пустой граф
void TestEmptyGraph_no1() {
    Graph* g = createGraph(0);
    expectNull("TestEmptyGraph_no1", g);
    freeGraph(g);
}

//2.Граф с одной вершиной, без ребер
void TestSingleVertex_no2() {
    Graph* g = createGraph(1);
    char buf[64];
    graphToString(g, buf, sizeof(buf));
    expectEq("TestSingleVertex_no2", buf, "0:\n");
    freeGraph(g);
}

//3.Граф с одним ребром
void TestSingleEdge_no3() {
    Graph* g = createGraph(2);
    addEdge(g, 0, 1);
    char buf[64];
    graphToString(g, buf, sizeof(buf));
    expectEq("TestSingleEdge_no3", buf, "0: 1\n1:\n");
    freeGraph(g);
}

//4.Полный граф 3 вершины
void TestFullGraph_no4() {
    Graph* g = createGraph(3);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 0);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    addEdge(g, 2, 1);
    char buf[128];
    graphToString(g, buf, sizeof(buf));
    expectEq("TestFullGraph_no4", buf, "0: 2 1\n1: 2 0\n2: 1 0\n");
    freeGraph(g);
}

//5.Граф с петлями
void TestSelfLoop_no5() {
    Graph* g = createGraph(2);
    addEdge(g, 0, 0);
    addEdge(g, 1, 1);
    char buf[64];
    graphToString(g, buf, sizeof(buf));
    expectEq("TestSelfLoop_no5", buf, "0: 0\n1: 1\n");
    freeGraph(g);
}

//6.Граф с несколькими вершинами, без ребер
void TestDisconnected_no6() {
    Graph* g = createGraph(3);
    char buf[64];
    graphToString(g, buf, sizeof(buf));
    expectEq("TestDisconnected_no6", buf, "0:\n1:\n2:\n");
    freeGraph(g);
}

//7.Направленный граф с несколькими ребрами
void TestDirectedGraph_no7() {
    Graph* g = createGraph(3);
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    char buf[64];
    graphToString(g, buf, sizeof(buf));
    expectEq("TestDirectedGraph_no7", buf, "0: 1\n1: 2\n2:\n");
    freeGraph(g);
}

//8.Считывание графа из файла
void TestFromFile_no8() {
    FILE* f = fopen("matrix.txt", "r");
    if (!f) {
        printf("[SKIP] TestFromFile_no8\n");
        return;
    }
    fclose(f);
    int size = 0;
    int** matrix = readMatrixFromFile("matrix.txt", &size);
    Graph* g = convertMatrixToList(matrix, size);
    char buf[256];
    graphToString(g, buf, sizeof(buf));
    printf("[INFO] TestFromFile_no8 result:\n%s\n", buf);
    freeGraph(g);
}

//9.Граф с повторяющимися ребрами
void TestDuplicateEdges_no9() {
    Graph* g = createGraph(2);
    addEdge(g, 0, 1);
    addEdge(g, 0, 1);
    char buf[64];
    graphToString(g, buf, sizeof(buf));
    expectEq("TestDuplicateEdges_no9", buf, "0: 1 1\n1:\n");
    freeGraph(g);
}

//10.Сложный граф с комбинацией направленных, повторяющихся и петлей
void TestComplexGraph_no10() {
    Graph* g = createGraph(3);
    addEdge(g, 0, 0);
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    char buf[128];

    graphToString(g, buf, sizeof(buf));
    expectEq("TestComplexGraph_no10", buf, "0: 1 0\n1: 2 2\n2: 0\n");
    freeGraph(g);
}

int main() {
    TestEmptyGraph_no1();
    TestSingleVertex_no2();
    TestSingleEdge_no3();
    TestFullGraph_no4();
    TestSelfLoop_no5();
    TestDisconnected_no6();
    TestDirectedGraph_no7();
    TestFromFile_no8();
    TestDuplicateEdges_no9();
    TestComplexGraph_no10();
    return 0;
}