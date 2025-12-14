#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

long long read_input(const char* filename) {
    FILE* fin = fopen(filename, "r");
    if (!fin) {
        printf("error open %s\n", filename);
        exit(1);
    }

    long long N;
    if (fscanf_s(fin, "%lld", &N) != 1) {
        printf("error read\n");
        fclose(fin);
        exit(1);
    }
    fclose(fin);
    return N;
}

void write_output(const char* filename, long long* cols, long long N) {
    FILE* fout = fopen(filename, "w");
    if (!fout) {
        printf("error open %s\n", filename);
        exit(1);
    }

    for (long long i = 0; i < N; i++)
        fprintf(fout, "%lld %lld\n", i, cols[i] - 1);

    fclose(fout);
}

void generate_solution(long long* cols, long long N) {
    long long i, c = 0;

    if (N % 6 != 2 && N % 6 != 3) {
        for (i = 2; i <= N; i += 2) cols[c++] = i;
        for (i = 1; i <= N; i += 2) cols[c++] = i;
    }
    else if (N % 6 == 2) {
        for (i = 2; i <= N; i += 2) cols[c++] = i;
        for (i = 1; i <= N; i += 2) cols[c++] = i;

        long long tmp = cols[0]; cols[0] = cols[1]; cols[1] = tmp;

        if (N > 4) {
            long long idx5 = -1;
            for (i = 0; i < N; i++)
                if (cols[i] == 5) idx5 = i;
            if (idx5 != -1) {
                long long val = cols[idx5];
                for (long long j = idx5; j < N - 1; j++)
                    cols[j] = cols[j + 1];
                cols[N - 1] = val;
            }
        }
    }
    else if (N % 6 == 3) {
        for (i = 1; i <= N; i += 2) cols[c++] = i;
        for (i = 2; i <= N; i += 2) cols[c++] = i;

        long long tmp = cols[0]; cols[0] = cols[1]; cols[1] = tmp;

        long long idx2 = -1;
        for (i = 0; i < N; i++)
            if (cols[i] == 2) idx2 = i;
        if (idx2 != -1) {
            long long val = cols[idx2];
            for (long long j = idx2; j < N - 1; j++)
                cols[j] = cols[j + 1];
            cols[N - 1] = val;
        }
    }
}