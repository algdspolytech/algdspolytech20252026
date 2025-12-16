#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>

class SetTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_set.clear();
        test_vector.clear();
        initialization_count = 0;
        max_size = 100;
    }

    void TearDown() override {
        test_set.clear();
        test_vector.clear();
        initialization_count = 0;
    }

    std::set<int> test_set;
    std::vector<int> test_vector;
    int initialization_count;
    int max_size;
};

TEST_F(SetTest, EmptySetInitialization_no1) {
    ASSERT_TRUE(test_set.empty());
    ASSERT_EQ(test_set.size(), 0);
    ASSERT_FALSE(test_set.find(1) != test_set.end());
}

TEST_F(SetTest, AddSingleElement_no2) {
    test_set.insert(42);
    ASSERT_FALSE(test_set.empty());
    ASSERT_EQ(test_set.size(), 1);
    ASSERT_TRUE(test_set.find(42) != test_set.end());
    ASSERT_FALSE(test_set.find(100) != test_set.end());
}

TEST_F(SetTest, AddMultipleElements_no3) {
    test_set.insert(10);
    test_set.insert(20);
    test_set.insert(30);
    ASSERT_EQ(test_set.size(), 3);
    ASSERT_TRUE(test_set.find(10) != test_set.end());
    ASSERT_TRUE(test_set.find(20) != test_set.end());
    ASSERT_TRUE(test_set.find(30) != test_set.end());
}

TEST_F(SetTest, RemoveExistingElement_no4) {
    test_set.insert(5);
    test_set.insert(15);
    test_set.insert(25);
    ASSERT_EQ(test_set.size(), 3);

    test_set.erase(15);
    ASSERT_EQ(test_set.size(), 2);
    ASSERT_FALSE(test_set.find(15) != test_set.end());
    ASSERT_TRUE(test_set.find(5) != test_set.end());
    ASSERT_TRUE(test_set.find(25) != test_set.end());
}

TEST_F(SetTest, RemoveNonExistentElement_no5) {
    test_set.insert(100);
    ASSERT_EQ(test_set.size(), 1);

    test_set.erase(999);
    ASSERT_EQ(test_set.size(), 1);
    ASSERT_TRUE(test_set.find(100) != test_set.end());
}

TEST_F(SetTest, DuplicateElementsIgnored_no6) {
    test_set.insert(50);
    test_set.insert(50);
    test_set.insert(50);
    ASSERT_EQ(test_set.size(), 1);
    ASSERT_TRUE(test_set.find(50) != test_set.end());
}

TEST_F(SetTest, ClearAllElements_no7) {
    test_set.insert(1);
    test_set.insert(2);
    test_set.insert(3);
    ASSERT_EQ(test_set.size(), 3);

    test_set.clear();
    ASSERT_TRUE(test_set.empty());
    ASSERT_EQ(test_set.size(), 0);
    ASSERT_FALSE(test_set.find(1) != test_set.end());
}

TEST_F(SetTest, BoundaryValues_no8) {
    test_set.insert(INT_MIN);
    test_set.insert(0);
    test_set.insert(INT_MAX);
    ASSERT_EQ(test_set.size(), 3);
    ASSERT_TRUE(test_set.find(INT_MIN) != test_set.end());
    ASSERT_TRUE(test_set.find(0) != test_set.end());
    ASSERT_TRUE(test_set.find(INT_MAX) != test_set.end());
}

TEST_F(SetTest, VectorOperations_no9) {
    test_vector.push_back(10);
    test_vector.push_back(20);
    test_vector.push_back(30);
    ASSERT_EQ(test_vector.size(), 3);
    ASSERT_EQ(test_vector[0], 10);
    ASSERT_EQ(test_vector[1], 20);
    ASSERT_EQ(test_vector[2], 30);

    test_vector.pop_back();
    ASSERT_EQ(test_vector.size(), 2);
    ASSERT_EQ(test_vector.back(), 20);
}

TEST_F(SetTest, ComplexOperations_no10) {
    for (int i = 0; i < 10; i++) {
        test_set.insert(i * 2);
    }
    ASSERT_EQ(test_set.size(), 10);

    int count = 0;
    for (auto it = test_set.begin(); it != test_set.end(); ++it) {
        count++;
        ASSERT_GE(*it, 0);
        ASSERT_LE(*it, 18);
    }
    ASSERT_EQ(count, 10);

    test_set.erase(0);
    test_set.erase(18);
    ASSERT_EQ(test_set.size(), 8);
    ASSERT_FALSE(test_set.find(0) != test_set.end());
    ASSERT_FALSE(test_set.find(18) != test_set.end());
}