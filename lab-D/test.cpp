#include <gtest/gtest.h>
#include <fstream>
#include <cstdlib>
#include <climits>
#include "subset.h"

class TempFile {
public:
    explicit TempFile(const std::string& content) {
        filename = "test_" + std::to_string(rand()) + ".txt";
        std::ofstream file(filename);
        file << content;
    }
    
    ~TempFile() {
        std::remove(filename.c_str());
    }
    
    const char* name() const { return filename.c_str(); }
    
private:
    std::string filename;
};

TEST(SubsetTest, ReadProblem_ValidFileWithSpacesAndNewlines_ReturnSuccess_no1) {
    TempFile tf("   10   \n   5   \n   2   3   4   5   9   ");
    
    ProblemInput input = {0, NULL, 0};
    
    ASSERT_TRUE(read_problem(tf.name(), &input));
    EXPECT_EQ(input.target_sum, 10u);
    EXPECT_EQ(input.numbers_count, 5u);
    
    free_input(&input);
}

TEST(SubsetTest, ReadProblem_FileWithTabsAndExtraSpaces_ParseCorrectly_no2) {
    TempFile tf("100\t\n4\t\n10\t20\t30\t40");
    
    ProblemInput input = {0, NULL, 0};
    
    ASSERT_TRUE(read_problem(tf.name(), &input));
    EXPECT_EQ(input.target_sum, 100u);
    EXPECT_EQ(input.numbers_count, 4u);
    
    free_input(&input);
}

TEST(SubsetTest, ReadProblem_EmptyFile_ReturnFailure_no3) {
    TempFile tf("");
    
    ProblemInput input = {0, NULL, 0};
    
    EXPECT_FALSE(read_problem(tf.name(), &input));
}

TEST(SubsetTest, ReadProblem_OnlyTargetNoElements_ReturnFailure_no4) {
    TempFile tf("100\n");
    
    ProblemInput input = {0, NULL, 0};
    
    EXPECT_FALSE(read_problem(tf.name(), &input));
}

TEST(SubsetTest, FindSubset_LargeTargetSmallElements_ReturnNoSolution_no5) {
    TempFile tf("1000000000\n3\n1 2 3");
    
    ProblemInput input = {0, NULL, 0};
    SelectionResult result = {NULL, 0, false};
    
    read_problem(tf.name(), &input);
    find_subset_sum(&input, &result);
    
    EXPECT_FALSE(result.solution_exists);
    
    free_input(&input);
    free_result(&result);
}

TEST(SubsetTest, FindSubset_SumOverflowPotential_PreventOverflow_no6) {
    TempFile tf("18446744073709551615\n2\n9223372036854775807 9223372036854775808");
    
    ProblemInput input = {0, NULL, 0};
    SelectionResult result = {NULL, 0, false};
    
    read_problem(tf.name(), &input);
    find_subset_sum(&input, &result);
    
    if (result.solution_exists) {
        uint64_t sum = 0;
        for (size_t i = 0; i < result.selected_count; i++) {
            sum += result.selected_items[i];
        }
        EXPECT_EQ(sum, input.target_sum);
    }
    
    free_input(&input);
    free_result(&result);
}

TEST(SubsetTest, FindSubset_TargetZeroNonEmptySet_ReturnEmptySolution_no8) {
    TempFile tf("0\n5\n100 200 300 400 500");
    
    ProblemInput input = {0, NULL, 0};
    SelectionResult result = {NULL, 0, false};
    
    read_problem(tf.name(), &input);
    find_subset_sum(&input, &result);
    
    EXPECT_TRUE(result.solution_exists);
    EXPECT_EQ(result.selected_count, 0u);
    
    free_input(&input);
    free_result(&result);
}

TEST(SubsetTest, FindSubset_AllElementsSameValue_FindCorrectCombination_no9) {
    TempFile tf("30\n10\n5 5 5 5 5 5 5 5 5 5");
    
    ProblemInput input = {0, NULL, 0};
    SelectionResult result = {NULL, 0, false};
    
    read_problem(tf.name(), &input);
    find_subset_sum(&input, &result);
    
    EXPECT_TRUE(result.solution_exists);
    
    uint64_t sum = 0;
    for (size_t i = 0; i < result.selected_count; i++) {
        EXPECT_EQ(result.selected_items[i], 5u);
        sum += result.selected_items[i];
    }
    EXPECT_EQ(sum, input.target_sum);
    EXPECT_EQ(result.selected_count, 6u);
    
    free_input(&input);
    free_result(&result);
}

