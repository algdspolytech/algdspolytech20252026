/* Baydakova Margarita
 * 5030102/40004
 * Task 1 Variant 11
 * Queue
 * List realisation file
 * Update: 10.10.25
 */

#include <stdio.h>
#include <stdlib.h>

#include "que.h"

 /* Static function that displays one elem of array on the screen(now is INT)
  * ARGS:
  *   t_que A - element;
  * RETS: None.
  */
static void PrintElem(t_que A)
{
	/*Now its int*/
	printf("%i ", A);
} /* End of "PrintElem" function */

/* Function that sets empty array
 * ARGS:
 *   QARR *A - pointer to the array struct;
 * RETS: None.
 */
void CreateArray(QARR* A)
{
	(*A).Arr = NULL;
	(*A).Size = 0;
} /* End of "CreateArray" function */

/* Function that displays an array on the screen
 * ARGS:
 *   QARR* A - pointer to the array;
 * RETS: None.
 */
void PrintArray(QARR A)
{
	int i;

	printf("\nPrint Array\n");
	if (A.Arr == NULL)
	{
		printf("(array)QUEUE is EMPTY\n");
		return;
	}

	for (i = 0; i < A.Size; i++)
		PrintElem(A.Arr[i]);
	printf("\n");
} /* End of "PrintArray" function */

/* Function that adds element to the end of the array
 * ARGS:
 *   QARR* A - pointer to the array
 *   t_que NewData - new element;
 * RETS: (int) - success or not.
 */
int PushToArray(QARR *A, t_que NewData)
{
	t_que* NewArr;
	int i;

	if (A == NULL)
		return 0;
	if (A->Size == 0)
		CreateArray(A);
	if ((NewArr = malloc(sizeof(t_que) * (++((*A).Size)))) != NULL)
	{
		for (i = 0; i < ((*A).Size) - 1; i++)
			NewArr[i] = (*A).Arr[i];
		NewArr[i] = NewData;
		(*A).Arr = NewArr;
		if ((*A).Arr[((*A).Size) - 1] == NewData)
			return 1;
	}
	return 0;
} /* End of "PushToArray" function */

/* Function that deletes element from the begin of the array
 * ARGS:
 *   QARR* A - pointer to the array
 * RETS: (int) - success or not.
 */
int PopFromArray(QARR *A)
{
	t_que* NewArr;
	int i;

	if (A == NULL || A->Size == 0)
		return 0;
	NewArr = malloc(sizeof(t_que) * (A->Size));
	A->Size -= 1;
	if (NewArr != NULL)
	{
		for (i = 0; i < A->Size; i++)
			NewArr[i] = A->Arr[i+1];
		free(A->Arr);
		if (A->Size > 0)
		{
			if ((A->Arr = malloc(sizeof(t_que) * ((*A).Size))) != NULL)
				for (i = 0; i < A->Size; i++)
					A->Arr[i] = NewArr[i];
		}
		else
			A->Arr = NULL;
		free(NewArr);
		return 1;
	}
	return 0;
} /* End of "PopFromArray" function */

/* Function that deletes all array
 * ARGS:
 *   QARR* A - pointer to the array
 * RETS: (int) - success or not.
 */
int ClearArray(QARR* A)
{
	if (A == NULL || A->Size == 0)
		return 0;
	while (A->Arr != NULL)
		PopFromArray(A);
	return 1;
} /* End of "ClearArray" function */

/* end of "array.c" file */