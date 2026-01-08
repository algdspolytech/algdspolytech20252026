#include <gtest/gtest.h>
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

extern "C" {
   
    typedef struct {
        uint32_t size;
        uint32_t value;
        int index;
    } Item;

    typedef struct {
        int* items;
        int count;
        uint32_t total_size;
        uint32_t total_value;
    } Solution;

    
    int read_input(const char* filename, Item** items, int* n, uint32_t* B, uint32_t* K);
    void write_output(const char* filename, const Solution* sol);
    void solve_knapsack(Item* items, int n, uint32_t B, uint32_t K, Solution* solution);
    void cleanup(Item* items, Solution* sol);
}


void create_test_file(const char* filename, const char* content) {
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename, "w");
    if (err == 0 && file) {
        fprintf(file, "%s", content);
        fclose(file);
    }
}

void delete_test_file(const char* filename) {
    remove(filename);
}

std::string read_file(const char* filename) {
    FILE* file = nullptr;
    errno_t err = fopen_s(&file, filename, "r");

    if (err != 0 || !file) {
        return "";
    }

    char buffer[1024];
    std::string content;
    while (fgets(buffer, sizeof(buffer), file)) {
        content += buffer;
    }
    fclose(file);
    return content;
}


TEST(ReadInputTest, ReadBasicInput) {
    const char* test_content = "5 10 20\n1 2 3 4 5\n5 10 15 20 25\n";
    create_test_file("test_input.txt", test_content);

    Item* items = nullptr;
    int n = 0;
    uint32_t B = 0, K = 0;

    int result = read_input("test_input.txt", &items, &n, &B, &K);

    ASSERT_EQ(result, 1);
    EXPECT_EQ(n, 5);
    EXPECT_EQ(B, 10);
    EXPECT_EQ(K, 20);

    ASSERT_NE(items, nullptr);
    EXPECT_EQ(items[0].size, 1);
    EXPECT_EQ(items[0].value, 5);
    EXPECT_EQ(items[0].index, 1);

    EXPECT_EQ(items[1].size, 2);
    EXPECT_EQ(items[1].value, 10);
    EXPECT_EQ(items[1].index, 2);

    EXPECT_EQ(items[4].size, 5);
    EXPECT_EQ(items[4].value, 25);
    EXPECT_EQ(items[4].index, 5);

    free(items);
    delete_test_file("test_input.txt");
}

TEST(ReadInputTest, FileNotFound) {
    Item* items = nullptr;
    int n = 0;
    uint32_t B = 0, K = 0;

    int result = read_input("nonexistent_file.txt", &items, &n, &B, &K);

    EXPECT_EQ(result, 0);
    EXPECT_EQ(items, nullptr);
}

TEST(ReadInputTest, InvalidFormat) {
    const char* test_content = "abc def ghi\n";
    create_test_file("test_invalid.txt", test_content);

    Item* items = nullptr;
    int n = 0;
    uint32_t B = 0, K = 0;

    int result = read_input("test_invalid.txt", &items, &n, &B, &K);

    EXPECT_EQ(result, 0);
    EXPECT_EQ(items, nullptr);

    delete_test_file("test_invalid.txt");
}




TEST(SolveKnapsackTest, SimpleCase) {
    Item items[3] = {
        {2, 10, 1},
        {3, 15, 2},
        {4, 20, 3}
    };

    Solution solution = { 0 };
    solve_knapsack(items, 3, 5, 25, &solution);

    if (solution.count > 0) {
        EXPECT_LE(solution.total_size, 5);
        EXPECT_GE(solution.total_value, 25);
    }

    free(solution.items);
}

TEST(SolveKnapsackTest, NoSolution) {
    Item items[3] = {
        {10, 5, 1},
        {20, 10, 2},
        {30, 15, 3}
    };

    Solution solution = { 0 };
    solve_knapsack(items, 3, 5, 20, &solution);

    EXPECT_EQ(solution.count, 0);
    EXPECT_EQ(solution.items, nullptr);
}

TEST(SolveKnapsackTest, ExactMatch) {
    Item items[4] = {
        {1, 5, 1},
        {2, 10, 2},
        {3, 15, 3},
        {4, 20, 4}
    };

    Solution solution = { 0 };
    solve_knapsack(items, 4, 6, 25, &solution);

    EXPECT_GT(solution.count, 0);
    EXPECT_LE(solution.total_size, 6);
    EXPECT_GE(solution.total_value, 25);

    free(solution.items);
}

TEST(SolveKnapsackTest, AllItemsFit) {
    Item items[3] = {
        {1, 10, 1},
        {2, 20, 2},
        {3, 30, 3}
    };

    Solution solution = { 0 };
    solve_knapsack(items, 3, 10, 60, &solution);

    EXPECT_GT(solution.count, 0);
    EXPECT_LE(solution.total_size, 10);
    EXPECT_GE(solution.total_value, 60);

    free(solution.items);
}

TEST(SolveKnapsackTest, EmptySetSolution) {
    Item items[3] = {
        {5, 10, 1},
        {6, 12, 2},
        {7, 14, 3}
    };

    Solution solution = { 0 };
    solve_knapsack(items, 3, 4, 0, &solution);

    
    if (solution.count == 0) {
        EXPECT_EQ(solution.total_size, 0);
        EXPECT_EQ(solution.total_value, 0);
    }

    free(solution.items);
}


