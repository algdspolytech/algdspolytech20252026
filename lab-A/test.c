#include <gtest/gtest.h>
#include "list.h"

TEST(UnrolledListTest, create_block_CreateNewBlock_ReturnsZeroSize_no1) {
    Block* block = create_block();
    ASSERT_NE(block, nullptr);
    EXPECT_EQ(block->size, 0);
    EXPECT_EQ(block->next, nullptr);
    free(block);
}

TEST(UnrolledListTest, list_insert_InsertToEmptyList_IncreasesSizeCorrectly_no2) {
    UnrolledList list = { NULL };
    list_insert(&list, 42);
    EXPECT_EQ(list_size(&list), 1);
    EXPECT_EQ(list.head->size, 1);
    EXPECT_EQ(list.head->data[0], 42);
}

TEST(UnrolledListTest, list_insert_FillFirstBlock_CreatesSecondBlock_no3) {
    UnrolledList list = { NULL };
    for (int i = 1; i <= BLOCK_CAPACITY + 1; i++) {
        list_insert(&list, i * 10);
    }
    EXPECT_EQ(list_size(&list), BLOCK_CAPACITY + 1);
    EXPECT_NE(list.head->next, nullptr);
    EXPECT_EQ(list.head->size, BLOCK_CAPACITY);
    EXPECT_EQ(list.head->next->size, 1);
}

TEST(UnrolledListTest, list_size_EmptyList_ReturnsZero_no4) {
    UnrolledList list = { NULL };
    EXPECT_EQ(list_size(&list), 0);
}

TEST(UnrolledListTest, list_size_MultipleBlocks_ReturnsCorrectTotal_no5) {
    UnrolledList list = { NULL };
    for (int i = 0; i < 10; i++) {
        list_insert(&list, i);
    }
    EXPECT_EQ(list_size(&list), 10);
}

TEST(UnrolledListTest, list_find_index_ExistingElement_ReturnsCorrectIndex_no6) {
    UnrolledList list = { NULL };
    list_insert(&list, 5);
    list_insert(&list, 10);
    list_insert(&list, 15);
    list_insert(&list, 20);
    list_insert(&list, 25);
    
    EXPECT_EQ(list_find_index(&list, 15), 2);
    EXPECT_EQ(list_find_index(&list, 25), 4);
}

TEST(UnrolledListTest, list_find_index_NonExistentElement_ReturnsMinusOne_no7) {
    UnrolledList list = { NULL };
    list_insert(&list, 1);
    list_insert(&list, 2);
    list_insert(&list, 3);
    
    EXPECT_EQ(list_find_index(&list, 99), -1);
}

TEST(UnrolledListTest, list_get_at_ValidPositions_ReturnsCorrectValues_no8) {
    UnrolledList list = { NULL };
    for (int i = 0; i < 7; i++) {
        list_insert(&list, i * 3);
    }
    
    EXPECT_EQ(list_get_at(&list, 0), 0);
    EXPECT_EQ(list_get_at(&list, 3), 9);
    EXPECT_EQ(list_get_at(&list, 6), 18);
}

TEST(UnrolledListTest, list_get_at_InvalidPosition_ReturnsMinusOne_no9) {
    UnrolledList list = { NULL };
    list_insert(&list, 1);
    list_insert(&list, 2);
    
    EXPECT_EQ(list_get_at(&list, -1), -1);
    EXPECT_EQ(list_get_at(&list, 2), -1);
    EXPECT_EQ(list_get_at(&list, 100), -1);
}

TEST(UnrolledListTest, list_remove_at_RemoveFromBeginning_UpdatesStructureCorrectly_no10) {
    UnrolledList list = { NULL };
    for (int i = 0; i < 6; i++) {
        list_insert(&list, i);
    }
    
    EXPECT_EQ(list_remove_at(&list, 0), 0);
    EXPECT_EQ(list_size(&list), 5);
    EXPECT_EQ(list_get_at(&list, 0), 1);
}

TEST(UnrolledListTest, list_remove_at_RemoveFromMiddle_ShiftsElements_no11) {
    UnrolledList list = { NULL };
    list_insert(&list, 100);
    list_insert(&list, 200);
    list_insert(&list, 300);
    list_insert(&list, 400);
    list_insert(&list, 500);
    
    EXPECT_EQ(list_remove_at(&list, 2), 300);
    EXPECT_EQ(list_size(&list), 4);
    EXPECT_EQ(list_get_at(&list, 2), 400);
}

TEST(UnrolledListTest, list_remove_at_RemoveLastElement_EmptyBlockRemoved_no12) {
    UnrolledList list = { NULL };
    for (int i = 1; i <= BLOCK_CAPACITY + 1; i++) {
        list_insert(&list, i);
    }
    
    EXPECT_EQ(list_remove_at(&list, BLOCK_CAPACITY), BLOCK_CAPACITY + 1);
    EXPECT_EQ(list_size(&list), BLOCK_CAPACITY);
    EXPECT_EQ(list.head->next, nullptr);
}

TEST(UnrolledListTest, list_remove_at_InvalidPosition_ReturnsMinusOne_no13) {
    UnrolledList list = { NULL };
    list_insert(&list, 1);
    
    EXPECT_EQ(list_remove_at(&list, -1), -1);
    EXPECT_EQ(list_remove_at(&list, 1), -1);
}

TEST(UnrolledListTest, list_get_next_ValidPosition_ReturnsNextElement_no14) {
    UnrolledList list = { NULL };
    list_insert(&list, 10);
    list_insert(&list, 20);
    list_insert(&list, 30);
    list_insert(&list, 40);
    list_insert(&list, 50);
    
    EXPECT_EQ(list_get_next(&list, 0), 20);
    EXPECT_EQ(list_get_next(&list, 3), 50);
}

TEST(UnrolledListTest, list_get_next_LastPosition_ReturnsMinusOne_no15) {
    UnrolledList list = { NULL };
    list_insert(&list, 1);
    list_insert(&list, 2);
    list_insert(&list, 3);
    
    EXPECT_EQ(list_get_next(&list, 2), -1);
    EXPECT_EQ(list_get_next(&list, 3), -1);
}

TEST(UnrolledListTest, list_operations_ComplexScenario_CorrectBehavior_no16) {
    UnrolledList list = { NULL };
    
    for (int i = 0; i < 12; i++) {
        list_insert(&list, i * 2);
    }
    
    EXPECT_EQ(list_size(&list), 12);
    
    list_remove_at(&list, 5);
    EXPECT_EQ(list_size(&list), 11);
    
    EXPECT_EQ(list_find_index(&list, 12), 5);
    EXPECT_EQ(list_get_at(&list, 7), 14);
    EXPECT_EQ(list_get_next(&list, 7), 16);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
