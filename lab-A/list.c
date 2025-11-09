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

 /* Static function that displays one elem of list on the screen(now is INT)
  * ARGS:
  *   t_que A - element;
  * RETS: None.
  */
static void PrintElem(t_que A)
{
	/*Now its int*/
	printf("%i ", A);
} /* End of "PrintElem" function */

/* Function that displays a list on the screen
 * ARGS:
 *   QLIST* L - pointer to the beginning of the list being used;
 * RETS: None.
 */
void PrintList(QLIST *L)
{
	printf("\nPrint List\n");
	if (L == NULL)
	{
		printf("(list)QUEUE is EMPTY\n");
		return;
	}
	while (L != NULL)
	{
		PrintElem(L->Data);
		L = L->Next;
	}
	printf("\n");
} /* End of "PrintList" function */

/* Function that adds element to the end of the list
 * ARGS:
 *   QLIST** L - double pointer to the beginning of the list being used;
 *   t_que NewData - new element;
 * RETS: (int) - success or not.
 */
int PushToList(QLIST** L, t_que NewData)
{
	QLIST* NewElem, *Tmp = *L;

	if ((NewElem = malloc(sizeof(QLIST))) == NULL)
		return 0;

	NewElem->Data = NewData;
	NewElem->Next = NULL;

	if (*L == NULL)
		*L = NewElem;
	else
	{
		while (Tmp->Next != NULL)
			Tmp = Tmp->Next;
		Tmp->Next = NewElem;
	}
	return 1;
}/* End of "PushToList" function */

/* Function that deletes element from the begin of the list
 * ARGS:
 *   QLIST** L - double pointer to the beginning of the list being used;
 * RETS: (int) - success or not.
 */
int PopFromList(QLIST** L)
{
	QLIST* NewList = NULL;

	if (*L == NULL)
		return 0;
	if ((*L)->Next != NULL)
		NewList = (*L)->Next;
	free(*L);
	*L = NewList;
	return 1;
}/* End of "PopFromList" function */

/* Function that deletes all list
 * ARGS:
 *   QLIST** L - double pointer to the beginning of the list being used;
 * RETS: (int) - success or not.
 */
int ClearList(QLIST** L)
{
	if (*L == NULL)
		return 0;
	while (*L != NULL)
		PopFromList(L);
	return 1;
}/* End of "ClearList" function */

/* end of "list.c" file */