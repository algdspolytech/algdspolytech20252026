#pragma once
#ifndef LABC_H
#define LABC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int ReadM(FILE* file, int*** A);
void PrintM(int** A, int N);
void PrintAdjL(int** A, int N);
void WriteAdjL(FILE* file, int** A, int N);
void FreeMatrix(int** A, int N);

#ifdef __cplusplus
}
#endif

#endif