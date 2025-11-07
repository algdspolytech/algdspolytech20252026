/* Baydakova Margarita
 * 5030102/40004
 * Task 3 Variant 12
 * Graph Comparison
 * Header file
 * Update: 01.11.25
 */

#ifndef _grcomp_h_

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_VERT 20
#define MAX_LS 7
#define isn(c) (c >= '0' && c <= '9')
#define CR(i) (i == 0 ? "Not Same" : (i == 2 ? "Diff Size" : "Same"))

/* matr struct */
typedef struct 
{
	int **Matr;   // Data field(in program use INT)
	int Size;     // Size of matr (Number of vertexes)
} GRMATR;

void FreeMatr(GRMATR* M);
void CreateMatr(GRMATR* M, int Size);
void PrintMatr(GRMATR* M, const char* Descr);

int CountSize(char* Str);
int GetStr(char* Src, char** Dst, int SP);
int FindMax(char* Txt);
int ParserMatr(GRMATR* M, char* Text);
int ParserList(GRMATR* M, char* Text);

int ReadGraph(GRMATR* M, const char* FN);
int CompareGraphs(GRMATR* M1, GRMATR* M2);

void AllUnits(void);

#endif _grcomp_h_

/* end of 'grcomp.h' file */