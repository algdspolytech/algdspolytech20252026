#include <stdio.h>
#include <stdlib.h>
#include "LabD.h"

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable: 4996)

void Read(int* B, int* N, int** A) {
	FILE* file = fopen("input.txt", "r");
	if (file == NULL) {
		return;
	}
	fscanf(file, "%i", B);
	fscanf(file, "%i", N);
	*A = (int*)malloc(*N * sizeof(int));
	for (int i = 0; i < *N; i++) {
		fscanf(file, "%i", &((*A)[i]));
	}
	fclose(file);
}

void FindSum(int B, int N, int* A, FILE* output, int** DEBUGResult, int* DEBUGResultSize) {
	int** D = (int**)malloc((N + 1) * sizeof(int*));
	for (int i = 0; i <= N; i++) {
		D[i] = (int*)malloc((B + 1) * sizeof(int));
	}
	for (int i = 0; i <= N; i++) {
		D[i][0] = 1;
	}
	for (int j = 1; j <= B; j++) {
		D[0][j] = 0;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= B; j++) {
			if (A[i - 1] > j) {
				D[i][j] = D[i - 1][j];
			}
			else {
				D[i][j] = D[i - 1][j] || D[i - 1][j - A[i - 1]];
			}
		}
	}
	if (D[N][B] == 1) {
		int csum = B;
		int* result = (int*)malloc(N * sizeof(int));
		int rN = 0;
		for (int i = N; i > 0; i--) {
			if (csum > 0) {
				if (D[i - 1][csum] == 0) {
					result[rN++] = A[i - 1];
					csum -= A[i - 1];
				}
			}
		}
		*DEBUGResult = result;
		*DEBUGResultSize = rN;
		for (int i = rN - 1; i >= 0; i--) {
			fprintf(output, "%i ", result[i]);
		}
	}
	else {
		fprintf(output, "0");
	}
	for (int i = 0; i <= N; i++) {
		free(D[i]);
	}
	free(D);
}

int CalculateSum(int* result, int N) {
	int sum = 0;
	if (result == NULL) {
		return 0;
	}

	for (int i = 0; i < N; i++) {
		if (result[i] == 0) {
			break;
		}
		sum += result[i];
	}
	return sum;
}