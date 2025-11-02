#include <gtest/gtest.h>

#pragma warning(disable: 4996)

#define _CRT_SECURE_NO_WARNINGS

extern "C" {
#include "Header.h"
}

TEST(Lab1_test, CreateNode_AnyDigit_returnNode) {
    int_t* a2 = Createnode(5);
    ASSERT_NE(a2, nullptr);
    EXPECT_EQ(a2->digit, 5);
    EXPECT_EQ(a2->next, nullptr);
    FreeList(a2);
}

TEST(Lab1_test, Bend_AnyDigit_returnLong) {
    int_t* a3 = Createnode(1);
    Bend(&a3, 2);
    ASSERT_NE(a3, nullptr);
    EXPECT_EQ(a3->digit, 2);
    ASSERT_NE(a3->next, nullptr);
    EXPECT_EQ(a3->next->digit, 1);
    EXPECT_EQ(a3->next->next, nullptr);
    FreeList(a3);
}

TEST(Lab1_test, Mul10x_LongInt_returnLong) {
    int_t* a4 = Createnode(2);
    Bend(&a4, 5);

    Mul10x(&a4, 1);

    EXPECT_EQ(a4->digit, 0);
    ASSERT_NE(a4->next, nullptr);
    EXPECT_EQ(a4->next->digit, 5);
    ASSERT_NE(a4->next->next, nullptr);
    EXPECT_EQ(a4->next->next->digit, 2);
    EXPECT_EQ(a4->next->next->next, nullptr);
    FreeList(a4);
}

TEST(Lab1_test, Mul10x_LongZero_returnSameLong) {
    int_t* a5 = Createnode(2);
    Bend(&a5, 5);

    Mul10x(&a5, 0);

    ASSERT_NE(a5, nullptr);
    EXPECT_EQ(a5->digit, 5);
    ASSERT_NE(a5->next, nullptr);
    EXPECT_EQ(a5->next->digit, 2);
    EXPECT_EQ(a5->next->next, nullptr);
    FreeList(a5);
}

TEST(Lab1_test, Mul10x_ZeroInt_returnZero) {
    int_t* a6 = Createnode(0);

    Mul10x(&a6, 4);
    ASSERT_NE(a6, nullptr);
    EXPECT_EQ(a6->digit, 0);
    int_t* current = a6;
    int zero_count = 0;
    while (current != nullptr) {
        EXPECT_EQ(current->digit, 0);
        zero_count++;
        current = current->next;
    }
    EXPECT_EQ(zero_count, 5);
    FreeList(a6);
}

TEST(Lab1_test, StrLen_AnyStr_returnInt) {
    EXPECT_EQ(StrLen(""), 0);
    EXPECT_EQ(StrLen("a"), 1);
    EXPECT_EQ(StrLen("string"), 6);
    EXPECT_EQ(StrLen("vicinity of obscenity"), 21);
}

TEST(Lab1_test, FreeList_AnyLong_returnNull) {
    int_t* a7 = Createnode(3);
    Bend(&a7, 7);

    FreeList(a7);
    SUCCEED();
}

