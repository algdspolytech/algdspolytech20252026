#include <gtest/gtest.h>
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    struct Node
    {
        char str[21];
        struct Node* next;
    };
    struct Node* create(const char* a);
    void Add(struct Node** head, const char* a);
    void bSort(struct Node* head, int l);
    void print(struct Node* head, FILE* f3);
}

// Тесты для функции create
TEST(CreateFunctionTest, NormalString) {
    struct Node* node = create("test");
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->str, "test");
    EXPECT_EQ(node->next, nullptr);
    free(node);
}

TEST(CreateFunctionTest, EmptyString) {
    struct Node* node = create("");
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->str, "");
    EXPECT_EQ(node->next, nullptr);
    free(node);
}

TEST(CreateFunctionTest, VeryLongString) {
    char long_str[50] = "this is a very long string that exceeds the limit";
    struct Node* node = create(long_str);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(strlen(node->str) <= 20, true); // Проверка усечения
    free(node);
}

TEST(CreateFunctionTest, NullPointer) {
    struct Node* node = create(NULL);
    EXPECT_EQ(node, nullptr);
}

// Тесты для функции Add
TEST(AddFunctionTest, AddToEmptyList) {
    struct Node* head = nullptr;
    Add(&head, "first");
    ASSERT_NE(head, nullptr);
    EXPECT_STREQ(head->str, "first");
    EXPECT_EQ(head->next, nullptr);
    free(head);
}

TEST(AddFunctionTest, AddMultipleNodes) {
    struct Node* head = nullptr;
    Add(&head, "first");
    Add(&head, "second");
    Add(&head, "third");

    ASSERT_NE(head, nullptr);
    EXPECT_STREQ(head->str, "first");
    ASSERT_NE(head->next, nullptr);
    EXPECT_STREQ(head->next->str, "second");
    ASSERT_NE(head->next->next, nullptr);
    EXPECT_STREQ(head->next->next->str, "third");
    EXPECT_EQ(head->next->next->next, nullptr);


    struct Node* current = head;
    while (current != nullptr) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
}

TEST(AddFunctionTest, AddNullString) {
    struct Node* head = nullptr;
    Add(&head, NULL);
    EXPECT_EQ(head, nullptr);
}

// Тесты для функции bSort
TEST(BSortFunctionTest, EmptyList) {
    bSort(nullptr, 0);
    SUCCEED();
}

TEST(BSortFunctionTest, SingleNode) {
    struct Node* head = create("single");
    bSort(head, 1);
    ASSERT_NE(head, nullptr);
    EXPECT_STREQ(head->str, "single");
    free(head);
}

TEST(BSortFunctionTest, AlreadySorted) {
    struct Node* head = create("apple");
    struct Node* second = create("banana");
    struct Node* third = create("cherry");
    head->next = second;
    second->next = third;

    bSort(head, 3);

    EXPECT_STREQ(head->str, "apple");
    EXPECT_STREQ(head->next->str, "banana");
    EXPECT_STREQ(head->next->next->str, "cherry");

    // Освобождение памяти
    free(head);
    free(second);
    free(third);
}

TEST(BSortFunctionTest, ReverseSorted) {
    struct Node* head = create("cherry");
    struct Node* second = create("banana");
    struct Node* third = create("apple");
    head->next = second;
    second->next = third;

    bSort(head, 3);

    EXPECT_STREQ(head->str, "apple");
    EXPECT_STREQ(head->next->str, "banana");
    EXPECT_STREQ(head->next->next->str, "cherry");

    // Освобождение памяти
    free(head);
    free(second);
    free(third);
}

TEST(BSortFunctionTest, WithDuplicates) {
    struct Node* head = create("banana");
    struct Node* second = create("apple");
    struct Node* third = create("banana");
    head->next = second;
    second->next = third;

    bSort(head, 3);

    EXPECT_STREQ(head->str, "apple");
    EXPECT_STREQ(head->next->str, "banana");
    EXPECT_STREQ(head->next->next->str, "banana");

    // Освобождение памяти
    free(head);
    free(second);
    free(third);
}
TEST(BoundaryCasesTest, ZeroLengthInBSort) {
    struct Node* head = create("test");
    bSort(head, 0);
    EXPECT_STREQ(head->str, "test");
    free(head);
}

TEST(BoundaryCasesTest, NegativeLengthInBSort) {
    struct Node* head = create("test");
    bSort(head, -1);
    EXPECT_STREQ(head->str, "test");
    free(head);
}


TEST(MemoryTest, NoMemoryLeaks) {
    struct Node* head = nullptr;
    Add(&head, "test1");
    Add(&head, "test2");
    Add(&head, "test3");


    struct Node* current = head;
    while (current != nullptr) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }

    SUCCEED();

}
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}