#pragma warning (disable:4996)



#include <assert.h> 
#include "Header.h" 


void Test_FromStr2Num_AlphaDigitString_ReturnNULLN1() {
    printf("Test 1: Numbers and letters or delimetrs mixed in string\n");


    int len = 4;
    const char* str = ".f75";

    int res = FromStr2Num(str, len);

    assert((res == -1));
    printf("Returned NULL. Error:letters or delimetrs mixed in string\n");
}

void Test_FromStr2Num_DigitString_ReturnNUMN2() {
    printf("Test 2:Just digits in string\n");


    int len = 3;
    const char* str = "137";

    int res = FromStr2Num(str, len);

    assert((res == 137));
    printf("Success\n");

}

void Test_ReadGraph_NULLLines_ReturnNULLN3() {
    printf("Test 3:NULLLines\n");

    vertex* graph;
    char* lines = NULL;
    int len = 1;
    int graphlen;

    graph = ReadGraph(lines, len, &graphlen);

    assert((graph == NULL));
    printf("Returned NULL. Error:srting lines is NULL\n");

}

void Test_ReadGraph_InvalidLen_ReturnNULLN4() {
    printf("Test 4:InvalidLen\n");

    vertex* graph;
    char* lines = "1: 2 3 4";
    int len = 0;
    int graphlen;

    graph = ReadGraph(lines, len, &graphlen);

    assert((graph == NULL));
    printf("Returned NULL. Error:invalid len\n");

}

void Test_ReadGraph_ReadGraph_ValidValN5() {
    printf("Test 5:ReadGraph\n");

    vertex* graph;
    char* lines = "1: 2 3 4";
    int len = 8;
    int graphlen;

    graph = ReadGraph(lines, len, &graphlen);

    assert(graph->NeighboursVert[0] == 2 || graph->NeighboursVert[1] == 3 || graph->NeighboursVert[2] == 4 || graph->NumOfNeigh == 3 || graph->Vertnum == 1);
    printf("Success\n");
    free(graph->NeighboursVert);
    free(graph);
}

void Test_DeQueue_Queue_ValidValN6() {
    printf("Test 6:Queue\n");

    Node* vert = (Node*)malloc(sizeof(Node));
    Node* res;
    vertex v;
    v.NeighboursVert = NULL;
    v.NumOfNeigh = 0;
    v.Vertnum = 1;

    vert->vert = v;
    vert->next = NULL;

    Queue q;
    q.first = vert;
    q.last = vert;
    
    res = DeQueue(&q);

    assert(res->vert.Vertnum == 1);
    printf("Success\n");
    free(res);
}

void Test_DeQueue_NULLQueue_ReturnNULLN7() {
    printf("Test 7:NULLQueue\n");

    Node* res;
    Queue q;
    q.first = NULL;
    q.last = NULL;

    res = DeQueue(&q);

    assert(res == NULL);
    printf("Returned NULL. Error:NULL Queue\n");
}

void Test_InQueue_NULLQueue_ValidValN8() {
    printf("Test 8:NULLQueue\n");

    Node* res = (Node*)malloc(sizeof(Node));
    vertex v;
    v.NeighboursVert = NULL;
    v.NumOfNeigh = 0;
    v.Vertnum = 1;

    res->vert = v;
    res->next = NULL;

    Queue q;
    q.first = NULL;
    q.last = NULL;

    InQueue(res,&q);

    assert(q.first->vert.Vertnum == 1);
    printf("Success\n");
    free(res);
}

void Test_InQueue_Queue_ValidValN9() {
    printf("Test 9:InQueue\n");

    Node* res = (Node*)malloc(sizeof(Node));
    Node* N = (Node*)malloc(sizeof(Node));
    vertex v1;
    vertex v2;

    v1.NeighboursVert = NULL;
    v1.NumOfNeigh = 0;
    v1.Vertnum = 2;

    v2.NeighboursVert = NULL;
    v2.NumOfNeigh = 0;
    v2.Vertnum = 1;


    res->vert = v1;
    res->next = NULL;
    N->vert = v2;
    N->next = NULL;


    Queue q;
    q.first = N;
    q.last = N;

    InQueue(res, &q);

    assert(q.first->next->vert.Vertnum == 2);
    printf("Success\n");
    free(res);
    free(N);
}

