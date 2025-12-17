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

void Test_ReadNum_NULLLines_ReturnNULLN3() {
    printf("Test 3:NULLLines\n");
    char* lines = NULL;
    int i = 0;
    int l = 0;
    char* res = ReadNum(lines, 0, &i, &l, ' ');

    assert(res == NULL);
    printf("Returned NULL. Error:NULL Lines\n");
    free(res);
}

void Test_ReadNum_NULLLenght_ReturnNULLN4() {
    printf("Test 4:NULLLenght\n");
    char* lines = "NULL";
    int i = 0;
    int l = 0;
    char* res = ReadNum(lines, 0, &i, &l, ' ');

    assert(res == NULL);
    printf("Returned NULL. Error:NULL Lenght\n");
    free(res);
}

void Test_ReadNum_NoEndChar_ReturnNULLN5() {
    printf("Test 5:NoEndChar\n");
    char* lines = "23\0";
    int i = 0;
    int l = 0;
    char* res = ReadNum(lines, 3, &i, &l, '0');

    assert(res == NULL);
    printf("Returned NULL. Error:There is no EndChar in lines\n");
    free(res);
}

void Test_ReadNum_ReadData_ValidValN6() {
    printf("Test 6:ReadData\n");
    char* lines = "2 3 4";
    int i = 0;
    int l = 0;
    char* res = ReadNum(lines, 6, &i, &l, ' ');

    assert(res[0] == '2');
    printf("Success\n");
    free(res);
}

void Test_ReadGraph_NULLLines_ReturnNULLN7() {
    printf("Test 7:NULLLines\n");
    int graphlen;
    int fromvert;
    int tovert;
    int k;
    vertex* res = ReadGraph(NULL, 2, &graphlen, &fromvert, &tovert, &k);

    assert(res == NULL);
    printf("Returned NULL. Error:NULL Lines\n");
    free(res);
}

void Test_ReadGraph_NULLLenght_ReturnNULLN8() {
    printf("Test 8:NULLLenght\n");
    char* lines = "NULL";
    int graphlen;
    int fromvert;
    int tovert;
    int k;
    vertex* res = ReadGraph(lines, 0, &graphlen, &fromvert, &tovert, &k);

    assert(res == NULL);
    printf("Returned NULL. Error:NULL Lenght\n");
    free(res);
}

void Test_ReadGraph_ReadData_ValidValN9() {
    printf("Test 9:ReadData\n");
    char* lines = "3 1 3 2\n2 3\n1 3\n1 2";
    int graphlen;
    int fromvert;
    int tovert;
    int k;
    vertex* res = ReadGraph(lines, 19, &graphlen, &fromvert, &tovert, &k);
    printf("%d", res[0].NeighboursVert[1]);

    assert((res[0].NeighboursVert[0] == 3)
        && (res[0].NeighboursVert[1] == 2)

        && (res[1].NeighboursVert[0] == 3)
        && (res[1].NeighboursVert[1] == 1) 

        && (res[2].NeighboursVert[0] == 2)
        && (res[2].NeighboursVert[1] == 1)
        && (graphlen == 3) && (fromvert == 1) && (tovert==3)&&(k==2));
    printf("Success\n");
    free(res[0].NeighboursVert);
    free(res[1].NeighboursVert);
    free(res[2].NeighboursVert);
    free(res);
}

void Test_IsInWay_NULLVert1_ReturnNULLN10() {
    printf("Test 10:NULLVert1\n");
    edge way[1];
    way[0].vert1 = 1;
    way[0].vert2 = 2;
    vertex* res = IsInWay(0,2,way,1);

    assert(res == 0);
    printf("Returned NULL. Error:NULL vert1\n");
}

void Test_IsInWay_NULLVert2_ReturnNULLN11() {
    printf("Test 11:NULLVert2\n");
    edge way[1];
    way[0].vert1 = 1;
    way[0].vert2 = 2;
    vertex* res = IsInWay(1, 0, way, 1);

    assert(res == 0);
    printf("Returned NULL. Error:NULL vert2\n");
}

void Test_IsInWay_NULLWay_ReturnNULLN12() {
    printf("Test 12:NULLWay\n");
    edge way[1];
    way[0].vert1 = 1;
    way[0].vert2 = 2;
    vertex* res = IsInWay(1, 2, NULL, 1);

    assert(res == 0);
    printf("Returned NULL. Error:NULL way\n");
}

void Test_IsInWay_NULLLenght_ReturnNULLN13() {
    printf("Test 13:NULLLenght\n");
    edge way[1];
    way[0].vert1 = 1;
    way[0].vert2 = 2;
    vertex* res = IsInWay(1, 2, way, 0);

    assert(res == 0);
    printf("Returned NULL. Error:NULL Lenght\n");
}

