#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.H"

void FileParsing__NonExistFile(void)
{
	char *tmp;

	printf("FileParsing__NonExistFile: ");
	printf(FileParsing("> TheNonExistingFile <.txt", &tmp) == 0 ? "SUCCESS" : "ERROR");
	printf("\n");
}

void FileParsing__EmptyFile(void)
{
	char *res;

	FileParsing("EmptyFile.txt", &res);

	printf("FileParsing__EmptyFile: ");
	printf(strcmp(res, "") == 0 ? "SUCCESS" : "ERROR");
	printf("\n");

	free(res);
}

void FileParsing__NotEmptyFile(void)
{
	char* res;
	int i;

	const char *fpart = "2 1 3\n    1 2\n\n\n\n\n           \n\n";
	const char *spart = "\n\n3 2   4 5          \n4 3 5\n5 3    ";
	const char *tpart = "                                       4";
	char full[107];

	for (i = 0; i < 107; i++)
	{
		full[i] = 0;
	}

	strcat_s(full, 32, fpart);
	strcat_s(full, 67, spart);
	strcat_s(full, 107, tpart);

	FileParsing("input.txt", &res);

	printf("FileParsing__NotEmptyFile: ");
	printf(strcmp(res, full) == 0 ? "SUCCESS" : "ERROR");
	printf("\n");

	free(res);
}

void ListParsing__IncorrectSymbol(void)
{
	list_t l;
	int i;
	char *str;
	const char *str2 = "1 2 3\n2 1 3\n3 !1 2\n";
	
	str = (char*)malloc(20 * sizeof(char));
	if (str == NULL)
	{
		return;
	}

	for (i = 0; i < 20; i++)
	{
		str[i] = str2[i];
	}

	ListCreate(&l);

	printf("ListParsing__IncorrectSymbol: ");
	printf(ListParsing(l, str) == 0 ? "SUCCESS" : "ERROR");
	printf("\n");

	ListDestroy(l);
	free(str);
}

void ListParsing__ManySpaces(void)
{
	list_t l;
	int i;
	char *str, *res;
	const char *str2 = "1 2       3\n2    1 3\n3 1      2       \n";
	
	str = (char*)malloc(40 * sizeof(char));
	if (str == NULL)
	{
		return;
	}

	for (i = 0; i < 40; i++)
	{
		str[i] = str2[i];
	}

	ListCreate(&l);

	printf("ListParsing__ManySpaces: ");

	ListParsing(l, str);
	res = ListPrint(l);
	printf(strcmp(res, "1 2 3\n2 1 3\n3 1 2\n") == 0 ? "SUCCESS" : "ERROR");
	printf("\n");

	ListDestroy(l);
	free(str);
	free(res);
}

void ListParsing__EmptyLines(void)
{
	list_t l;
	int i;
	char *str, *res;
	const char *str2 = "1 2 3\n2 1 3\n\n\n\n\n\n\n\n\n3 1 2\n\n\n";

	str = (char*)malloc(29 * sizeof(char));
	if (str == NULL)
	{
		return;
	}

	for (i = 0; i < 29; i++)
	{
		str[i] = str2[i];
	}

	ListCreate(&l);

	printf("ListParsing__EmptyLines: ");

	ListParsing(l, str);
	res = ListPrint(l);
	printf(strcmp(res, "1 2 3\n2 1 3\n3 1 2\n") == 0 ? "SUCCESS" : "ERROR");
	printf("\n");

	ListDestroy(l);
	free(str);
	free(res);
}

void ListParsing__EmptyString(void)
{
	list_t l;
	char *str, *res;

	str = (char*)malloc(sizeof(char));
	if (str == NULL)
	{
		return;
	}
	str[0] = 0;

	ListCreate(&l);
	printf("ListParsing__EmptyString: ");

	ListParsing(l, str);
	res = ListPrint(l);
	printf(strcmp(res, "") == 0 ? "SUCCESS" : "ERROR");
	printf("\n");
	ListDestroy(l);
	free(str);
	free(res);
}

void ListParsing__ZeroEdges(void)
{
	list_t l;
	char *str, *res;

	str = (char*)malloc(2 * sizeof(char));
	if (str == NULL)
	{
		return;
	}
	str[0] = '1';
	str[1] = 0;

	ListCreate(&l);
	printf("ListParsing__ZeroEdges: ");

	ListParsing(l, str);
	res = ListPrint(l);

	printf(strcmp(res, "1\n") == 0 ? "SUCCESS" : "ERROR");
	printf("\n");
	ListDestroy(l);
	free(str);
	free(res);
}

void MatrixCreate__NonExistingNodes(void)
{
	list_t l;
	int i;
	int **matrix;
	char *str, *res;
	const char *str2 = "1 2 3\n2 1 3 4 5 6 7 8 9\n3 1 2\n";

	str = (char*)malloc(31 * sizeof(char));
	if (str == NULL)
	{
		return;
	}

	for (i = 0; i < 31; i++)
	{
		str[i] = str2[i];
	}

	ListCreate(&l);

	printf("MatrixCreate__NonExistingNodes: ");

	ListParsing(l, str);
	MatrixCreate(l, &matrix);
	res = MatrixGet(matrix);
	printf(strcmp(res, "0 1 1\n1 0 1\n1 1 0\n") == 0 ? "SUCCESS" : "ERROR");
	printf("\n");

	ListDestroy(l);
	MatrixDestroy(matrix);
	free(str);
	free(res);
}

void MatrixCreate__EmptyMatrix(void)
{
	list_t l;
	int** matrix;
	char* str, *res;

	FileParsing("EmptyFile.txt", &str);

	ListCreate(&l);

	printf("MatrixCreate__EmptyMatrix: ");

	ListParsing(l, str);
	MatrixCreate(l, &matrix);
	res = MatrixGet(matrix);
	printf(strcmp(res, "") == 0 ? "SUCCESS" : "ERROR");
	printf("\n");

	ListDestroy(l);
	MatrixDestroy(matrix);
	free(str);
	free(res);
}
