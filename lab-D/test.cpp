#include "func.h"

#include <gtest/gtest.h>
#include <string>
#include <cstring>
#include <iostream>

extern "C" {
}

TEST(calculatorTest, calculator_Addition_Valid_no1) {
    EXPECT_EQ(calculator(5, 3, '+'), 8);
}

TEST(calculatorTest, calculator_Subtraction_Valid_no2) {
    EXPECT_EQ(calculator(10, 4, '-'), 6);
}

TEST(calculatorTest, calculator_Multiplication_Valid_no3) {
    EXPECT_EQ(calculator(7, 6, '*'), 42);
}

TEST(calculatorTest, calculator_Division_Valid_no4) {
    EXPECT_EQ(calculator(20, 5, '/'), 4);
}

TEST(calculatorTest, calculator_DivisionByZero_Zero_no5) {
    EXPECT_EQ(calculator(10, 0, '/'), 0);
}

TEST(searchTest, search_SimpleAddition_Valid_no6) {
    char result[MAX_LENGTH];
    EXPECT_TRUE(search("123", 6, result));
    EXPECT_STREQ(result, "1+2+3");
}

TEST(searchTest, search_Multiplication_Valid_no7) {
    char result[MAX_LENGTH];
    EXPECT_TRUE(search("23", 6, result));
    EXPECT_STREQ(result, "2*3");
}

TEST(searchTest, search_ComplexExample_Valid_no8) {
    char result[MAX_LENGTH];
    long long target = 12 + 34 * 56 - 78 * 9;
    EXPECT_TRUE(search("123456789", target, result));
    EXPECT_TRUE(strlen(result) > 0);
}

TEST(searchTest, search_NoSolution_False_no9) {
    char result[MAX_LENGTH];
    EXPECT_FALSE(search("111", 1000, result));
}

TEST(searchTest, search_WithZeros_Valid_no10) {
    char result[MAX_LENGTH];
    EXPECT_TRUE(search("1001", 2, result));
    EXPECT_STREQ(result, "1+0+0+1");
}

TEST(searchTest, search_EmptyString_False_no11) {
    char result[MAX_LENGTH];
    EXPECT_FALSE(search("", 0, result));
}

TEST(searchTest, search_NullInput_False_no12) {
    char result[MAX_LENGTH];
    EXPECT_FALSE(search(NULL, 0, result));
}

TEST(searchTest, search_LargeNumber_Valid_no13) {
    char result[MAX_LENGTH];
    char largeNum[50];
    for (int i = 0; i < 49; i++) largeNum[i] = '1';
    largeNum[49] = '\0';

    EXPECT_TRUE(search(largeNum, 49, result));
    EXPECT_TRUE(strlen(result) > 0);
}

TEST(searchTest, search_NegativeTarget_Valid_no14) {
    char result[MAX_LENGTH];
    EXPECT_TRUE(search("1234", -8, result));
    EXPECT_TRUE(strlen(result) > 0);
}

TEST(searchTest, search_ZeroTarget_Valid_no15) {
    char result[MAX_LENGTH];
    EXPECT_TRUE(search("11", 0, result));
    EXPECT_TRUE(strlen(result) > 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}