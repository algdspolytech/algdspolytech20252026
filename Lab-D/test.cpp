#include <gtest/gtest.h>
#include "N_Queens.h"

// solve_nqueens_IsN1_ReturnsTrue
TEST(solve_nqueens, IsN1_ReturnsTrue) {
    int out[1];
    EXPECT_TRUE(solve_nqueens(1, out));
}

// solve_nqueens_IsN1_MatchesExpectedPlacement
TEST(solve_nqueens, IsN1_MatchesExpectedPlacement) {
    int out[1];
    solve_nqueens(1, out);
    int expected[1] = { 0 };
    EXPECT_EQ(out[0], expected[0]);
}

// solve_nqueens_IsN4_ReturnsTrue
TEST(solve_nqueens, IsN4_ReturnsTrue) {
    int out[4];
    EXPECT_TRUE(solve_nqueens(4, out));
}

// solve_nqueens_IsN4_MatchesOneOfExpectedSolutions
TEST(solve_nqueens, IsN4_MatchesOneOfExpectedSolutions) {
    int out[4];
    solve_nqueens(4, out);
    int expected1[4] = { 1, 3, 0, 2 };  // одно из решений
    int expected2[4] = { 2, 0, 3, 1 };  // другое
    bool match = (out[0] == expected1[0] && out[1] == expected1[1] &&
        out[2] == expected1[2] && out[3] == expected1[3]) ||
        (out[0] == expected2[0] && out[1] == expected2[1] &&
            out[2] == expected2[2] && out[3] == expected2[3]);
    EXPECT_TRUE(match);
}

// solve_nqueens_IsN5_ReturnsTrue
TEST(solve_nqueens, IsN5_ReturnsTrue) {
    int out[5];
    EXPECT_TRUE(solve_nqueens(5, out));
}

// solve_nqueens_IsN5_HasNoDiagonalConflicts
TEST(solve_nqueens, IsN5_HasNoDiagonalConflicts) {
    int out[5];
    solve_nqueens(5, out);
    bool safe = true;
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            safe = safe && (abs(out[i] - out[j]) != abs(i - j));
        }
    }
    EXPECT_TRUE(safe);
}

// solve_nqueens_IsN2_ReturnsFalse
TEST(solve_nqueens, IsN2_ReturnsFalse) {
    int out[2];
    EXPECT_FALSE(solve_nqueens(2, out));
}

// solve_nqueens_IsN3_ReturnsFalse
TEST(solve_nqueens, IsN3_ReturnsFalse) {
    int out[3];
    EXPECT_FALSE(solve_nqueens(3, out));
}

// solve_nqueens_IsN0_ReturnsFalse
TEST(solve_nqueens, IsN0_ReturnsFalse) {
    int out[1];
    EXPECT_FALSE(solve_nqueens(0, out));
}

// solve_nqueens_IsN1000000_ReturnsFalse
TEST(solve_nqueens, IsN1000000_ReturnsFalse) {
    int* out = new int[1000000];
    EXPECT_FALSE(solve_nqueens(1000000, out));
    delete[] out;
}