#include <gtest/gtest.h>
extern "C" {
#include "list.h"
}

// Suite: Basic operations
class SortedListTest : public ::testing::Test {
protected:
    SortedList list;
    void SetUp() override {
        create_list(&list);
    }
    void TearDown() override {
        free_list(&list);
    }
};

TEST_F(SortedListTest, InitList_no1) {
    ASSERT_EQ(list.head, nullptr);
}

TEST_F(SortedListTest, InsertSingle_no2) {
    int rc = insert_sorted(&list, "apple", 10);
    ASSERT_EQ(rc, 0);
    ASSERT_NE(list.head, nullptr);
    EXPECT_STREQ(list.head->word, "apple");
    EXPECT_EQ(list.head->key, 10);
    EXPECT_EQ(list.head->next, nullptr);
}

TEST_F(SortedListTest, FindExisting_no3) {
    insert_sorted(&list, "a", 5);
    insert_sorted(&list, "b", 15);
    const char* w = find_by_key(&list, 15);
    ASSERT_NE(w, nullptr);
    EXPECT_STREQ(w, "b");
}

TEST_F(SortedListTest, FindNonExisting_no4) {
    insert_sorted(&list, "a", 5);
    EXPECT_EQ(find_by_key(&list, 7), nullptr);
    EXPECT_EQ(find_by_key(&list, 100), nullptr);
}

TEST_F(SortedListTest, InsertMaintainsOrder_no5) {
    insert_sorted(&list, "b", 20);
    insert_sorted(&list, "a", 10);
    insert_sorted(&list, "c", 30);
    // expected order: a(10) -> b(20) -> c(30)
    Node* cur = list.head;
    ASSERT_NE(cur, nullptr);
    EXPECT_STREQ(cur->word, "a");
    EXPECT_EQ(cur->key, 10);
    cur = cur->next;
    ASSERT_NE(cur, nullptr);
    EXPECT_STREQ(cur->word, "b");
    EXPECT_EQ(cur->key, 20);
    cur = cur->next;
    ASSERT_NE(cur, nullptr);
    EXPECT_STREQ(cur->word, "c");
    EXPECT_EQ(cur->key, 30);
    EXPECT_EQ(cur->next, nullptr);
}

TEST_F(SortedListTest, InsertDuplicate_no6) {
    int rc1 = insert_sorted(&list, "x", 5);
    ASSERT_EQ(rc1, 0);
    int rc2 = insert_sorted(&list, "y", 5);
    EXPECT_EQ(rc2, 1); // duplicate key
    // ensure list still has only first node
    ASSERT_NE(list.head, nullptr);
    EXPECT_STREQ(list.head->word, "x");
    EXPECT_EQ(list.head->next, nullptr);
}

TEST_F(SortedListTest, InsertAtHead_no7) {
    insert_sorted(&list, "m", 50);
    insert_sorted(&list, "h", 10); // should become head
    ASSERT_NE(list.head, nullptr);
    EXPECT_EQ(list.head->key, 10);
    EXPECT_STREQ(list.head->word, "h");
}

TEST_F(SortedListTest, InsertAtTail_no8) {
    insert_sorted(&list, "start", 1);
    insert_sorted(&list, "end", 1000);
    Node* cur = list.head;
    while (cur->next) cur = cur->next;
    EXPECT_EQ(cur->key, 1000);
    EXPECT_STREQ(cur->word, "end");
}

TEST_F(SortedListTest, InsertFromLineGood_no9) {
    int rc = insert_from_line(&list, "hello 42");
    EXPECT_EQ(rc, 0);
    const char* w = find_by_key(&list, 42);
    ASSERT_NE(w, nullptr);
    EXPECT_STREQ(w, "hello");
}

TEST_F(SortedListTest, InsertFromLineBad_no10) {
    int rc = insert_from_line(&list, "bad_line_without_key");
    EXPECT_EQ(rc, -1);
    EXPECT_EQ(list.head, nullptr);
}

TEST_F(SortedListTest, ManyInsertMaintainOrder_no11) {
    // insert in descending keys
    for (int k = 100; k >= 0; k -= 10) {
        char buf[32];
        snprintf(buf, sizeof(buf), "w%d", k);
        int rc = insert_sorted(&list, buf, k);
        ASSERT_EQ(rc, 0);
    }
    // verify ascending order
    int expect = 0;
    Node* cur = list.head;
    while (cur) {
        EXPECT_EQ(cur->key, expect);
        expect += 10;
        cur = cur->next;
    }
    EXPECT_EQ(expect, 110); // last checked was 100 -> expect = 110
}

TEST_F(SortedListTest, FreeList_no12) {
    insert_sorted(&list, "one", 1);
    insert_sorted(&list, "two", 2);
    free_list(&list);
    EXPECT_EQ(list.head, nullptr);
    // free again should be safe
    free_list(&list);
    EXPECT_EQ(list.head, nullptr);
}