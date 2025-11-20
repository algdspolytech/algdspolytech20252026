#include "labD.h"

int read_backpack_data(const char* filename, BackpackData* data) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    if (fscanf(file, "%u %llu %llu", &data->n, &data->B, &data->K) != 3) {
        fclose(file);
        return -1;
    }

    data->weights = (unsigned int*)malloc(data->n * sizeof(unsigned int));
    data->values = (unsigned int*)malloc(data->n * sizeof(unsigned int));

    if (data->weights == NULL || data->values == NULL) {
        fclose(file);
        free(data->weights);
        free(data->values);
        return -1;
    }

    for (unsigned int i = 0; i < data->n; i++) {
        if (fscanf(file, "%u", &data->weights[i]) != 1) {
            fclose(file);
            free(data->weights);
            free(data->values);
            return -1;
        }
    }

    for (unsigned int i = 0; i < data->n; i++) {
        if (fscanf(file, "%u", &data->values[i]) != 1) {
            fclose(file);
            free(data->weights);
            free(data->values);
            return -1;
        }
    }

    fclose(file);
    return 0;
}

void free_backpack_data(BackpackData* data) {
    if (data != NULL) {
        free(data->weights);
        free(data->values);
    }
}

void solve_backpack(BackpackData* data) {
    int* current_set = (int*)malloc(data->n * sizeof(int));
    int* best_set = (int*)malloc(data->n * sizeof(int));
    int best_size = 0;
    unsigned long long max_value = 0;

    FILE* output = fopen("output.txt", "w");

    if (backtrack(data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value)) {
        for (int i = 0; i < best_size; i++) {
            fprintf(output, "%d", best_set[i]);
            if (i < best_size - 1) {
                fprintf(output, " ");
            }
        }
    }
    else {
        fprintf(output, "0");
    }

    fclose(output);
    free(current_set);
    free(best_set);
}

int main() {
    BackpackData data;

    if (read_backpack_data("input.txt", &data) == 0) {
        solve_backpack(&data);
        free_backpack_data(&data);
    }
    else {
        FILE* output = fopen("output.txt", "w");
        fprintf(output, "0");
        fclose(output);
    }

    printf("Running backpack algorithm tests...\n\n");

    TestBacktrack_EmptyBackpack_NoItems_no1();
    TestBacktrack_SingleItemFits_ShouldInclude_no2();
    TestBacktrack_SingleItemTooHeavy_ShouldReject_no3();
    TestBacktrack_MultipleItems_OptimalCombination_no4();
    TestBacktrack_ExactWeightLimit_ShouldAccept_no5();
    TestBacktrack_ValueThresholdNotReached_ShouldFail_no6();
    TestBacktrack_AllItemsIncluded_HappyPath_no7();
    TestBacktrack_PruningByWeight_ShouldStopEarly_no8();
    TestBacktrack_ZeroCapacity_ShouldRejectAll_no9();
    TestBacktrack_ZeroValueThreshold_ShouldAlwaysSucceed_no10();

    printf("\nAll tests passed successfully!\n");

    return 0;
}
