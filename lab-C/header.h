#pragma once

#define x 10
#define y 10

void FindStart(int A[x][y], int* sx, int* sy, int* ex, int* ey);
void FindWay(int A[x][y], int sx, int sy);
void Way(int A[x][y], int ex, int ey, int c, char B[x][y]);
void FullArr(char A[x][y], char c);
void Print(int A[x][y]);
void PrintChar(char A[x][y]);