#include "ruckzack.h"
#include <stdio.h>

static void assert_int(int a, int b) {
    printf("%s\n", a == b ? "PASS" : "FAIL");
}

void knapsack_solve_EmptyInput_returnZero_no1() {
    int w[1] = {1};
    int v[1] = {1};
    int r[10];
    int result = knapsack_solve(0, 5, 1, w, v, r);
    assert_int(result, 0);
}

void knapsack_solve_SingleItemFits_returnOne_no2() {
    int w[1] = {1};
    int v[1] = {5};
    int r[10];
    int result = knapsack_solve(1, 1, 5, w, v, r);
    assert_int(result, 1);
    assert_int(r[0], 1);
}

void knapsack_solve_SingleItemTooHeavy_returnZero_no3() {
    int w[1] = {5};
    int v[1] = {10};
    int r[10];
    int result = knapsack_solve(1, 3, 10, w, v, r);
    assert_int(result, 0);
}

void knapsack_solve_AllItemsFit_returnThree_no4() {
    int w[3] = {1, 1, 1};
    int v[3] = {1, 1, 1};
    int r[10];
    int result = knapsack_solve(3, 3, 3, w, v, r);
    assert_int(result, 3);
    assert_int(r[0], 3);
    assert_int(r[1], 2);
    assert_int(r[2], 1);
}

void knapsack_solve_ThreeEqualTakeOne_returnOne_no5() {
    int w[3] = {3, 3, 3};
    int v[3] = {5, 5, 5};
    int r[10];
    int result = knapsack_solve(3, 3, 5, w, v, r);
    assert_int(result, 1);
    assert_int(r[0], 1);
}

void knapsack_solve_TwoItemsTakeOne_returnOne_no6() {
    int w[2] = {2, 2};
    int v[2] = {3, 3};
    int r[10];
    int result = knapsack_solve(2, 3, 3, w, v, r);
    assert_int(result, 1);
    assert_int(r[0], 1);
}

void knapsack_solve_BestValueSelected_returnOne_no7() {
    int w[3] = {1, 2, 3};
    int v[3] = {3, 4, 8};
    int r[10];
    int result = knapsack_solve(3, 3, 7, w, v, r);
    assert_int(result, 1);
    assert_int(r[0], 3);
}

void knapsack_solve_OnlyBigItemFits_returnOne_no8() {
    int w[3] = {1, 10, 10};
    int v[3] = {1, 20, 20};
    int r[10];
    int result = knapsack_solve(3, 10, 20, w, v, r);
    assert_int(result, 1);
    assert_int(r[0], 2);
}

void knapsack_solve_OnlySmallItemsPossible_returnTwo_no9() {
    int w[3] = {1, 1, 10};
    int v[3] = {1, 1, 50};
    int r[10];
    int result = knapsack_solve(3, 2, 1, w, v, r);
    assert_int(result, 2);
    assert_int(r[0], 2);
    assert_int(r[1], 1);
}

void knapsack_solve_LargeValueItem_returnOne_no10() {
    int w[3] = {2, 2, 2};
    int v[3] = {1, 1, 100};
    int r[10];
    int result = knapsack_solve(3, 2, 100, w, v, r);
    assert_int(result, 1);
    assert_int(r[0], 3);
}

void test_runner() {
    knapsack_solve_EmptyInput_returnZero_no1();
    knapsack_solve_SingleItemFits_returnOne_no2();
    knapsack_solve_SingleItemTooHeavy_returnZero_no3();
    knapsack_solve_AllItemsFit_returnThree_no4();
    knapsack_solve_ThreeEqualTakeOne_returnOne_no5();
    knapsack_solve_TwoItemsTakeOne_returnOne_no6();
    knapsack_solve_BestValueSelected_returnOne_no7();
    knapsack_solve_OnlyBigItemFits_returnOne_no8();
    knapsack_solve_OnlySmallItemsPossible_returnTwo_no9();
    knapsack_solve_LargeValueItem_returnOne_no10();
}

int main() {
    test_runner();
    return 0;
}