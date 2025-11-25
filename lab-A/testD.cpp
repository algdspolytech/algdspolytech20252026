#include "pch.h"
#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "LabD.h"
}

TEST(FindSumTest, FindSum_SimpleCase_returnTrue) {
    int B = 5;
    int N = 3;
    int A[] = { 1, 2, 3 };
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    ASSERT_NE(debug_result, nullptr);
    EXPECT_EQ(CalculateSum(debug_result, debug_result_size), B);
    free(debug_result);
    fclose(output);
}

TEST(FindSumTest, FindSum_NoSolution_returnFalse) {
    int B = 10;
    int N = 3;
    int A[] = { 1, 2, 3 };
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    EXPECT_EQ(debug_result, nullptr);
    fclose(output);
}

TEST(FindSumTest, FindSum_ElementEqualsB_returnTrue) {
    int B = 7;
    int N = 4;
    int A[] = { 1, 7, 3, 5 };
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    ASSERT_NE(debug_result, nullptr);
    EXPECT_EQ(CalculateSum(debug_result, debug_result_size), B);
    free(debug_result);
    fclose(output);
}

TEST(FindSumTest, FindSum_MultipleSumEqualsB_returnTrue) {
    int B = 10;
    int N = 5;
    int A[] = { 1, 4, 2, 7, 3 };
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    ASSERT_NE(debug_result, nullptr);
    EXPECT_EQ(CalculateSum(debug_result, debug_result_size), B);
    free(debug_result);
    fclose(output);
}

TEST(FindSumTest, FindSum_AllElementsEqualsB_returnTrue) {
    int B = 15;
    int N = 5;
    int A[] = { 1, 2, 3, 4, 5 };
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    ASSERT_NE(debug_result, nullptr);
    EXPECT_EQ(CalculateSum(debug_result, debug_result_size), B);
    free(debug_result);
    fclose(output);
}

TEST(FindSumTest, FindSum_LargeNumbers_returnTrue) {
    int B = 1000000;
    int N = 3;
    int A[] = { 500000, 300000, 200000 };
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    ASSERT_NE(debug_result, nullptr);
    EXPECT_EQ(CalculateSum(debug_result, debug_result_size), B);
    free(debug_result);
    fclose(output);
}

TEST(FindSumTest, FindSum_DuplicateElements_returnTrue) {
    int B = 6;
    int N = 5;
    int A[] = { 1, 2, 2, 3, 4 };
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    ASSERT_NE(debug_result, nullptr);
    EXPECT_EQ(CalculateSum(debug_result, debug_result_size), B);
    free(debug_result);
    fclose(output);
}

TEST(FindSumTest, FindSum_EmptyA_returnFalse) {
    int B = 5;
    int N = 0;
    int* A = NULL;
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    EXPECT_EQ(debug_result, nullptr);
    fclose(output);
}

TEST(FindSumTest, FindSum_AWithZeros_returnTrue) {
    int B = 5;
    int N = 4;
    int A[] = { 0, 2, 3, 5 };
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    ASSERT_NE(debug_result, nullptr);
    EXPECT_EQ(CalculateSum(debug_result, debug_result_size), B);
    free(debug_result);
    fclose(output);
}

TEST(FindSumTest, FindSum_LargeN_returnTrue) {
    int B = 50;
    int N = 20;
    int A[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    if (debug_result != NULL) {
        EXPECT_EQ(CalculateSum(debug_result, debug_result_size), B);
        free(debug_result);
    }
    fclose(output);
}

TEST(FindSumTest, FindSum_AllElementsLargerB_returnTrue) {
    int B = 5;
    int N = 3;
    int A[] = { 6, 7, 8 };
    FILE* output = tmpfile();
    int* debug_result = NULL;
    int debug_result_size = 0;
    FindSum(B, N, A, output, &debug_result, &debug_result_size);
    EXPECT_EQ(debug_result, nullptr);
    fclose(output);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}