#include "gtest/gtest.h"
#include "Header.h"
#include <fstream>
#include <sstream>
#include <cstdio>
TEST(SubsetSumTest, SimpleCaseWithSolution) {
	int sizes[] = { 2,3,4,5,9 };
	struct SubsetResult* result = findSubsetSum(10, 5, sizes);
	EXPECT_NE(result, nullptr);
	EXPECT_TRUE(result->found);
	EXPECT_GT(result->count, 0);
	unsigned int sum = 0;
	for (int i = 0;i < result->count;i++) sum += result->elements[i];
	EXPECT_EQ(sum, 10u);
	freeSubsetResult(result);
}
TEST(SubsetSumTest, NoSolution) {
	int sizes[] = { 2,4,6 };
	struct SubsetResult* result = findSubsetSum(5, 3, sizes);
	EXPECT_NE(result, nullptr);
	EXPECT_FALSE(result->found);
	freeSubsetResult(result);
}
TEST(SubsetSumTest, SingleElementEqualsB) {
	int sizes[] = { 1,5,10,15 };
	struct SubsetResult* result = findSubsetSum(10, 4, sizes);
	EXPECT_NE(result, nullptr);
	EXPECT_TRUE(result->found);
	EXPECT_EQ(result->count, 1);
	EXPECT_EQ(result->elements[0], 10);
	freeSubsetResult(result);
}
TEST(SubsetSumTest, EmptyArray) {
	int* sizes = NULL;
	struct SubsetResult* result = findSubsetSum(10, 0, sizes);
	EXPECT_NE(result, nullptr);
	EXPECT_FALSE(result->found);
	freeSubsetResult(result);
}
TEST(SubsetSumTest, MultipleElementsSum) {
	int sizes[] = { 1,2,3,4,5,6,7,8,9,10 };
	struct SubsetResult* result = findSubsetSum(15, 10, sizes);
	EXPECT_NE(result, nullptr);
	EXPECT_TRUE(result->found);
	unsigned int sum = 0;
	for (int i = 0;i < result->count;i++) sum += result->elements[i];
	EXPECT_EQ(sum, 15u);
	freeSubsetResult(result);
}
TEST(SubsetSumTest, ZeroSum) {
	int sizes[] = { 1,2,3 };
	struct SubsetResult* result = findSubsetSum(0, 3, sizes);
	EXPECT_NE(result, nullptr);
	EXPECT_TRUE(result->found);
	EXPECT_EQ(result->count, 0);
	freeSubsetResult(result);
}
TEST(SubsetSumTest, AllElementsSum) {
	int sizes[] = { 1,2,3,4 };
	struct SubsetResult* result = findSubsetSum(10, 4, sizes);
	EXPECT_NE(result, nullptr);
	EXPECT_TRUE(result->found);
	unsigned int sum = 0;
	for (int i = 0;i < result->count;i++) sum += result->elements[i];
	EXPECT_EQ(sum, 10u);
	freeSubsetResult(result);
}
TEST(SubsetSumTest, LargeNumbers) {
	int sizes[] = { 10000,20000,30000,40000 };
	struct SubsetResult* result = findSubsetSum(50000, 4, sizes);
	EXPECT_NE(result, nullptr);
	EXPECT_TRUE(result->found);
	unsigned int sum = 0;
	for (int i = 0;i < result->count;i++) sum += result->elements[i];
	EXPECT_EQ(sum, 50000u);
	freeSubsetResult(result);
}
TEST(SubsetSumTest, FileOperations) {
	const char* inputFilename = "test_input.txt";
	const char* outputFilename = "test_output.txt";
	std::ofstream inputFile(inputFilename);
	inputFile << "10\n5\n2 3 4 5 9\n";
	inputFile.close();
	struct SubsetResult* result = readAndSolve(inputFilename);
	ASSERT_NE(result, nullptr);
	saveResultToFile(result, outputFilename);
	std::ifstream outputFile(outputFilename);
	std::string line;
	std::getline(outputFile, line);
	outputFile.close();
	std::istringstream iss(line);
	int num;
	unsigned int sum = 0;
	while (iss >> num) sum += num;
	EXPECT_EQ(sum, 10u);
	freeSubsetResult(result);
	remove(inputFilename);
	remove(outputFilename);
}
TEST(SubsetSumTest, MultipleSolutions) {
	int sizes[] = { 1,2,3,4,5 };
	struct SubsetResult* result = findSubsetSum(5, 5, sizes);
	EXPECT_NE(result, nullptr);
	EXPECT_TRUE(result->found);
	unsigned int sum = 0;
	for (int i = 0;i < result->count;i++) sum += result->elements[i];
	EXPECT_EQ(sum, 5u);
	freeSubsetResult(result);
}
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}