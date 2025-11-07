/* Baydakova Margarita
 * 5030102/40004
 * Task 3 Variant 12
 * Graph Comparison
 * DMP work file
 * Update: 30.10.25
 */

#include "grcomp.h"

void FreeMatr(GRMATR* M)
{
	int i;

	if (M == NULL)
		return;
	for (i = 0; i < M->Size; i++)
		free(M->Matr[i]);
	M->Size = 0;
}

void CreateMatr(GRMATR* M, int Size)
{
	int i, j;

	if (M == NULL)
		return;
	if ((M->Matr = malloc(sizeof(int*) * Size)) == NULL)
		return;
	for(i = 0; i < Size;i++)
	{
		if ((M->Matr[i] = malloc(sizeof(int) * Size)) == NULL)
			return;
		for (j = 0; j < Size; j++)
			M->Matr[i][j] = 0;
	}
	(*M).Size = Size;
}

