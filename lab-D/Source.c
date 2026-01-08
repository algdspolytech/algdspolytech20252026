#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint32_t size;
    uint32_t value;
    int index;
} Item;

typedef struct {
    int* items;
    int count;
    uint32_t total_size;
    uint32_t total_value;
} Solution;


int read_input(const char* filename, Item** items, int* n, uint32_t* B, uint32_t* K) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Не удалось открыть input.txt");
        return 0;
    }


    if (fscanf_s(file, "%d %u %u", n, B, K) != 3) {
        fclose(file);
        return 0;
    }

    *items = (Item*)malloc(*n * sizeof(Item));
    if (!*items) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < *n; i++) {
        (*items)[i].index = i + 1;

        if (fscanf_s(file, "%u", &(*items)[i].size) != 1) {
            free(*items);
            fclose(file);
            return 0;
        }
    }

    for (int i = 0; i < *n; i++) {
        if (fscanf_s(file, "%u", &(*items)[i].value) != 1) {
            free(*items);
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}


void write_output(const char* filename, const Solution* sol) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Не удалось открыть output.txt");
        return;
    }

    if (sol->count == 0) {
        fprintf(file, "0\n");
    }
    else {
        for (int i = 0; i < sol->count; i++) {
            fprintf(file, "%d", sol->items[i]);
            if (i < sol->count - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


void find_subset(Item* items, int pos, int n, uint32_t B, uint32_t K,
    Solution* current, Solution* best) {

    if (current->total_value >= K && current->total_size <= B) {
        if (best->count == 0 || current->total_value > best->total_value ||
            (current->total_value == best->total_value && current->total_size < best->total_size)) {

            free(best->items);
            best->items = (int*)malloc(current->count * sizeof(int));
            best->count = current->count;
            best->total_size = current->total_size;
            best->total_value = current->total_value;
            for (int i = 0; i < current->count; i++) {
                best->items[i] = current->items[i];
            }
        }
    }


    if (pos >= n || current->total_size > B) {
        return;
    }


    find_subset(items, pos + 1, n, B, K, current, best);


    current->items[current->count] = items[pos].index;
    current->total_size += items[pos].size;
    current->total_value += items[pos].value;
    current->count++;

    find_subset(items, pos + 1, n, B, K, current, best);


    current->count--;
    current->total_size -= items[pos].size;
    current->total_value -= items[pos].value;
}


void solve_knapsack(Item* items, int n, uint32_t B, uint32_t K, Solution* solution) {
    Solution current = { 0 };
    Solution best = { 0 };

    current.items = (int*)malloc(n * sizeof(int));
    if (!current.items) {
        return;
    }

    find_subset(items, 0, n, B, K, &current, &best);

    if (best.count > 0 && best.total_value >= K && best.total_size <= B) {
        *solution = best;
        free(current.items);
    }
    else {
        free(current.items);
        free(best.items);
        solution->count = 0;
    }
}


void cleanup(Item* items, Solution* sol) {
    free(items);
    free(sol->items);
}

int main_orig() {
    Item* items = NULL;
    int n;
    uint32_t B, K;
    Solution solution = { 0 };

    if (!read_input("text.txt", &items, &n, &B, &K)) {
        fprintf(stderr, "Ошибка чтения входных данных\n");
        return 1;
    }

    solve_knapsack(items, n, B, K, &solution);

    write_output("output.txt", &solution);

    cleanup(items, &solution);



    items = NULL;
    Solution solution2 = { 0 };
    if (!read_input("text2.txt", &items, &n, &B, &K)) {
        fprintf(stderr, "Ошибка чтения входных данных222\n");
        return 1;
    }

    solve_knapsack(items, n, B, K, &solution2);

    write_output("output2.txt", &solution2);

    cleanup(items, &solution2);
    return 0;
}