#include "labD.h"

int backtrack(BackpackData* data, int index, unsigned long long current_weight,
    unsigned long long current_value, int* current_set,
    int current_size, int* best_set, int* best_size,
    unsigned long long* max_value) {

    if (current_weight > data->B) {
        return 0;
    }

    if (current_value >= data->K) {
        for (int i = 0; i < current_size; i++) {
            best_set[i] = current_set[i];
        }
        *best_size = current_size;
        *max_value = current_value;
        return 1;
    }

    if (index >= data->n) {
        return 0;
    }

    unsigned long long remaining_value = 0;
    for (int i = index; i < data->n; i++) {
        remaining_value += data->values[i];
    }
    if (current_value + remaining_value < data->K) {
        return 0;
    }

    current_set[current_size] = index + 1;
    if (backtrack(data, index + 1, current_weight + data->weights[index],
        current_value + data->values[index], current_set,
        current_size + 1, best_set, best_size, max_value)) {
        return 1;
    }

    if (backtrack(data, index + 1, current_weight, current_value, current_set,
        current_size, best_set, best_size, max_value)) {
        return 1;
    }

    return 0;
}
