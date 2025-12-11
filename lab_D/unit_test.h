#pragma once
#define UNIT_TESTS_H

#include <stdbool.h>

bool run_test(const char* input_content, const char* expected_output);

void test_NoDependencies_HappyPath_no1();
void test_NegativeCosts_SuccessfulSchedule_no2();
void test_LinearDependencies_ValidSchedule_no3();
void test_ExceedCostLimit_ShouldFail_no4();
void test_CyclicDependencies_ShouldFail_no5();
void test_MaxTasks_ValidSchedule_no6();
void test_ZeroCosts_ValidSchedule_no7();
void test_ComplexDependencies_ValidSchedule_no8();
void test_MaxKValue_ValidSchedule_no9();
void test_ImpossibleDependencies_ShouldFail_no10();
