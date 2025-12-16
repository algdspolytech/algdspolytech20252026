#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "subset_sum_solver.h"
}

// Вспомогательная функция для создания временного файла
class TempFile {
public:
    TempFile(const char* content) {
        filename = tmpnam(nullptr);
        FILE* f = fopen(filename, "w");
        fputs(content, f);
        fclose(f);
    }

    ~TempFile() {
        remove(filename);
        free(filename);
    }

    const char* getFilename() const { return filename; }

private:
    char* filename;
};

TEST(SubsetSumTest, BasicCase) {
    int numbers[] = { 1, 2, 3, 4, 5 };
    int target = 7;

    SubsetSolution result = solve_subset_sum_problem(target, numbers, 5);

    EXPECT_TRUE(result.found);
    EXPECT_GT(result.length, 0);

    int sum = compute_subset_total(result.items, result.length);
    EXPECT_EQ(sum, target);

    release_solution(&result);
}

TEST(SubsetSumTest, NoSolution) {
    int numbers[] = { 1, 2, 3 };
    int target = 10;

    SubsetSolution result = solve_subset_sum_problem(target, numbers, 3);

    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.length, 0);

    release_solution(&result);
}

TEST(SubsetSumTest, ExactElement) {
    int numbers[] = { 3, 7, 2, 9 };
    int target = 7;

    SubsetSolution result = solve_subset_sum_problem(target, numbers, 4);

    EXPECT_TRUE(result.found);
    EXPECT_EQ(result.length, 1);
    EXPECT_EQ(result.items[0], 7);

    release_solution(&result);
}

TEST(SubsetSumTest, MultipleCombinations) {
    int numbers[] = { 1, 4, 2, 7, 3 };
    int target = 10;

    SubsetSolution result = solve_subset_sum_problem(target, numbers, 5);

    EXPECT_TRUE(result.found);
    int sum = compute_subset_total(result.items, result.length);
    EXPECT_EQ(sum, target);

    release_solution(&result);
}

TEST(SubsetSumTest, AllElementsSum) {
    int numbers[] = { 1, 2, 3, 4, 5 };
    int target = 15;

    SubsetSolution result = solve_subset_sum_problem(target, numbers, 5);

    EXPECT_TRUE(result.found);
    int sum = compute_subset_total(result.items, result.length);
    EXPECT_EQ(sum, target);

    release_solution(&result);
}

TEST(SubsetSumTest, LargeNumbers) {
    int numbers[] = { 100000, 200000, 300000, 400000 };
    int target = 500000;

    SubsetSolution result = solve_subset_sum_problem(target, numbers, 4);

    EXPECT_TRUE(result.found);
    int sum = compute_subset_total(result.items, result.length);
    EXPECT_EQ(sum, target);

    release_solution(&result);
}

TEST(SubsetSumTest, DuplicateElements) {
    int numbers[] = { 2, 2, 3, 3, 4 };
    int target = 6;

    SubsetSolution result = solve_subset_sum_problem(target, numbers, 5);

    EXPECT_TRUE(result.found);
    int sum = compute_subset_total(result.items, result.length);
    EXPECT_EQ(sum, target);

    release_solution(&result);
}

TEST(SubsetSumTest, ZeroTarget) {
    int numbers[] = { 1, 2, 3 };
    int target = 0;

    SubsetSolution result = solve_subset_sum_problem(target, numbers, 3);

    EXPECT_TRUE(result.found);
    EXPECT_EQ(result.length, 0);

    release_solution(&result);
}

TEST(SubsetSumTest, EmptyArray) {
    int target = 5;

    SubsetSolution result = solve_subset_sum_problem(target, nullptr, 0);

    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.length, 0);

    release_solution(&result);
}

TEST(SubsetSumTest, FileOperations) {
    const char* file_content = "10\n5\n1 4 2 7 3\n";
    TempFile temp_file(file_content);

    int target, count;
    int* numbers = load_data_from_file(temp_file.getFilename(), &target, &count);

    ASSERT_NE(numbers, nullptr);
    EXPECT_EQ(target, 10);
    EXPECT_EQ(count, 5);

    SubsetSolution result = solve_subset_sum_problem(target, numbers, count);
    EXPECT_TRUE(result.found);

    free(numbers);
    release_solution(&result);
}

TEST(SubsetSumTest, NegativeCase) {
    int numbers[] = { 8, 9, 10 };
    int target = 5;

    SubsetSolution result = solve_subset_sum_problem(target, numbers, 3);

    EXPECT_FALSE(result.found);

    release_solution(&result);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}