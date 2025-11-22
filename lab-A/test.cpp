#include <gtest/gtest.h>
#include "xor_list.h"

// Вспомогательные функции для тестов.
void setup_list(XORList* list, const char* strings[], int count) {
    init_list(list);
    for (int i = 0; i < count; ++i) {
        insert(list, strings[i]);
    }
}

void teardown_list(XORList* list) {
    free_list(list);
}

// Фикстура тестов.
class XORListTest : public ::testing::Test {
protected:
    XORList list;

    void SetUp() override { init_list(&list); }
    void TearDown() override { free_list(&list); }
};

// Тесты insert()
TEST_F(XORListTest, Insert_EmptyList_ReturnValidVal_no1) {
    insert(&list, "Test");
    ASSERT_NE(list.head, nullptr);
    ASSERT_EQ(list.tail, list.head);
    ASSERT_STREQ(list.head->data, "Test");
    ASSERT_EQ(list.head->link, (uintptr_t)nullptr);
}

TEST_F(XORListTest, Insert_OneElementList_ReturnValidVal_no2) {
    insert(&list, "First");
    insert(&list, "Second");
    ASSERT_NE(list.head, nullptr);
    ASSERT_STREQ(list.head->data, "Second");
    ASSERT_EQ(xor_ptr(nullptr, (Node*)list.head->link), list.tail);
    ASSERT_STREQ(list.tail->data, "First");
}

TEST_F(XORListTest, Insert_MultipleElements_ReturnValidVal_no3) {
    const char* items[] = { "A", "B", "C" };
    setup_list(&list, items, 3);
    ASSERT_NE(list.head, nullptr);
    ASSERT_STREQ(list.head->data, "C");
    Node* current = list.head;
    Node* prev = nullptr;
    Node* next = xor_ptr(prev, (Node*)current->link);
    ASSERT_STREQ(next->data, "B");
}

// Тесты find()
TEST_F(XORListTest, Find_EmptyList_ReturnNull_no4) {
    Node* result = find(&list, "Test");
    ASSERT_EQ(result, nullptr);
}

TEST_F(XORListTest, Find_SingleElementFound_ReturnValidVal_no5) {
    insert(&list, "Test");
    Node* result = find(&list, "Test");
    ASSERT_NE(result, nullptr);
    ASSERT_STREQ(result->data, "Test");
}

TEST_F(XORListTest, Find_MultiElementNotFound_ReturnNull_no6) {
    const char* items[] = { "A", "B", "C" };
    setup_list(&list, items, 3);
    Node* result = find(&list, "D");
    ASSERT_EQ(result, nullptr);
}

TEST_F(XORListTest, Find_MultiElementFound_ReturnValidVal_no7) {
    const char* items[] = { "A", "B", "C" };
    setup_list(&list, items, 3);
    Node* result = find(&list, "B");
    ASSERT_NE(result, nullptr);
    ASSERT_STREQ(result->data, "B");
}

// Тесты remove_by_key() и remove_by_ptr()
TEST_F(XORListTest, RemoveByKey_EmptyList_NoChange_no8) {
    remove_by_key(&list, "Test");
    ASSERT_EQ(list.head, nullptr);
    ASSERT_EQ(list.tail, nullptr);
}

TEST_F(XORListTest, RemoveByKey_SingleElement_ReturnEmpty_no9) {
    insert(&list, "Test");
    remove_by_key(&list, "Test");
    ASSERT_EQ(list.head, nullptr);
    ASSERT_EQ(list.tail, nullptr);
}

TEST_F(XORListTest, RemoveByKey_MultiElementMiddle_ReturnValidVal_no10) {
    const char* items[] = { "A", "B", "C" };
    setup_list(&list, items, 3);
    remove_by_key(&list, "B");
    Node* current = list.head;
    ASSERT_STREQ(current->data, "C");
    Node* next = xor_ptr(nullptr, (Node*)current->link);
    ASSERT_STREQ(next->data, "A");
    ASSERT_EQ(list.tail, next);
}

TEST_F(XORListTest, RemoveByPtr_HeadElement_ReturnValidVal_no11) {
    const char* items[] = { "A", "B" };
    setup_list(&list, items, 2);
    Node* to_remove = find(&list, "B");
    remove_by_ptr(&list, to_remove);
    ASSERT_STREQ(list.head->data, "A");
    ASSERT_EQ(list.head, list.tail);
    ASSERT_EQ(list.head->link, (uintptr_t)nullptr);
}

TEST_F(XORListTest, RemoveByPtr_TailElement_ReturnValidVal_no12) {
    const char* items[] = { "A", "B" };
    setup_list(&list, items, 2);
    Node* to_remove = find(&list, "A");
    remove_by_ptr(&list, to_remove);
    ASSERT_STREQ(list.head->data, "B");
    ASSERT_EQ(list.head, list.tail);
    ASSERT_EQ(list.head->link, (uintptr_t)nullptr);
}

// Тесты iterate()
TEST_F(XORListTest, Iterate_EmptyList_NoOutput_no13) {
    testing::internal::CaptureStdout();
    iterate(&list);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE(output.empty());
}

TEST_F(XORListTest, Iterate_SingleElement_PrintOneLine_no14) {
    insert(&list, "One");
    testing::internal::CaptureStdout();
    iterate(&list);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, std::string("One\n"));
}

TEST_F(XORListTest, Iterate_MultipleElements_CorrectOrder_no15) {
    const char* items[] = { "A", "B", "C" };
    setup_list(&list, items, 3);
    testing::internal::CaptureStdout();
    iterate(&list);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, std::string("C\nB\nA\n"));
}

TEST_F(XORListTest, Iterate_AfterRemoveByKey_SkipRemoved_no16) {
    const char* items[] = { "A", "B", "C" };
    setup_list(&list, items, 3);
    remove_by_key(&list, "B");
    testing::internal::CaptureStdout();
    iterate(&list);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, std::string("C\nA\n"));
}