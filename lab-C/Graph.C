#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.H"

typedef struct MyList
{
	int vert;
	int size;
	int *verts;
	struct MyList *next;
} MyList;

typedef struct MyListShell
{
	int size;
	struct MyList *next;
} MyListShell;

int MyCompare(const void* a, const void* b)
{
	const MyList* const* pa = a;
	const MyList* const* pb = b;

	if ((*pa)->vert < (*pb)->vert)
	{
		return -1;
	}
	if ((*pa)->vert > (*pb)->vert)
	{
		return 1;
	}
	return 0;
}

int ListCreate(list_t *l)
{
	*l = (list_t)malloc(sizeof(MyListShell));
	if (*l == NULL)
	{
		return -1;
	}

	(*l)->size = 0;
	(*l)->next = NULL;

	return 1;
}

int ListDestroy(list_t l)
{
	int i;
	MyList *cur, *prev;

	cur = l->next;
	for (i = 0; i < l->size; i++)
	{
		prev = cur;
		cur = cur->next;
		free(prev->verts);
		free(prev);
	}
	free(l);

	return 1;
}

char* ListPrint(list_t l)
{
	int i, j, k;
	MyList *cur;
	char tmp[11];
	char *res, *tmp2;
	int size;

	for (i = 0; i < 11; i++)
	{
		tmp[i] = 0;
	}

	res = (char*)malloc(sizeof(char));
	if (res == NULL)
	{
		return NULL;
	}
	res[0] = 0;

	cur = l->next;
	for (i = 0; i < l->size; i++)
	{
		snprintf(tmp, 11, "%i", cur->vert);

		size = (int)_msize(res) / sizeof(char);

		tmp2 = res;
		res = (char*)realloc(res, _msize(res) + sizeof(char) * strlen(tmp));
		if (res == NULL)
		{
			res = tmp2;
			return res;
		}
		for (j = size - 1; j < _msize(res) / sizeof(char); j++)
		{
			res[j] = 0;
		}

		for (j = 0; j < strlen(tmp); j++)
		{
			res[size - 1 + j] = tmp[j];
		}
		
		for (j = 0; j < cur->size; j++)
		{
			snprintf(tmp, 11, "%i", cur->verts[j]);

			size = (int)_msize(res) / sizeof(char);

			tmp2 = res;
			res = (char*)realloc(res, _msize(res) + sizeof(char) * (strlen(tmp) + 1));
			if (res == NULL)
			{
				res = tmp2;
				return res;
			}
			for (k = size - 1; k < _msize(res) / sizeof(char); k++)
			{
				res[k] = 0;
			}

			res[size - 1] = ' ';
			for (k = 0; k < strlen(tmp); k++)
			{
				res[size + k] = tmp[k];
			}
		}

		tmp2 = res;
		res = (char*)realloc(res, _msize(res) + sizeof(char));
		if (res == NULL)
		{
			res = tmp2;
			return res;
		}
		res[_msize(res) - 2] = '\n';
		res[_msize(res) - 1] = 0;

		cur = cur->next;
	}

	return res;
}

int FileParsing(char *fname, char **res)
{
	FILE *f;
	char *tmp;
	int c;

	f = fopen(fname, "r");
	if (f == NULL)
	{
		return 0;
	}

	*res = (char*)malloc(sizeof(char));
	if (*res == NULL)
	{
		return -1;
	}
	(*res)[0] = 0;

	c = fgetc(f);
	while (c != EOF)
	{
		tmp = *res;
		*res = (char*)realloc(*res, _msize(*res) + sizeof(char));
		if (*res == NULL)
		{
			*res = tmp;
			return -1;
		}

		(*res)[_msize(*res) / sizeof(char) - 1] = 0;
		(*res)[_msize(*res) / sizeof(char) - 2] = (char)c;

		c = fgetc(f);
	}
	fclose(f);

	return 1;
}

