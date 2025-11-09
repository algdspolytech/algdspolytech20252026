#include <gtest/gtest.h>
#include "stack_s.h"
#include "stack_a.h"

// StackList Tests
TEST(StackListTest, CreateEmptyStack_ReturnValidStack_no1) {
    StackList* stack = stack_list_create();
    EXPECT_NE(stack, nullptr);
    EXPECT_TRUE(stack_list_is_empty(stack));
    EXPECT_EQ(stack_list_size(stack), 0);
    stack_list_destroy(stack);
}

TEST(StackListTest, PushOneElement_SizeIncreased_no2) {
    StackList* stack = stack_list_create();

    bool result = stack_list_push(stack, 5);

    EXPECT_TRUE(result);
    EXPECT_EQ(stack_list_size(stack), 1);
    EXPECT_FALSE(stack_list_is_empty(stack));
    stack_list_destroy(stack);
}

TEST(StackListTest, PushMultipleElements_CorrectOrder_no3) {
    StackList* stack = stack_list_create();

    stack_list_push(stack, 10);
    stack_list_push(stack, 20);
    stack_list_push(stack, 30);

    EXPECT_EQ(stack_list_size(stack), 3);

    int value;
    stack_list_pop(stack, &value);
    EXPECT_EQ(value, 30);
    stack_list_pop(stack, &value);
    EXPECT_EQ(value, 20);
    stack_list_pop(stack, &value);
    EXPECT_EQ(value, 10);

    stack_list_destroy(stack);
}

TEST(StackListTest, PopEmptyStack_ReturnFalse_no4) {
    StackList* stack = stack_list_create();
    int value;

    bool result = stack_list_pop(stack, &value);

    EXPECT_FALSE(result);
    stack_list_destroy(stack);
}

TEST(StackListTest, PeekNonEmptyStack_ReturnValueNoRemove_no5) {
    StackList* stack = stack_list_create();
    stack_list_push(stack, 42);
    int value;

    bool result = stack_list_peek(stack, &value);

    EXPECT_TRUE(result);
    EXPECT_EQ(value, 42);
    EXPECT_EQ(stack_list_size(stack), 1);
    stack_list_destroy(stack);
}

TEST(StackListTest, MultiplePushPop_CorrectLIFO_no6) {
    StackList* stack = stack_list_create();

    stack_list_push(stack, 100);
    stack_list_push(stack, 200);

    int value;
    stack_list_pop(stack, &value);
    EXPECT_EQ(value, 200);

    stack_list_pop(stack, &value);
    EXPECT_EQ(value, 100);

    stack_list_destroy(stack);
}

// StackArray Tests  
TEST(StackArrayTest, CreateEmptyStack_ReturnValidStack_no7) {
    StackArray* stack = stack_array_create();
    EXPECT_NE(stack, nullptr);
    EXPECT_TRUE(stack_array_is_empty(stack));
    EXPECT_EQ(stack_array_size(stack), 0);
    stack_array_destroy(stack);
}

TEST(StackArrayTest, PushBeyondCapacity_AutoResize_no8) {
    StackArray* stack = stack_array_create();

    for (int i = 0; i < 15; i++) {
        EXPECT_TRUE(stack_array_push(stack, i));
    }

    EXPECT_EQ(stack_array_size(stack), 15);
    EXPECT_GE(stack_array_capacity(stack), 15);

    int value;
    for (int i = 14; i >= 0; i--) {
        EXPECT_TRUE(stack_array_pop(stack, &value));
        EXPECT_EQ(value, i);
    }

    stack_array_destroy(stack);
}

TEST(StackArrayTest, MixedOperations_CorrectBehavior_no9) {
    StackArray* stack = stack_array_create();

    stack_array_push(stack, 1);
    stack_array_push(stack, 2);

    int value;
    stack_array_pop(stack, &value);
    EXPECT_EQ(value, 2);

    stack_array_push(stack, 3);
    stack_array_push(stack, 4);

    EXPECT_EQ(stack_array_size(stack), 3);

    stack_array_pop(stack, &value);
    EXPECT_EQ(value, 4);
    stack_array_pop(stack, &value);
    EXPECT_EQ(value, 3);
    stack_array_pop(stack, &value);
    EXPECT_EQ(value, 1);

    stack_array_destroy(stack);
}

TEST(StackArrayTest, PeekEmptyStack_ReturnFalse_no10) {
    StackArray* stack = stack_array_create();
    int value;

    bool result = stack_array_peek(stack, &value);

    EXPECT_FALSE(result);
    stack_array_destroy(stack);
}

TEST(StackArrayTest, CapacityNewStack_ReturnInitialCapacity_no11) {
    StackArray* stack = stack_array_create();

    size_t capacity = stack_array_capacity(stack);

    EXPECT_EQ(capacity, STACK_ARRAY_INITIAL_CAPACITY);
    stack_array_destroy(stack);
}

TEST(StackArrayTest, MultiplePushPop_CorrectLIFO_no12) {
    StackArray* stack = stack_array_create();

    stack_array_push(stack, 100);
    stack_array_push(stack, 200);

    int value;
    stack_array_pop(stack, &value);
    EXPECT_EQ(value, 200);

    stack_array_pop(stack, &value);
    EXPECT_EQ(value, 100);

    stack_array_destroy(stack);
}

