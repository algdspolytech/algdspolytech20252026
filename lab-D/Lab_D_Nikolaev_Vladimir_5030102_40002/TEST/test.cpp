#include "gtest/gtest.h"
#include "rates.h"
#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void CreateTestFile(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    fprintf(file, "%s", content);
    fclose(file);
}


TEST(AllFunctionsTest, BasicWorkingCase_no1) {
    const char* test_input = "3 10\n2 3 4\n1 2\n2 3\n0\n";
    CreateTestFile("test1.txt", test_input);

    FILE* file = fopen("test1.txt", "r");
    int T, K;
    fscanf(file, "%d %d\n", &T, &K);

    int* size_of_operation = (int*)malloc(sizeof(int) * T);
    int** connect = (int**)malloc(sizeof(int*) * T);
    int* in_degree = (int*)malloc(sizeof(int) * T);
    int* cnt = (int*)malloc(sizeof(int) * T);

    Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);

    EXPECT_EQ(T, 3);
    EXPECT_EQ(K, 10);
    EXPECT_EQ(size_of_operation[0], 2);
    EXPECT_EQ(size_of_operation[1], 3);
    EXPECT_EQ(size_of_operation[2], 4);
    EXPECT_EQ(in_degree[0], 0);
    EXPECT_EQ(in_degree[1], 1);
    EXPECT_EQ(in_degree[2], 1);

    int* seq = (int*)malloc(sizeof(int) * T);
    bool result = MinMaxRates2(0, 0, connect, size_of_operation, cnt, in_degree, T, K, seq);
    EXPECT_TRUE(result);

    FILE* output = fopen("output1.txt", "w");
    Add_To_File(output, seq, T, result);
    fclose(output);

    FILE* result_file = fopen("output1.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result_file);
    fclose(result_file);
    EXPECT_TRUE(strlen(buffer) > 1);

    for (int i = 0; i < T; i++) free(connect[i]);
    free(size_of_operation); free(connect); free(in_degree); free(cnt); free(seq);
    remove("test1.txt"); remove("output1.txt");
}

TEST(AllFunctionsTest, NoSolutionKTooSmall_no2) {
    const char* test_input = "3 5\n6 7 8\n1 2\n2 3\n0\n";
    CreateTestFile("test2.txt", test_input);

    FILE* input = fopen("test2.txt", "r");
    FILE* output = fopen("output2.txt", "w");

    Full_Rates(input, output);
    fclose(output);

    FILE* result_file = fopen("output2.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result_file);
    fclose(result_file);
    EXPECT_STREQ("0", buffer);

    remove("test2.txt"); remove("output2.txt");
}

TEST(AllFunctionsTest, SingleOperation_no3) {
    const char* test_input = "1 5\n4\n0\n";
    CreateTestFile("test3.txt", test_input);

    FILE* file = fopen("test3.txt", "r");
    int T, K;
    fscanf(file, "%d %d\n", &T, &K); 

    int* size_of_operation = (int*)malloc(sizeof(int) * T);
    int** connect = (int**)malloc(sizeof(int*) * T);
    int* in_degree = (int*)malloc(sizeof(int) * T);
    int* cnt = (int*)malloc(sizeof(int) * T);

    Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);

    EXPECT_EQ(T, 1);
    EXPECT_EQ(K, 5);
    EXPECT_EQ(size_of_operation[0], 4);
    EXPECT_EQ(in_degree[0], 0);
    EXPECT_EQ(cnt[0], 0);

    int* seq = (int*)malloc(sizeof(int) * T);
    bool result = MinMaxRates2(0, 0, connect, size_of_operation, cnt, in_degree, T, K, seq);
    EXPECT_TRUE(result);
    EXPECT_EQ(seq[0], 0);

    FILE* output_file = fopen("output3.txt", "w");
    Add_To_File(output_file, seq, T, result);
    fclose(output_file);

    free(connect[0]); free(size_of_operation); free(connect); free(in_degree); free(cnt); free(seq);
    remove("test3.txt"); remove("output3.txt");
}