TEST(Lab1_test, Add_AnyDigitDigit_returnLong) {
    int_t* a = Createnode(3);
    ASSERT_NE(a, nullptr);

    int_t* b = Createnode(4);
    ASSERT_NE(b, nullptr);

    int_t* c = Add(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 7);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

TEST(Lab1_test, Add_ThroughDigit_returnLong) {
    int_t* a = Createnode(7);
    ASSERT_NE(a, nullptr);

    int_t* b = Createnode(8);
    ASSERT_NE(b, nullptr);

    int_t* c = Add(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 5);
    ASSERT_NE(c->next, nullptr);
    EXPECT_EQ(c->next->digit, 1);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

TEST(Lab1_test, Add_MultipleDigit_returnLong) {
    int_t* a = Createnode(1);
    ASSERT_NE(a, nullptr);
    Bend(&a, 5);

    int_t* b = Createnode(3);
    ASSERT_NE(b, nullptr);
    Bend(&b, 9);

    int_t* c = Add(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 4);
    ASSERT_NE(c->next, nullptr);
    EXPECT_EQ(c->next->digit, 5);
    EXPECT_EQ(c->next->next, nullptr);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

TEST(Lab1_test, Add_Zero_returnLong) {
    int_t* a = Createnode(1);
    ASSERT_NE(a, nullptr);
    Bend(&a, 5);

    int_t* b = Createnode(0);
    ASSERT_NE(b, nullptr);

    int_t* c = Add(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 5);
    ASSERT_NE(c->next, nullptr);
    EXPECT_EQ(c->next->digit, 1);
    EXPECT_EQ(c->next->next, nullptr);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

TEST(Lab1_test, Mul_AnyDigitDigit_returnLong) {
    int_t* a = Createnode(3);
    ASSERT_NE(a, nullptr);

    int_t* b = Createnode(4);
    ASSERT_NE(b, nullptr);

    int_t* c = Mul(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 2);
    ASSERT_NE(c->next, nullptr);
    EXPECT_EQ(c->next->digit, 1);
    EXPECT_EQ(c->next->next, nullptr);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

TEST(Lab1_test, Mul_AnyNumOne_returnNum) {
    int_t* a = Createnode(1);
    Bend(&a, 2);
    ASSERT_NE(a, nullptr);

    int_t* b = Createnode(1);
    ASSERT_NE(b, nullptr);

    int_t* c = Mul(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 2);
    ASSERT_NE(c->next, nullptr);
    EXPECT_EQ(c->next->digit, 1);
    EXPECT_EQ(c->next->next, nullptr);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

TEST(Lab1_test, Mul_Zero_returnZero) {
    int_t* a = Createnode(8);
    ASSERT_NE(a, nullptr);

    int_t* b = Createnode(0);
    ASSERT_NE(b, nullptr);

    int_t* c = Mul(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 0);
    EXPECT_EQ(c->next, nullptr);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

TEST(Lab1_test, Mul_MultipleDigit_returnLong) {
    int_t* a = Createnode(1);
    Bend(&a, 8);
    ASSERT_NE(a, nullptr);

    int_t* b = Createnode(2);
    Bend(&b, 7);
    ASSERT_NE(b, nullptr);

    int_t* c = Mul(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 6);
    ASSERT_NE(c->next, nullptr);
    EXPECT_EQ(c->next->digit, 8);
    ASSERT_NE(c->next->next, nullptr);
    EXPECT_EQ(c->next->next->digit, 4);
    EXPECT_EQ(c->next->next->next, nullptr);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

TEST(Lab1_test, Poww_AnyDigitDigit_returnLong) {
    int_t* a = Createnode(2);
    ASSERT_NE(a, nullptr);

    int_t* b = Createnode(4);
    ASSERT_NE(b, nullptr);

    int_t* c = Poww(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 6);
    ASSERT_NE(c->next, nullptr);
    EXPECT_EQ(c->next->digit, 1);
    EXPECT_EQ(c->next->next, nullptr);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

TEST(Lab1_test, Poww_AnyDigitZero_returnOne) {
    int_t* a = Createnode(5);
    ASSERT_NE(a, nullptr);

    int_t* b = Createnode(0);
    ASSERT_NE(b, nullptr);

    int_t* c = Poww(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 1);
    EXPECT_EQ(c->next, nullptr);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

TEST(Lab1_test, Poww_AnyNumOne_returnNum) {
    int_t* a = Createnode(1);
    Bend(&a, 2);
    ASSERT_NE(a, nullptr);

    int_t* b = Createnode(1);
    ASSERT_NE(b, nullptr);

    int_t* c = Poww(a, b);
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->digit, 2);
    ASSERT_NE(c->next, nullptr);
    EXPECT_EQ(c->next->digit, 1);
    EXPECT_EQ(c->next->next, nullptr);

    FreeList(a);
    FreeList(b);
    FreeList(c);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}