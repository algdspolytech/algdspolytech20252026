#include <gtest/gtest.h>
#include <cstring>
#include <locale.h>
// ¬ключаем C заголовочный файл
extern "C" {
#include "Lab1.h"
}
int main(int argc, char** argv) {
    setlocale(LC_ALL, "en_US.UTF-8");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// create_node tests
TEST(create_node_ValidData_ReturnValidNode_no1, Test) {
    ListNode* node = create_node("test");
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->data, "test");
    EXPECT_EQ(node->next, nullptr);
    free_list(node);
}

TEST(create_node_NullData_ReturnNull_no2, Test) {
    ListNode* node = create_node(nullptr);
    EXPECT_EQ(node, nullptr);
}

// push_front tests
TEST(push_front_ValidData_AddToFront_no3, Test) {
    ListNode* head = nullptr;
    push_front(&head, "second");
    push_front(&head, "first");

    EXPECT_STREQ(head->data, "first");
    EXPECT_STREQ(head->next->data, "second");
    EXPECT_EQ(head->next->next, nullptr);

    free_list(head);
}

TEST(push_front_NullParams_NoChange_no4, Test) {
    ListNode* head = nullptr;
    push_front(nullptr, "test");
    push_front(&head, nullptr);
    EXPECT_EQ(head, nullptr);
}

// push_back tests
TEST(push_back_ValidData_AddToEnd_no5, Test) {
    ListNode* head = nullptr;
    push_back(&head, "first");
    push_back(&head, "second");

    EXPECT_STREQ(head->data, "first");
    EXPECT_STREQ(head->next->data, "second");
    EXPECT_EQ(head->next->next, nullptr);

    free_list(head);
}

TEST(push_back_NullParams_NoChange_no6, Test) {
    ListNode* head = nullptr;
    push_back(nullptr, "test");
    push_back(&head, nullptr);
    EXPECT_EQ(head, nullptr);
}

// list_length tests
TEST(list_length_EmptyList_ReturnZero_no7, Test) {
    ListNode* head = nullptr;
    EXPECT_EQ(list_length(head), 0);
}

TEST(list_length_ThreeElements_ReturnThree_no8, Test) {
    ListNode* head = nullptr;
    push_back(&head, "one");
    push_back(&head, "two");
    push_back(&head, "three");

    EXPECT_EQ(list_length(head), 3);
    free_list(head);
}

// get_node_at tests
TEST(get_node_at_ValidIndex_ReturnNode_no9, Test) {
    ListNode* head = nullptr;
    push_back(&head, "zero");
    push_back(&head, "one");
    push_back(&head, "two");

    ListNode* node0 = get_node_at(head, 0);
    ListNode* node1 = get_node_at(head, 1);
    ListNode* node2 = get_node_at(head, 2);

    EXPECT_STREQ(node0->data, "zero");
    EXPECT_STREQ(node1->data, "one");
    EXPECT_STREQ(node2->data, "two");

    free_list(head);
}

TEST(get_node_at_OutOfRange_ReturnNull_no10, Test) {
    ListNode* head = nullptr;
    push_back(&head, "test");

    EXPECT_EQ(get_node_at(head, 1), nullptr);
    EXPECT_EQ(get_node_at(head, 100), nullptr);

    free_list(head);
}

// get_data_at tests
TEST(get_data_at_ValidIndex_ReturnData_no11, Test) {
    ListNode* head = nullptr;
    push_back(&head, "first");
    push_back(&head, "second");

    EXPECT_STREQ(get_data_at(head, 0), "first");
    EXPECT_STREQ(get_data_at(head, 1), "second");

    free_list(head);
}

// front_back_split tests
TEST(front_back_split_FourElements_SplitHalf_no12, Test) {
    ListNode* head = nullptr;
    push_back(&head, "a");
    push_back(&head, "b");
    push_back(&head, "c");
    push_back(&head, "d");

    ListNode* front = nullptr;
    ListNode* back = nullptr;
    front_back_split(head, &front, &back);

    EXPECT_EQ(list_length(front), 2);
    EXPECT_EQ(list_length(back), 2);
    EXPECT_STREQ(front->data, "a");
    EXPECT_STREQ(back->data, "c");

    free_list(front);
    free_list(back);
}

TEST(front_back_split_SingleElement_BackNull_no13, Test) {
    ListNode* head = create_node("word");
    ListNode* front = nullptr;
    ListNode* back = nullptr;

    front_back_split(head, &front, &back);

    EXPECT_STREQ(front->data, "word");
    EXPECT_EQ(back, nullptr);

    free_list(front);
}

