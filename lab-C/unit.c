/* Baydakova Margarita
 * 5030102/40004
 * Task 3 Variant 12
 * Graph Comparison
 * Unit test file
 * Update: 04.11.25
 */

#include "grcomp.h"

#define TMS 2
#define BMS 12
#define BPS 30

static void UnitCreateMatrix(void)
{
	GRMATR M;
	
	CreateMatr(&M, TMS);
	PrintMatr(&M, "Test 1");
}

static void UnitFreeMatrix(void)
{
	GRMATR M;

	M.Size = TMS;
	M.Matr = malloc(sizeof(int *) * TMS);
	M.Matr[0] = malloc(sizeof(int) * TMS);
	M.Matr[1] = malloc(sizeof(int) * TMS);

	M.Matr[0][0] = 0;
	M.Matr[0][1] = 0;
	M.Matr[1][0] = 0;
	M.Matr[1][1] = 0;
	FreeMatr(&M);
	
	PrintMatr(&M, "Test 2");
}

static void UnitGetString(void)
{
	char Buffer[BMS] = "test\nstring";
	char *Str;

	Str = malloc(sizeof(char) * BMS);
	GetStr(Buffer, &Str, 0);
	printf("Resulting String: %s\n", Str);
	GetStr(Buffer, &Str, BMS / 2);
	printf("Resulting String: %s\n", Str);
}

static void UnitCountSize(void)
{
	char Str[BMS] = "0 1 0 1";
	int c = CountSize(Str);

	printf("Size of Matrix: %i\n", c);
}

static void UnitFindMax(void)
{
	char Str[BMS] = "1 2\n5 3\n";
	int c = FindMax(Str);

	printf("Size of Matrix: %i\n", c);

}

static void UnitParserMatr(void)
{
	GRMATR M;

	ParserMatr(&M, "1 0\n0 1\n");
	PrintMatr(&M, "Test 6");
}

static void UnitParserList(void)
{
	GRMATR M;

	ParserList(&M, "1 2\n2 1");
	PrintMatr(&M, "Test 7");
}

static void UnitCGDS(void)
{
	GRMATR M1, M2;

	M1.Size = 1;
	M1.Matr = malloc(sizeof(int*));
	M1.Matr[0] = malloc(sizeof(int));
	
	M2.Size = TMS;
	M2.Matr = malloc(sizeof(int*) * TMS);
	M2.Matr[0] = malloc(sizeof(int) * TMS);
	M2.Matr[1] = malloc(sizeof(int) * TMS);

	M1.Matr[0][0] = 0;
	M2.Matr[0][0] = 0;
	M2.Matr[0][1] = 0;
	M2.Matr[1][0] = 0;
	M2.Matr[1][1] = 0;

	printf("Compare Graphs with %i and %i vertexes: %s\n", M1.Size, M2.Size, CR(CompareGraphs(&M1, &M2)));
}

static void UnitCGSS0(void)
{
	GRMATR M1, M2;

	M1.Size = TMS;
	M1.Matr = malloc(sizeof(int*) * TMS);
	M1.Matr[0] = malloc(sizeof(int) * TMS);
	M1.Matr[1] = malloc(sizeof(int) * TMS);

	M2.Size = TMS;
	M2.Matr = malloc(sizeof(int*) * TMS);
	M2.Matr[0] = malloc(sizeof(int) * TMS);
	M2.Matr[1] = malloc(sizeof(int) * TMS);

	M1.Matr[0][0] = 0;
	M1.Matr[0][1] = 0;
	M1.Matr[1][0] = 0;
	M1.Matr[1][1] = 1;

	M2.Matr[0][0] = 0;
	M2.Matr[0][1] = 0;
	M2.Matr[1][0] = 0;
	M2.Matr[1][1] = 0;

	printf("Compare Graphs with %i and %i vertexes: %s\n", M1.Size, M2.Size, CR(CompareGraphs(&M1, &M2)));
}

static void UnitCGSS1(void)
{
	GRMATR M1, M2;

	M1.Size = TMS;
	M1.Matr = malloc(sizeof(int*) * TMS);
	M1.Matr[0] = malloc(sizeof(int) * TMS);
	M1.Matr[1] = malloc(sizeof(int) * TMS);

	M2.Size = TMS;
	M2.Matr = malloc(sizeof(int*) * TMS);
	M2.Matr[0] = malloc(sizeof(int) * TMS);
	M2.Matr[1] = malloc(sizeof(int) * TMS);

	M1.Matr[0][0] = 0;
	M1.Matr[0][1] = 0;
	M1.Matr[1][0] = 0;
	M1.Matr[1][1] = 0;

	M2.Matr[0][0] = 0;
	M2.Matr[0][1] = 0;
	M2.Matr[1][0] = 0;
	M2.Matr[1][1] = 0;

	printf("Compare Graphs with %i and %i vertexes: %s\n", M1.Size, M2.Size, CR(CompareGraphs(&M1, &M2)));

}

void AllUnits(void)
{
	printf("Unit #1 : (Create Matrix 2x2)\n");
	UnitCreateMatrix();
	printf("Unit #2 : (Free Matrix 3x3)\n");
	UnitFreeMatrix();
	printf("Unit #3 : (Get one String from Buffer by position)\n");
	UnitGetString();
	printf("Unit #4 : (Count number of Vertexes by one string Adjacency Matrix)\n");
	UnitCountSize();
	printf("Unit #5 : (Count number of Vertexes by MAX element at Adjacency List)\n");
	UnitFindMax();
	printf("Unit #6 : (Parser file like a Matrix)\n");
	UnitParserMatr();
	printf("Unit #7 : (Parser file like a List)\n");
	UnitParserList();
	printf("Unit #8 : (Compare Graphs with different number of Vertexes)\n");
	UnitCGDS();
	printf("Unit #9 : (Compare Similar Graphs)\n");
	UnitCGSS1();
	printf("Unit #10: (Compare Graphs with same number of Vertexes)\n");
	UnitCGSS0();
}