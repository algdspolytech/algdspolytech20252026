#include "wagon.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    int t;
    int idx; /* 1-based */
} TimeIdx;

static int cmp_timeidx(const void *a, const void *b) {
    const TimeIdx *A = a;
    const TimeIdx *B = b;
    if (A->t != B->t) return (A->t < B->t) ? -1 : 1;
    return (A->idx < B->idx) ? -1 : 1;
}


int solve_instance(int W,
                   const int *times,
                   int D,
                   int K,
                   const int (*edges)[2],
                   int m_edges,
                   int *out_order,
                   int *out_len)
{
    if (W <= 0) {
        if (out_len) *out_len = 0;
        return 0;
    }
    if (K < 0) K = 0;
    if (K > W) K = W;

    int M = W - K;
    if (M <= 0) {
        if (out_len) *out_len = 0;
        return 0;
    }

    TimeIdx *arr = (TimeIdx*)malloc(sizeof(TimeIdx) * W);
    if (!arr) return 0;
    for (int i = 0; i < W; ++i) {
        arr[i].t = times[i];
        arr[i].idx = i + 1;
    }

    qsort(arr, W, sizeof(TimeIdx), cmp_timeidx);

    long long sum = 0;
    for (int i = 0; i < M; ++i) sum += arr[i].t;
    if (sum > D) {
        free(arr);
        if (out_len) *out_len = 0;
        return 0;
    }

    char *selected = (char*)calloc(W + 1, sizeof(char));
    if (!selected) { free(arr); return 0; }
    for (int i = 0; i < M; ++i) selected[arr[i].idx] = 1;

    int *indeg = (int*)calloc(W + 1, sizeof(int));
    int *adj_count = (int*)calloc(W + 1, sizeof(int));
    if (!indeg || !adj_count) { free(arr); free(selected); free(indeg); free(adj_count); return 0; }

    for (int e = 0; e < m_edges; ++e) {
        int u = edges[e][0];
        int v = edges[e][1];
        if (u < 1 || u > W || v < 1 || v > W) continue;
        if (selected[u] && selected[v]) {
            adj_count[u]++;
            indeg[v]++;
        }
    }

    int total_edges = 0;
    for (int i = 1; i <= W; ++i) total_edges += adj_count[i];
    int *adj_index = (int*)malloc(sizeof(int) * (W + 1));
    int *adj_list = (int*)malloc(sizeof(int) * (total_edges > 0 ? total_edges : 1));
    if (!adj_index || !adj_list) {
        free(arr); free(selected); free(indeg); free(adj_count); free(adj_index); free(adj_list);
        return 0;
    }
    adj_index[1] = 0;
    for (int i = 2; i <= W; ++i) adj_index[i] = adj_index[i-1] + adj_count[i-1];
    int *cursor = (int*)malloc(sizeof(int)*(W+1));
    if (!cursor) { free(arr); free(selected); free(indeg); free(adj_count); free(adj_index); free(adj_list); return 0;}
    for (int i = 1; i <= W; ++i) cursor[i] = adj_index[i];

    for (int e = 0; e < m_edges; ++e) {
        int u = edges[e][0];
        int v = edges[e][1];
        if (u < 1 || u > W || v < 1 || v > W) continue;
        if (selected[u] && selected[v]) {
            int pos = cursor[u]++;
            adj_list[pos] = v;
        }
    }

    int *queue = (int*)malloc(sizeof(int)*(M+5));
    int qh = 0, qt = 0;
    for (int i = 1; i <= W; ++i) {
        if (selected[i]) {
            if (indeg[i] == 0) queue[qt++] = i;
        }
    }

    int outpos = 0;
    while (qh < qt) {
        int v = queue[qh++];
        out_order[outpos++] = v;
        int start = adj_index[v];
        int end = (v == W) ? total_edges : adj_index[v] + adj_count[v];
        for (int p = start; p < end; ++p) {
            int to = adj_list[p];
            indeg[to]--;
            if (indeg[to] == 0) queue[qt++] = to;
        }
    }

        if (outpos != M) {
        free(arr); free(selected); free(indeg); free(adj_count); free(adj_index); free(adj_list); free(cursor); free(queue);
        if (out_len) *out_len = 0;
        return 0;
    }

    if (out_len) *out_len = outpos;

    free(arr); free(selected); free(indeg); free(adj_count); free(adj_index); free(adj_list); free(cursor); free(queue);

    return outpos;
}
