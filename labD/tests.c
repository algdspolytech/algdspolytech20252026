#include "ruckzack.h"
#include <stdio.h>

static void assert_int(int a, int b) {
    printf("%s\n", a == b ? "PASS" : "FAIL");
}

void solve_ruckzack_EmptySet_returnFalse_no1() {
    int w[1] = { 1 };
    int v[1] = { 1 };
    int r[10];
    int c = 0;
    solve_ruckzack(0, 5, 1, w, v, r, &c);
    assert_int(c, 0);
}

void solve_ruckzack_OneItemFits_returnValidVal_no2() {
    int w[1] = { 1 };
    int v[1] = { 5 };
    int r[10];
    int c = 0;
    solve_ruckzack(1, 1, 5, w, v, r, &c);
    assert_int(c, 1);
    assert_int(r[0], 1);
}

void solve_ruckzack_OneItemTooHeavy_returnFalse_no3() {
    int w[1] = { 5 };
    int v[1] = { 10 };
    int r[10];
    int c = 0;
    solve_ruckzack(1, 3, 10, w, v, r, &c);
    assert_int(c, 0);
}

void solve_ruckzack_AllItemsFitExact_returnValidVal_no4() {
    int w[3] = { 1, 1, 1 };
    int v[3] = { 1, 1, 1 };
    int r[10];
    int c = 0;
    solve_ruckzack(3, 3, 3, w, v, r, &c);
    assert_int(c, 3);
    assert_int(r[0], 3);
    assert_int(r[1], 2);
    assert_int(r[2], 1);
}

void solve_ruckzack_ThreeEqualItemsTakeOne_returnValidVal_no5() {
    int w[3] = { 3, 3, 3 };
    int v[3] = { 5, 5, 5 };
    int r[10];
    int c = 0;
    solve_ruckzack(3, 3, 5, w, v, r, &c);
    assert_int(c, 1);
    assert_int(r[0], 1);
}

void solve_ruckzack_TwoItemsTakeOne_returnValidVal_no6() {
    int w[2] = { 2, 2 };
    int v[2] = { 3, 3 };
    int r[10];
    int c = 0;
    solve_ruckzack(2, 3, 3, w, v, r, &c);
    assert_int(c, 1);
    assert_int(r[0], 1);
}

void solve_ruckzack_BestValueUnderCapacity_returnValidVal_no7() {
    int w[3] = { 1, 2, 3 };
    int v[3] = { 3, 4, 8 };
    int r[10];
    int c = 0;
    solve_ruckzack(3, 3, 7, w, v, r, &c);
    assert_int(c, 1);
    assert_int(r[0], 3);
}

void solve_ruckzack_OnlyBigItemFits_returnValidVal_no8() {
    int w[3] = { 1, 10, 10 };
    int v[3] = { 1, 20, 20 };
    int r[10];
    int c = 0;
    solve_ruckzack(3, 10, 20, w, v, r, &c);
    assert_int(c, 1);
    assert_int(r[0], 2);
}

void solve_ruckzack_OnlySmallItemsPossible_returnValidVal_no9() {
    int w[3] = { 1, 1, 10 };
    int v[3] = { 1, 1, 50 };
    int r[10];
    int c = 0;
    solve_ruckzack(3, 2, 1, w, v, r, &c);
    assert_int(c, 2);
    assert_int(r[0], 2);
    assert_int(r[1], 1);
}

void solve_ruckzack_LargeValueSingleItem_returnValidVal_no10() {
    int w[3] = { 2, 2, 2 };
    int v[3] = { 1, 1, 100 };
    int r[10];
    int c = 0;
    solve_ruckzack(3, 2, 100, w, v, r, &c);
    assert_int(c, 1);
    assert_int(r[0], 3);
}

int main() {
    solve_ruckzack_EmptySet_returnFalse_no1();
    solve_ruckzack_OneItemFits_returnValidVal_no2();
    solve_ruckzack_OneItemTooHeavy_returnFalse_no3();
    solve_ruckzack_AllItemsFitExact_returnValidVal_no4();
    solve_ruckzack_ThreeEqualItemsTakeOne_returnValidVal_no5();
    solve_ruckzack_TwoItemsTakeOne_returnValidVal_no6();
    solve_ruckzack_BestValueUnderCapacity_returnValidVal_no7();
    solve_ruckzack_OnlyBigItemFits_returnValidVal_no8();
    solve_ruckzack_OnlySmallItemsPossible_returnValidVal_no9();
    solve_ruckzack_LargeValueSingleItem_returnValidVal_no10();
    return 0;
}