TEST(AllFunctionsTest, NoDependencies_no4) {
    const char* test_input = "3 15\n4 5 6\n0\n";
    CreateTestFile("test4.txt", test_input);

    FILE* file = fopen("test4.txt", "r");
    int T, K;
    fscanf(file, "%d %d\n", &T, &K); 

    int* size_of_operation = (int*)malloc(sizeof(int) * T);
    int** connect = (int**)malloc(sizeof(int*) * T);
    int* in_degree = (int*)malloc(sizeof(int) * T);
    int* cnt = (int*)malloc(sizeof(int) * T);

    Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);

    EXPECT_EQ(T, 3);
    EXPECT_EQ(K, 15);
    EXPECT_EQ(size_of_operation[0], 4);
    EXPECT_EQ(size_of_operation[1], 5);
    EXPECT_EQ(size_of_operation[2], 6);
    EXPECT_EQ(in_degree[0], 0);
    EXPECT_EQ(in_degree[1], 0);
    EXPECT_EQ(in_degree[2], 0);

    int* seq = (int*)malloc(sizeof(int) * T);
    bool result = MinMaxRates2(0, 0, connect, size_of_operation, cnt, in_degree, T, K, seq);
    EXPECT_TRUE(result);

    FILE* output = fopen("output4.txt", "w");
    Add_To_File(output, seq, T, result);
    fclose(output);

    for (int i = 0; i < T; i++) free(connect[i]);
    free(size_of_operation); free(connect); free(in_degree); free(cnt); free(seq);
    remove("test4.txt"); remove("output4.txt");
}

TEST(AllFunctionsTest, ComplexDependencies_no5) {
    const char* test_input = "4 20\n2 4 3 5\n1 2\n1 3\n2 4\n3 4\n0\n";
    CreateTestFile("test5.txt", test_input);

    FILE* file = fopen("test5.txt", "r");
    int T, K;
    fscanf(file, "%d %d\n", &T, &K); 

    int* size_of_operation = (int*)malloc(sizeof(int) * T);
    int** connect = (int**)malloc(sizeof(int*) * T);
    int* in_degree = (int*)malloc(sizeof(int) * T);
    int* cnt = (int*)malloc(sizeof(int) * T);

    Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);

    EXPECT_EQ(T, 4);
    EXPECT_EQ(K, 20);
    EXPECT_EQ(size_of_operation[0], 2);
    EXPECT_EQ(size_of_operation[1], 4);
    EXPECT_EQ(size_of_operation[2], 3);
    EXPECT_EQ(size_of_operation[3], 5);
    EXPECT_EQ(in_degree[3], 2); 

    int* seq = (int*)malloc(sizeof(int) * T);
    bool result = MinMaxRates2(0, 0, connect, size_of_operation, cnt, in_degree, T, K, seq);
    EXPECT_TRUE(result);

    FILE* output = fopen("output5.txt", "w");
    Add_To_File(output, seq, T, result);
    fclose(output);

    for (int i = 0; i < T; i++) free(connect[i]);
    free(size_of_operation); free(connect); free(in_degree); free(cnt); free(seq);
    remove("test5.txt"); remove("output5.txt");
}

TEST(AllFunctionsTest, SumEqualsK_no6) {
    const char* test_input = "3 9\n3 3 3\n1 2\n2 3\n0\n";
    CreateTestFile("test6.txt", test_input);

    FILE* file = fopen("test6.txt", "r");
    int T, K;
    fscanf(file, "%d %d\n", &T, &K);

    EXPECT_EQ(T, 3);
    EXPECT_EQ(K, 9);

    int* size_of_operation = (int*)malloc(sizeof(int) * T);
    int** connect = (int**)malloc(sizeof(int*) * T);
    int* in_degree = (int*)malloc(sizeof(int) * T);
    int* cnt = (int*)malloc(sizeof(int) * T);

    Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);

    int* seq = (int*)malloc(sizeof(int) * T);
    bool result = MinMaxRates2(0, 0, connect, size_of_operation, cnt, in_degree, T, K, seq);
    EXPECT_TRUE(result);

    for (int i = 0; i < T; i++) free(connect[i]);
    free(size_of_operation); free(connect); free(in_degree); free(cnt); free(seq);
    remove("test6.txt");
}

