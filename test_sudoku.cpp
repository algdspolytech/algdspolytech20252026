#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "sudoku_dlx.h"

class SudokuTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {
        std::remove("test_input.txt");
        std::remove("test_output.txt");
    }

    void create_test_file(const std::string& content) {
        std::ofstream f("test_input.txt");
        f << content;
        f.close();
    }

    bool file_contains_zero(const char* filename) {
        std::ifstream f(filename);
        if (!f) return false;
        std::string line;
        getline(f, line);
        return line == "0";
    }

    bool file_exists_and_not_empty(const char* filename) {
        std::ifstream f(filename);
        if (!f) return false;
        f.seekg(0, std::ios::end);
        return f.tellg() > 0;
    }
};

// Тест 1: Простейшая решаемая доска 2x2
TEST_F(SudokuTest, Simple2x2Solvable_no1) {
    create_test_file(
        "2\n"
        "1 0 3 0\n"
        "0 0 0 0\n"
        "0 0 0 0\n"
        "0 0 0 0\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_TRUE(solved);
    EXPECT_TRUE(file_exists_and_not_empty("test_output.txt"));
    EXPECT_FALSE(file_contains_zero("test_output.txt"));
}

// Тест 2: Уже решенная доска 3x3
TEST_F(SudokuTest, AlreadySolved3x3_no2) {
    create_test_file(
        "3\n"
        "1 2 3 4 5 6 7 8 9\n"
        "4 5 6 7 8 9 1 2 3\n"
        "7 8 9 1 2 3 4 5 6\n"
        "2 3 4 5 6 7 8 9 1\n"
        "5 6 7 8 9 1 2 3 4\n"
        "8 9 1 2 3 4 5 6 7\n"
        "3 4 5 6 7 8 9 1 2\n"
        "6 7 8 9 1 2 3 4 5\n"
        "9 1 2 3 4 5 6 7 8\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_TRUE(solved);
    EXPECT_TRUE(file_exists_and_not_empty("test_output.txt"));
    EXPECT_FALSE(file_contains_zero("test_output.txt"));
}

// Тест 3: Одна пустая клетка
TEST_F(SudokuTest, OneEmptyCell_no3) {
    create_test_file(
        "3\n"
        "1 2 3 4 5 6 7 8 9\n"
        "4 5 6 7 8 9 1 2 3\n"
        "7 8 9 1 2 3 4 5 6\n"
        "2 3 4 5 6 7 8 9 1\n"
        "5 6 7 8 9 1 2 3 4\n"
        "8 9 1 2 3 4 5 6 7\n"
        "3 4 5 6 7 8 9 1 2\n"
        "6 7 8 9 1 2 3 4 5\n"
        "9 1 2 3 4 5 6 7 0\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_TRUE(solved);
    EXPECT_TRUE(file_exists_and_not_empty("test_output.txt"));
    EXPECT_FALSE(file_contains_zero("test_output.txt"));
}

// Тест 4: Неразрешимая доска (две единицы в первой строке)
TEST_F(SudokuTest, UnsolvableBoard_no4) {
    create_test_file(
        "3\n"
        "1 2 3 4 5 6 7 8 1\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_FALSE(solved);
    EXPECT_TRUE(file_contains_zero("test_output.txt"));
}

// Тест 5: Несуществующий файл
TEST_F(SudokuTest, NonExistentFile_no5) {
    bool solved = solve_sudoku_dlx("non_existent_file_12345.txt", "test_output.txt");
    EXPECT_FALSE(solved);
    EXPECT_TRUE(file_contains_zero("test_output.txt"));
}

// Тест 6: Пример из задания (должен решаться)
TEST_F(SudokuTest, ExampleFromTask_no6) {
    create_test_file(
        "3\n"
        "0 0 5 3 0 0 0 0 0\n"
        "8 0 0 0 0 0 0 0 2\n"
        "0 7 0 0 1 0 5 0 0\n"
        "4 0 0 0 0 5 3 0 0\n"
        "0 1 0 0 7 0 0 0 6\n"
        "0 3 2 0 0 0 0 8 0\n"
        "0 6 0 5 0 0 0 0 9\n"
        "0 0 4 0 0 0 0 3 0\n"
        "0 0 0 0 0 9 7 0 0\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_TRUE(solved);
    EXPECT_TRUE(file_exists_and_not_empty("test_output.txt"));
    EXPECT_FALSE(file_contains_zero("test_output.txt"));
}

// Тест 7: Пустая доска 3x3
TEST_F(SudokuTest, Empty3x3Board_no7) {
    create_test_file(
        "3\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_TRUE(solved);
    EXPECT_TRUE(file_exists_and_not_empty("test_output.txt"));
    EXPECT_FALSE(file_contains_zero("test_output.txt"));
}

// Тест 8: Несколько предзаполненных клеток
TEST_F(SudokuTest, PartiallyFilled3x3_no8) {
    create_test_file(
        "3\n"
        "5 3 0 0 7 0 0 0 0\n"
        "6 0 0 1 9 5 0 0 0\n"
        "0 9 8 0 0 0 0 6 0\n"
        "8 0 0 0 6 0 0 0 3\n"
        "4 0 0 8 0 3 0 0 1\n"
        "7 0 0 0 2 0 0 0 6\n"
        "0 6 0 0 0 0 2 8 0\n"
        "0 0 0 4 1 9 0 0 5\n"
        "0 0 0 0 8 0 0 7 9\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_TRUE(solved);
    EXPECT_TRUE(file_exists_and_not_empty("test_output.txt"));
    EXPECT_FALSE(file_contains_zero("test_output.txt"));
}

// Тест 9: Противоречие в блоке (две одинаковые цифры в одном блоке 3x3)
TEST_F(SudokuTest, BlockContradiction_no9) {
    create_test_file(
        "3\n"
        "1 0 0 0 0 0 0 0 0\n"
        "0 1 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_FALSE(solved);
    EXPECT_TRUE(file_contains_zero("test_output.txt"));
}

// Тест 10: Простой случай с несколькими цифрами
TEST_F(SudokuTest, SimpleCaseWithFewNumbers_no10) {
    create_test_file(
        "3\n"
        "0 0 0 2 6 0 7 0 1\n"
        "6 8 0 0 7 0 0 9 0\n"
        "1 9 0 0 0 4 5 0 0\n"
        "8 2 0 1 0 0 0 4 0\n"
        "0 0 4 6 0 2 9 0 0\n"
        "0 5 0 0 0 3 0 2 8\n"
        "0 0 9 3 0 0 0 7 4\n"
        "0 4 0 0 5 0 0 3 6\n"
        "7 0 3 0 1 8 0 0 0\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_TRUE(solved);
    EXPECT_TRUE(file_exists_and_not_empty("test_output.txt"));
    EXPECT_FALSE(file_contains_zero("test_output.txt"));
}

// Тест 11: Только одна цифра в центре
TEST_F(SudokuTest, SingleNumberInCenter_no11) {
    create_test_file(
        "3\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 5 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_TRUE(solved);
    EXPECT_TRUE(file_exists_and_not_empty("test_output.txt"));
    EXPECT_FALSE(file_contains_zero("test_output.txt"));
}

// Тест 12: Противоречие в столбце
TEST_F(SudokuTest, ColumnContradiction_no12) {
    create_test_file(
        "3\n"
        "1 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "1 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0\n"
    );
    bool solved = solve_sudoku_dlx("test_input.txt", "test_output.txt");
    EXPECT_FALSE(solved);
    EXPECT_TRUE(file_contains_zero("test_output.txt"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}