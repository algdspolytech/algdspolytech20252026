#include <gtest/gtest.h>
#include "func.h"

TEST(ArrayStack, InitStArr_EmptyStack_returnValidVal_no1) {
    st_arr s;
    InitStArr(&s);
    EXPECT_EQ(s.top, 0);
    for (int i = 0; i < MAX_SIZE; i++)
        EXPECT_EQ(s.arr[i], 0);
}

TEST(ArrayStack, PushStArr_PushElement_returnValidVal_no2) {
    st_arr s;
    InitStArr(&s);
    PushStArr(&s, 10);
    EXPECT_EQ(s.top, 1);
    EXPECT_EQ(s.arr[0], 10);
}

TEST(ArrayStack, PushStArr_PushSomeElements_returnValidVal_no3) {
    st_arr s;
    InitStArr(&s);
    PushStArr(&s, 1);
    PushStArr(&s, 2);
    PushStArr(&s, 3);
    EXPECT_EQ(s.top, 3);
    EXPECT_EQ(s.arr[2], 3);
}

TEST(ArrayStack, PushStArr_OverflowStack_returnValidVal_no4) {
    st_arr s;
    InitStArr(&s);
    for (int i = 0; i < MAX_SIZE; i++)
        PushStArr(&s, i);
    int before = s.top;
    PushStArr(&s, 1);
    EXPECT_EQ(s.top, before);
}

TEST(ArrayStack, PopStArr_PopExistElement_returnValidVal_no5) {
    st_arr s;
    InitStArr(&s);
    PushStArr(&s, 1);
    int val = PopStArr(&s);
    EXPECT_EQ(val, 1);
    EXPECT_EQ(s.top, 0);
}

TEST(ArrayStack,  PopStArr_UnderflowStack_returnValidVal_no6) {
    st_arr s;
    InitStArr(&s);
    EXPECT_EQ(PopStArr(&s), -1);
}

TEST(ListStack, InitStList_EmptyStack_returnNull_no7) {
    st_list s;
    InitStList(&s);
    EXPECT_EQ(s.head, nullptr);
}

TEST(ListStack, PushStList_PushElement_returnValidVal_no8) {
    st_list s;
    InitStList(&s);
    PushStList(&s, 1);
    ASSERT_NE(s.head, nullptr);
    EXPECT_EQ(s.head->data, 1);
    EXPECT_EQ(s.head->next, nullptr);
}

TEST(ListStack, PushStArr_PushSomeElements_returnValidVal_no9) {
    st_list s;
    InitStList(&s);
    PushStList(&s, 1);
    PushStList(&s, 2);
    PushStList(&s, 3);
    ASSERT_NE(s.head, nullptr);
    EXPECT_EQ(s.head->data, 3);
    EXPECT_NE(s.head->next, nullptr);
}

TEST(ListStack, PopStList_PopExistElement_returnValidVal_no10) {
    st_list s;
    InitStList(&s);
    PushStList(&s, 1);
    int val = PopStList(&s);
    EXPECT_EQ(val, 1);
    EXPECT_EQ(s.head, nullptr);
}

TEST(ListStack, PopStList_PopSomeElements_returnValidVal_no11) {
    st_list s;
    InitStList(&s);
    PushStList(&s, 1);
    PushStList(&s, 2);
    PushStList(&s, 3);

    EXPECT_EQ(PopStList(&s), 3);
    EXPECT_EQ(PopStList(&s), 2);
    EXPECT_EQ(PopStList(&s), 1);
}

TEST(ListStack, PopStList_UnderflowStack_returnValidVal_no12) {
    st_list s;
    InitStList(&s);

    EXPECT_EQ(PopStList(&s), -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}