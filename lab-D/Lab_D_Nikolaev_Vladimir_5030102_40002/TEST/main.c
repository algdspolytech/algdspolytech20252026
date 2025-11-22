#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable: 4996)

void Read_From_File(FILE* file, int T, int* size_of_operation_new, int** connect_new, int* in_degree_new, int* cnt_new) {
	for (int x = 0; x < T; x++) {
		fscanf(file, "%d ", &size_of_operation_new[x]);
		connect_new[x] = malloc(sizeof(int));
		connect_new[x][0] = -1;
		cnt_new[x] = 0;
		in_degree_new[x] = 0;
	}
	int con1;
	int con2;
	while (fscanf(file, "%d %d\n", &con1, &con2) != EOF && con1 != 0) {
		connect_new[con1 - 1] = realloc(connect_new[con1 - 1], sizeof(int) * (cnt_new[con1 - 1] + 1));
		connect_new[con1 - 1][cnt_new[con1 - 1]] = con2 - 1;
		in_degree_new[con2 - 1] += 1;
		cnt_new[con1 - 1] += 1;
	}
	fclose(file);
}

bool MinMaxRates2(int summ, int step, int** connect, int* size_of_operation, int* cnt, int* in_degree, int T, int K, int* seq) {
	int ind = -1;
	int size = RAND_MAX;
	if (step == T) {
		return true;
	}
	for (int x = 0; x < T; x++) {
		if (size_of_operation[x] < size && in_degree[x] == 0 && size_of_operation[x] + summ <= K) {
			in_degree[x]--;
			seq[step] = x;
			for (int y = 0; y < cnt[x]; y++) {
				in_degree[connect[x][y]]--;
			}
			if (MinMaxRates2(summ + size_of_operation[x], step + 1, connect, size_of_operation, cnt, in_degree, T, K, seq)) {
				return true;
			}
			in_degree[x]++;
			for (int y = 0; y < cnt[x]; y++) {
				in_degree[connect[x][y]]++;
			}
		}
	}
	if (ind == -1) {
		return false;
	}
}

void Add_To_File(FILE* file, int* items, int T, bool flag) {
	if (flag) {
		for (int x = 0; x < T; x++) {
			fprintf(file, "%d ", items[x] + 1);
		}
	}
	else {
		fprintf(file, "%d", 0);
	}
}

void Full_Rates(FILE* file, FILE* file_in) {
	int T;
	int K;
	fscanf(file, "%d %d\n", &T, &K);
	int summ = 0;
	int step = 0;
	int* size_of_operation = malloc(sizeof(int) * T);
	int* in_degree = malloc(sizeof(int) * T);
	int** connect = malloc(sizeof(int*) * T);
	int* cnt = malloc(sizeof(int) * T);
	Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);
	int* seq = malloc(sizeof(int) * T);
	bool g = MinMaxRates2(summ, step, connect, size_of_operation, cnt, in_degree, T, K, seq);
	Add_To_File(file_in, seq, T, g);
}