TEST(SubsetTest, FindSubset_PrimeNumbers_ComplexComputation_no10) {
    TempFile tf("41\n10\n2 3 5 7 11 13 17 19 23 29");
    
    ProblemInput input = {0, NULL, 0};
    SelectionResult result = {NULL, 0, false};
    
    read_problem(tf.name(), &input);
    find_subset_sum(&input, &result);
    
    EXPECT_TRUE(result.solution_exists);
    
    uint64_t sum = 0;
    for (size_t i = 0; i < result.selected_count; i++) {
        sum += result.selected_items[i];
    }
    EXPECT_EQ(sum, input.target_sum);
    
    free_input(&input);
    free_result(&result);
}

TEST(SubsetTest, FindSubset_FibonacciSequence_FindExactSum_no11) {
    TempFile tf("88\n10\n1 1 2 3 5 8 13 21 34 55");
    
    ProblemInput input = {0, NULL, 0};
    SelectionResult result = {NULL, 0, false};
    
    read_problem(tf.name(), &input);
    find_subset_sum(&input, &result);
    
    EXPECT_TRUE(result.solution_exists);
    
    uint64_t sum = 0;
    for (size_t i = 0; i < result.selected_count; i++) {
        sum += result.selected_items[i];
    }
    EXPECT_EQ(sum, input.target_sum);
    
    free_input(&input);
    free_result(&result);
}

TEST(SubsetTest, FindSubset_PowersOfTwo_BinaryRepresentation_no12) {
    TempFile tf("73\n7\n1 2 4 8 16 32 64");
    
    ProblemInput input = {0, NULL, 0};
    SelectionResult result = {NULL, 0, false};
    
    read_problem(tf.name(), &input);
    find_subset_sum(&input, &result);
    
    EXPECT_TRUE(result.solution_exists);
    
    uint64_t sum = 0;
    for (size_t i = 0; i < result.selected_count; i++) {
        sum += result.selected_items[i];
    }
    EXPECT_EQ(sum, input.target_sum);
    
    free_input(&input);
    free_result(&result);
}

TEST(SubsetTest, FindSubset_ConsecutiveNumbers_MultipleSolutions_no13) {
    TempFile tf("7\n6\n1 2 3 4 5 6");
    
    ProblemInput input = {0, NULL, 0};
    SelectionResult result = {NULL, 0, false};
    
    read_problem(tf.name(), &input);
    find_subset_sum(&input, &result);
    
    EXPECT_TRUE(result.solution_exists);
    
    uint64_t sum = 0;
    for (size_t i = 0; i < result.selected_count; i++) {
        sum += result.selected_items[i];
    }
    EXPECT_EQ(sum, input.target_sum);
    
    free_input(&input);
    free_result(&result);
}

TEST(SubsetTest, WriteResult_SingleElement_NoTrailingSpace_no14) {
    const char* outfile = "test_single.txt";
    std::remove(outfile);
    
    SelectionResult result;
    result.selected_items = (uint64_t*)malloc(sizeof(uint64_t));
    result.selected_items[0] = 42;
    result.selected_count = 1;
    result.solution_exists = true;
    
    ASSERT_TRUE(write_result(outfile, &result));
    
    std::ifstream file(outfile);
    std::string line;
    std::getline(file, line);
    
    EXPECT_EQ(line, "42");
    
    std::remove(outfile);
    free_result(&result);
}

TEST(SubsetTest, WriteResult_VeryLargeNumbers_FormatCorrectly_no15) {
    const char* outfile = "test_large.txt";
    std::remove(outfile);
    
    SelectionResult result;
    result.selected_items = (uint64_t*)malloc(2 * sizeof(uint64_t));
    result.selected_items[0] = 18446744073709551615ULL;
    result.selected_items[1] = 1;
    result.selected_count = 2;
    result.solution_exists = true;
    
    ASSERT_TRUE(write_result(outfile, &result));
    
    std::ifstream file(outfile);
    std::string line;
    std::getline(file, line);
    
    EXPECT_EQ(line, "18446744073709551615 1");
    
    std::remove(outfile);
    free_result(&result);
}

TEST(SubsetTest, WriteResult_SpecialFilename_HandleCorrectly_no16) {
    const char* outfile = "";
    SelectionResult result = {NULL, 0, false};
    
    EXPECT_FALSE(write_result(outfile, &result));
}

TEST(SubsetTest, WriteResult_FilePermissionDenied_ReturnFailure_no17) {
    const char* outfile = "/proc/self/test_output.txt";
    SelectionResult result = {NULL, 0, true};
    
    EXPECT_FALSE(write_result(outfile, &result));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
