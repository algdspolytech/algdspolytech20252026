#include "C:\Users\Арюна\source\repos\TestforLabD\LabD\functionsfull.c"

#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>

TEST(ReadInputTest, ReadValidFile) {
    const char* filename = "test_input_temp.txt";
    FILE* f = fopen(filename, "w");
    fprintf(f, "8\n");
    fclose(f);

    long long N = read_input(filename);
    EXPECT_EQ(N, 8);

    remove(filename);
}

TEST(ReadInputTest, ReadLargeNumber) {
    const char* filename = "test_large_temp.txt";
    FILE* f = fopen(filename, "w");
    fprintf(f, "999999\n");
    fclose(f);

    long long N = read_input(filename);
    EXPECT_EQ(N, 999999);

    remove(filename);
}

TEST(WriteOutputTest, WriteSmallBoard) {
    const char* filename = "test_output_temp.txt";
    long long N = 4;
    long long cols[] = { 2, 4, 1, 3 };

    write_output(filename, cols, N);

    FILE* f = fopen(filename, "r");
    ASSERT_NE(f, nullptr);

    long long row, col;
    for (long long i = 0; i < N; i++) {
        int result = fscanf(f, "%lld %lld", &row, &col);
        EXPECT_EQ(result, 2);
        EXPECT_EQ(row, i);
        EXPECT_EQ(col, cols[i] - 1);
    }

    fclose(f);
    remove(filename);
}

TEST(WriteOutputTest, WriteOneQueen) {
    const char* filename = "test_one_temp.txt";
    long long N = 1;
    long long cols[] = { 1 };

    write_output(filename, cols, N);

    FILE* f = fopen(filename, "r");
    ASSERT_NE(f, nullptr);

    long long row, col;
    int result = fscanf(f, "%lld %lld", &row, &col);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(row, 0);
    EXPECT_EQ(col, 0);

    fclose(f);
    remove(filename);
}

bool IsValidQueensSolution(long long* cols, long long N) {

    for (long long i = 0; i < N; i++) {
        if (cols[i] < 1 || cols[i] > N) {
            return false;
        }
    }

    std::vector<long long> sorted(cols, cols + N);
    std::sort(sorted.begin(), sorted.end());
    for (long long i = 0; i < N; i++) {
        if (sorted[i] != i + 1) {
            return false;
        }
    }

    for (long long i = 0; i < N; i++) {
        for (long long j = i + 1; j < N; j++) {
            long long row_diff = std::abs(i - j);
            long long col_diff = std::abs(cols[i] - cols[j]);
            if (row_diff == col_diff) {
                return false;
            }
        }
    }

    return true;
}

class GenerateSolutionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Инициализация для каждого теста
    }

    void TearDown() override {
        if (cols != nullptr) {
            free(cols);
            cols = nullptr;
        }
    }

    void GenerateAndTest(long long N) {
        cols = (long long*)malloc(N * sizeof(long long));
        ASSERT_NE(cols, nullptr);

        generate_solution(cols, N);

        EXPECT_TRUE(IsValidQueensSolution(cols, N));
    }

    long long* cols = nullptr;
};

TEST_F(GenerateSolutionTest, N6) {
    GenerateAndTest(6);
}


TEST_F(GenerateSolutionTest, N0) {

    cols = (long long*)malloc(sizeof(long long));
    ASSERT_NE(cols, nullptr);

    EXPECT_NO_FATAL_FAILURE(generate_solution(cols, 0));
}

TEST_F(GenerateSolutionTest, N100) {
    GenerateAndTest(100);
}

TEST_F(GenerateSolutionTest, N2NoCrash) {
    cols = (long long*)malloc(2 * sizeof(long long));
    ASSERT_NE(cols, nullptr);

    EXPECT_NO_FATAL_FAILURE(generate_solution(cols, 2));

    for (int i = 0; i < 2; i++) {
        EXPECT_GE(cols[i], 1);
        EXPECT_LE(cols[i], 2);
    }
}

TEST_F(GenerateSolutionTest, N3NoCrash) {
    cols = (long long*)malloc(3 * sizeof(long long));
    ASSERT_NE(cols, nullptr);

    EXPECT_NO_FATAL_FAILURE(generate_solution(cols, 3));

    for (int i = 0; i < 3; i++) {
        EXPECT_GE(cols[i], 1);
        EXPECT_LE(cols[i], 3);
    }
}

class GenerateSolutionParamTest : public ::testing::TestWithParam<int> {
protected:
    void SetUp() override {
        N = GetParam();
        if (N > 0) {
            cols = (long long*)malloc(N * sizeof(long long));
            ASSERT_NE(cols, nullptr);
        }
    }

    void TearDown() override {
        if (cols != nullptr) {
            free(cols);
            cols = nullptr;
        }
    }

    long long N;
    long long* cols = nullptr;
};

TEST_P(GenerateSolutionParamTest, ValidSolution) {
    if (N > 0 && N != 2 && N != 3) {
        generate_solution(cols, N);
        EXPECT_TRUE(IsValidQueensSolution(cols, N));
    }
}

TEST(OutputFormatTest, CorrectFormat) {
    const char* filename = "test_format_temp.txt";
    long long N = 3;
    long long cols[] = { 2, 4, 1 };

    write_output(filename, cols, N);

    FILE* f = fopen(filename, "r");
    ASSERT_NE(f, nullptr);

    char line[100];
    for (int i = 0; i < N; i++) {
        ASSERT_NE(fgets(line, sizeof(line), f), nullptr);

        long long a, b;
        int result = sscanf(line, "%lld %lld", &a, &b);
        EXPECT_EQ(result, 2);
        EXPECT_EQ(a, i);
    }

    fclose(f);
    remove(filename);
}

TEST(AlgorithmTest, ConsecutiveValues) {

    for (int N = 1; N <= 20; N++) {
        if (N == 2 || N == 3) continue;

        long long* cols = (long long*)malloc(N * sizeof(long long));
        ASSERT_NE(cols, nullptr);

        generate_solution(cols, N);

        std::vector<long long> values(cols, cols + N);
        std::sort(values.begin(), values.end());

        for (int i = 0; i < N; i++) {
            EXPECT_EQ(values[i], i + 1);
        }

        free(cols);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();

    return result;
}