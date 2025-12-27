#pragma once
#ifndef QUEENS_H
#define QUEENS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

	int Check(int* A, int N, int x, int y);
	int Queens(int* A, int N, int x, int y, int c);
	void Print(int* A, int N);

#ifdef __cplusplus
}
#endif

#endif