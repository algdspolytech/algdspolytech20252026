#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
struct SubsetResult* createSubsetResult() {
	struct SubsetResult* result = (struct SubsetResult*)malloc(sizeof(struct SubsetResult));
	if (result) {
		result->elements = NULL;
		result->count = 0;
		result->found = 0;
	}
	return result;
}
void freeSubsetResult(struct SubsetResult* result) {
	if (result) {
		if (result->elements) {
			free(result->elements);
		}
		free(result);
	}
}
int findSubsetRecursive(unsigned int B, int* sizes, int N, int index,
	unsigned int currentSum, int* selected, int* selectedCount,
	int* solution, int* solutionCount) {
	if (currentSum == B) {
		*solutionCount = *selectedCount;
		for (int i = 0; i < *selectedCount; i++) {
			solution[i] = selected[i];
		}
		return 1;
	}
	if (currentSum > B || index >= N) {
		return 0;
	}
	selected[*selectedCount] = sizes[index];
	(*selectedCount)++;
	if (findSubsetRecursive(B, sizes, N, index + 1,
		currentSum + sizes[index],
		selected, selectedCount,
		solution, solutionCount)) {
		return 1;
	}
	(*selectedCount)--;
	return findSubsetRecursive(B, sizes, N, index + 1,
		currentSum,
		selected, selectedCount,
		solution, solutionCount);
}
struct SubsetResult* findSubsetSum(unsigned int B, int N, int* sizes) {
	struct SubsetResult* result = createSubsetResult();
	if (!result) return NULL;
	if (N == 0) return result;
	int* selected = (int*)malloc(N * sizeof(int));
	int* solution = (int*)malloc(N * sizeof(int));
	int selectedCount = 0;
	int solutionCount = 0;
	if (!selected || !solution) {
		free(selected);
		free(solution);
		freeSubsetResult(result);
		return NULL;
	}
	if (findSubsetRecursive(B, sizes, N, 0, 0,
		selected, &selectedCount,
		solution, &solutionCount)) {
		result->found = 1;
		result->count = solutionCount;
		result->elements = (int*)malloc(solutionCount * sizeof(int));
		if (result->elements) {
			for (int i = 0; i < solutionCount; i++) {
				result->elements[i] = solution[i];
			}
		}
	}
	free(selected);
	free(solution);
	return result;
}
void saveResultToFile(struct SubsetResult* result, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) return;
	if (result->found) {
		for (int i = 0; i < result->count; i++) {
			fprintf(file, "%d", result->elements[i]);
			if (i < result->count - 1) fprintf(file, " ");
		}
	}
	else {
		fprintf(file, "0");
	}
	fclose(file);
}
struct SubsetResult* readAndSolve(const char* inputFilename) {
	FILE* file = fopen(inputFilename, "r");
	if (!file) return NULL;
	unsigned int B;
	int N;
	if (fscanf(file, "%u", &B) != 1) {
		fclose(file);
		return NULL;
	}
	if (fscanf(file, "%d", &N) != 1) {
		fclose(file);
		return NULL;
	}
	int* sizes = (int*)malloc(N * sizeof(int));
	if (!sizes) {
		fclose(file);
		return NULL;
	}
	for (int i = 0; i < N; i++) {
		if (fscanf(file, "%d", &sizes[i]) != 1) {
			free(sizes);
			fclose(file);
			return NULL;
		}
	}
	fclose(file);
	struct SubsetResult* result = findSubsetSum(B, N, sizes);
	free(sizes);
	return result;
}