TEST(AllFunctionsTest, AddToFileWithFalseFlag_no7) {
    FILE* output = fopen("output7.txt", "w");
    int T = 3;
    int* items = (int*)malloc(sizeof(int) * T);
    items[0] = 0; items[1] = 1; items[2] = 2;

    Add_To_File(output, items, T, false);
    fclose(output);

    FILE* result_file = fopen("output7.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result_file);
    fclose(result_file);
    EXPECT_STREQ("0", buffer);

    free(items);
    remove("output7.txt");
}

TEST(AllFunctionsTest, MultipleDependenciesFromOneNode_no8) {
    const char* test_input = "4 15\n1 2 3 4\n1 2\n1 3\n1 4\n0\n";
    CreateTestFile("test8.txt", test_input);

    FILE* file = fopen("test8.txt", "r");
    int T, K;
    fscanf(file, "%d %d\n", &T, &K);

    int* size_of_operation = (int*)malloc(sizeof(int) * T);
    int** connect = (int**)malloc(sizeof(int*) * T);
    int* in_degree = (int*)malloc(sizeof(int) * T);
    int* cnt = (int*)malloc(sizeof(int) * T);

    Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);

    EXPECT_EQ(T, 4);
    EXPECT_EQ(K, 15);
    EXPECT_EQ(cnt[0], 3); 
    EXPECT_EQ(in_degree[1], 1);
    EXPECT_EQ(in_degree[2], 1);
    EXPECT_EQ(in_degree[3], 1);

    int* seq = (int*)malloc(sizeof(int) * T);
    bool result = MinMaxRates2(0, 0, connect, size_of_operation, cnt, in_degree, T, K, seq);
    EXPECT_TRUE(result);

    for (int i = 0; i < T; i++) free(connect[i]);
    free(size_of_operation); free(connect); free(in_degree); free(cnt); free(seq);
    remove("test8.txt");
}

TEST(AllFunctionsTest, ZeroSizeOperations_no9) {
    const char* test_input = "3 10\n0 0 0\n1 2\n2 3\n0\n";
    CreateTestFile("test9.txt", test_input);

    FILE* file = fopen("test9.txt", "r");
    int T, K;
    fscanf(file, "%d %d\n", &T, &K);

    int* size_of_operation = (int*)malloc(sizeof(int) * T);
    int** connect = (int**)malloc(sizeof(int*) * T);
    int* in_degree = (int*)malloc(sizeof(int) * T);
    int* cnt = (int*)malloc(sizeof(int) * T);

    Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);

    EXPECT_EQ(T, 3);
    EXPECT_EQ(K, 10);
    EXPECT_EQ(size_of_operation[0], 0);
    EXPECT_EQ(size_of_operation[1], 0);
    EXPECT_EQ(size_of_operation[2], 0);

    int* seq = (int*)malloc(sizeof(int) * T);
    bool result = MinMaxRates2(0, 0, connect, size_of_operation, cnt, in_degree, T, K, seq);
    EXPECT_TRUE(result); 

    for (int i = 0; i < T; i++) free(connect[i]);
    free(size_of_operation); free(connect); free(in_degree); free(cnt); free(seq);
    remove("test9.txt");
}

