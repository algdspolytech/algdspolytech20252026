#pragma once
#ifndef LAB_D_H
#define LAB_D_H

#define MAX_V 1000

#ifdef __cplusplus
extern "C" {
#endif

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GrphStrc {
  int** Grph;
  int* w;
  int* path;
  int ptl;
  int flag;
} GrphStrc;

void InGraph(GrphStrc* graph, int V);
void FreeGraph(GrphStrc* graph, int V);
int ReadLst(FILE* file, GrphStrc* strct, int* V, int* s, int* t, int* K);
int DeepSearc(GrphStrc* strct, int s, int len, int V, int t, int K);
int Write(FILE* file, GrphStrc* strct);

#ifdef __cplusplus
}
#endif

#endif