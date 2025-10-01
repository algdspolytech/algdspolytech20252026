#include "pch.h"
#include<vector>

//#include "gtest/gtest.h"

extern "C" {
#include"Node.h"
}

void inorderTraversal(pNode t, std::vector<int>& keys) { // делает обход дерева слева направо
    if (!t) return;
    inorderTraversal(t->l, keys);
    keys.push_back(t->key);
    inorderTraversal(t->r, keys);
}

bool checkHeapProperty(pNode t) { // проверяет heap свойство декартвово дерева
    if (!t) return true;
    if (t->l && t->priority > t->l->priority) return false;
    if (t->r && t->priority > t->r->priority) return false;
    return checkHeapProperty(t->l) && checkHeapProperty(t->r);
}

// проверяет создание узла
TEST(TreapTest, CreateNode) { 
    pNode node = createNode(10, 5);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->key, 10);
    EXPECT_EQ(node->priority, 5);
    EXPECT_EQ(node->l, nullptr);
    EXPECT_EQ(node->r, nullptr);
    freeTree(node);
}

// Тест вставки одного узла
TEST(TreapTest, AddSingleNode) {
    pNode root = nullptr;
    add(&root, createNode(20, 15));
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->key, 20);
    EXPECT_EQ(root->l, nullptr);
    EXPECT_EQ(root->r, nullptr);
    freeTree(root);
}

// Тест вставки нескольких узлов
TEST(TreapTest, AddMultipleNodes) {
    pNode root = nullptr;
    add(&root, createNode(10, 30));
    add(&root, createNode(20, 20));
    add(&root, createNode(5, 25));

    std::vector<int> keys;
    inorderTraversal(root, keys);

    for (size_t i = 1; i < keys.size(); ++i)
        EXPECT_LT(keys[i - 1], keys[i]);

    EXPECT_TRUE(checkHeapProperty(root));

    freeTree(root);
}

// Тест удаления узла
TEST(TreapTest, RemoveNode) {
    pNode root = nullptr;
    add(&root, createNode(10, 30));
    add(&root, createNode(20, 20));
    add(&root, createNode(5, 25));

    removeAt(&root, 20);
    std::vector<int> keys;
    inorderTraversal(root, keys);

    for (int k : keys) EXPECT_NE(k, 20);

    EXPECT_TRUE(checkHeapProperty(root));

    freeTree(root);
}

// Тест split и merge
TEST(TreapTest, SplitAndMerge) {
    pNode root = nullptr;
    add(&root, createNode(10, 30));
    add(&root, createNode(20, 20));
    add(&root, createNode(5, 25));

    pNode l = nullptr, r = nullptr;
    split(root, 10, &l, &r);

    std::vector<int> leftKeys, rightKeys;
    inorderTraversal(l, leftKeys);
    inorderTraversal(r, rightKeys);

    for (int k : leftKeys) EXPECT_LE(k, 10);
    for (int k : rightKeys) EXPECT_GT(k, 10);

    pNode merged = nullptr;
    merge(&merged, l, r);

    std::vector<int> mergedKeys;
    inorderTraversal(merged, mergedKeys);
    for (size_t i = 1; i < mergedKeys.size(); ++i)
        EXPECT_LT(mergedKeys[i - 1], mergedKeys[i]);
    EXPECT_TRUE(checkHeapProperty(merged));

    freeTree(merged);
}




