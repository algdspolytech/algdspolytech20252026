#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <locale.h>
#pragma warning(disable: 4996)

#define MAX_T 1000

typedef struct {
    int l;
    int d;
    int w;
    int index;
} Telegram;

Telegram telegrams[MAX_T];
int used[MAX_T] = { 0 };
int order[MAX_T];
int best_order[MAX_T];
int found = 0;
int T;
uint64_t K;
uint64_t min_penalty = UINT64_MAX;

uint64_t calculate_penalty(int* seq) {
    uint64_t total_penalty = 0;
    int time = 0;

    for (int i = 0; i < T; i++) {
        int idx = seq[i];
        int finish_time = time + telegrams[idx].l;
        int delay = finish_time - telegrams[idx].d;

        if (delay > 0) {
            total_penalty += (uint64_t)delay * telegrams[idx].w;
        }
        time = finish_time;
    }

    return total_penalty;
}

void backtrack(int depth, uint64_t current_penalty, int current_time) {
    if (found || current_penalty > K) {
        return;
    }

    if (depth == T) {
        if (current_penalty <= K) {
            found = 1;
            for (int i = 0; i < T; i++) {
                best_order[i] = order[i];
            }
        }
        return;
    }

    for (int i = 0; i < T; i++) {
        if (!used[i]) {
            used[i] = 1;
            order[depth] = i;

            int finish_time = current_time + telegrams[i].l;
            int delay = finish_time - telegrams[i].d;
            uint64_t penalty_add = 0;
            if (delay > 0) {
                penalty_add = (uint64_t)delay * telegrams[i].w;
            }

            backtrack(depth + 1, current_penalty + penalty_add, finish_time);

            used[i] = 0;

            if (found) {
                return;
            }
        }
    }
}

int main() {
    FILE* input = fopen("input10.txt", "r");
    FILE* output = fopen("output10.txt", "w");

    setlocale(LC_ALL, "Russian");

    if (!input || !output) {
        printf("Ошибка открытия файлов\n");
        return 1;
    }

    fscanf(input, "%d %llu", &T, &K);

    for (int i = 0; i < T; i++) {
        fscanf(input, "%d %d %d", &telegrams[i].l, &telegrams[i].d, &telegrams[i].w);
        telegrams[i].index = i + 1;
    }

    fclose(input);

    backtrack(0, 0, 0);

    if (found) {
        for (int i = 0; i < T; i++) {
            fprintf(output, "%d ", telegrams[best_order[i]].index);
        }
        fprintf(output, "\n");
    }
    else {
        fprintf(output, "0\n");
    }

    fclose(output);
    return 0;
}