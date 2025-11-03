#include <gtest/gtest.h>
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

extern "C" {
    struct node
    {
        int vertex;
        struct node* next;
    };

    struct node* Create(int a);
    struct node* Add(struct node* head, int a);
    void converet(int A[], const char* buffer);
    int accept(FILE* f, int i, const char** matrix);
}

// Вспомогательная функция для очистки списка
void freeList(struct node* head) {
    while (head != nullptr) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }
}

// Тесты для функции Create
TEST(CreateFunctionTest, NormalValue) {
    struct node* node = Create(5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->vertex, 5);
    EXPECT_EQ(node->next, nullptr);
    free(node);
}

TEST(CreateFunctionTest, ZeroValue) {
    struct node* node = Create(0);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->vertex, 0);
    EXPECT_EQ(node->next, nullptr);
    free(node);
}

TEST(CreateFunctionTest, NegativeValue) {
    struct node* node = Create(-10);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->vertex, -10);
    EXPECT_EQ(node->next, nullptr);
    free(node);
}

// Тесты для функции Add
TEST(AddFunctionTest, AddToEmptyList) {
    struct node* head = nullptr;
    head = Add(head, 1);
    ASSERT_NE(head, nullptr);
    EXPECT_EQ(head->vertex, 1);
    EXPECT_EQ(head->next, nullptr);
    freeList(head);
}

TEST(AddFunctionTest, AddMultipleNodes) {
    struct node* head = nullptr;
    head = Add(head, 1);
    head = Add(head, 2);
    head = Add(head, 3);

    ASSERT_NE(head, nullptr);
    EXPECT_EQ(head->vertex, 1);
    ASSERT_NE(head->next, nullptr);
    EXPECT_EQ(head->next->vertex, 2);
    ASSERT_NE(head->next->next, nullptr);
    EXPECT_EQ(head->next->next->vertex, 3);
    EXPECT_EQ(head->next->next->next, nullptr);

    freeList(head);
}

TEST(AddFunctionTest, AddDuplicateValues) {
    struct node* head = nullptr;
    head = Add(head, 5);
    head = Add(head, 5);
    head = Add(head, 5);

    ASSERT_NE(head, nullptr);
    EXPECT_EQ(head->vertex, 5);
    ASSERT_NE(head->next, nullptr);
    EXPECT_EQ(head->next->vertex, 5);
    ASSERT_NE(head->next->next, nullptr);
    EXPECT_EQ(head->next->next->vertex, 5);
    EXPECT_EQ(head->next->next->next, nullptr);

    freeList(head);
}

// Тесты для функции converet
TEST(ConveretFunctionTest, SingleNumber) {
    int A[100];
    char buffer[] = "5";
    converet(A, buffer);

    EXPECT_EQ(A[0], 5);
    EXPECT_EQ(A[1], -1);
}

TEST(ConveretFunctionTest, MultipleNumbers) {
    int A[100];
    char buffer[] = "1 2 3 4";
    converet(A, buffer);

    EXPECT_EQ(A[0], 1);
    EXPECT_EQ(A[1], 2);
    EXPECT_EQ(A[2], 3);
    EXPECT_EQ(A[3], 4);
    EXPECT_EQ(A[4], -1);
}


// Интеграционные тесты
TEST(IntegrationTest, CreateAndAddSequence) {
    struct node* head = nullptr;
    head = Create(1);
    ASSERT_NE(head, nullptr);

    head = Add(head, 2);
    head = Add(head, 3);

    EXPECT_EQ(head->vertex, 1);
    EXPECT_EQ(head->next->vertex, 2);
    EXPECT_EQ(head->next->next->vertex, 3);
    EXPECT_EQ(head->next->next->next, nullptr);

    freeList(head);
}

TEST(IntegrationTest, MemoryManagement) {
    struct node* head = nullptr;

    // Создаем большой список
    for (int i = 0; i < 100; i++) {
        head = Add(head, i);
    }

    // Проверяем, что все элементы на месте
    struct node* current = head;
    for (int i = 0; i < 100; i++) {
        ASSERT_NE(current, nullptr);
        EXPECT_EQ(current->vertex, i);
        current = current->next;
    }
    EXPECT_EQ(current, nullptr);

    freeList(head);
}

// Граничные случаи
TEST(BoundaryCasesTest, AddToNullList) {
    struct node* head = Add(nullptr, 10);
    ASSERT_NE(head, nullptr);
    EXPECT_EQ(head->vertex, 10);
    EXPECT_EQ(head->next, nullptr);
    freeList(head);
}


TEST(BoundaryCasesTest, ConveretWithNewline) {
    int A[100];
    char buffer[] = "1 2\n3";
    converet(A, buffer);

    EXPECT_EQ(A[0], 1);
    EXPECT_EQ(A[1], 2);
    EXPECT_EQ(A[2], 3);
    EXPECT_EQ(A[3], -1);
}

// Тест на утечки памяти
TEST(MemoryTest, NoMemoryLeaksInList) {
    struct node* head = nullptr;
    head = Add(head, 1);
    head = Add(head, 2);
    head = Add(head, 3);

    freeList(head);
    SUCCEED();
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}