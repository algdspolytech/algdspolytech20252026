#include <gtest/gtest.h>
#include "solution.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void create_test_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fputs(content, file);
        fclose(file);
    }
}


static char* read_file_content(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(length + 1);
    if (content) {
        fread(content, 1, length, file);
        content[length] = '\0';
    }

    fclose(file);
    return content;
}


static void delete_file(const char* filename) {
    remove(filename);
}

// тест 1
TEST(SubsetSumTest, SimpleCase_SolutionExists_no1) {
    const char* input = "10\n5\n2 3 4 5 9";
    create_test_file("input.txt", input);

    int B, N;
    int* A = NULL;
    EXPECT_TRUE(read_input(&B, &N, &A));
    EXPECT_EQ(B, 10);
    EXPECT_EQ(N, 5);
    EXPECT_NE(A, nullptr);
    free(A);

    SubsetResult result = find_subset_sum((const int[]){2, 3, 4, 5, 9}, 5, 10);
    EXPECT_TRUE(result.found);
    EXPECT_EQ(result.count, 3);
    EXPECT_EQ(result.elements[0], 2);
    EXPECT_EQ(result.elements[1], 3);
    EXPECT_EQ(result.elements[2], 5);

    free_subset_result(&result);
    delete_file("input.txt");
}

// тест 2
TEST(SubsetSumTest, NoSolution_no2) {
    const char* input = "100\n3\n1 2 3";
    create_test_file("input.txt", input);

    SubsetResult result = find_subset_sum((const int[]){1, 2, 3}, 3, 100);
    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.count, 0);

    free_subset_result(&result);
    delete_file("input.txt");
}

// тест 3
TEST(SubsetSumTest, EmptyArray_no3) {
    const char* input = "5\n0\n";
    create_test_file("input.txt", input);

    SubsetResult result = find_subset_sum(NULL, 0, 5);
    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.count, 0);

    free_subset_result(&result);
    delete_file("input.txt");
}

// тест 4:
TEST(SubsetSumTest, TargetSumZero_no4) {
    const char* input = "0\n3\n1 2 3";
    create_test_file("input.txt", input);

    SubsetResult result = find_subset_sum((const int[]){1, 2, 3}, 3, 0);
    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.count, 0);

    free_subset_result(&result);
    delete_file("input.txt");
}

// тест 5
TEST(SubsetSumTest, SingleElementMatchesTarget_no5) {
    const char* input = "5\n1\n5";
    create_test_file("input.txt", input);

    SubsetResult result = find_subset_sum((const int[]){5}, 1, 5);
    EXPECT_TRUE(result.found);
    EXPECT_EQ(result.count, 1);
    EXPECT_EQ(result.elements[0], 5);

    free_subset_result(&result);
    delete_file("input.txt");
}

// тест 6
TEST(SubsetSumTest, SingleElementDoesNotMatchTarget_no6) {
    const char* input = "10\n1\n5";
    create_test_file("input.txt", input);

    SubsetResult result = find_subset_sum((const int[]){5}, 1, 10);
    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.count, 0);

    free_subset_result(&result);
    delete_file("input.txt");
}

// тест 7
TEST(SubsetSumTest, AllElementsInSolution_no7) {
    const char* input = "6\n3\n1 2 3";
    create_test_file("input.txt", input);

    SubsetResult result = find_subset_sum((const int[]){1, 2, 3}, 3, 6);
    EXPECT_TRUE(result.found);
    EXPECT_EQ(result.count, 3);
    EXPECT_EQ(result.elements[0], 1);
    EXPECT_EQ(result.elements[1], 2);
    EXPECT_EQ(result.elements[2], 3);

    free_subset_result(&result);
    delete_file("input.txt");
}

// тест 8
TEST(SubsetSumTest, MultipleSolutions_ReturnFirst_no8) {
    const char* input = "5\n4\n1 2 3 4";
    create_test_file("input.txt", input);

    SubsetResult result = find_subset_sum((const int[]){1, 2, 3, 4}, 4, 5);
    EXPECT_TRUE(result.found);
    int sum = 0;
    for (int i = 0; i < result.count; ++i) {
        sum += result.elements[i];
    }
    EXPECT_EQ(sum, 5);

    free_subset_result(&result);
    delete_file("input.txt");
}

// тест 9
TEST(SubsetSumTest, ElementsLargerThanTarget_no9) {
    const char* input = "3\n3\n4 5 6";
    create_test_file("input.txt", input);

    SubsetResult result = find_subset_sum((const int[]){4, 5, 6}, 3, 3);
    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.count, 0);

    free_subset_result(&result);
    delete_file("input.txt");
}