void Test_FindTheWay_NULLGraph_ReturnNULLN10() {
    printf("Test 10:NULLGraph\n");

    vertex* graph = NULL;
    int* res;
    int waylen;
    res = FindTheWay(&waylen, graph, 1, 1, 1);
    assert(res == NULL);
    printf("Returned NULL. Error:NULL Graph\n");
}

void Test_FindTheWay_NULLGraphLen_ReturnNULLN11() {
    printf("Test 11:NULLGraphLen\n");

    vertex* graph = (vertex*)malloc(sizeof(vertex));
    vertex v1;
    v1.NeighboursVert = NULL;
    v1.NumOfNeigh = 0;
    v1.Vertnum = 2;
    graph[0] = v1;

    int* res;
    int waylen;
    res = FindTheWay(&waylen, graph, 0, 1, 1);
    assert(res == NULL);
    printf("Returned NULL. Error:NULL Graphlen\n");
    free(graph);
}

void Test_FindTheWay_NULLFromNum_ReturnNULLN12() {
    printf("Test 12:NULLFromNum\n");

    vertex* graph = (vertex*)malloc(sizeof(vertex));
    vertex v1;
    v1.NeighboursVert = NULL;
    v1.NumOfNeigh = 0;
    v1.Vertnum = 2;
    graph[0] = v1;

    int* res;
    int waylen;
    res = FindTheWay(&waylen, graph, 1, 0, 1);
    assert(res == NULL);
    printf("Returned NULL. Error:NULL FromNum\n");
    free(graph);
}

void Test_FindTheWay_NULLToNum_ReturnNULLN13() {
    printf("Test 13:NULLToNum\n");

    vertex* graph = (vertex*)malloc(sizeof(vertex));
    vertex v1;
    vertex v2;
    v1.NeighboursVert = NULL;
    v1.NumOfNeigh = 0;
    v1.Vertnum = 2;
    graph[0] = v1;

    int* res;
    int waylen;
    res = FindTheWay(&waylen, graph, 1, 1, 0);
    assert(res == NULL);
    printf("Returned NULL. Error:NULL ToNum\n");
    free(graph);
}

void Test_FindTheWay_FindTheWay_ValidValN14() {
    printf("Test 14:FindTheWay\n");

    vertex* graph = (vertex*)malloc(2 * sizeof(vertex));
    vertex v1;
    vertex v2;
    int Neighb[1];
    Neighb[0] = 2;

    v1.NeighboursVert = Neighb;
    v1.NumOfNeigh = 1;
    v1.Vertnum = 1;

    v2.NeighboursVert = NULL;
    v2.NumOfNeigh = 0;
    v2.Vertnum = 2;
    graph[0] = v1;
    graph[1] = v2;

    int* res;
    int waylen;

    res = FindTheWay(&waylen, graph, 2, 1, 2);
    assert(res[0] == 1 && res[1] == 2 && waylen == 2);
    printf("Success\n");
    free(graph);
    free(res);
}

int main(void) {

    setlocale(LC_CTYPE, "Russian");
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    Test_FromStr2Num_AlphaDigitString_ReturnNULLN1();
    Test_FromStr2Num_DigitString_ReturnNUMN2();
    Test_ReadGraph_NULLLines_ReturnNULLN3();
    Test_ReadGraph_InvalidLen_ReturnNULLN4();
    Test_ReadGraph_ReadGraph_ValidValN5();
    Test_DeQueue_Queue_ValidValN6();
    Test_DeQueue_NULLQueue_ReturnNULLN7();
    Test_InQueue_NULLQueue_ValidValN8();
    Test_InQueue_Queue_ValidValN9();
    Test_FindTheWay_NULLGraph_ReturnNULLN10();
    Test_FindTheWay_NULLGraphLen_ReturnNULLN11();
    Test_FindTheWay_NULLFromNum_ReturnNULLN12();
    Test_FindTheWay_NULLToNum_ReturnNULLN13();
    Test_FindTheWay_FindTheWay_ValidValN14();

    return 0;
}