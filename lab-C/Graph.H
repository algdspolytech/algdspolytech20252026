#pragma once

typedef struct MyListShell* list_t;

int ListCreate(list_t *l);
int ListDestroy(list_t l);
char* ListPrint(list_t l);
int FileParsing(char *fname, char **res);
int ListParsing(list_t l, char *str);
int MatrixCreate(list_t l, int ***matrix);
int MatrixDestroy(int **matrix);
char* MatrixGet(int **matrix);
int MatrixPrint(list_t l, int **matrix);