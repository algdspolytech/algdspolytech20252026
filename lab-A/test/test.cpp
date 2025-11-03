#include <gtest/gtest.h>
#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS

extern "C" {
#include "main.h"
}

TEST(LinkedListTest, CreateNode_no1) {
	Node* n = createNode("apple", 10);
	ASSERT_NE(n, nullptr);
	EXPECT_STREQ(n->word, "apple");
	EXPECT_EQ(n->key, 10);
	EXPECT_EQ(n->next, nullptr);
	freeList(n);
}

TEST(LinkedListTest, InsertIntoEmpty_no2) {
	Node* head = nullptr;
	head = insertSorted(head, "a", 5);
	EXPECT_EQ(head->key, 5);
	freeList(head);
}

TEST(LinkedListTest, InsertToHead_no3) {
	Node* head = nullptr;
	head = insertSorted(head, "b", 20);
	head = insertSorted(head, "a", 10);
	EXPECT_EQ(head->key, 10);
	freeList(head);
}

TEST(LinkedListTest, InsertToEnd_no4) {
	Node* head = nullptr;
	head = insertSorted(head, "a", 10);
	head = insertSorted(head, "b", 20);
	EXPECT_EQ(head->next->key, 20);
	freeList(head);
}

TEST(LinkedListTest, InsertDuplicate_no5) {
	Node* head = nullptr;
	head = insertSorted(head, "a", 10);
	head = insertSorted(head, "b", 10);
	EXPECT_EQ(head->next, nullptr);
	freeList(head);
}

TEST(LinkedListTest, FindExisting_no6) {
	Node* head = nullptr;
	head = insertSorted(head, "a", 10);
	head = insertSorted(head, "b", 20);
	testing::internal::CaptureStdout();
	findWord(head, 20);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("Найдено слово: b"), std::string::npos);
	freeList(head);
}

TEST(LinkedListTest, FindMissing_no7) {
	Node* head = nullptr;
	head = insertSorted(head, "a", 10);
	testing::internal::CaptureStdout();
	findWord(head, 5);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_NE(output.find("не найдено"), std::string::npos);
	freeList(head);
}

TEST(LinkedListTest, NegativeKeys_no8) {
	Node* head = nullptr;
	head = insertSorted(head, "minus", -5);
	head = insertSorted(head, "zero", 0);
	EXPECT_EQ(head->key, -5);
	EXPECT_EQ(head->next->key, 0);
	freeList(head);
}

TEST(LinkedListTest, FreeEmpty_no9) {
	Node* head = nullptr;
	freeList(head);
	SUCCEED();
}

TEST(LinkedListTest, InsertMiddle_no10) {
	Node* head = nullptr;
	head = insertSorted(head, "a", 10);
	head = insertSorted(head, "c", 30);
	head = insertSorted(head, "b", 20);
	EXPECT_EQ(head->next->key, 20);
	freeList(head);
}
