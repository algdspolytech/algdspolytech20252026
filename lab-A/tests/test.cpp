#include "pch.h"
#include <gtest/gtest.h>

extern "C" {
#include "../BirthdayList/birthdays.h"
}

// Тест 1: создание узла
TEST(BirthdayTest, CreateNode_no1) {
    Person p = { "Ivanov", "Petr", "Sidorovich", 15, 5, 1990 };
    Node* node = create_node(p);

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->data.last_name, "Ivanov");
    EXPECT_EQ(node->data.day, 15);

    if (node != nullptr) {
        free(node);
    }
}

// Тест 2: вставка в пустой список
TEST(BirthdayTest, InsertToEmptyList_no2) {
    Node* head = NULL;
    Person p = { "Petrov", "Ivan", "Sergeevich", 10, 1, 1995 };

    insert_sorted(&head, p);
    EXPECT_NE(head, nullptr);

    if (head != nullptr) {
        free_list(head);
    }
}

// Тест 3: освобождение пустого списка
TEST(BirthdayTest, FreeEmptyList_no3) {
    Node* head = NULL;
    free_list(head);
    SUCCEED();
}

// Тест 4: вставка двух элементов
TEST(BirthdayTest, InsertTwoElements_no4) {
    Node* head = NULL;
    Person p1 = { "A", "A", "A", 2, 1, 2000 };
    Person p2 = { "B", "B", "B", 1, 1, 2000 };

    insert_sorted(&head, p1);
    insert_sorted(&head, p2);

    EXPECT_NE(head, nullptr);

    if (head != nullptr) {
        free_list(head);
    }
}

// Тест 5: поиск по дате (простой)
TEST(BirthdayTest, FindByDateSimple_no5) {
    Node* head = NULL;
    Person p = { "Ivanov", "Petr", "Sidorovich", 15, 5, 1990 };

    insert_sorted(&head, p);

    // проверяем что функция не падает
    testing::internal::CaptureStdout();
    find_by_date(head, 15, 5);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.length(), 0);

    if (head != nullptr) {
        free_list(head);
    }
}

// Тест 6: создание нескольких узлов
TEST(BirthdayTest, CreateMultipleNodes_no6) {
    Person p1 = { "A", "A", "A", 1, 1, 2000 };
    Person p2 = { "B", "B", "B", 2, 1, 2000 };

    Node* node1 = create_node(p1);
    Node* node2 = create_node(p2);

    EXPECT_NE(node1, nullptr);
    EXPECT_NE(node2, nullptr);

    if (node1 != nullptr) free(node1);
    if (node2 != nullptr) free(node2);
}

// Тест 7: вставка в начало
TEST(BirthdayTest, InsertAtBeginning_no7) {
    Node* head = NULL;
    Person p1 = { "First", "A", "A", 10, 1, 2000 };
    Person p2 = { "Second", "B", "B", 5, 1, 2000 };

    insert_sorted(&head, p1);
    insert_sorted(&head, p2);

    EXPECT_NE(head, nullptr);

    if (head != nullptr) {
        free_list(head);
    }
}

// Тест 8: вставка в конец
TEST(BirthdayTest, InsertAtEnd_no8) {
    Node* head = NULL;
    Person p1 = { "First", "A", "A", 1, 1, 2000 };
    Person p2 = { "Last", "B", "B", 31, 12, 2000 };

    insert_sorted(&head, p1);
    insert_sorted(&head, p2);

    EXPECT_NE(head, nullptr);

    if (head != nullptr) {
        free_list(head);
    }
}

// Тест 9: поиск несуществующей даты
TEST(BirthdayTest, FindNonExistingDate_no9) {
    Node* head = NULL;
    Person p = { "Ivanov", "Petr", "Sidorovich", 15, 5, 1990 };

    insert_sorted(&head, p);

    testing::internal::CaptureStdout();
    find_by_date(head, 31, 12);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.length(), 0);

    if (head != nullptr) {
        free_list(head);
    }
}

// Тест 10: множественная вставка
TEST(BirthdayTest, MultipleInsertions_no10) {
    Node* head = NULL;
    Person p1 = { "A", "A", "A", 3, 1, 2000 };
    Person p2 = { "B", "B", "B", 2, 1, 2000 };
    Person p3 = { "C", "C", "C", 1, 1, 2000 };

    insert_sorted(&head, p1);
    insert_sorted(&head, p2);
    insert_sorted(&head, p3);

    EXPECT_NE(head, nullptr);

    if (head != nullptr) {
        free_list(head);
    }
}