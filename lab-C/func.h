#ifndef LAB_1_H
#include <stdio.h>
#define LAB_1_H

#ifdef __cplusplus
extern "C" {
#endif

enum{N = 6};

int** ReadMatrix(FILE* f);
int ExistPath(int **Arr, int v, int k);

#endif

#ifdef __cplusplus
}
#endif