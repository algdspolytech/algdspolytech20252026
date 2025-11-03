#include <gtest/gtest.h>
extern "C" {
    #include "stack.h"
}

// ---------- Тесты для стека на связном списке ----------

// Тест №1 — push и peek
TEST(StackListTest, PushAndPeek_HappyPath_no1) {
    StackList s; initStackList(&s);
    pushList(&s, 10);
    EXPECT_EQ(peekList(&s), 10);
    clearStackList(&s);
}

// Тест №2 — push и pop
TEST(StackListTest, PopAfterPush_HappyPath_no2) {
    StackList s; initStackList(&s);
    pushList(&s, 5);
    EXPECT_EQ(popList(&s), 5);
}

// Тест №3 — несколько push/pop подряд
TEST(StackListTest, MultiplePushPop_HappyPath_no3) {
    StackList s; initStackList(&s);
    pushList(&s, 1);
    pushList(&s, 2);
    pushList(&s, 3);
    EXPECT_EQ(popList(&s), 3);
    EXPECT_EQ(popList(&s), 2);
    EXPECT_EQ(popList(&s), 1);
}

// Тест №4 — peek на пустом стеке
TEST(StackListTest, PeekOnEmpty_Edge_no4) {
    StackList s; initStackList(&s);
    EXPECT_EXIT(peekList(&s), ::testing::ExitedWithCode(1), "Stack is empty");
}

// Тест №5 — очистка стека
TEST(StackListTest, ClearList_HappyPath_no5) {
    StackList s; initStackList(&s);
    for (int i = 0; i < 5; ++i) pushList(&s, i);
    clearStackList(&s);
    EXPECT_TRUE(isEmptyList(&s));
}

// ---------- Тесты для стека на массиве ----------

// Тест №6 — push и peek
TEST(StackArrayTest, PushAndPeek_HappyPath_no6) {
    StackArray s; initStackArray(&s);
    pushArray(&s, 42);
    EXPECT_EQ(peekArray(&s), 42);
}

// Тест №7 — push и pop
TEST(StackArrayTest, PopAfterPush_HappyPath_no7) {
    StackArray s; initStackArray(&s);
    pushArray(&s, 100);
    EXPECT_EQ(popArray(&s), 100);
}

// Тест №8 — несколько push/pop подряд
TEST(StackArrayTest, MultiplePushPop_HappyPath_no8) {
    StackArray s; initStackArray(&s);
    for (int i = 0; i < 3; ++i) pushArray(&s, i);
    EXPECT_EQ(popArray(&s), 2);
    EXPECT_EQ(popArray(&s), 1);
    EXPECT_EQ(popArray(&s), 0);
}

// Тест №9 — переполнение стека
TEST(StackArrayTest, Overflow_Edge_no9) {
    StackArray s; initStackArray(&s);
    for (int i = 0; i < MAX_SIZE; ++i) pushArray(&s, i);
    EXPECT_EXIT(pushArray(&s, 999), ::testing::ExitedWithCode(1), "Stack overflow");
}

// Тест №10 — извлечение из пустого стека
TEST(StackArrayTest, Underflow_Edge_no10) {
    StackArray s; initStackArray(&s);
    EXPECT_EXIT(popArray(&s), ::testing::ExitedWithCode(1), "Stack underflow");
}
