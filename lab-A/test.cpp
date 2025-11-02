#include <gtest/gtest.h>
#include "stack.h"

class ArrayStackTest : public ::testing::Test {
protected:
    ArrayStack stack;
    
    void SetUp() override {
        createArrayStack(&stack);
    }
};

class ListStackTest : public ::testing::Test {
protected:
    ListStack stack;
    
    void SetUp() override {
        createListStack(&stack);
    }
    
    void TearDown() override {
        // Очищаем память, выделенную для узлов списка
        while (!isListStackEmpty(&stack)) {
            popListStack(&stack);
        }
    }
    
    // Вспомогательная функция для проверки пустоты стека
    bool isListStackEmpty(ListStack* stack) {
        return s->top == nullptr;
    }
};

// Тесты для стека на связном списке с использованием фикстуры

// Тест создания пустого стека на списке
TEST_F(ListStackTest, CreateListStack_EmptyStack_ReturnValidVal_no1) {
    EXPECT_EQ(stack.top, nullptr);
    EXPECT_EQ(stack.size, 0);
}

// Тест добавления одного элемента в стек на списке
TEST_F(ListStackTest, PushStackList_SingleElement_ReturnValidVal_no2) {
    pushListStack(&stack, 1);
    EXPECT_EQ(stack.top->data, 1);
    EXPECT_EQ(stack.top->next, nullptr);
    EXPECT_EQ(stack.size, 1);
}

// Тест добавления нескольких элементов в стек на списке
TEST_F(ListStackTest, PushStackList_SomeElements_ReturnValidVal_no3) {
    for (int i = 1; i <= 5; i++) {
        pushListStack(&stack, i);
    }
    
    EXPECT_EQ(stack.top->data, 5);
    EXPECT_EQ(stack.size, 5);
}

// Тест извлечения элемента из стека на списке
TEST_F(ListStackTest, PopStackList_SingleElement_ReturnValidVal_no4) {
    pushListStack(&stack, 1);
    int val = popListStack(&stack);
    EXPECT_EQ(val, 1);
    EXPECT_EQ(stack.top, nullptr);
    EXPECT_EQ(stack.size, 0);
}

// Тест извлечения из пустого стека на списке
TEST_F(ListStackTest, PopStackList_EmptyStack_ReturnErrorCode_no5) {
    EXPECT_EQ(popListStack(&stack), -1);
}

// Тест просмотра верхнего элемента стека на списке
TEST_F(ListStackTest, PeekList_SingleElement_ReturnValidVal_no6) {
    pushListStack(&stack, 1);
    EXPECT_EQ(peekListStack(&stack), 1);
    EXPECT_EQ(stack.size, 1);
}

// Тесты для стека на массиве

// Тест создания пустого стека на массиве
TEST_F(ArrayStackTest, CreateArrayStack_EmptyStack_ReturnValidVal_no7) {
    EXPECT_EQ(stack.top, -1);
}

// Тест добавления одного элемента в стек на массиве
TEST_F(ArrayStackTest, PushArray_SingleElement_ReturnValidVal_no8) {
    pushArrayStack(&stack, 1);
    EXPECT_EQ(stack.top, 0);
    EXPECT_EQ(stack.data[0], 1);
}

// Тест добавления нескольких элементов в стек на массиве
TEST_F(ArrayStackTest, PushArray_SomeElements_ReturnValidVal_no9) {
    for (int i = 0; i < 5; i++){
        pushArrayStack(&stack, i + 1);
    }
    EXPECT_EQ(stack.top, 4);
    EXPECT_EQ(stack.data[0], 1);
    EXPECT_EQ(stack.data[1], 2);
    EXPECT_EQ(stack.data[2], 3);
    EXPECT_EQ(stack.data[3], 4);
    EXPECT_EQ(stack.data[4], 5);
}

// Тест переполнения стека на массиве
TEST_F(ArrayStackTest, PushArray_OverflowStack_ReturnValidVal_no10) {
    // Заполняем стек до предела
    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        pushArrayStack(&stack, i);
    }
    
    int before_top = stack.top;
    pushArrayStack(&stack, 1);
    EXPECT_EQ(stack.top, before_top);
}

// Тест извлечения элемента из стека на массиве
TEST_F(ArrayStackTest, PopArray_SingleElement_ReturnValidVal_no11) {
    pushArrayStack(&stack, 1);
    int val = popArrayStack(&stack);
    EXPECT_EQ(val, 1);
    EXPECT_EQ(stack.top, -1);
}

// Тест извлечения из пустого стека на массиве
TEST_F(ArrayStackTest, PopArray_EmptyStack_ReturnErrorCode_no12) {
    EXPECT_EQ(popArrayStack(&stack), -1);
}

// Тест просмотра верхнего элемента стека на массиве
TEST_F(ArrayStackTest, PeekArray_SingleElement_ReturnValidVal_no13) {
    pushArray(&stack, 1);
    EXPECT_EQ(peekArrayStack(&stack), 1);
    EXPECT_EQ(stack.top, 0);
}

// Главная функция запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
