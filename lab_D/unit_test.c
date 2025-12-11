#pragma once
#include "unit_test.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

bool run_test(const char* input_content, const char* expected_output) {
    FILE* input = fopen("input.txt", "w");
    if (!input)
        return false;
    fprintf(input, "%s", input_content);
    fclose(input);

    system("./lab-D.exe");

    FILE* output = fopen("output.txt", "r");
    if (!output) {
        remove("input.txt");
        return false;
    }

    char actual_output[10000];
    fgets(actual_output, sizeof(actual_output), output);
    fclose(output);

    size_t len = strlen(actual_output);
    if (len > 0 && actual_output[len - 1] == '\n') {
        actual_output[len - 1] = '\0';
    }

    bool result = (strcmp(actual_output, expected_output) == 0);

    remove("input.txt");
    remove("output.txt");

    return result;
}

void test_NoDependencies_HappyPath_no1() {
    printf("Test 1: No dependencies, happy path... ");
    const char* input = "3 10\n"
        "1 2 3\n"
        "0\n";
    const char* expected = "1 2 3";

    if (run_test(input, expected)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
}

void test_NegativeCosts_SuccessfulSchedule_no2() {
    printf("Test 2: Tasks with negative costs... ");
    const char* input = "4 5\n"
        "-1 -2 3 4\n"
        "0\n";
    const char* expected = "2 1 3 4";

    if (run_test(input, expected)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
}

void test_LinearDependencies_ValidSchedule_no3() {
    printf("Test 3: Linear dependencies... ");
    const char* input = "5 20\n"
        "5 3 7 2 4\n"
        "1 2\n"
        "2 3\n"
        "3 4\n"
        "4 5\n"
        "0\n";
    const char* expected = "1 2 3 4 5";

    if (run_test(input, expected)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
}

void test_ExceedCostLimit_ShouldFail_no4() {
    printf("Test 4: Exceeding cost limit... ");
    const char* input = "3 5\n"
        "3 4 2\n"
        "0\n";
    const char* expected = "0";

    if (run_test(input, expected)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
}

void test_CyclicDependencies_ShouldFail_no5() {
    printf("Test 5: Cyclic dependencies... ");
    const char* input = "3 10\n"
        "2 3 4\n"
        "1 2\n"
        "2 3\n"
        "3 1\n"
        "0\n";
    const char* expected = "0";

    if (run_test(input, expected)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
}

void test_MaxTasks_ValidSchedule_no6() {
    printf("Test 6: Maximum number of tasks (1000)... ");
    char input[100000];
    sprintf(input, "1000 1000000\n");

    for (int i = 0; i < 1000; i++) {
        char num[10];
        sprintf(num, "%d ", 1);
        strcat(input, num);
    }
    strcat(input, "\n0\n");

    char expected[5000];
    expected[0] = '\0';
    for (int i = 1; i <= 1000; i++) {
        char num[10];
        sprintf(num, "%d", i);
        strcat(expected, num);
        if (i < 1000)
            strcat(expected, " ");
    }

    if (run_test(input, expected)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
}

void test_ZeroCosts_ValidSchedule_no7() {
    printf("Test 7: Tasks with zero costs... ");
    const char* input = "4 0\n"
        "0 0 0 0\n"
        "1 2\n"
        "2 4\n"
        "3 4\n"
        "0\n";
    const char* expected = "1 2 3 4";

    if (run_test(input, expected)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
}

void test_ComplexDependencies_ValidSchedule_no8() {
    printf("Test 8: Complex dependency graph... ");
    const char* input = "6 15\n"
        "3 5 2 4 1 6\n"
        "1 4\n"
        "2 4\n"
        "3 5\n"
        "4 6\n"
        "5 6\n"
        "0\n";

    const char* expected = "3 5 1 2 4 6";

    if (run_test(input, expected)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
}

void test_MaxKValue_ValidSchedule_no9() {
    printf("Test 9: Maximum K value... ");
    const char* input = "3 4294967295\n"
        "1000000000 2000000000 3000000000\n"
        "0\n";
    const char* expected = "1 2 3";

    if (run_test(input, expected)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
}

void test_ImpossibleDependencies_ShouldFail_no10() {
    printf("Test 10: Impossible dependencies... ");
    const char* input = "4 10\n"
        "1 2 3 4\n"
        "1 2\n"
        "2 3\n"
        "3 1\n"
        "0\n";
    const char* expected = "0";

    if (run_test(input, expected)) {
        printf("PASSED\n");
    }
    else {
        printf("FAILED\n");
    }
}

int main() {
    test_NoDependencies_HappyPath_no1();
    test_NegativeCosts_SuccessfulSchedule_no2();
    test_LinearDependencies_ValidSchedule_no3();
    test_ExceedCostLimit_ShouldFail_no4();
    test_CyclicDependencies_ShouldFail_no5();
    test_MaxTasks_ValidSchedule_no6();
    test_ZeroCosts_ValidSchedule_no7();
    test_ComplexDependencies_ValidSchedule_no8();
    test_MaxKValue_ValidSchedule_no9();
    test_ImpossibleDependencies_ShouldFail_no10();

    return 0;
}
