#include "labD.h"
#include <assert.h>

void TestBacktrack_EmptyBackpack_NoItems_no1() {
    printf("Test 1: Empty backpack (no items)... ");

    BackpackData data = { 0, 10, 5, NULL, NULL };
    int current_set[10], best_set[10];
    int best_size = 0;
    unsigned long long max_value = 0;

    int result = backtrack(&data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value);

    assert(result == 0);
    printf("PASS\n");
}

void TestBacktrack_SingleItemFits_ShouldInclude_no2() {
    printf("Test 2: Single item that fits... ");

    unsigned int weights[] = { 5 };
    unsigned int values[] = { 10 };

    BackpackData data = { 1, 10, 5, weights, values };
    int current_set[10], best_set[10];
    int best_size = 0;
    unsigned long long max_value = 0;

    int result = backtrack(&data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value);

    assert(result == 1);
    assert(best_size == 1);
    assert(best_set[0] == 1);
    assert(max_value == 10);
    printf("PASS\n");
}

void TestBacktrack_SingleItemTooHeavy_ShouldReject_no3() {
    printf("Test 3: Single item too heavy... ");

    unsigned int weights[] = { 15 };
    unsigned int values[] = { 100 };

    BackpackData data = { 1, 10, 5, weights, values };
    int current_set[10], best_set[10];
    int best_size = 0;
    unsigned long long max_value = 0;

    int result = backtrack(&data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value);

    assert(result == 0);
    printf("PASS\n");
}

void TestBacktrack_MultipleItems_OptimalCombination_no4() {
    printf("Test 4: Multiple items - find optimal combination... ");

    unsigned int weights[] = { 2, 3, 4 };
    unsigned int values[] = { 3, 4, 5 };

    BackpackData data = { 3, 5, 7, weights, values };
    int current_set[10], best_set[10];
    int best_size = 0;
    unsigned long long max_value = 0;

    int result = backtrack(&data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value);

    assert(result == 1);
    assert(max_value >= 7);
    printf("PASS\n");
}

void TestBacktrack_ExactWeightLimit_ShouldAccept_no5() {
    printf("Test 5: Exact weight limit... ");

    unsigned int weights[] = { 10 };
    unsigned int values[] = { 10 };

    BackpackData data = { 1, 10, 5, weights, values };
    int current_set[10], best_set[10];
    int best_size = 0;
    unsigned long long max_value = 0;

    int result = backtrack(&data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value);

    assert(result == 1);
    assert(best_size == 1);
    printf("PASS\n");
}

void TestBacktrack_ValueThresholdNotReached_ShouldFail_no6() {
    printf("Test 6: Value threshold not reached... ");

    unsigned int weights[] = { 1, 1 };
    unsigned int values[] = { 2, 2 };

    BackpackData data = { 2, 10, 10, weights, values };
    int current_set[10], best_set[10];
    int best_size = 0;
    unsigned long long max_value = 0;

    int result = backtrack(&data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value);

    assert(result == 0);
    printf("PASS\n");
}

void TestBacktrack_AllItemsIncluded_HappyPath_no7() {
    printf("Test 7: All items included successfully... ");

    unsigned int weights[] = { 1, 1, 1 };
    unsigned int values[] = { 5, 5, 5 };

    BackpackData data = { 3, 5, 15, weights, values };
    int current_set[10], best_set[10];
    int best_size = 0;
    unsigned long long max_value = 0;

    int result = backtrack(&data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value);

    assert(result == 1);
    assert(best_size == 3);
    assert(max_value == 15);
    printf("PASS\n");
}

void TestBacktrack_PruningByWeight_ShouldStopEarly_no8() {
    printf("Test 8: Pruning by weight limit... ");

    unsigned int weights[] = { 10, 1 };
    unsigned int values[] = { 1, 100 };

    BackpackData data = { 2, 5, 50, weights, values };
    int current_set[10], best_set[10];
    int best_size = 0;
    unsigned long long max_value = 0;

    int result = backtrack(&data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value);

    assert(result == 1);
    printf("PASS\n");
}

void TestBacktrack_ZeroCapacity_ShouldRejectAll_no9() {
    printf("Test 9: Zero capacity backpack... ");

    unsigned int weights[] = { 1, 2 };
    unsigned int values[] = { 100, 200 };

    BackpackData data = { 2, 0, 1, weights, values };
    int current_set[10], best_set[10];
    int best_size = 0;
    unsigned long long max_value = 0;

    int result = backtrack(&data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value);

    assert(result == 0);
    printf("PASS\n");
}

void TestBacktrack_ZeroValueThreshold_ShouldAlwaysSucceed_no10() {
    printf("Test 10: Zero value threshold... ");

    unsigned int weights[] = { 5 };
    unsigned int values[] = { 1 };

    BackpackData data = { 1, 10, 0, weights, values };
    int current_set[10], best_set[10];
    int best_size = 0;
    unsigned long long max_value = 0;

    int result = backtrack(&data, 0, 0, 0, current_set, 0, best_set, &best_size,
        &max_value);

    assert(result == 1);
    printf("PASS\n");
}
