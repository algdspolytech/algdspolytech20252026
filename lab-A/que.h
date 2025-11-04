/* Baydakova Margarita
 * 5030102/40004
 * Task 1 Variant 11
 * Queue
 * Header file
 * Update: 10.10.25
 */

#ifndef _que_h_

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/* choose working type */
typedef int t_que;

/* list struct */
typedef struct tagQLIST QLIST;
struct tagQLIST
{
	t_que Data;   // Data field(in program use INT)
	QLIST* Next;  // Pointer to next element
};
/* array struct */
typedef struct
{
	t_que* Arr;   // Pointer to first elem of array
	int Size;     // Current size of array
} QARR;

/* Function that displays a list on the screen
 * ARGS:
 *   QLIST* L - pointer to the beginning of the list being used;
 * RETS: None.
 */
void PrintList(QLIST* L);

/* Function that adds element to the end of the list
 * ARGS:
 *   QLIST** L - double pointer to the beginning of the list being used;
 *   t_que NewData - new element;
 * RETS: (int) - success or not.
 */
int PushToList(QLIST** L, t_que NewData);

/* Function that deletes element from the begin of the list
 * ARGS:
 *   QLIST** L - double pointer to the beginning of the list being used;
 * RETS: (int) - success or not.
 */
int PopFromList(QLIST** L);

/* Function that deletes all list
 * ARGS:
 *   QLIST** L - double pointer to the beginning of the list being used;
 * RETS: (int) - success or not.
 */
int ClearList(QLIST** L);

/* Function that sets empty array
 * ARGS:
 *   QARR *A - pointer to the array struct;
 * RETS: None.
 */
void CreateArray(QARR* A);

/* Function that displays an array on the screen
 * ARGS:
 *   QARR* A - pointer to the array;
 * RETS: None.
 */
void PrintArray(QARR A);

/* Function that adds element to the end of the array
 * ARGS:
 *   QARR* A - pointer to the array
 *   t_que NewData - new element;
 * RETS: (int) - success or not.
 */
int PushToArray(QARR* A, t_que NewData);

/* Function that deletes element from the begin of the array
 * ARGS:
 *   QARR* A - pointer to the array
 * RETS: (int) - success or not.
 */
int PopFromArray(QARR *A);

/* Function that deletes all array
 * ARGS:
 *   QARR* A - pointer to the array
 * RETS: (int) - success or not.
 */
int ClearArray(QARR* A);

/* Actually one function to use all unit tests */
void AllUnits(void);

#endif _que_h_

/* end of 'que.h' file */