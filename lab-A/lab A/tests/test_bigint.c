#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/bigint.h"

static int check_eq(const char *expected, char *got, const char *name) {
    if (!got) {
        printf("❌ %s: got NULL, expected %s\n", name, expected);
        return 0;
    }
    if (strcmp(expected, got) == 0) {
        printf("✅ %s: OK\n", name);
        free(got);
        return 1;
    } else {
        printf("❌ %s: expected %s, got %s\n", name, expected, got);
        free(got);
        return 0;
    }
}

int main() {
    int ok = 0, total = 0;
    total++; ok += check_eq("0", bigint_add("0","0"), "TestAdd_Zero_no1");
    total++; ok += check_eq("1000", bigint_add("999","1"), "TestAdd_Carry_no2");
    total++; ok += check_eq("579", bigint_add("123","456"), "TestAdd_Small_no3");
    total++; ok += check_eq("111111111011111111100", bigint_add("12345678901234567890","98765432109876543210"), "TestAdd_Large_no4");
    total++; ok += check_eq("5", bigint_add("2","3"), "TestAdd_Simple_no5");

    total++; ok += check_eq("0", bigint_mul("0","123456"), "TestMul_Zero_no6");
    total++; ok += check_eq("144", bigint_mul("12","12"), "TestMul_Small_no7");
    total++; ok += check_eq("121932631112635269", bigint_mul("123456789","987654321"), "TestMul_Medium_no8");
    total++; ok += check_eq("56088", bigint_mul("123","456"), "TestMul_Simple_no9");
    total++; ok += check_eq("90000000000000000000", bigint_mul("30000000000","3000000000"), "TestMul_Big_no10");

    total++; ok += check_eq("1024", bigint_pow("2",10), "TestPow_2_10_no11");
    total++; ok += check_eq("1", bigint_pow("7",0), "TestPow_ZeroExp_no12");
    total++; ok += check_eq("248832", bigint_pow("12",5), "TestPow_12_5_no13");

    printf("\nSummary: %d/%d tests passed\n", ok, total);
    return (ok==total) ? 0 : 1;
}
