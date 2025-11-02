#pragma once
#include <stdio.h>
#define n 10


#ifdef __cplusplus
extern "C" {
#endif

    int Num_In_Mas(int* mas, int num);

    int* Add_To_List(int* mas, int num);

    int* DFS(int** a, int* marked_node, int num);

    int** Create_Graph_Matrix(FILE* file);

    char* Way_Between_Graph_Node(int** a, int node1, int node2);

#ifdef __cplusplus
}
#endif