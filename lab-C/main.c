/* Baydakova Margarita
 * 5030102/40004
 * Task 3 Variant 12
 * Graph Comparison
 * Main C file
 * Update: 01.11.25
 */

#include "grcomp.h"

void PrintMatr(GRMATR* M, const char *Descr)
{
	int i, j;
	printf("Print: %s\n", Descr);
	if (M->Size == 0)
	{
		printf("EMPTY\n");
		return;
	}
	for (i = 0; i < M->Size; i++)
	{
		for (j = 0; j < M->Size; j++)
			printf("|%3i", M->Matr[i][j]);
		printf("|\n");
	}
}

int CompareGraphs(GRMATR *M1, GRMATR *M2)
{
	int i, j;

	if (M1 == NULL || M2 == NULL)
		return 2;
	
	if (M1->Size != M2->Size)
		return 0;
	for (i = 0; i < M1->Size; i++)
		for (j = 0; j < M1->Size; j++)
			if (M1->Matr[i][j] != M2->Matr[i][j])
				return 0;
	return 1;
}

int main(void)
{
	GRMATR *M;
	GRMATR *L;
	int res;
	char ResDescr[3][10] = { "Not Same", "Same", "Error" };

	if ((M = malloc(sizeof(GRMATR))) != NULL && (L = malloc(sizeof(GRMATR))) != NULL)
	{
		ReadGraph(M, "matr.txt");
		PrintMatr(M, "Graph By Matr");
		ReadGraph(L, "list.txt");
		PrintMatr(L, "Graph By List");

		res = CompareGraphs(M, L);
		printf("Result of Comparing: %s\n", ResDescr[res]);
		FreeMatr(M);
		FreeMatr(L);
	}

	AllUnits();
}
