#include "pch.h"
#include "DoublyLinkedList.h"
#include <gtest/gtest.h>
#include <cstring>


TEST(CreateNode_ValidString_ReturnValidNode_no1) {

    const char* test_data = "test_string";

 
    linkedListNode* result = createNode(test_data);


    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "test_string");
    EXPECT_EQ(result->next, nullptr);
    EXPECT_EQ(result->prev, nullptr);

    free(result->data);
    free(result);
}

TEST(CreateNode_EmptyString_ReturnValidNode_no2) {

    const char* test_data = "";


    linkedListNode* result = createNode(test_data);


    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "");
    EXPECT_EQ(result->next, nullptr);
    EXPECT_EQ(result->prev, nullptr);


    free(result->data);
    free(result);
}

TEST(CreateNode_LongString_ReturnValidNode_no3) {

    const char* test_data = "very_long_string_abcdefghijklmnopqrstuvwxyz";


    linkedListNode* result = createNode(test_data);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "very_long_string_abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(result->next, nullptr);
    EXPECT_EQ(result->prev, nullptr);

    free(result->data);
    free(result);
}


TEST(AppendNode_EmptyList_ReturnNewNode_no4) {
    // Arrange
    linkedListNode* head = nullptr;
    const char* test_data = "first_element";


    linkedListNode* result = appendNode(head, test_data);


    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "first_element");
    EXPECT_EQ(result->next, nullptr);
    EXPECT_EQ(result->prev, nullptr);


    freeList(result);
}

TEST(AppendNode_SingleElementList_ReturnHeadWithNewNode_no5) {
    linkedListNode* head = createNode("first");


    linkedListNode* result = appendNode(head, "second");


    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "first");
    ASSERT_NE(result->next, nullptr);
    EXPECT_STREQ(result->next->data, "second");
    EXPECT_EQ(result->next->prev, result);
    EXPECT_EQ(result->next->next, nullptr);

    freeList(result);
}

TEST(AppendNode_MultipleElements_ReturnHeadWithCorrectLinks_no6) {

    linkedListNode* head = createNode("first");
    head = appendNode(head, "second");


    linkedListNode* result = appendNode(head, "third");


    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "first");
    ASSERT_NE(result->next, nullptr);
    EXPECT_STREQ(result->next->data, "second");
    ASSERT_NE(result->next->next, nullptr);
    EXPECT_STREQ(result->next->next->data, "third");
    EXPECT_EQ(result->next->next->prev, result->next);
    EXPECT_EQ(result->next->next->next, nullptr);


    freeList(result);
}


TEST(ListLength_EmptyList_ReturnZero_no7) {

    linkedListNode* head = nullptr;


    int result = listLength(head);


    EXPECT_EQ(result, 0);
}

TEST(ListLength_SingleElement_ReturnOne_no8) {

    linkedListNode* head = createNode("single");

    int result = listLength(head);


    EXPECT_EQ(result, 1);

    freeList(head);
}

TEST(ListLength_ThreeElements_ReturnThree_no9) {

    linkedListNode* head = createNode("first");
    head = appendNode(head, "second");
    head = appendNode(head, "third");

    int result = listLength(head);


    EXPECT_EQ(result, 3);


    freeList(head);
}


TEST(BubbleSort_EmptyList_ReturnNull_no10) {

    linkedListNode* head = nullptr;

    linkedListNode* result = bubbleSort(head);


    EXPECT_EQ(result, nullptr);
}

TEST(BubbleSort_SingleElement_ReturnSameList_no11) {
    linkedListNode* head = createNode("single");

    linkedListNode* result = bubbleSort(head);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "single");
    EXPECT_EQ(result->next, nullptr);
    EXPECT_EQ(result->prev, nullptr);

    freeList(result);
}

TEST(BubbleSort_TwoElementsSorted_ReturnSameOrder_no12) {
    linkedListNode* head = createNode("apple");
    head = appendNode(head, "banana");

    linkedListNode* result = bubbleSort(head);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "apple");
    ASSERT_NE(result->next, nullptr);
    EXPECT_STREQ(result->next->data, "banana");
    EXPECT_EQ(result->next->prev, result);

    freeList(result);
}