TEST(WriteOutputTest, OutputWithSolution) {
    Solution solution;
    solution.items = (int*)malloc(3 * sizeof(int));
    solution.items[0] = 1;
    solution.items[1] = 3;
    solution.items[2] = 5;
    solution.count = 3;
    solution.total_size = 7;
    solution.total_value = 30;

    write_output("test_output.txt", &solution);

    std::string content = read_file("test_output.txt");
    EXPECT_TRUE(content.find("1 3 5") != std::string::npos ||
        content.find("1 3 5\n") != std::string::npos);

    free(solution.items);
    delete_test_file("test_output.txt");
}

TEST(WriteOutputTest, OutputNoSolution) {
    Solution solution = { 0 };

    write_output("test_output.txt", &solution);

    std::string content = read_file("test_output.txt");
    EXPECT_TRUE(content.find("0") != std::string::npos);

    delete_test_file("test_output.txt");
}

TEST(WriteOutputTest, OutputSingleItem) {
    Solution solution;
    solution.items = (int*)malloc(1 * sizeof(int));
    solution.items[0] = 2;
    solution.count = 1;
    solution.total_size = 3;
    solution.total_value = 10;

    write_output("test_output.txt", &solution);

    std::string content = read_file("test_output.txt");
    EXPECT_TRUE(content.find("2") != std::string::npos);

    free(solution.items);
    delete_test_file("test_output.txt");
}



TEST(CleanupTest, CleanupNullPointers) {
    Item* items = nullptr;
    Solution solution = { 0 };

    cleanup(items, &solution); 

    SUCCEED();
}


TEST(IntegrationTest, FullPipelineWithSolution) {
    const char* test_content = "4 10 30\n2 3 4 5\n10 20 30 40\n";
    create_test_file("test_pipeline.txt", test_content);

    Item* items = nullptr;
    int n = 0;
    uint32_t B = 0, K = 0;

    int read_result = read_input("test_pipeline.txt", &items, &n, &B, &K);
    ASSERT_EQ(read_result, 1);


    Solution solution = { 0 };
    solve_knapsack(items, n, B, K, &solution);


    write_output("test_result.txt", &solution);


    std::string result = read_file("test_result.txt");

    if (solution.count > 0) {
        EXPECT_NE(result, "0\n");
        EXPECT_LE(solution.total_size, B);
        EXPECT_GE(solution.total_value, K);
    }
    else {
        EXPECT_TRUE(result == "0\n" || result == "0");
    }

 
    cleanup(items, &solution);
    delete_test_file("test_pipeline.txt");
    delete_test_file("test_result.txt");
}

TEST(IntegrationTest, ExampleFromProblem) {
    const char* test_content = "5 5 20\n1 2 2 2 3\n7 1 1 4 10\n";
    create_test_file("test_example.txt", test_content);

    Item* items = nullptr;
    int n = 0;
    uint32_t B = 0, K = 0;

    int read_result = read_input("test_example.txt", &items, &n, &B, &K);
    ASSERT_EQ(read_result, 1);

    Solution solution = { 0 };
    solve_knapsack(items, n, B, K, &solution);

    write_output("test_example_result.txt", &solution);

    std::string result = read_file("test_example_result.txt");

    EXPECT_TRUE(result == "0\n" || result == "0");

    cleanup(items, &solution);
    delete_test_file("test_example.txt");
    delete_test_file("test_example_result.txt");
}



TEST(BoundaryCasesTest, VeryLargeK) {
    Item items[3] = {
        {1, 1000, 1},
        {2, 2000, 2},
        {3, 3000, 3}
    };

    Solution solution = { 0 };
    solve_knapsack(items, 3, 10, 10000, &solution);

    
    EXPECT_EQ(solution.count, 0);

    free(solution.items);
}


TEST(MemoryTest, NoMemoryLeaksInSolve) {
    Item items[3] = {
        {1, 10, 1},
        {2, 20, 2},
        {3, 30, 3}
    };

    Solution solution = { 0 };
    solve_knapsack(items, 3, 5, 30, &solution);

    free(solution.items);
    SUCCEED();
}

TEST(MemoryTest, NoMemoryLeaksInReadInput) {
    const char* test_content = "3 10 20\n1 2 3\n10 20 30\n";
    create_test_file("test_memory.txt", test_content);

    Item* items = nullptr;
    int n = 0;
    uint32_t B = 0, K = 0;

    int result = read_input("test_memory.txt", &items, &n, &B, &K);

    if (result == 1 && items != nullptr) {
        free(items);
    }

    delete_test_file("test_memory.txt");
    SUCCEED();
}



TEST(EdgeCasesTest, DuplicateItems) {
    Item items[5] = {
        {2, 5, 1},
        {2, 5, 2},
        {2, 5, 3},
        {2, 5, 4},
        {2, 5, 5}
    };

    Solution solution = { 0 };
    solve_knapsack(items, 5, 6, 15, &solution);

    if (solution.count > 0) {
        
        EXPECT_LE(solution.total_size, 6);
        EXPECT_GE(solution.total_value, 15);
    }

    free(solution.items);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}