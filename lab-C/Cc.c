#include <stdio.h>
#include "Ch.h"

#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable: 4996)

#define MAX 100

void Createqueue(queue* a) {
    a->back = -1;
    a->head = -1;
}

int isqueueempty(queue* a) {
    if (a->back == -1) {
        return 1;
    }
    return 0;
}

void Addinqueue(queue* a, point p) {
    if (a->head == -1) {
        a->head = 0;
    }
    a->back++;
    a->info[a->back] = p;
}

point Removefromqueue(queue* a) {
    point p;
    if (isqueueempty(a) == 1) {
        point perr = { -1, -1 };
        return perr;
    }
    else {
        p = a->info[a->head];
        a->head++;
        if (a->head > a->back) {
            a->head = -1;
            a->back = -1;
        }
        return p;
    }
}

int SheetSeparation(int m, int n, int matrix[MAX][MAX]) {
    int visited[MAX][MAX] = { 0 };
    int count = 0;
    queue a;
    Createqueue(&a);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && visited[i][j] == 0) {
                point p = { i, j };
                Addinqueue(&a, p);
                visited[i][j] = 1;
                while (isqueueempty(&a) == 0) {
                    point current = Removefromqueue(&a);
                    int i1 = current.x;
                    int j1 = current.y;
                    if (i1 - 1 >= 0) {
                        if (matrix[i1 - 1][j1] == 1 && visited[i1 - 1][j1] == 0) {
                            point pleft = { i1 - 1, j1 };
                            Addinqueue(&a, pleft);
                            visited[i1 - 1][j1] = 1;
                        }
                    }
                    if (j1 - 1 >= 0) {
                        if (matrix[i1][j1 - 1] == 1 && visited[i1][j1 - 1] == 0) {
                            point pdown = { i1 , j1 - 1 };
                            Addinqueue(&a, pdown);
                            visited[i1][j1 - 1] = 1;
                        }
                    }
                    if (i1 + 1 < m) {
                        if (matrix[i1 + 1][j1] == 1 && visited[i1 + 1][j1] == 0) {
                            point pright = { i1 + 1, j1 };
                            Addinqueue(&a, pright);
                            visited[i1 + 1][j1] = 1;
                        }
                    }
                    if (j1 + 1 < n) {
                        if (matrix[i1][j1 + 1] == 1 && visited[i1][j1 + 1] == 0) {
                            point pup = { i1 , j1 + 1 };
                            Addinqueue(&a, pup);
                            visited[i1][j1 + 1] = 1;
                        }
                    }
                }
                count++;
            }
        }
    }
    return count;
}
