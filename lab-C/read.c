/* Baydakova Margarita
 * 5030102/40004
 * Task 3 Variant 12
 * Graph Comparison
 * Read from .txt and parse functions file
 * Update: 01.11.25
 */

#include "grcomp.h"

int CountSize(char* Str)
{
	int N = 0, i = 0;

	if (Str == NULL)
		return 0;

	while (Str[i] != 0)
	{
		if (isn(Str[i]))
			N++;
		i++;
	}
	return N;
}

int GetStr(char* Src, char **Dst, int SP)
{
	int i = SP;

	if (Src == NULL || *Dst == NULL)
		return -1;

	while (Src[i] != '\n' && Src[i] != 0)
		(*Dst)[i - (SP)] = Src[i], i++;
	(*Dst)[i - (SP)] = 0;
	if (Src[i] == 0)
		return i;
	return i + 1;
}

int FindMax(char* Txt)
{

	int i = 0;
	int Res = 0, Cur = 0;
	while (Txt[i] != 0)
	{
		while (!isn(Txt[i]))
			i++;
		while (isn(Txt[i]))
			Cur = Cur * 10 + (Txt[i] - '0'), i++;
		if (Cur > Res)
			Res = Cur;
		Cur = 0;
	}
	return Res;
}

int ParserMatr(GRMATR* M, char* Text)
{
	char* Str;
	int i, j, c = 0;
	int Size;

	if ((Str = malloc(sizeof(char) * MAX_VERT * 2 + 1)) == NULL)
		return 0;

	GetStr(Text, &Str, c);
	Size = CountSize(Str);

	if (Size == 0)
		return 0;

	CreateMatr(M, Size);
	if (M == NULL)
		return 0;
	c = 0;
	for (i = 0; i < Size && Text[c] != 0; i++)
	{
		for (j = 0; j < Size; j++)
		{
			c = i * Size * 2 + j * 2;
			if (Text[c] != 0)
				M->Matr[i][j] = Text[c] - '0';
		}
	}
	return 1;
}

int ParserList(GRMATR* M, char* Text)
{
	char* Str;
	int pos = 0, size = 0, mx, j;

	if (M == NULL || (Str = malloc(sizeof(char) * MAX_LS)) == NULL)
		return 0;
	Str[0] = 0;
	mx = FindMax(Text);

	CreateMatr(M, mx);
	while (Text[pos] != 0)
	{
		int N1, N2;
		pos = GetStr(Text, &Str, pos);
		if (pos == -1)
			return 0;
		j = sscanf(Str, "%i %i", &N1, &N2);
		M->Matr[N1 - 1][N2 - 1] = 1;
	}
	return 1;
}

int ReadGraph(GRMATR* M, const char* FN)
{
	FILE* F;
	char Text[MAX_VERT * MAX_VERT * 6 + 1];
	int j;

	if (M == NULL || (F = fopen(FN, "r")) == NULL)
		return 0;
	j = fread(Text, sizeof(char), MAX_VERT * MAX_VERT * 6 + 1, F);
	Text[j] = 0;
	
	if (FN[0] == 'l')
		ParserList(M, Text);
	else if (FN[0] == 'm')
		ParserMatr(M, Text);
	
	fclose(F);
	return 1;
}
