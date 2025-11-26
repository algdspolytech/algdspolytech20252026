#include <stdio.h>
#include <stdlib.h>
#include "wagon.h"

int main(void) {
    const char *inname = "input.txt";
    const char *outname = "output.txt";
    FILE *fin = fopen(inname, "r");
    if (!fin) {
        fprintf(stderr, "Cannot open %s\n", inname);
        return 1;
    }

    int W, D, K;
    if (fscanf(fin, "%d %d %d", &W, &D, &K) != 3) { fclose(fin); fprintf(stderr,"Bad header\n"); return 1; }
    if (W <= 0) { fclose(fin); FILE *fout=fopen(outname,"w"); fprintf(fout,"0\n"); fclose(fout); return 0; }

    int *times = (int*)malloc(sizeof(int)*W);
    for (int i = 0; i < W; ++i) {
        if (fscanf(fin, "%d", &times[i]) != 1) times[i]=0;
    }

    int N;
    if (fscanf(fin, "%d", &N) != 1) N = 0;
    int (*edges)[2] = NULL;
    if (N > 0) {
        edges = (int(*)[2])malloc(sizeof(int)*2*N);
        for (int i = 0; i < N; ++i) {
            int a,b;
            if (fscanf(fin, "%d %d", &a, &b) != 2) { a=b=0; }
            edges[i][0] = a;
            edges[i][1] = b;
        }
    }

    int *out_order = (int*)malloc(sizeof(int)*W);
    int out_len = 0;
    int res = solve_instance(W, times, D, K, edges ? edges : (const int(*)[2])0, N, out_order, &out_len);

    FILE *fout = fopen(outname, "w");
    if (!fout) { fprintf(stderr,"Cannot open %s for write\n", outname); return 2; }

    if (res == 0) {
        fprintf(fout, "0\n");
    } else {
        for (int i = 0; i < out_len; ++i) {
            if (i) fprintf(fout, " ");
            fprintf(fout, "%d", out_order[i]);
        }
        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);
    free(times);
    free(edges);
    free(out_order);
    return 0;
}