// sorted_merge tests
TEST(sorted_merge_TwoLists_ReturnMerged_no14, Test) {
    ListNode* a = nullptr;
    push_back(&a, "apple");
    push_back(&a, "cherry");

    ListNode* b = nullptr;
    push_back(&b, "berry");
    push_back(&b, "data");

    ListNode* merged = sorted_merge(a, b);

    EXPECT_STREQ(merged->data, "apple");
    EXPECT_STREQ(merged->next->data, "berry");
    EXPECT_STREQ(merged->next->next->data, "cherry");
    EXPECT_STREQ(merged->next->next->next->data, "data");

    free_list(merged);
}

TEST(sorted_merge_EmptyList_ReturnOtherList_no15, Test) {
    ListNode* a = nullptr;
    ListNode* b = create_node("empty");

    ListNode* merged = sorted_merge(a, b);
    EXPECT_STREQ(merged->data, "empty");

    free_list(merged);
}

// merge_sort tests
TEST(merge_sort_UnsortedList_ReturnSorted_no16, Test) {
    ListNode* head = nullptr;
    push_back(&head, "delta");
    push_back(&head, "alpha");
    push_back(&head, "gamma");
    push_back(&head, "beta");

    head = merge_sort(head);

    EXPECT_TRUE(is_sorted(head));
    EXPECT_STREQ(head->data, "alpha");
    EXPECT_STREQ(head->next->data, "beta");
    EXPECT_STREQ(head->next->next->data, "delta");
    EXPECT_STREQ(head->next->next->next->data, "gamma");

    free_list(head);
}

TEST(merge_sort_EmptyList_ReturnNull_no17, Test) {
    ListNode* head = nullptr;
    head = merge_sort(head);
    EXPECT_EQ(head, nullptr);
}

TEST(merge_sort_SingleElement_ReturnSame_no18, Test) {
    ListNode* head = create_node("one");
    head = merge_sort(head);

    EXPECT_STREQ(head->data, "one");
    EXPECT_EQ(head->next, nullptr);

    free_list(head);
}

TEST(merge_sort_AlreadySorted_ReturnSorted_no19, Test) {
    ListNode* head = nullptr;
    push_back(&head, "a");
    push_back(&head, "b");
    push_back(&head, "c");

    head = merge_sort(head);

    EXPECT_TRUE(is_sorted(head));
    EXPECT_STREQ(head->data, "a");
    EXPECT_STREQ(head->next->data, "b");
    EXPECT_STREQ(head->next->next->data, "c");

    free_list(head);
}

// is_sorted tests
TEST(is_sorted_SortedList_ReturnTrue_no20, Test) {
    ListNode* head = nullptr;
    push_back(&head, "a");
    push_back(&head, "b");
    push_back(&head, "c");

    EXPECT_TRUE(is_sorted(head));
    free_list(head);
}

TEST(is_sorted_UnsortedList_ReturnFalse_no21, Test) {
    ListNode* head = nullptr;
    push_back(&head, "c");
    push_back(&head, "a");
    push_back(&head, "b");

    EXPECT_FALSE(is_sorted(head));
    free_list(head);
}

TEST(is_sorted_EmptyList_ReturnTrue_no22, Test) {
    ListNode* head = nullptr;
    EXPECT_TRUE(is_sorted(head));
}

// Special cases tests
TEST(merge_sort_DuplicateValues_ReturnSorted_no23, Test) {
    ListNode* head = nullptr;
    push_back(&head, "table");
    push_back(&head, "table");
    push_back(&head, "bank");
    push_back(&head, "apple");

    head = merge_sort(head);

    EXPECT_TRUE(is_sorted(head));
    ListNode* current = head;
    EXPECT_STREQ(current->data, "apple");
    current = current->next;
    EXPECT_STREQ(current->data, "bank");
    current = current->next;
    EXPECT_STREQ(current->data, "table");
    current = current->next;
    EXPECT_STREQ(current->data, "table");

    free_list(head);
}

TEST(merge_sort_ReverseSorted_ReturnSorted_no24, Test) {
    ListNode* head = nullptr;
    push_back(&head, "C");
    push_back(&head, "B");
    push_back(&head, "A");

    head = merge_sort(head);

    EXPECT_TRUE(is_sorted(head));
    EXPECT_STREQ(head->data, "A");
    EXPECT_STREQ(head->next->data, "B");
    EXPECT_STREQ(head->next->next->data, "C");

    free_list(head);
}