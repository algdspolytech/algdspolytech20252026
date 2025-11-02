#include <stdio.h>
#include "stack_list.h"
#include "stack_array.h"

static int total = 0;
static int passed = 0;
static int failed = 0;

#define TEST_START() printf("T %s\n", __func__)

#define TEST_ASSERT(condition) \
    do { \
        total++; \
        if (condition) { \
            passed++; \
            printf("P\n"); \
        } else { \
            failed++; \
            printf("F %s:%d\n", __FILE__, __LINE__); \
        } \
    } while(0)

#define TEST_EQUAL(expected, actual) \
    TEST_ASSERT((expected) == (actual))

#define TEST_NOT_EQUAL(expected, actual) \
    TEST_ASSERT((expected) != (actual))

#define TEST_TRUE(condition) \
    TEST_ASSERT((condition))

#define TEST_FALSE(condition) \
    TEST_ASSERT(!(condition))

#define TEST_NULL(ptr) \
    TEST_ASSERT((ptr) == NULL)

#define TEST_NOT_NULL(ptr) \
    TEST_ASSERT((ptr) != NULL)

void test_stack_list_create_destroy_no1(void)
{
    TEST_START();
    StackList* stack = createStackList();
    TEST_NOT_NULL(stack);
    TEST_EQUAL(0, sizeList(stack));
    TEST_TRUE(isEmptyList(stack));
    destroyStackList(stack);
}

void test_stack_list_push_pop_no2(void)
{
    TEST_START();
    StackList* stack = createStackList();
    int value;

    TEST_TRUE(pushList(stack, 10));
    TEST_EQUAL(1, sizeList(stack));
    TEST_TRUE(popList(stack, &value));
    TEST_EQUAL(10, value);
    TEST_EQUAL(0, sizeList(stack));

    destroyStackList(stack);
}

void test_stack_list_push_multiple_no3(void)
{
    TEST_START();
    StackList* stack = createStackList();
    int value;

    TEST_TRUE(pushList(stack, 10));
    TEST_TRUE(pushList(stack, 20));
    TEST_EQUAL(2, sizeList(stack));

    TEST_TRUE(popList(stack, &value));
    TEST_EQUAL(20, value);
    TEST_TRUE(popList(stack, &value));
    TEST_EQUAL(10, value);

    destroyStackList(stack);
}

void test_stack_list_peek_no4(void)
{
    TEST_START();
    StackList* stack = createStackList();
    int value;

    TEST_TRUE(pushList(stack, 30));
    TEST_TRUE(peekList(stack, &value));
    TEST_EQUAL(30, value);
    TEST_EQUAL(1, sizeList(stack));

    destroyStackList(stack);
}

void test_stack_list_pop_empty_no5(void)
{
    TEST_START();
    StackList* stack = createStackList();
    int value;

    TEST_FALSE(popList(stack, &value));
    TEST_FALSE(popList(NULL, &value));
    TEST_FALSE(popList(stack, NULL));

    destroyStackList(stack);
}

void test_stack_list_peek_empty_no6(void)
{
    TEST_START();
    StackList* stack = createStackList();
    int value;

    TEST_FALSE(peekList(stack, &value));
    TEST_FALSE(peekList(NULL, &value));
    TEST_FALSE(peekList(stack, NULL));

    destroyStackList(stack);
}

void test_stack_list_push_pop_sequence_no7(void)
{
    TEST_START();
    StackList* stack = createStackList();
    int values[] = { 1, 2, 3, 4, 5 };
    int value;

    for (int i = 0; i < 5; i++) {
        TEST_TRUE(pushList(stack, values[i]));
    }
    TEST_EQUAL(5, sizeList(stack));

    for (int i = 4; i >= 0; i--) {
        TEST_TRUE(popList(stack, &value));
        TEST_EQUAL(values[i], value);
    }

    destroyStackList(stack);
}

void test_stack_list_empty_after_pop_all_no8(void)
{
    TEST_START();
    StackList* stack = createStackList();
    int value;

    TEST_TRUE(pushList(stack, 100));
    TEST_TRUE(popList(stack, &value));
    TEST_TRUE(isEmptyList(stack));

    destroyStackList(stack);
}

void test_stack_list_size_after_push_no9(void)
{
    TEST_START();
    StackList* stack = createStackList();

    for (int i = 0; i < 10; i++)
    {
        TEST_TRUE(pushList(stack, i));
    }
    TEST_EQUAL(10, sizeList(stack));

    destroyStackList(stack);
}

void test_stack_list_push_null_stack_no10(void)
{

    TEST_START();
    TEST_FALSE(pushList(NULL, 10));
}

void test_stack_array_create_destroy_no1(void)
{
    TEST_START();
    StackArray* stack = createStackArray();
    TEST_NOT_NULL(stack);
    TEST_EQUAL(0, sizeArray(stack));
    TEST_TRUE(isEmptyArray(stack));
    destroyStackArray(stack);
}