void Test_IsInWay_CheckInWay_ReturnTrue14() {
    printf("Test 14:CheckInWay\n");
    edge way[1];
    way[0].vert1 = 1;
    way[0].vert2 = 2;
    vertex* res = IsInWay(1, 2, way, 1);

    assert(res == 1);
    printf("Success\n");
}

void Test_FindWay_NULLLenght_ReturnNULLN15() {
    printf("Test 15:NULLVert1\n");
    int currwaylen = 0;
    edge way[1];
    way[0].vert1 = 1;
    way[0].vert2 = 2;
    vertex* res = FindWay(NULL,1,1,1,1,1,&way,&currwaylen);

    assert(res == 0);
    printf("Returned NULL. Error:NULL graph\n");
}

void Test_FindWay_NULLGraphLen_ReturnNULLN16() {
    printf("Test 16:NULLgraphlen\n");
    vertex graph[3];
    int graphlen = 3;
    int fromvert = 1;
    int tovert = 3;
    int k = 2;
    int currwaylen = 0;
    edge* way = (edge*)malloc(sizeof(edge));
    int* NeighboursVert1 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert2 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert3 = (int*)malloc(sizeof(int) * 2);
    NeighboursVert1[0] = 3;
    NeighboursVert1[1] = 2;

    NeighboursVert2[0] = 3;
    NeighboursVert2[1] = 1;

    NeighboursVert3[0] = 2;
    NeighboursVert3[1] = 1;
    graph[0].NeighboursVert = NeighboursVert1;
    graph[1].NeighboursVert = NeighboursVert2;
    graph[2].NeighboursVert = NeighboursVert3;

    int res = FindWay(graph, 0, -1, fromvert, tovert, k, &way, &currwaylen);

    assert(res == 0);
    printf("Returned NULL. Error:NULL graphlen\n");
    free(NeighboursVert1);
    free(NeighboursVert2);
    free(NeighboursVert3);
    free(way);
}

void Test_FindWay_InvalidFromVert_ReturnNULLN17() {
    printf("Test 17:InvalidFromVert\n");
    vertex graph[3];
    int graphlen = 3;
    int fromvert = 1;
    int tovert = 3;
    int k = 2;
    int currwaylen = 0;
    edge* way = (edge*)malloc(sizeof(edge));

    int* NeighboursVert1 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert2 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert3 = (int*)malloc(sizeof(int) * 2);
    NeighboursVert1[0] = 3;
    NeighboursVert1[1] = 2;

    NeighboursVert2[0] = 3;
    NeighboursVert2[1] = 1;

    NeighboursVert3[0] = 2;
    NeighboursVert3[1] = 1;
    graph[0].NeighboursVert = NeighboursVert1;
    graph[1].NeighboursVert = NeighboursVert2;
    graph[2].NeighboursVert = NeighboursVert3;

    int res = FindWay(graph, graphlen, -1, 55, tovert, k, &way, &currwaylen);

    assert(res == 0);
    printf("Returned NULL. Error: Invalid FromVert\n");
    free(NeighboursVert1);
    free(NeighboursVert2);
    free(NeighboursVert3);
    free(way);
}

void Test_FindWay_InvalidToVert_ReturnNULLN18() {
    printf("Test 18:InvalidToVert\n");
    vertex graph[3];
    int graphlen = 3;
    int fromvert = 1;
    int tovert = 3;
    int k = 2;
    int currwaylen = 0;
    edge* way = (edge*)malloc(sizeof(edge));

    int* NeighboursVert1 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert2 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert3 = (int*)malloc(sizeof(int) * 2);
    NeighboursVert1[0] = 3;
    NeighboursVert1[1] = 2;

    NeighboursVert2[0] = 3;
    NeighboursVert2[1] = 1;

    NeighboursVert3[0] = 2;
    NeighboursVert3[1] = 1;
    graph[0].NeighboursVert = NeighboursVert1;
    graph[1].NeighboursVert = NeighboursVert2;
    graph[2].NeighboursVert = NeighboursVert3;

    int res = FindWay(graph, graphlen, -1, fromvert, 0, k, &way, &currwaylen);

    assert(res == 0);
    printf("Returned NULL. Error: Invalid ToVert\n");
    free(NeighboursVert1);
    free(NeighboursVert2);
    free(NeighboursVert3);
    free(way);
}

void Test_FindWay_InvalidK_ReturnNULLN19() {
    printf("Test 19:InvalidK\n");
    vertex graph[3];
    int graphlen = 3;
    int fromvert = 1;
    int tovert = 3;
    int k = 2;
    int currwaylen = 0;
    edge* way = (edge*)malloc(sizeof(edge));

    int* NeighboursVert1 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert2 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert3 = (int*)malloc(sizeof(int) * 2);
    NeighboursVert1[0] = 3;
    NeighboursVert1[1] = 2;

    NeighboursVert2[0] = 3;
    NeighboursVert2[1] = 1;

    NeighboursVert3[0] = 2;
    NeighboursVert3[1] = 1;
    graph[0].NeighboursVert = NeighboursVert1;
    graph[1].NeighboursVert = NeighboursVert2;
    graph[2].NeighboursVert = NeighboursVert3;

    int res = FindWay(graph, graphlen, -1, fromvert, tovert, 573, &way, &currwaylen);

    assert(res == 0);
    printf("Returned NULL. Error: Invalid k\n");
    free(NeighboursVert1);
    free(NeighboursVert2);
    free(NeighboursVert3);
    free(way);
}

