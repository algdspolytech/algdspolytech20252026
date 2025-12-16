#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

void print_subset(int subset[], int subset_size, int target_sum) {
    printf("Найдено подмножество с суммой %d: ", target_sum);
    for (int i = 0; i < subset_size; i++) {
        printf("%d ", subset[i]);
    }
    printf("\n");
}

void subset_sum_backtrack_all(int arr[], int subset[], int n, int target_sum, int index, int current_sum, int subset_size) {
    if (current_sum == target_sum) {
        print_subset(subset, subset_size, target_sum);
        return;
    }

    if (index >= n || current_sum > target_sum) {
        return;
    }

    subset[subset_size] = arr[index];
    subset_sum_backtrack_all(arr, subset, n, target_sum, index + 1, current_sum + arr[index], subset_size + 1);

    subset_sum_backtrack_all(arr, subset, n, target_sum, index + 1, current_sum, subset_size);
}