// тест 10
TEST(SubsetSumTest, WriteOutput_SolutionExists_no10) {
    const char* input = "10\n5\n2 3 4 5 9";
    create_test_file("input.txt", input);

    SubsetResult result;
    result.found = true;
    result.count = 3;
    result.elements = (int*)malloc(3 * sizeof(int));
    result.elements[0] = 2;
    result.elements[1] = 3;
    result.elements[2] = 5;

    EXPECT_TRUE(write_output(&result));

    char* content = read_file_content("output.txt");
    ASSERT_NE(content, nullptr);
    EXPECT_STREQ(content, "2 3 5\n");

    free(content);
    free_subset_result(&result);
    delete_file("input.txt");
    delete_file("output.txt");
}

// тест 11
TEST(SubsetSumTest, WriteOutput_NoSolution_no11) {
    const char* input = "100\n3\n1 2 3";
    create_test_file("input.txt", input);

    SubsetResult result;
    result.found = false;
    result.count = 0;
    result.elements = NULL;

    EXPECT_TRUE(write_output(&result));

    char* content = read_file_content("output.txt");
    ASSERT_NE(content, nullptr);
    EXPECT_STREQ(content, "0\n");

    free(content);
    free_subset_result(&result);
    delete_file("input.txt");
    delete_file("output.txt");
}

// тест 12
TEST(SubsetSumTest, ReadInput_FileNotFound_no12) {
    int B, N;
    int* A = NULL;
    EXPECT_FALSE(read_input(&B, &N, &A));
    EXPECT_EQ(A, nullptr);
}

// тест 13
TEST(SubsetSumTest, ReadInput_InvalidFormat_no13) {
    const char* input = "abc\n5\n2 3 4 5 9";
    create_test_file("input.txt", input);

    int B, N;
    int* A = NULL;
    EXPECT_FALSE(read_input(&B, &N, &A));
    EXPECT_EQ(A, nullptr);

    delete_file("input.txt");
}

// тест 14
TEST(SubsetSumTest, ReadInput_EmptyFile_no14) {
    create_test_file("input.txt", "");

    int B, N;
    int* A = NULL;
    EXPECT_FALSE(read_input(&B, &N, &A));
    EXPECT_EQ(A, nullptr);

    delete_file("input.txt");
}

// тест 15
TEST(SubsetSumTest, ReadInput_NZero_no15) {
    const char* input = "10\n0\n";
    create_test_file("input.txt", input);

    int B, N;
    int* A = NULL;
    EXPECT_TRUE(read_input(&B, &N, &A));
    EXPECT_EQ(B, 10);
    EXPECT_EQ(N, 0);
    EXPECT_EQ(A, nullptr);

    delete_file("input.txt");
}

// тест 16
TEST(SubsetSumTest, FindSubsetSum_EmptyArray_no16) {
    SubsetResult result = find_subset_sum(NULL, 0, 5);
    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.count, 0);

    free_subset_result(&result);
}

// тест 17
TEST(SubsetSumTest, FindSubsetSum_TargetZero_no17) {
    SubsetResult result = find_subset_sum((const int[]){1, 2, 3}, 3, 0);
    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.count, 0);

    free_subset_result(&result);
}

// тест 18
TEST(SubsetSumTest, FindSubsetSum_TargetNegative_no18) {
    SubsetResult result = find_subset_sum((const int[]){1, 2, 3}, 3, -5);
    EXPECT_FALSE(result.found);
    EXPECT_EQ(result.count, 0);

    free_subset_result(&result);
}

// тест 19
TEST(SubsetSumTest, FindSubsetSum_LargeArray_no19) {
    int A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SubsetResult result = find_subset_sum(A, 10, 15);
    EXPECT_TRUE(result.found);
    int sum = 0;
    for (int i = 0; i < result.count; ++i) {
        sum += result.elements[i];
    }
    EXPECT_EQ(sum, 15);

    free_subset_result(&result);
}

// тест 20
TEST(SubsetSumTest, FindSubsetSum_MaxValues_no20) {
    int A[1] = {65536}; 
    SubsetResult result = find_subset_sum(A, 1, 65536);
    EXPECT_TRUE(result.found);
    EXPECT_EQ(result.count, 1);
    EXPECT_EQ(result.elements[0], 65536);

    free_subset_result(&result);
}