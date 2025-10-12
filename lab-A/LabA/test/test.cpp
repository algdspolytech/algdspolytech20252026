#define _CRT_SECURE_NO_WARNINGS
#include "gtest/gtest.h"
#include "list.h"

TEST(UnrolledListTest, create_node_EmptyNode_returnZeroFilled_no1) {
    node* n = create_node();
    ASSERT_NE(n, nullptr);
    EXPECT_EQ(n->filled_num, 0);
    EXPECT_EQ(n->next, nullptr);
    free(n);
}

TEST(UnrolledListTest, add_to_list_AddToEmptyList_returnValidCount_no2) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    EXPECT_EQ(count_elem(&list), 1);
    EXPECT_EQ(elem_by_num(&list, 0), 1);
}

TEST(UnrolledListTest,
    add_to_list_AddElementToPartiallyFilledNode_returnValidCount_no3) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    add_to_list(&list, 2);
    add_to_list(&list, 3);
    EXPECT_EQ(count_elem(&list), 3);
    EXPECT_EQ(list.head->filled_num, 3);
}

TEST(UnrolledListTest, add_to_list_FullNode_AddToNewNode_returnValidCount_no4) {
    UnrolledList list = { NULL };
    for (int i = 0; i < 5; i++) {
        add_to_list(&list, i);
    }
    EXPECT_EQ(count_elem(&list), 5);
    EXPECT_NE(list.head->next, nullptr);
    EXPECT_EQ(list.head->next->filled_num, 1);
    EXPECT_EQ(elem_by_num(&list, 4), 4);
}

TEST(UnrolledListTest, count_elem_EmptyList_return0_no5) {
    UnrolledList list = { NULL };
    EXPECT_EQ(count_elem(&list), 0);
}

TEST(UnrolledListTest, count_elem_AfterAdd_returnValidCount_no6) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    add_to_list(&list, 2);
    add_to_list(&list, 3);
    EXPECT_EQ(count_elem(&list), 3);
}

TEST(UnrolledListTest, count_elem_AfterAddAndDelete_returnValidCount_no7) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    add_to_list(&list, 2);
    add_to_list(&list, 3);
    delete_by_num(&list, 1);
    EXPECT_EQ(count_elem(&list), 2);
}

TEST(UnrolledListTest, num_by_key_ValidKey_returnValidIndex_no8) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    add_to_list(&list, 2);
    add_to_list(&list, 3);
    EXPECT_EQ(num_by_key(&list, 2), 1);
}

TEST(UnrolledListTest, num_by_key_NotValidKey_returnMinus1_no9) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    EXPECT_EQ(num_by_key(&list, 10), -1);
}

TEST(UnrolledListTest, delete_by_num_DeleteMiddleElem_returnValidIndex_no10) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    add_to_list(&list, 2);
    add_to_list(&list, 3);
    delete_by_num(&list, 1);
    EXPECT_EQ(count_elem(&list), 2);
    EXPECT_EQ(elem_by_num(&list, 0), 1);
    EXPECT_EQ(elem_by_num(&list, 1), 3);
}

TEST(UnrolledListTest, delete_by_num_DeleteLastElem_returnValidCount_no11) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    add_to_list(&list, 2);
    delete_by_num(&list, 1);
    EXPECT_EQ(count_elem(&list), 1);
    EXPECT_EQ(elem_by_num(&list, 0), 1);
}

TEST(UnrolledListTest, next_by_num_ValidIndex_returnValidNextValue_no12) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    add_to_list(&list, 2);
    EXPECT_EQ(next_by_num(&list, 0), 2);
}

TEST(UnrolledListTest, elem_by_num_ValidIndex_returnValidValue_no13) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    add_to_list(&list, 2);
    add_to_list(&list, 3);
    EXPECT_EQ(elem_by_num(&list, 1), 2);
}

TEST(UnrolledListTest, elem_by_num_NotValidIndex_returnMinus1_no14) {
    UnrolledList list = { NULL };
    add_to_list(&list, 1);
    add_to_list(&list, 2);
    EXPECT_EQ(elem_by_num(&list, 2), -1);
}

int main(int argc, char** argv) {
    setlocale(LC_CTYPE, "Rus");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}