TEST(AllFunctionsTest, AddToFileSingleItem_no10) {
    FILE* output = fopen("output10.txt", "w");
    int T = 1;
    int* items = (int*)malloc(sizeof(int) * T);
    items[0] = 2;

    Add_To_File(output, items, T, true);
    fclose(output);

    FILE* result_file = fopen("output10.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result_file);
    fclose(result_file);
    EXPECT_STREQ("3 ", buffer);

    free(items);
    remove("output10.txt");
}

TEST(AllFunctionsTest, CyclicDependencies_no11) {
    const char* test_input = "3 10\n2 3 4\n1 2\n2 3\n3 1\n0\n";
    CreateTestFile("test11.txt", test_input);

    FILE* file = fopen("test11.txt", "r");
    int T, K;
    fscanf(file, "%d %d\n", &T, &K);

    int* size_of_operation = (int*)malloc(sizeof(int) * T);
    int** connect = (int**)malloc(sizeof(int*) * T);
    int* in_degree = (int*)malloc(sizeof(int) * T);
    int* cnt = (int*)malloc(sizeof(int) * T);

    Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);

    EXPECT_EQ(T, 3);
    EXPECT_EQ(K, 10);

    EXPECT_EQ(cnt[0], 1);
    EXPECT_EQ(cnt[1], 1);
    EXPECT_EQ(cnt[2], 1);

    int* seq = (int*)malloc(sizeof(int) * T);
    bool result = MinMaxRates2(0, 0, connect, size_of_operation, cnt, in_degree, T, K, seq);


    for (int i = 0; i < T; i++) free(connect[i]);
    free(size_of_operation); free(connect); free(in_degree); free(cnt); free(seq);
    remove("test11.txt");
}

TEST(AllFunctionsTest, FullRatesCompleteTest_no12) {
    const char* test_input = "4 12\n1 3 2 4\n1 2\n2 3\n3 4\n0\n";
    CreateTestFile("test12.txt", test_input);

    FILE* input = fopen("test12.txt", "r");
    FILE* output = fopen("output12.txt", "w");

    Full_Rates(input, output);
    fclose(output);

    FILE* result_file = fopen("output12.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result_file);
    fclose(result_file);

    EXPECT_TRUE(strlen(buffer) > 0);
    EXPECT_STRNE("0", buffer);

    remove("test12.txt"); remove("output12.txt");
}

TEST(AllFunctionsTest, ReadMinimalData_no13) {
    const char* test_input = "1 5\n1\n0\n";
    CreateTestFile("test13.txt", test_input);

    FILE* file = fopen("test13.txt", "r");
    int T, K;
    fscanf(file, "%d %d\n", &T, &K);

    int* size_of_operation = (int*)malloc(sizeof(int) * T);
    int** connect = (int**)malloc(sizeof(int*) * T);
    int* in_degree = (int*)malloc(sizeof(int) * T);
    int* cnt = (int*)malloc(sizeof(int) * T);

    Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);

    EXPECT_EQ(T, 1);
    EXPECT_EQ(K, 5);
    EXPECT_EQ(size_of_operation[0], 1);
    EXPECT_EQ(in_degree[0], 0);
    EXPECT_EQ(cnt[0], 0);

    free(connect[0]); free(size_of_operation); free(connect); free(in_degree); free(cnt);
    remove("test13.txt");
}

TEST(AllFunctionsTest, ComprehensiveIntegrationTest_no14) {
    const char* test_input = "5 25\n3 5 2 6 4\n1 2\n1 3\n2 4\n3 4\n4 5\n0\n";
    CreateTestFile("test14.txt", test_input);

    FILE* file = fopen("test14.txt", "r");
    int T, K;
    fscanf(file, "%d %d\n", &T, &K);

    EXPECT_EQ(T, 5);
    EXPECT_EQ(K, 25);

    int* size_of_operation = (int*)malloc(sizeof(int) * T);
    int** connect = (int**)malloc(sizeof(int*) * T);
    int* in_degree = (int*)malloc(sizeof(int) * T);
    int* cnt = (int*)malloc(sizeof(int) * T);

    Read_From_File(file, T, size_of_operation, connect, in_degree, cnt);

    int* seq = (int*)malloc(sizeof(int) * T);
    bool result = MinMaxRates2(0, 0, connect, size_of_operation, cnt, in_degree, T, K, seq);

    FILE* output = fopen("output14.txt", "w");
    Add_To_File(output, seq, T, result);
    fclose(output);

    FILE* result_file = fopen("output14.txt", "r");
    char buffer[100];
    fgets(buffer, sizeof(buffer), result_file);
    fclose(result_file);
    EXPECT_TRUE(strlen(buffer) >= 1);

    for (int i = 0; i < T; i++) free(connect[i]);
    free(size_of_operation); free(connect); free(in_degree); free(cnt); free(seq);
    remove("test14.txt"); remove("output14.txt");
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}