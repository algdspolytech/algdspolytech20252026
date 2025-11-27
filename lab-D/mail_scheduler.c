#define _CRT_SECURE_NO_WARNINGS
#include "mail_scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Компаратор для qsort
int compare_telegrams(const void* a, const void* b) {
    Telegram* ta = (Telegram*)a;
    Telegram* tb = (Telegram*)b;
    int deadline_a = ta->d + ta->l;
    int deadline_b = tb->d + tb->l;
    if (deadline_a < deadline_b) return -1;
    if (deadline_a > deadline_b) return 1;
    return 0; 
}

// Функция для чтения телеграмм из файла
int read_telegrams_from_file(const char* filename, Telegram* telegrams, int* K) {
    if (!filename || !telegrams || !K) {
        return -1;
    }

    FILE* file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    int T;
    if (fscanf(file, "%d %d", &T, K) != 2 || T < 0 || T > MAX_TELEGRAMS) {
        fclose(file);
        return -1;
    }

    for (int i = 0; i < T; i++) {
        if (fscanf(file, "%d %d %d", &telegrams[i].l, &telegrams[i].d, &telegrams[i].w) != 3) {
            fclose(file);
            return -1; 
        }
        telegrams[i].id = i + 1; 
    }

    fclose(file);
    return T;
}

// Функция для вычисления оптимальной последовательности
int calculate_optimal_schedule(Telegram* telegrams, int num_telegrams, int K, int* sorted_order) {
    if (!telegrams || !sorted_order || K < 0) {
        return -1;
    }

    Telegram temp_telegrams[MAX_TELEGRAMS];
    for (int i = 0; i < num_telegrams; i++) {
        temp_telegrams[i] = telegrams[i];
    }

    qsort(temp_telegrams, num_telegrams, sizeof(Telegram), compare_telegrams);

    int current_time = 0;
    int total_penalty = 0;

    for (int i = 0; i < num_telegrams; i++) {
        int start_time = current_time;
        int completion_time = start_time + temp_telegrams[i].l;
        int deadline = temp_telegrams[i].d + temp_telegrams[i].l;

        if (completion_time > deadline) {
            total_penalty += temp_telegrams[i].w * (completion_time - deadline);
        }

        current_time = completion_time;
        sorted_order[i] = temp_telegrams[i].id - 1;
    }

    if (total_penalty > K) {
        return -1;
    }

    return total_penalty;
}
// Функция для вывода результата в файл
int write_result_to_file(int* sorted_order, int schedule_size, const char* filename) {
    if (!filename) {
        return -1;
    }

    FILE* file = fopen(filename, "w");
    if (!file) {
        return -1;
    }

    if (schedule_size == -1) {
        fprintf(file, "0\n");
    }
    else {
        for (int i = 0; i < schedule_size; i++) {
            fprintf(file, "%d", sorted_order[i] + 1); // Выводим 1-based id
            if (i < schedule_size - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    return 0;
}