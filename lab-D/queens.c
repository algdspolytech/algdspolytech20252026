#include "queens.h"

int Check(int* A, int N, int x, int y) {
    if (A[y] == -1) {
        for (int i = 0; i < N; i++) {
            if (A[i] == x) { return 0; }
            if (A[i] != -1 && abs(i - y) == abs(x - A[i])) { return 0; }
        }
        return 1;
    }
    else { return 0; }
}

int Queens(int* A, int N, int x, int y, int c) {
    A[y] = x;
    c += 1;
    if (c == N) { return 1; }

    for (int i = y + 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (Check(A, N, j, i) == 1) {
                if (Queens(A, N, j, i, c)) {
                    return 1;
                }
            }
        }
    }
    A[y] = -1;
    return 0;
}

void Print(int* A, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i] == j) { printf("1 "); }
            else { printf("0 "); }
        }
        printf("\n");
    }
}