void test_stack_array_push_pop_no2(void)
{
    TEST_START();
    StackArray* stack = createStackArray();
    int value;

    TEST_TRUE(pushArray(stack, 10));
    TEST_EQUAL(1, sizeArray(stack));
    TEST_TRUE(popArray(stack, &value));
    TEST_EQUAL(10, value);
    TEST_EQUAL(0, sizeArray(stack));

    destroyStackArray(stack);
}

void test_stack_array_push_multiple_no3(void)
{
    TEST_START();
    StackArray* stack = createStackArray();
    int value;

    TEST_TRUE(pushArray(stack, 10));
    TEST_TRUE(pushArray(stack, 20));
    TEST_EQUAL(2, sizeArray(stack));

    TEST_TRUE(popArray(stack, &value));
    TEST_EQUAL(20, value);
    TEST_TRUE(popArray(stack, &value));
    TEST_EQUAL(10, value);

    destroyStackArray(stack);
}

void test_stack_array_peek_no4(void)
{
    TEST_START();
    StackArray* stack = createStackArray();
    int value;

    TEST_TRUE(pushArray(stack, 30));
    TEST_TRUE(peekArray(stack, &value));
    TEST_EQUAL(30, value);
    TEST_EQUAL(1, sizeArray(stack));

    destroyStackArray(stack);
}

void test_stack_array_pop_empty_no5(void)
{
    TEST_START();
    StackArray* stack = createStackArray();
    int value;

    TEST_FALSE(popArray(stack, &value));
    TEST_FALSE(popArray(NULL, &value));
    TEST_FALSE(popArray(stack, NULL));

    destroyStackArray(stack);
}

void test_stack_array_peek_empty_no6(void)
{
    TEST_START();
    StackArray* stack = createStackArray();
    int value;

    TEST_FALSE(peekArray(stack, &value));
    TEST_FALSE(peekArray(NULL, &value));
    TEST_FALSE(peekArray(stack, NULL));

    destroyStackArray(stack);
}

void test_stack_array_resize_no7(void)
{
    TEST_START();
    StackArray* stack = createStackArray();

    for (int i = 0; i < 10; i++) {
        TEST_TRUE(pushArray(stack, i));
    }
    TEST_EQUAL(10, sizeArray(stack));

    destroyStackArray(stack);
}

void test_stack_array_push_pop_sequence_no8(void)
{
    TEST_START();
    StackArray* stack = createStackArray();
    int values[] = { 1, 2, 3, 4, 5 };
    int value;

    for (int i = 0; i < 5; i++)
    {
        TEST_TRUE(pushArray(stack, values[i]));
    }
    TEST_EQUAL(5, sizeArray(stack));

    for (int i = 4; i >= 0; i--)
    {
        TEST_TRUE(popArray(stack, &value));
        TEST_EQUAL(values[i], value);
    }

    destroyStackArray(stack);
}

void test_stack_array_empty_after_pop_all_no9(void)
{
    TEST_START();
    StackArray* stack = createStackArray();
    int value;

    TEST_TRUE(pushArray(stack, 100));
    TEST_TRUE(popArray(stack, &value));
    TEST_TRUE(isEmptyArray(stack));

    destroyStackArray(stack);
}

void test_stack_array_push_null_stack_no10(void)
{
    TEST_START();
    TEST_FALSE(pushArray(NULL, 10));
}

void run_all_tests(void)
{
    printf("LIST\n");
    test_stack_list_create_destroy_no1();
    test_stack_list_push_pop_no2();
    test_stack_list_push_multiple_no3();
    test_stack_list_peek_no4();
    test_stack_list_pop_empty_no5();
    test_stack_list_peek_empty_no6();
    test_stack_list_push_pop_sequence_no7();
    test_stack_list_empty_after_pop_all_no8();
    test_stack_list_size_after_push_no9();
    test_stack_list_push_null_stack_no10();

    printf("ARRAY\n");
    test_stack_array_create_destroy_no1();
    test_stack_array_push_pop_no2();
    test_stack_array_push_multiple_no3();
    test_stack_array_peek_no4();
    test_stack_array_pop_empty_no5();
    test_stack_array_peek_empty_no6();
    test_stack_array_resize_no7();
    test_stack_array_push_pop_sequence_no8();
    test_stack_array_empty_after_pop_all_no9();
    test_stack_array_push_null_stack_no10();

    printf("SUMMARY\n");
    printf("TOTAL:%d\n", total);
    printf("PASSED:%d\n", passed);
    printf("FAILED:%d\n", failed);
    printf("RATE:%.1f\n", (float)passed / total * 100);

    if (failed == 0)
    {
        printf("ALL_OK\n");
    }
    else
    {
        printf("SOME_FAILED\n");
    }
}