TEST(BubbleSort_TwoElementsUnsorted_ReturnSortedOrder_no13) {
    linkedListNode* head = createNode("banana");
    head = appendNode(head, "apple");

    linkedListNode* result = bubbleSort(head);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "apple");
    ASSERT_NE(result->next, nullptr);
    EXPECT_STREQ(result->next->data, "banana");
    EXPECT_EQ(result->next->prev, result);

    freeList(result);
}

TEST(BubbleSort_ThreeElementsRandom_ReturnSortedOrder_no14) {
    linkedListNode* head = createNode("cherry");
    head = appendNode(head, "apple");
    head = appendNode(head, "banana");


    linkedListNode* result = bubbleSort(head);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "apple");
    ASSERT_NE(result->next, nullptr);
    EXPECT_STREQ(result->next->data, "banana");
    ASSERT_NE(result->next->next, nullptr);
    EXPECT_STREQ(result->next->next->data, "cherry");
    EXPECT_EQ(result->next->prev, result);
    EXPECT_EQ(result->next->next->prev, result->next);

    freeList(result);
}

TEST(BubbleSort_DuplicateElements_ReturnSortedOrder_no15) {

    linkedListNode* head = createNode("beta");
    head = appendNode(head, "alpha");
    head = appendNode(head, "beta");
    head = appendNode(head, "gamma");


    linkedListNode* result = bubbleSort(head);


    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "alpha");
    ASSERT_NE(result->next, nullptr);
    EXPECT_STREQ(result->next->data, "beta");
    ASSERT_NE(result->next->next, nullptr);
    EXPECT_STREQ(result->next->next->data, "beta");
    ASSERT_NE(result->next->next->next, nullptr);
    EXPECT_STREQ(result->next->next->next->data, "gamma");

    freeList(result);
}

TEST(BubbleSort_ReverseSorted_ReturnSortedOrder_no16) {

    linkedListNode* head = createNode("delta");
    head = appendNode(head, "charlie");
    head = appendNode(head, "bravo");
    head = appendNode(head, "alpha");


    linkedListNode* result = bubbleSort(head);


    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "alpha");
    ASSERT_NE(result->next, nullptr);
    EXPECT_STREQ(result->next->data, "bravo");
    ASSERT_NE(result->next->next, nullptr);
    EXPECT_STREQ(result->next->next->data, "charlie");
    ASSERT_NE(result->next->next->next, nullptr);
    EXPECT_STREQ(result->next->next->next->data, "delta");


    freeList(result);
}

TEST(BubbleSort_SpecialCharacters_ReturnSortedOrder_no17) {

    linkedListNode* head = createNode("123");
    head = appendNode(head, "!@#");
    head = appendNode(head, "abc");

    linkedListNode* result = bubbleSort(head);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->data, "!@#");
    ASSERT_NE(result->next, nullptr);
    EXPECT_STREQ(result->next->data, "123");
    ASSERT_NE(result->next->next, nullptr);
    EXPECT_STREQ(result->next->next->data, "abc");

    freeList(result);
}

TEST(PrintList_EmptyList_PrintNull_no18) {

    linkedListNode* head = nullptr;

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " -> NULL\n");
}

TEST(PrintList_SingleElement_PrintCorrectFormat_no19) {

    linkedListNode* head = createNode("test");


    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "test -> NULL\n");

    freeList(head);
}

TEST(PrintList_MultipleElements_PrintCorrectFormat_no20) {
    linkedListNode* head = createNode("first");
    head = appendNode(head, "second");
    head = appendNode(head, "third");

    testing::internal::CaptureStdout();
    printList(head);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "first <-> second <-> third -> NULL\n");

    freeList(head);
}



TEST(FreeList_EmptyList_NoCrash_no21) {

    linkedListNode* head = nullptr;

    EXPECT_NO_FATAL_FAILURE(freeList(head));
}

TEST(FreeList_SingleElement_NoCrash_no22) {

    linkedListNode* head = createNode("test");

    EXPECT_NO_FATAL_FAILURE(freeList(head));
}

TEST(FreeList_MultipleElements_NoCrash_no23) {

    linkedListNode* head = createNode("first");
    head = appendNode(head, "second");
    head = appendNode(head, "third");

    EXPECT_NO_FATAL_FAILURE(freeList(head));
}