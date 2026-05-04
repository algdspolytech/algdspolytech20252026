#include "pch.h"
#define DEFAULT_TREE_SIZE 5

extern "C" {
	#include "../LabE/surce.c"
}

TEST(createTreeTest, createBalancedElementaryTreeNegativeSizeExit_no1) {
	EXPECT_EXIT(createBalancedElementaryTree(-1),
		::testing::ExitedWithCode(INCORECRT_TREE_SIZE),
		"");
}

TEST(createTreeTest, createBalancedElementaryTreeZeroSizeReturnNULL_no2) {
	EXPECT_FALSE(createBalancedElementaryTree(0));
}

TEST(createTreeTest, createDisbalancedElementaryTreeNegativeSizeExit_no3) {
	EXPECT_EXIT(createDisbalancedElementaryTree(-1),
		::testing::ExitedWithCode(INCORECRT_TREE_SIZE), "");
}

TEST(createTreeTest, createDisbalancedElementaryTreeZeroSizeReturnNULL_no4) {
	EXPECT_FALSE(createDisbalancedElementaryTree(0));
}

TEST(createTreeTest, createMixedTreeNegativeSizeExit_no5) {
	EXPECT_EXIT(createMixedTree(-1),
		::testing::ExitedWithCode(INCORECRT_TREE_SIZE), "");
}

TEST(createTreeTest, createMixedTreeZeroSizeReturnNULL_no6) {
	EXPECT_FALSE(createMixedTree(0));
}

TEST(treeFunctionsTest, getMaxElementNullPtrExit_no7) {
	EXPECT_EXIT(getMaxElement(NULL),
		::testing::ExitedWithCode(TREE_PTR_IS_NULL), "");
}

TEST(treeFunctionsTest, getMaxElementElementaryTreeReturn1_no8) {
	NodeT* tree = createMixedTree(DEFAULT_TREE_SIZE);
	tree->data = 0;

	int expectReturnValue = 1;
	EXPECT_EQ(getMaxElement(tree), expectReturnValue);

	freeTree(tree);
}

TEST(treeFunctionsTest, getHeightNullReturnZero_no9) {
	EXPECT_EQ(getHeight(NULL), 0);
}

TEST(treeFunctionsTest, getHeightLeafReturn1_no10) {
	NodeT* tree = createLeaf(1);
	
	EXPECT_EQ(getHeight(tree), 1);

	freeTree(tree);
}