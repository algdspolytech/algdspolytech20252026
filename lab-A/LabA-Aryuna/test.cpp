#include "C:\Users\Àðþíà\source\repos\testforLabA\LabAtest\functionsfull.c"

#include <gtest/gtest.h>

class LinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        init_list(&list);
    }

    void TearDown() override {
        free_list(&list);
    }

    Linkedlist list;
};

TEST_F(LinkedListTest, CreateNodeValidString) {
    const char* test_str = "Hello";
    Node* node = create(test_str);

    ASSERT_NE(node, nullptr);
    EXPECT_NE(node->str, nullptr);
    EXPECT_STREQ(node->str, "Hello");
    EXPECT_EQ(node->l, 5);
    EXPECT_EQ(node->next, nullptr);

    free(node->str);
    free(node);
}

TEST_F(LinkedListTest, CreateNodeEmptyString) {
    Node* node = create("");

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->str, "");
    EXPECT_EQ(node->l, 0);
    EXPECT_EQ(node->next, nullptr);

    free(node->str);
    free(node);
}

TEST_F(LinkedListTest, CreateNodeLongString) {
    const char* long_str = "This is a very long string for testing purposes";
    Node* node = create(long_str);

    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->str, long_str);
    EXPECT_EQ(node->l, strlen(long_str));

    free(node->str);
    free(node);
}

TEST_F(LinkedListTest, InitList) {
    Linkedlist local_list;
    init_list(&local_list);

    EXPECT_EQ(local_list.first, nullptr);
    EXPECT_EQ(local_list.last, nullptr);
    EXPECT_EQ(local_list.totallen, 0);
}

TEST_F(LinkedListTest, AddNodeFirstNode) {
    add_node(&list, "First");

    ASSERT_NE(list.first, nullptr);
    EXPECT_EQ(list.last, list.first);
    EXPECT_STREQ(list.first->str, "First");
    EXPECT_EQ(list.first->l, 5);
    EXPECT_EQ(list.first->next, nullptr);
    EXPECT_EQ(list.totallen, 5);
}

TEST_F(LinkedListTest, AddNodeMultipleNodes) {
    add_node(&list, "First");
    add_node(&list, "Second");
    add_node(&list, "Third");

    ASSERT_NE(list.first, nullptr);
    ASSERT_NE(list.last, nullptr);

    EXPECT_STREQ(list.first->str, "First");

    Node* second = list.first->next;
    ASSERT_NE(second, nullptr);
    EXPECT_STREQ(second->str, "Second");

    EXPECT_STREQ(list.last->str, "Third");
    EXPECT_EQ(list.last->next, nullptr);

    EXPECT_EQ(list.totallen, 5 + 6 + 5);
}

TEST_F(LinkedListTest, AddNodeEmptyString) {
    add_node(&list, "");

    ASSERT_NE(list.first, nullptr);
    EXPECT_STREQ(list.first->str, "");
    EXPECT_EQ(list.first->l, 0);
    EXPECT_EQ(list.totallen, 0);
}

TEST_F(LinkedListTest, ConnectStringsEmptyList) {
    char* result = connect_strings(&list);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    free(result);
}

TEST_F(LinkedListTest, ConnectStringsSingleNode) {
    add_node(&list, "Single");
    char* result = connect_strings(&list);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Single");

    free(result);
}

TEST_F(LinkedListTest, ConnectStringsMultipleNodes) {
    add_node(&list, "Hello");
    add_node(&list, ", ");
    add_node(&list, "World");
    add_node(&list, "!");

    char* result = connect_strings(&list);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hello, World!");

    free(result);
}

TEST_F(LinkedListTest, ConnectStringsWithEmptyStrings) {
    add_node(&list, "Start");
    add_node(&list, "");
    add_node(&list, "End");

    char* result = connect_strings(&list);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "StartEnd");

    free(result);
}

TEST_F(LinkedListTest, ConnectStringsNullList) {
    char* result = connect_strings(nullptr);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");

    free(result);
}

TEST_F(LinkedListTest, FreeListEmptyList) {
    free_list(&list);

    EXPECT_EQ(list.first, nullptr);
    EXPECT_EQ(list.last, nullptr);
    EXPECT_EQ(list.totallen, 0);
}

TEST_F(LinkedListTest, FreeListNonEmptyList) {
    add_node(&list, "First");
    add_node(&list, "Second");
    add_node(&list, "Third");

    free_list(&list);

    EXPECT_EQ(list.first, nullptr);
    EXPECT_EQ(list.last, nullptr);
    EXPECT_EQ(list.totallen, 0);
}

TEST_F(LinkedListTest, MemoryLeakCheck) {
    for (int i = 0; i < 10; i++) {
        add_node(&list, "test");
        add_node(&list, "memory");
        add_node(&list, "leak");

        char* result = connect_strings(&list);
        free(result);

        free_list(&list);
        init_list(&list);
    }
}

TEST_F(LinkedListTest, ListConnections) {
    add_node(&list, "A");
    add_node(&list, "B");
    add_node(&list, "C");

    EXPECT_EQ(list.first->next->next, list.last);
    EXPECT_EQ(list.first->next->next->next, nullptr);
    EXPECT_STREQ(list.first->str, "A");
    EXPECT_STREQ(list.first->next->str, "B");
    EXPECT_STREQ(list.last->str, "C");
}

TEST_F(LinkedListTest, VeryLongString) {
    const char* long_str = "This is a very long string that should test the memory allocation and copying mechanisms properly without causing any buffer overflows or other issues.";
    add_node(&list, long_str);

    char* result = connect_strings(&list);

    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_str);
    EXPECT_EQ(list.totallen, strlen(long_str));

    free(result);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}