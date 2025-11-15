#include "gtest/gtest.h"
#include "xor_list.h" 

class XorListTestFixture : public ::testing::Test {
protected:
   
    void SetUp() override {
        cleanup_list_for_test();
    }
    
    void TearDown() override {
        cleanup_list_for_test();
    }
};


//  Тесты для xor_ptrs 

TEST_F(XorListTestFixture, NullNullReturnsZero_no1) {
    ASSERT_EQ(xor_ptrs(NULL, NULL), nullptr);
}

TEST_F(XorListTestFixture, Commutativity_no2) {
    Node p1, p2;
    ASSERT_EQ(xor_ptrs(&p1, &p2), xor_ptrs(&p2, &p1));
}

TEST_F(XorListTestFixture, Associativity_no3) {
    Node p1, p2;
    // (A^B)^B = A
    ASSERT_EQ((Node*)xor_ptrs((Node*)xor_ptrs(&p1, &p2), &p2), &p1);
}

//  Тесты для add_to_list 

TEST_F(XorListTestFixture, AddToEmptyList_no4) {
    const char* data = "test_data";
    add_to_list(data);

    ASSERT_NE(head, nullptr);
    ASSERT_EQ(head, tail);
    ASSERT_STREQ(head->data, data);
    ASSERT_EQ(head->xor_address, 0); // NULL ^ NULL
}

TEST_F(XorListTestFixture, AddToNonEmptyList_no5) {
    add_to_list("first");
    Node* firstNode = head;
    add_to_list("second");
    Node* secondNode = tail;

    ASSERT_NE(head, tail);
    ASSERT_STREQ(tail->data, "second");

   
    ASSERT_EQ((Node*)firstNode->xor_address, secondNode); 
}

//  Тесты для find_by_key 

TEST_F(XorListTestFixture, FindExisting_no6) {
    add_to_list("apple");
    add_to_list("banana");
    Node* found = find_by_key("banana");
    ASSERT_EQ(found, tail);
    ASSERT_STREQ(found->data, "banana");
}

TEST_F(XorListTestFixture, FindNonExisting_no7) {
    add_to_list("apple");
    Node* found = find_by_key("grape");
    ASSERT_EQ(found, nullptr);
}

TEST_F(XorListTestFixture, FindInEmptyList_no8) {
    Node* found = find_by_key("nothing_here");
    ASSERT_EQ(found, nullptr);
}

TEST_F(XorListTestFixture, FindFirstAndLast_no9) {
    add_to_list("first");
    add_to_list("last");
    ASSERT_EQ(find_by_key("first"), head);
    ASSERT_EQ(find_by_key("last"), tail);
}

//  Тесты для remove_by_pointer 

TEST_F(XorListTestFixture, RemoveSingleNode_no10) {
    add_to_list("only_one");
    Node* node = head;
    remove_by_pointer(node);
    ASSERT_EQ(head, nullptr);
    ASSERT_EQ(tail, nullptr);
}

TEST_F(XorListTestFixture, RemoveHead_no11) {
    add_to_list("head_val");
    add_to_list("tail_val");
    Node* old_head = head;
    remove_by_pointer(old_head);
    ASSERT_STREQ(head->data, "tail_val");
    ASSERT_EQ(head, tail); 
}

TEST_F(XorListTestFixture, RemoveTail_no12) {
    add_to_list("head_val");
    add_to_list("tail_val");
    Node* old_tail = tail;
    remove_by_pointer(old_tail);
    ASSERT_STREQ(tail->data, "head_val");
    ASSERT_EQ(head, tail);
}

TEST_F(XorListTestFixture, RemoveNull_no13) {
    add_to_list("data");
   
    ASSERT_NO_FATAL_FAILURE(remove_by_pointer(NULL)); 
    ASSERT_NE(head, nullptr);
}
