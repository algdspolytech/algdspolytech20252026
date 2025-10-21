#pragma warning(disable : 4996)

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include "labC.h"

#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int ReadM(FILE* file, int*** A) {
  if (file == NULL) {
    return 0;
  }

  int N;
  if (fscanf(file, "%d", &N) != 1) {
    fclose(file);
    return 0;
  }

  *A = (int**)malloc(N * sizeof(int*));
  for (int i = 0; i < N; i++) {
    (*A)[i] = (int*)malloc(N * sizeof(int));
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      fscanf(file, "%d", &(*A)[i][j]);
    }
  }

  fclose(file);
  return N;
}

void PrintM(int** A, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", A[i][j]);
    }
    printf("\n");
  }

  return 0;
}

void PrintAdjL(int** A, int N) {
  for (int i = 0; i < N; i++) {
    printf("%i|", i + 1);
    for (int j = 0; j < N; j++) {
      if (A[i][j] == 1) {
        printf(" %i", j + 1);
      }
    }
    printf("\n");
  }
  return 0;
}

void WriteAdjL(FILE* file, int** A, int N) {
  for (int i = 0; i < N; i++) {
    fprintf(file, "%i|", i + 1);
    for (int j = 0; j < N; j++) {
      if (A[i][j] == 1) {
        fprintf(file, " %i", j + 1);
      }
    }
    fprintf(file, "\n");
  }
  return 0;
}

void FreeMatrix(int** A, int N) {
  for (int i = 0; i < N; i++) {
    free(A[i]);
  }
  free(A);
}

 /*int main() {
  setlocale(LC_CTYPE, "Russian");
  FILE* file = fopen("labC.txt", "r");
  FILE* fileb = fopen("labCw.txt", "w+");

  int** A = 0;

  int N = ReadM(file, &A);

  PrintM(A, N);
  PrintAdjL(A, N);
  WriteAdjL(fileb, A, N);
  FreeMatrix(A, N);
  return 0;
}*/