void Test_FindWay_NoWay_ReturnNULLN20() {
    printf("Test 20:NoWay\n");
    vertex graph[3];
    int graphlen = 3;
    int fromvert = 1;
    int tovert = 3;
    int k = 4;
    int currwaylen = 0;
    edge* way = (edge*)malloc(sizeof(edge));

    int* NeighboursVert1 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert2 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert3 = (int*)malloc(sizeof(int) * 2);
    NeighboursVert1[0] = 3;
    NeighboursVert1[1] = 2;

    NeighboursVert2[0] = 3;
    NeighboursVert2[1] = 1;

    NeighboursVert3[0] = 2;
    NeighboursVert3[1] = 1;
    graph[0].NeighboursVert = NeighboursVert1;
    graph[1].NeighboursVert = NeighboursVert2;
    graph[2].NeighboursVert = NeighboursVert3;

    int res = FindWay(graph, graphlen, -1, fromvert, tovert, k, &way, &currwaylen);

    assert(res == 0);
    printf("Success\n");
    free(NeighboursVert1);
    free(NeighboursVert2);
    free(NeighboursVert3);
    free(way);
}

void Test_FindWay_FindWay13k2_ReturnNULLN21() {
    printf("Test 21:FindWay13k2\n");
    vertex graph[3];
    int graphlen = 3;
    int fromvert = 1;
    int tovert = 3;
    int k = 2;
    int currwaylen = 0;
    edge* way = (edge*)malloc(sizeof(edge));

    int* NeighboursVert1 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert2 = (int*)malloc(sizeof(int) * 2);
    int* NeighboursVert3 = (int*)malloc(sizeof(int) * 2);
    NeighboursVert1[0] = 3;
    NeighboursVert1[1] = 2;

    NeighboursVert2[0] = 3;
    NeighboursVert2[1] = 1;

    NeighboursVert3[0] = 2;
    NeighboursVert3[1] = 1;
    graph[0].NeighboursVert = NeighboursVert1;
    graph[1].NeighboursVert = NeighboursVert2;
    graph[2].NeighboursVert = NeighboursVert3;

    graph[0].NumOfNeigh = 2;
    graph[1].NumOfNeigh = 2;
    graph[2].NumOfNeigh = 2;

    graph[0].Vertnum = 1;
    graph[1].Vertnum = 2;
    graph[2].Vertnum = 3;
    int res = FindWay(graph, graphlen, -1, fromvert, tovert, k, &way, &currwaylen);

    assert((res == 1) && (currwaylen-1 == 2) && (way[0].vert2 == 1) && (way[1].vert2 == 2) && (way[2].vert2 == 3) );
    printf("Success\n");
    free(NeighboursVert1);
    free(NeighboursVert2);
    free(NeighboursVert3);
    free(way);
}

int main() {

    setlocale(LC_CTYPE, "Russian");
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    Test_FromStr2Num_AlphaDigitString_ReturnNULLN1();
    Test_FromStr2Num_DigitString_ReturnNUMN2();
    Test_ReadNum_NULLLines_ReturnNULLN3();
    Test_ReadNum_NULLLenght_ReturnNULLN4();
    Test_ReadNum_NoEndChar_ReturnNULLN5();
    Test_ReadNum_ReadData_ValidValN6();
    Test_ReadGraph_NULLLines_ReturnNULLN7();
    Test_ReadGraph_NULLLenght_ReturnNULLN8();
    Test_ReadGraph_ReadData_ValidValN9();
    Test_IsInWay_NULLVert1_ReturnNULLN10();
    Test_IsInWay_NULLVert2_ReturnNULLN11();
    Test_IsInWay_NULLWay_ReturnNULLN12();
    Test_IsInWay_NULLLenght_ReturnNULLN13();
    Test_IsInWay_CheckInWay_ReturnTrue14();
    Test_FindWay_NULLLenght_ReturnNULLN15();
    Test_FindWay_NULLGraphLen_ReturnNULLN16();
    Test_FindWay_InvalidFromVert_ReturnNULLN17();
    Test_FindWay_InvalidToVert_ReturnNULLN18();
    Test_FindWay_InvalidK_ReturnNULLN19();
    Test_FindWay_NoWay_ReturnNULLN20();
    Test_FindWay_FindWay13k2_ReturnNULLN21();

    return 0;
}