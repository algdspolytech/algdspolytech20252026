#include <locale.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"
//#include <gtest/gtest.h>

#pragma warning(disable : 4996)

#define x 10
#define y 10

void FindStart(int A[x][y], int* sx, int* sy, int* ex, int* ey) {

	*sx = -1;
	*sy = -1;
	*ex = -1;
	*ey = -1;

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (A[i][j] == -1) { *sx = i; *sy = j; }
			else if (A[i][j] == -2) { *ex = i; *ey = j; }
		}
	}

}

void Print(int A[x][y]) {
	for (int i = 0; i < x; i++) {
		printf("\n");
		for (int j = 0; j < y; j++) {
			printf("%d\t", A[i][j]);
		}
	}
}

void PrintChar(char A[x][y]) {
	for (int i = 0; i < x; i++) {
		printf("\n");
		for (int j = 0; j < y; j++) {
			printf("%c\t", A[i][j]);
		}
	}
}



//void Upgrade(float A[x][y], int* sx, int* sy, int nx, int ny);

void FindWay(int A[x][y], int sx, int sy) {

	if (sx + 1 < x && A[sx + 1][sy] == -2) { A[sx + 1][sy] = A[sx][sy] + 1; return; }
	if (sx - 1 >= 0 && A[sx - 1][sy] == -2) { A[sx - 1][sy] = A[sx][sy] + 1; return; }
	if (sy + 1 < y && A[sx][sy + 1] == -2) { A[sx][sy + 1] = A[sx][sy] + 1; return; }
	if (sy - 1 >= 0 && A[sx][sy - 1] == -2) { A[sx][sy - 1] = A[sx][sy] + 1; return; }



	if (sx + 1 < x && (A[sx + 1][sy] == 1 || A[sx + 1][sy] > A[sx][sy] + 1)) {
		A[sx + 1][sy] = A[sx][sy] + 1;
		FindWay(A, sx + 1, sy);
	}
	if (sx - 1 >= 0 && (A[sx - 1][sy] == 1 || A[sx - 1][sy] > A[sx][sy] + 1)) {
		A[sx - 1][sy] = A[sx][sy] + 1;
		FindWay(A, sx - 1, sy);
	}
	if (sy + 1 < y && (A[sx][sy + 1] == 1 || A[sx][sy + 1] > A[sx][sy] + 1)) {
		A[sx][sy + 1] = A[sx][sy] + 1;
		FindWay(A, sx, sy + 1);
	}
	if (sy - 1 >= 0 && (A[sx][sy - 1] == 1 || A[sx][sy - 1] > A[sx][sy] + 1)) {
		A[sx][sy - 1] = A[sx][sy] + 1;
		FindWay(A, sx, sy - 1);
	}
}


void Way(int A[x][y], int ex, int ey, int c, char B[x][y]) {
	if (ex - 1 >= 0 && A[ex - 1][ey] == c - 1 && c - 1 != 0) { B[ex - 1][ey] = '1'; Way(A, ex - 1, ey, c - 1, B); }
	if (ex + 1 < x && A[ex + 1][ey] == c - 1 && c - 1 != 0) { B[ex + 1][ey] = '1'; Way(A, ex + 1, ey, c - 1, B); }
	if (ey - 1 >= 0 && A[ex][ey - 1] == c - 1 && c - 1 != 0) { B[ex][ey - 1] = '1'; Way(A, ex, ey - 1, c - 1, B); }
	if (ey + 1 < y && A[ex][ey + 1] == c - 1 && c - 1 != 0) { B[ex][ey + 1] = '1'; Way(A, ex, ey + 1, c - 1, B); }

}


void FullArr(char A[x][y], char c) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) { A[i][j] = c; }
	}
}



#ifndef RUN_TESTS
int main() {
	setlocale(LC_CTYPE, "Russian");

	int A[x][y] = { {-1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
					{0, 1, 0, 1, 1, 1, 1, 1, 1, 0},
					{0, 1, 1, 1, 0, 0, 0, 0, 1, 0},
					{0, 0, 0, 1, 0, 1, 1, 1, 1, 0},
					{0, 1, 1, 1, 0, 1, 0, 0, 0, 0},
					{0, 1, 0, 1, 0, 1, 0, 1, 1, 0},
					{0, 1, 0, 1, 0, 0, 0, 0, 1, 0},
					{0, 1, 0, 1, 1, 1, 1, 0, 1, 0},
					{0, 1, 1, 1, 1, 0, 1, 1, 1, 1},
					{0, 0, 0, 0, 0, 0, 0, 0, 0, -2}
	};

	int sx = -1, sy, ex = -1, ey;
	FindStart(A, &sx, &sy, &ex, &ey);

	if (sx == -1) { printf("Старта нет"); }
	else if (ex == -1) { printf("Выхода нет"); }
	else {
		char B[x][y];
		FullArr(B, '#');
		printf("Исходный лабиринт: ");
		Print(A);

		A[sx][sy] = 1;
		FindWay(A, sx, sy);
		A[sx][sy] = 1;

		printf("\n Новый лабиринт:");
		Print(A);

		B[ex][ey] = '1';
		Way(A, ex, ey, A[ex][ey], B);
		printf("\n Кротчайший путь: ");
		PrintChar(B);
	}
}
#endif