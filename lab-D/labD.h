#pragma once
#ifndef Lab_h
#define Lab_h
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int n;
    unsigned long long B;
    unsigned long long K;
    unsigned int* weights;
    unsigned int* values;
} BackpackData;

int backtrack(BackpackData* data, int index, unsigned long long current_weight,
    unsigned long long current_value, int* current_set, int current_size,
    int* best_set, int* best_size, unsigned long long* max_value);

int read_backpack_data(const char* filename, BackpackData* data);

void free_backpack_data(BackpackData* data);

void solve_backpack(BackpackData* data);

#endif
