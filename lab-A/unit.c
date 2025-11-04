/* Unit module */

#include "que.h"

#define IsntMode(R) (R != 'a' && R != 'A' && R != 'l' && R != 'L')

/* Array Part */

static void UnitSetEmptyArray(void)
{
	QARR A;
	CreateArray(&A);
	PrintArray(A);
}

static void UnitAddElemArray(void)
{
	QARR A;
	A.Size = 0;
	PushToArray(&A, 1);
	PrintArray(A);
}

static void UnitAddSecondElemArray(void)
{
	QARR A;
	A.Size = 0;

	A.Arr = malloc(sizeof(t_que) * (++(A.Size)));
	A.Arr[0] = 1;

	PushToArray(&A, 1);
	PrintArray(A);
}

static void UnitDelElemArray(void)
{
	QARR A;
	A.Size = 0;

	A.Arr = malloc(sizeof(t_que) * (++(A.Size)));
	A.Arr[0] = 1;
	
	PopFromArray(&A);
	PrintArray(A);
}

static void UnitClearArray(void)
{
	QARR A;
	A.Size = 2;

	A.Arr = malloc(sizeof(t_que) * 2);
	A.Arr[0] = 1;
	A.Arr[1] = 1;

	ClearArray(&A);
	PrintArray(A);
}


/* List Part */

static void UnitSetEmptyList(void)
{
	QLIST* A = NULL;
	PrintList(A);
}

static void UnitAddElemList(void)
{
	QLIST* A = NULL;
	
	PushToList(&A, 1);
	PrintList(A);
}

static void UnitAddSecondElemList(void)
{
	QLIST* A;

	A = malloc(sizeof(QLIST));
	A->Data = 1;
	A->Next = NULL;

	PushToList(&A, 1);
	PrintList(A);
}

static void UnitDelElemList(void)
{
	QLIST *A;
	
	A = malloc(sizeof(QLIST));
	A->Data = 1;
	A->Next = NULL;
	
	PopFromList(&A);
	PrintList(A);
}

static void UnitClearList(void)
{
	QLIST* A;

	A = malloc(sizeof(QLIST));
	A->Data = 1;
	A->Next = malloc(sizeof(QLIST));
	A->Next->Data = 1;
	A->Next->Next = NULL;

	ClearList(&A);
	PrintList(A);
}

void AllUnits(void)
{
	printf("\n   ---   \nPrint Empty QUEUE(check structures initialization)\n");
	UnitSetEmptyList();
	UnitSetEmptyArray();

	printf("\n   ---   \nAdd one element to EMPTY QUEUE\n");
	UnitAddElemList();
	UnitAddElemArray();

	printf("\n   ---   \nAdd one element to NOT EMPTY QUEUE\n");
	UnitAddSecondElemList();
	UnitAddSecondElemArray();

	printf("\n   ---   \nDelete one element from QUEUE(is 1 elem, will be 0)\n"); 
	UnitDelElemList();
	UnitDelElemArray();

	printf("\n   ---   \nClear QUEUE(is 2 elem, will be 0)\n");
	UnitClearList();
	UnitClearArray();
}

