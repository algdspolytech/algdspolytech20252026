#pragma once

#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable: 4996)

void Read(int* B, int* N, int** A);

void FindSum(int B, int N, int* A, FILE* output, int** DEBUGResult, int* DEBUGResultSize);

int CalculateSum(int* result, int N);