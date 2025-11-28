#include "pch.h"
#include <gtest/gtest.h>
extern "C" {
#include "Ah.h"
}

TEST(ArrStackTest, CreateAS_AS_returnvoid) {
    arr_stack stack;
    CreateAS(&stack);
    EXPECT_EQ(stack.top, -1);
    EXPECT_TRUE(isASempty(&stack));
}

TEST(ArrStackTest, IsEmptyAS_AS_returnbool) {
    arr_stack stack;
    CreateAS(&stack);
    EXPECT_TRUE(isASempty(&stack));
}

TEST(ArrStackTest, PushAS_ASint_returnvoid) {
    arr_stack stack;
    CreateAS(&stack);
    pushAS(&stack, 10);
    EXPECT_FALSE(isASempty(&stack));
    EXPECT_EQ(stack.top, 0);
    EXPECT_EQ(stack.elements[stack.top], 10);
}

TEST(ArrStackTest, PopAS_ASint_returnint) {
    arr_stack stack;
    CreateAS(&stack);
    pushAS(&stack, 10);
    EXPECT_FALSE(isASempty(&stack));
    EXPECT_EQ(popAS(&stack), 10);
    EXPECT_TRUE(isASempty(&stack));
}

TEST(ArrStackTest, PopAS_MultiplePushPop_returnMultipleint) {
    arr_stack stack;
    CreateAS(&stack);
    pushAS(&stack, 4);
    pushAS(&stack, 13);
    pushAS(&stack, 21);
    EXPECT_EQ(popAS(&stack), 21);
    EXPECT_EQ(popAS(&stack), 13);
    EXPECT_EQ(popAS(&stack), 4);
    EXPECT_TRUE(isASempty(&stack));
}

TEST(ArrStackTest, PopAS_PopFromEmpty_returnerror) {
    arr_stack stack;
    CreateAS(&stack);
    EXPECT_EQ(popAS(&stack), -1); // Ошибка
}

TEST(NodeStackTest, CreateNS_NS_returnNS) {
    node_stack* a2 = CreateNS(17);
    ASSERT_NE(a2, nullptr);
    EXPECT_EQ(a2->value, 17);
    EXPECT_EQ(a2->next, nullptr);
    free(a2);
}

TEST(NodeStackTest, PushNS_NSint_returnvoid) {
    node_stack* stack = CreateNS(3);
    ASSERT_NE(stack, nullptr);
    EXPECT_EQ(stack->value, 3);
}

TEST(NodeStackTest, PopNS_NSint_returnint) {
    node_stack* stack = CreateNS(3);
    ASSERT_NE(stack, nullptr);
    EXPECT_EQ(popNS(&stack), 3);
    EXPECT_EQ(stack, nullptr);
}

TEST(NodeStackTest, PopNS_MultiplePushPop_returnMultipleint) {
    node_stack* stack = CreateNS(16);
    ASSERT_NE(stack, nullptr);
    pushNS(&stack, 84);
    pushNS(&stack, 35);
    EXPECT_EQ(popNS(&stack), 35);
    EXPECT_EQ(popNS(&stack), 84);
    EXPECT_EQ(popNS(&stack), 16);
    EXPECT_EQ(stack, nullptr);
}

TEST(NodeStackTest, PopNS_PopFromEmpty_returnerror) {
    node_stack* stack = nullptr;
    EXPECT_EQ(popNS(&stack), -1); // Ошибка
}

TEST(ComparisonTest, PopPush_SameBehavior_returnNSAS) {
    arr_stack arr_stack;
    node_stack* node_stack = CreateNS(1);
    ASSERT_NE(node_stack, nullptr);
    CreateAS(&arr_stack);
    pushAS(&arr_stack, 1);
    pushAS(&arr_stack, 2);
    pushAS(&arr_stack, 3);
    pushNS(&node_stack, 2);
    pushNS(&node_stack, 3);
    EXPECT_EQ(popAS(&arr_stack), popNS(&node_stack));
    EXPECT_EQ(popAS(&arr_stack), popNS(&node_stack));
    EXPECT_EQ(popAS(&arr_stack), popNS(&node_stack));
    EXPECT_TRUE(isASempty(&arr_stack));
    EXPECT_EQ(node_stack, nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