int ListParsing(list_t l, char *str)
{
	int size, i;
	int curnum, flag;
	int prevc, curc;
	int *tmp;
	MyList **cur, **p;

	size = (int)_msize(str) / sizeof(char);
	prevc = -1;
	curc = -1;
	flag = 1;
	curnum = 0;
	cur = &(l->next);
	str[size - 1] = '\n';

	for (i = 0; i < size; i++)
	{
		prevc = curc;
		curc = (int)str[i];

		if (curc != ' ' && curc != '\n' && (curc < '0' || curc > '9'))
		{
			return 0;
		}

		if (curc == ' ' && (prevc >= '0' && prevc <= '9'))
		{
			if (flag)
			{
				*cur = malloc(sizeof(MyList));
				if (*cur == NULL)
				{
					return -1;
				}

				(*cur)->vert = curnum;
				(*cur)->size = 0;
				(*cur)->verts = NULL;

				l->size += 1;
				flag = 0;
			}
			else
			{
				tmp = (*cur)->verts;
				(*cur)->verts = (int*)realloc((*cur)->verts, ((*cur)->size + 1) * sizeof(int));
				if ((*cur)->verts == NULL)
				{
					(*cur)->verts = tmp;
					return -1;
				}

				(*cur)->verts[(*cur)->size] = curnum;
				(*cur)->size += 1;
			}
			curnum = 0;
		}
		else if (curc >= '0' && curc <= '9')
		{
			curnum *= 10;
			curnum += curc - 48;
		}
		else if (curc == '\n')
		{
			if (prevc >= '0' && prevc <= '9')
			{
				if (flag)
				{
					*cur = malloc(sizeof(MyList));
					if (*cur == NULL)
					{
						return -1;
					}

					(*cur)->vert = curnum;
					(*cur)->size = 0;
					(*cur)->verts = NULL;

					l->size += 1;
					flag = 0;
				}
				else
				{
					tmp = (*cur)->verts;
					(*cur)->verts = (int*)realloc((*cur)->verts, ((*cur)->size + 1) * sizeof(int));
					if ((*cur)->verts == NULL)
					{
						(*cur)->verts = tmp;
						return -1;
					}

					(*cur)->verts[(*cur)->size] = curnum;
					(*cur)->size += 1;
				}
				curnum = 0;
			}
			if (flag != 1)
			{
				flag = 1;
				cur = &((*cur)->next);
			}
		}
	}
	str[size - 1] = 0;

	p = (MyList**)malloc(sizeof(MyList*) * (l->size));
	if (p == NULL)
	{
		return -1;
	}

	cur = &(l->next);
	for (i = 0; i < l->size; i++)
	{
		p[i] = *cur;
		cur = &((*cur)->next);
	}
	qsort(p, l->size, sizeof(MyList*), MyCompare);

	cur = &(l->next);
	for (i = 0; i < l->size; i++)
	{
		*cur = p[i];
		cur = &((*cur)->next);
	}

	free(p);

	return 1;
}

int MatrixCreate(list_t l, int ***matrix)
{
	int i, j, k;
	int curnum;
	MyList **p, **cur;

	p = (MyList**)malloc(sizeof(MyList*) * (l->size));
	if (p == NULL)
	{
		return -1;
	}

	cur = &(l->next);
	for (i = 0; i < l->size; i++)
	{
		p[i] = *cur;
		cur = &((*cur)->next);
	}
	
	*matrix = (int**)malloc(sizeof(int*) * (l->size));
	if (*matrix == NULL)
	{
		return -1;
	}

	for (i = 0; i < l->size; i++)
	{
		(*matrix)[i] = (int*)malloc(sizeof(int) * (l->size));
		if ((*matrix)[i] == NULL)
		{
			return -1;
		}

		for (j = 0; j < l->size; j++)
		{
			(*matrix)[i][j] = 0;
		}
	}

	for (i = 0; i < l->size; i++)
	{
		for (j = 0; j < (p[i])->size; j++)
		{
			curnum = (p[i])->verts[j];
			for (k = 0; k < l->size; k++)
			{
				if (curnum == (p[k])->vert)
				{
					(*matrix)[i][k] = 1;
				}
			}
		}
	}

	free(p);

	return 1;
}

int MatrixDestroy(int **matrix)
{
	int i, size;

	size = (int)_msize(matrix) / sizeof(int*);
	for (i = 0; i < size; i++)
	{
		free(matrix[i]);
	}
	free(matrix);

	return 1;
}

char* MatrixGet(int **matrix)
{
	int i, j, size, ressize;
	char *res, *tmp;

	res = (char*)malloc(sizeof(char));
	if (res == NULL)
	{
		return NULL;
	}
	res[0] = 0;

	for (i = 0; i < _msize(matrix) / sizeof(int*); i++)
	{
		ressize = (int)_msize(res) / sizeof(char);
		size = ((int)_msize(matrix[i]) / sizeof(int)) * 2;

		tmp = res;
		res = (char*)realloc(res, _msize(res) + size * sizeof(char));
		if (res == NULL)
		{
			res = tmp;
			return res;
		}
		for (j = ressize - 1; j < _msize(res) / sizeof(char); j++)
		{
			res[j] = 0;
		}

		res[ressize - 1] = (char)(matrix[i][0] + 48);
		for (j = 0; j < _msize(matrix[i]) / sizeof(int) - 1; j++)
		{
			res[ressize + j * 2] = ' ';
			res[ressize + j * 2 + 1] = (char)(matrix[i][j + 1] + 48);
		}
		res[_msize(res) / sizeof(char) - 2] = '\n';
	}

	return res;
}

int MatrixPrint(list_t l, int **matrix)
{
	int i, j;
	MyList **p, **cur;

	p = (MyList**)malloc(sizeof(MyList*) * (l->size));
	if (p == NULL)
	{
		return -1;
	}

	cur = &(l->next);
	for (i = 0; i < l->size; i++)
	{
		p[i] = *cur;
		cur = &((*cur)->next);
	}

	printf("  ");
	for (i = 0; i < l->size; i++)
	{
		printf(" %i", (p[i])->vert);
	}
	printf("\n");
	for (i = 0; i < l->size; i++)
	{
		printf("%i:", (p[i])->vert);
		for (j = 0; j < l->size; j++)
		{
			printf(" %i", matrix[i][j]);
		}
		printf("\n");
	}

	free(p);
	
	return 1;
}
