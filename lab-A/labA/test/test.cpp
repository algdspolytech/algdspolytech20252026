#define _CRT_SECURE_NO_WARNINGS
#include "gtest/gtest.h"
#include "Header.h"
TEST(LinkedListTest, InsertWord_EmptyList_HeadPointsToNewNode) {
    struct Item* head = NULL;
    InsertWord(&head, "test");
    EXPECT_STREQ(head->Word, "test");
    FreeList(head);
}

TEST(LinkedListTest, InsertWord_SingleWord_CorrectOrder) {
    struct Item* head = NULL;
    InsertWord(&head, "banana");
    InsertWord(&head, "apple");
    EXPECT_STREQ(head->Word, "apple");
    EXPECT_STREQ(head->NextItem->Word, "banana");
    FreeList(head);
}

TEST(LinkedListTest, CompareWords_DifferentLength_ShorterFirst) {
    int result = compareWords("cat", "apple");
    EXPECT_LT(result, 0);
}

TEST(LinkedListTest, CompareWords_SameLength_AlphabeticalOrder) {
    int result = compareWords("apple", "banana");
    EXPECT_LT(result, 0);
}

TEST(LinkedListTest, CompareWords_EqualWords_ReturnsZero) {
    int result = compareWords("test", "test");
    EXPECT_EQ(result, 0);
}

TEST(LinkedListTest, PrintLongWords_FilterCorrectly) {
    struct Item* head = NULL;
    InsertWord(&head, "a");
    InsertWord(&head, "abc");
    InsertWord(&head, "abcd");
    testing::internal::CaptureStdout();
    PrintLongWords(head, 2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("abc") != std::string::npos);
    EXPECT_TRUE(output.find("abcd") != std::string::npos);
    FreeList(head);
}

TEST(LinkedListTest, PrintWordsByLength_ExistingLength) {
    struct Item* head = NULL;
    InsertWord(&head, "cat");
    InsertWord(&head, "dog");
    testing::internal::CaptureStdout();
    PrintWordsByLength(head, 3);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("cat") != std::string::npos);
    EXPECT_TRUE(output.find("dog") != std::string::npos);
    FreeList(head);
}

TEST(LinkedListTest, PrintWordsByLength_NonExistingLength) {
    struct Item* head = NULL;
    InsertWord(&head, "apple");
    testing::internal::CaptureStdout();
    PrintWordsByLength(head, 10);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("No words") != std::string::npos);
    FreeList(head);
}

TEST(LinkedListTest, InsertWord_MultipleWords_SortedCorrectly) {
    struct Item* head = NULL;
    InsertWord(&head, "zzz");
    InsertWord(&head, "aaa");
    InsertWord(&head, "mm");
    EXPECT_STREQ(head->Word, "mm");
    EXPECT_STREQ(head->NextItem->Word, "aaa");
    EXPECT_STREQ(head->NextItem->NextItem->Word, "zzz");
    FreeList(head);
}

TEST(LinkedListTest, FreeList_MultipleNodes_NoMemoryLeaks) {
    struct Item* head = NULL;
    InsertWord(&head, "test1");
    InsertWord(&head, "test2");
    InsertWord(&head, "test3");
    FreeList(head);
    SUCCEED();
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}