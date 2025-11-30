#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

static int tests_passed = 0;
static int tests_failed = 0;

#define ASSERT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            printf(" [FAIL] %s\n", message); \
            tests_failed++; \
            return; \
        } \
    } while(0)

#define ASSERT_EQ(actual, expected, message) \
    do { \
        if ((actual) != (expected)) { \
            printf(" [FAIL] %s: ожидалось %d, получено %d\n", message, expected, actual); \
            tests_failed++; \
            return; \
        } \
    } while(0)

#define TEST(name) \
    void name(void); \
    printf("RUNNING: %s\n", #name); \
    name(); \
    if (tests_failed == 0 || tests_failed == tests_failed) { \
        tests_passed++; \
    }

// Тесты для ListStack


void TestPushToEmptyList_HappyPath_no1() {
    ListStack* stack = create_list_stack();
    ASSERT_TRUE(stack != NULL, "Не удалось создать стек");
    ASSERT_TRUE(list_push(stack, 1), "Push вернул false");
    ASSERT_EQ(list_peek(stack), 1, "Верхний элемент должен быть 1");
    ASSERT_EQ(list_size(stack), 1, "Размер должен быть 1");
    destroy_list_stack(stack);
}

void TestPopFromSingleElementList_HappyPath_no2() {
    ListStack* stack = create_list_stack();
    list_push(stack, 5);
    int val = list_pop(stack);
    ASSERT_EQ(val, 5, "Pop должен вернуть 5");
    ASSERT_TRUE(list_is_empty(stack), "После pop стек должен быть пуст");
    ASSERT_EQ(list_size(stack), 0, "Размер должен стать 0");
    destroy_list_stack(stack);
}

void TestPeekDoesNotRemove_HappyPath_no3() {
    ListStack* stack = create_list_stack();
    list_push(stack, 10);
    int val1 = list_peek(stack);
    int val2 = list_peek(stack);
    ASSERT_EQ(val1, 10, "Первый peek");
    ASSERT_EQ(val2, 10, "Второй peek");
    ASSERT_EQ(list_size(stack), 1, "Peek не должен удалять элемент");
    destroy_list_stack(stack);
}

void TestPushMultipleElements_OrderCorrect_no4() {
    ListStack* stack = create_list_stack();
    list_push(stack, 1);
    list_push(stack, 2);
    list_push(stack, 3);
    ASSERT_EQ(list_pop(stack), 3, "Первый pop");
    ASSERT_EQ(list_pop(stack), 2, "Второй pop");
    ASSERT_EQ(list_pop(stack), 1, "Третий pop");
    ASSERT_TRUE(list_is_empty(stack), "Стек должен быть пуст");
    destroy_list_stack(stack);
}

void TestIsEmptyOnNewStack_EmptyTrue_no5() {
    ListStack* stack = create_list_stack();
    ASSERT_TRUE(list_is_empty(stack), "Новый стек должен быть пуст");
    destroy_list_stack(stack);
}

void TestIsEmptyAfterAllPops_EmptyTrue_no6() {
    ListStack* stack = create_list_stack();
    list_push(stack, 1);
    list_pop(stack);
    ASSERT_TRUE(list_is_empty(stack), "После удаления последнего элемента — пуст");
    destroy_list_stack(stack);
}

void TestSizeIncreasesWithPush_SizeCorrect_no7() {
    ListStack* stack = create_list_stack();
    ASSERT_EQ(list_size(stack), 0, "Изначальный размер");
    list_push(stack, 1);
    ASSERT_EQ(list_size(stack), 1, "После push");
    list_push(stack, 2);
    ASSERT_EQ(list_size(stack), 2, "После второго push");
    destroy_list_stack(stack);
}

void TestDestroyNullListStack_NoCrash_no8() {
    destroy_list_stack(NULL); 
}

void TestPushNullListStack_ReturnsFalse_no9() {
    bool result = list_push(NULL, 5);
    ASSERT_TRUE(!result, "Push в NULL-стек должен вернуть false");
}

void TestPopFromEmptyList_CrashExpected_no10() {
    ListStack* stack = create_list_stack();
    ASSERT_TRUE(list_is_empty(stack), "Новый стек пуст");
    destroy_list_stack(stack);
}


// Тесты для ArrayStack


void TestPushToEmptyArray_HappyPath_no11() {
    ArrayStack* stack = create_array_stack();
    ASSERT_TRUE(stack != NULL, "Не удалось создать массивный стек");
    ASSERT_TRUE(array_push(stack, 1), "Push должен succeed");
    ASSERT_EQ(array_peek(stack), 1, "Верхний элемент");
    ASSERT_EQ(array_size(stack), 1, "Размер после push");
    destroy_array_stack(stack);
}

void TestPopFromSingleElementArray_HappyPath_no12() {
    ArrayStack* stack = create_array_stack();
    array_push(stack, 5);
    int val = array_pop(stack);
    ASSERT_EQ(val, 5, "Pop должен вернуть 5");
    ASSERT_TRUE(array_is_empty(stack), "Стек должен быть пуст");
    ASSERT_EQ(array_size(stack), 0, "Размер после pop");
    destroy_array_stack(stack);
}

void TestPeekDoesNotRemoveInArray_HappyPath_no13() {
    ArrayStack* stack = create_array_stack();
    array_push(stack, 10);
    int val1 = array_peek(stack);
    int val2 = array_peek(stack);
    ASSERT_EQ(val1, 10, "Первый peek");
    ASSERT_EQ(val2, 10, "Второй peek");
    ASSERT_EQ(array_size(stack), 1, "Peek не должен менять размер");
    destroy_array_stack(stack);
}

void TestPushMultipleToArray_OrderCorrect_no14() {
    ArrayStack* stack = create_array_stack();
    array_push(stack, 1);
    array_push(stack, 2);
    array_push(stack, 3);
    ASSERT_EQ(array_pop(stack), 3, "pop 1");
    ASSERT_EQ(array_pop(stack), 2, "pop 2");
    ASSERT_EQ(array_pop(stack), 1, "pop 3");
    ASSERT_TRUE(array_is_empty(stack), "Стек должен быть пуст");
    destroy_array_stack(stack);
}

void TestIsEmptyOnNewArray_EmptyTrue_no15() {
    ArrayStack* stack = create_array_stack();
    ASSERT_TRUE(array_is_empty(stack), "Новый массивный стек пуст");
    destroy_array_stack(stack);
}

void TestPushBeyondCapacity_ReturnsFalse_no16() {
    ArrayStack* stack = create_array_stack();
    for (int i = 0; i < ARRAY_STACK_CAPACITY; ++i) {
        ASSERT_TRUE(array_push(stack, i), "Push в пределах ёмкости");
    }
    ASSERT_TRUE(!array_push(stack, 999), "Push за пределы ёмкости должен провалиться");
    destroy_array_stack(stack);
}

void TestDestroyNullArrayStack_NoCrash_no17() {
    destroy_array_stack(NULL); // Безопасно
}

void TestPushNullArrayStack_ReturnsFalse_no18() {
    bool result = array_push(NULL, 5);
    ASSERT_TRUE(!result, "Push в NULL-стек должен вернуть false");
}

void TestSizeOfArrayStack_CorrectAfterOperations_no19() {
    ArrayStack* stack = create_array_stack();
    ASSERT_EQ(array_size(stack), 0, "Изначальный размер");
    array_push(stack, 1);
    ASSERT_EQ(array_size(stack), 1, "После push");
    array_push(stack, 2);
    ASSERT_EQ(array_size(stack), 2, "После второго push");
    array_pop(stack);
    ASSERT_EQ(array_size(stack), 1, "После pop");
    destroy_array_stack(stack);
}

void TestPopFromEmptyArray_Undefined_no20() {
    ArrayStack* stack = create_array_stack();
    ASSERT_TRUE(array_is_empty(stack), "Массивный стек пуст после создания");
    destroy_array_stack(stack);
}

// Главная функция


int main() {
    printf(" Запуск тестов стека \n\n");

    // Сброс счётчиков
    tests_passed = 0;
    tests_failed = 0;

    // Запуск всех тестов
    TEST(TestPushToEmptyList_HappyPath_no1);
    TEST(TestPopFromSingleElementList_HappyPath_no2);
    TEST(TestPeekDoesNotRemove_HappyPath_no3);
    TEST(TestPushMultipleElements_OrderCorrect_no4);
    TEST(TestIsEmptyOnNewStack_EmptyTrue_no5);
    TEST(TestIsEmptyAfterAllPops_EmptyTrue_no6);
    TEST(TestSizeIncreasesWithPush_SizeCorrect_no7);
    TEST(TestDestroyNullListStack_NoCrash_no8);
    TEST(TestPushNullListStack_ReturnsFalse_no9);
    TEST(TestPopFromEmptyList_CrashExpected_no10);

    TEST(TestPushToEmptyArray_HappyPath_no11);
    TEST(TestPopFromSingleElementArray_HappyPath_no12);
    TEST(TestPeekDoesNotRemoveInArray_HappyPath_no13);
    TEST(TestPushMultipleToArray_OrderCorrect_no14);
    TEST(TestIsEmptyOnNewArray_EmptyTrue_no15);
    TEST(TestPushBeyondCapacity_ReturnsFalse_no16);
    TEST(TestDestroyNullArrayStack_NoCrash_no17);
    TEST(TestPushNullArrayStack_ReturnsFalse_no18);
    TEST(TestSizeOfArrayStack_CorrectAfterOperations_no19);
    TEST(TestPopFromEmptyArray_Undefined_no20);

    // Итог
    printf("\n Результаты тестов \n");
    printf("Пройдено: %d\n", tests_passed);
    printf("Упало: %d\n", tests_failed);
    printf("Всего: %d\n", tests_passed + tests_failed);

    if (tests_failed == 0) {
        printf("Все тесты прошли успешно!\n");
        return 0;
    }
    else {
        printf("Есть упавшие тесты.\n");
        return 1;
    }
}