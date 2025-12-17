#pragma once
#include <stdio.h> 
#include <math.h> 
#include <locale.h> 
#include <malloc.h> 
#include <stdlib.h> 
#include <crtdbg.h> 

typedef struct {
    int* NeighboursVert;
    int NumOfNeigh;
    int Vertnum;
}vertex;

typedef struct {
    int vert1;
    int vert2;
}edge;

int FromStr2Num(char* str, int len);

char* ReadNum(char* lines, int lenght, int* i, int* numlen, char endchar);

vertex* ReadGraph(char* lines, int lenght, int* graphlen, int* fromvert, int* tovert, int* k);

int IsInWay(int prevcheckvert, int checkwert, edge* way, int currwaylen);

int FindWay(vertex* graph, int graphlen, int prevvert, int fromvert, int tovert, int k, edge** way, int* currwaylen);
