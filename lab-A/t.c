#include <stdlib.h>
#include "t.h"

int find_schedule(int* tasks, int** matrix, int n) {
    if (n <= 0) return 0;
    for (int i = 0; i < n; i++) {
        tasks[i] = i + 1;
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
    return n;
}
