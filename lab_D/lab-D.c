#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXEDGES 500000

#pragma warning(disable : 4996)

int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        return 0;
    }

    int n;
    long long K;

    fscanf(input, "%d %lld", &n, &K);

    long long cost[MAXN];

    for (int i = 1; i <= n; i++) {
        fscanf(input, "%lld", &cost[i]);
    }

    int indeg[MAXN] = { 0 };

    int* g_from = (int*)malloc(MAXEDGES * sizeof(int));
    int* g_to = (int*)malloc(MAXEDGES * sizeof(int));

    if (g_from == NULL || g_to == NULL) {
        fprintf(output, "0");
        return 0;
    }

    int edges = 0;

    while (1) {
        int a;
        if (fscanf(input, "%d", &a) != 1) {
            break;
        }
        if (a == 0) {
            break;
        }
        int b;
        fscanf(input, "%d", &b);

        if (edges >= MAXEDGES) {
            fprintf(output, "0");
            free(g_from);
            free(g_to);
            return 0;
        }

        g_from[edges] = a;
        g_to[edges] = b;
        edges++;

        indeg[b]++;
    }

    int order[MAXN];
    int used[MAXN] = { 0 };
    int pos = 0;

    long long sum = 0;

    for (int step = 0; step < n; step++) {
        int best = -1;
        long long bestCost = 0;

        for (int i = 1; i <= n; i++) {
            if (!used[i] && indeg[i] == 0) {
                if (best == -1 || cost[i] < bestCost) {
                    best = i;
                    bestCost = cost[i];
                }
            }
        }

        if (best == -1) {
            fprintf(output, "0");
            free(g_from);
            free(g_to);
            return 0;
        }

        if (sum + cost[best] > K) {
            fprintf(output, "0");
            free(g_from);
            free(g_to);
            return 0;
        }

        used[best] = 1;
        sum += cost[best];
        order[pos++] = best;

        for (int e = 0; e < edges; e++) {
            if (g_from[e] == best) {
                indeg[g_to[e]]--;
            }
        }
    }

    for (int i = 0; i < pos; i++) {
        fprintf(output, "%d", order[i]);
        if (i + 1 < pos) {
            fprintf(output, " ");
        }
    }

    free(g_from);
    free(g_to);
    fclose(input);
    fclose(output);
    return 0;
}