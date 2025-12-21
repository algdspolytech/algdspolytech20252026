#include <gtest/gtest.h>
#include "ordered_set.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

TEST(OrderedSetTest, FibonacciSets_no1) {
    OrderedSet* fib1 = set_create();
    OrderedSet* fib2 = set_create();
    
    int a = 1, b = 2;
    for (int i = 0; i < 8; i++) {
        set_add(fib1, a);
        int next = a + b;
        a = b;
        b = next;
    }
    
    a = 0; b = 1;
    for (int i = 0; i < 10; i++) {
        set_add(fib2, a);
        int next = a + b;
        a = b;
        b = next;
    }
    
    OrderedSet* union_set = set_union(fib1, fib2);
    OrderedSet* intersect_set = set_intersection(fib1, fib2);
    
    EXPECT_LE(set_size(intersect_set), set_size(fib1));
    EXPECT_LE(set_size(intersect_set), set_size(fib2));
    EXPECT_GE(set_size(union_set), set_size(fib1));
    EXPECT_GE(set_size(union_set), set_size(fib2));
    
    set_destroy(fib1);
    set_destroy(fib2);
    set_destroy(union_set);
    set_destroy(intersect_set);
}

TEST(OrderedSetTest, PrimeEvenIntersection_no2) {
    OrderedSet* primes = set_create();
    OrderedSet* evens = set_create();
    
    int prime_numbers[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    int prime_count = 15;
    
    for (int i = 0; i < prime_count; i++) {
        set_add(primes, prime_numbers[i]);
    }
    
    for (int i = 2; i <= 50; i += 2) {
        set_add(evens, i);
    }
    
    OrderedSet* intersection = set_intersection(primes, evens);
    EXPECT_EQ(set_size(intersection), 1);
    EXPECT_TRUE(set_contains(intersection, 2));
    
    OrderedSet* union_set = set_union(primes, evens);
    EXPECT_EQ(set_size(union_set), prime_count + 24);
    
    set_destroy(primes);
    set_destroy(evens);
    set_destroy(intersection);
    set_destroy(union_set);
}

TEST(OrderedSetTest, PowersIntersection_no3) {
    OrderedSet* powers_of_2 = set_create();
    OrderedSet* powers_of_3 = set_create();
    
    for (int i = 0; pow(2, i) < 1000; i++) {
        set_add(powers_of_2, (int)pow(2, i));
    }
    
    for (int i = 0; pow(3, i) < 1000; i++) {
        set_add(powers_of_3, (int)pow(3, i));
    }
    
    OrderedSet* common_powers = set_intersection(powers_of_2, powers_of_3);
    EXPECT_EQ(set_size(common_powers), 1);
    EXPECT_TRUE(set_contains(common_powers, 1));
    
    set_destroy(powers_of_2);
    set_destroy(powers_of_3);
    set_destroy(common_powers);
}

TEST(OrderedSetTest, ArithmeticProgressions_no4) {
    OrderedSet* ap1 = set_create();
    OrderedSet* ap2 = set_create();
    
    for (int n = 0; n < 20; n++) {
        set_add(ap1, 5 * n + 2);
        set_add(ap2, 3 * n + 1);
    }
    
    OrderedSet* intersection = set_intersection(ap1, ap2);
    OrderedSet* union_set = set_union(ap1, ap2);
    
    for (int i = 0; i < 100; i++) {
        bool in_ap1 = set_contains(ap1, i);
        bool in_ap2 = set_contains(ap2, i);
        bool in_intersection = set_contains(intersection, i);
        bool in_union = set_contains(union_set, i);
        
        if (in_intersection) {
            EXPECT_TRUE(in_ap1 && in_ap2);
        }
        
        if (in_ap1 || in_ap2) {
            EXPECT_TRUE(in_union);
        }
    }
    
    set_destroy(ap1);
    set_destroy(ap2);
    set_destroy(intersection);
    set_destroy(union_set);
}

TEST(OrderedSetTest, RandomStressTest_no5) {
    OrderedSet* set = set_create();
    srand(time(NULL));
    
    for (int i = 0; i < 1000; i++) {
        int op = rand() % 3;
        int val = rand() % 100;
        
        switch (op) {
            case 0:
                set_add(set, val);
                break;
            case 1:
                set_remove(set, val);
                break;
            case 2:
                set_contains(set, val);
                break;
        }
    }
    
    EXPECT_TRUE(set_size(set) <= 100);
    set_destroy(set);
}

TEST(OrderedSetTest, SetAlgebraProperties_no6) {
    OrderedSet* A = set_create();
    OrderedSet* B = set_create();
    OrderedSet* C = set_create();
    
    for (int i = 0; i < 30; i++) {
        if (i % 2 == 0) set_add(A, i);
        if (i % 3 == 0) set_add(B, i);
        if (i % 5 == 0) set_add(C, i);
    }
    
    OrderedSet* A_union_B = set_union(A, B);
    OrderedSet* B_union_A = set_union(B, A);
    EXPECT_EQ(set_size(A_union_B), set_size(B_union_A));
    
    OrderedSet* A_inter_B = set_intersection(A, B);
    OrderedSet* B_inter_A = set_intersection(B, A);
    EXPECT_EQ(set_size(A_inter_B), set_size(B_inter_A));
    
    OrderedSet* left_union = set_union(A_union_B, C);
    OrderedSet* B_union_C = set_union(B, C);
    OrderedSet* right_union = set_union(A, B_union_C);
    EXPECT_EQ(set_size(left_union), set_size(right_union));
    
    set_destroy(A);
    set_destroy(B);
    set_destroy(C);
    set_destroy(A_union_B);
    set_destroy(B_union_A);
    set_destroy(A_inter_B);
    set_destroy(B_inter_A);
    set_destroy(left_union);
    set_destroy(B_union_C);
    set_destroy(right_union);
}

TEST(OrderedSetTest, PalindromeNumbers_no7) {
    OrderedSet* palindromes = set_create();
    
    for (int i = 0; i < 10000; i++) {
        int n = i, reversed = 0, original = i;
        while (n > 0) {
            reversed = reversed * 10 + n % 10;
            n /= 10;
        }
        if (original == reversed) {
            set_add(palindromes, original);
        }
    }
    
    OrderedSet* evens = set_create();
    for (int i = 0; i < 10000; i += 2) {
        set_add(evens, i);
    }
    
    OrderedSet* even_palindromes = set_intersection(palindromes, evens);
    
    int expected[] = {0, 2, 4, 6, 8, 22, 44, 66, 88, 202, 212, 222};
    int expected_count = 12;
    
    for (int i = 0; i < expected_count; i++) {
        EXPECT_TRUE(set_contains(even_palindromes, expected[i]));
    }
    
    set_destroy(palindromes);
    set_destroy(evens);
    set_destroy(even_palindromes);
}

TEST(OrderedSetTest, GeometricSequence_no8) {
    OrderedSet* geometric = set_create();
    
    for (int n = 0; n <= 10; n++) {
        set_add(geometric, (int)pow(2, n));
    }
    
    int count = 0;
    int prev = -1;
    SetIterator it = set_iterator_begin(geometric);
    while (set_iterator_has_next(&it)) {
        int current = set_iterator_next(&it);
        EXPECT_GT(current, prev);
        prev = current;
        count++;
    }
    
    EXPECT_EQ(count, 11);
    EXPECT_TRUE(set_contains(geometric, 1));
    EXPECT_TRUE(set_contains(geometric, 2));
    EXPECT_TRUE(set_contains(geometric, 1024));
    
    set_destroy(geometric);
}

TEST(OrderedSetTest, TriangularNumbers_no9) {
    OrderedSet* triangular = set_create();
    
    for (int n = 1; n <= 20; n++) {
        int t = n * (n + 1) / 2;
        set_add(triangular, t);
    }
    
    int expected[] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 
                      66, 78, 91, 105, 120, 136, 153, 171, 190, 210};
    
    for (int i = 0; i < 20; i++) {
        EXPECT_TRUE(set_contains(triangular, expected[i]));
    }
    
    OrderedSet* squares = set_create();
    for (int i = 1; i * i <= 210; i++) {
        set_add(squares, i * i);
    }
    
    OrderedSet* triangular_squares = set_intersection(triangular, squares);
    EXPECT_TRUE(set_contains(triangular_squares, 1));
    EXPECT_TRUE(set_contains(triangular_squares, 36));
    
    set_destroy(triangular);
    set_destroy(squares);
    set_destroy(triangular_squares);
}

TEST(OrderedSetTest, SetDifferenceSimulation_no10) {
    OrderedSet* A = set_create();
    OrderedSet* B = set_create();
    
    for (int i = 0; i < 50; i++) {
        set_add(A, i);
    }
    
    for (int i = 0; i < 50; i += 2) {
        set_add(B, i);
    }
    
    OrderedSet* A_minus_B = set_create();
    SetIterator it = set_iterator_begin(A);
    while (set_iterator_has_next(&it)) {
        int val = set_iterator_next(&it);
        set_add(A_minus_B, val);
    }
    
    it = set_iterator_begin(B);
    while (set_iterator_has_next(&it)) {
        int val = set_iterator_next(&it);
        set_remove(A_minus_B, val);
    }
    
    for (int i = 0; i < 50; i++) {
        bool in_result = set_contains(A_minus_B, i);
        bool should_be_in = (i % 2 != 0);
        EXPECT_EQ(in_result, should_be_in);
    }
    
    set_destroy(A);
    set_destroy(B);
    set_destroy(A_minus_B);
}

TEST(OrderedSetTest, SymmetricDifference_no11) {
    OrderedSet* A = set_create();
    OrderedSet* B = set_create();
    
    for (int i = 1; i <= 30; i++) {
        if (i % 2 == 0 || i % 3 == 0) set_add(A, i);
        if (i % 3 == 0 || i % 5 == 0) set_add(B, i);
    }
    
    OrderedSet* sym_diff = set_create();
    
    SetIterator it = set_iterator_begin(A);
    while (set_iterator_has_next(&it)) {
        int val = set_iterator_next(&it);
        if (!set_contains(B, val)) set_add(sym_diff, val);
    }
    
    it = set_iterator_begin(B);
    while (set_iterator_has_next(&it)) {
        int val = set_iterator_next(&it);
        if (!set_contains(A, val)) set_add(sym_diff, val);
    }
    
    EXPECT_TRUE(set_contains(sym_diff, 2));
    EXPECT_TRUE(set_contains(sym_diff, 5));
    EXPECT_FALSE(set_contains(sym_diff, 15));
    EXPECT_FALSE(set_contains(sym_diff, 6));
    
    set_destroy(A);
    set_destroy(B);
    set_destroy(sym_diff);
}

TEST(OrderedSetTest, SumCartesianProduct_no12) {
    OrderedSet* X = set_create();
    OrderedSet* Y = set_create();
    
    for (int i = 1; i <= 3; i++) set_add(X, i);
    for (int i = 10; i <= 20; i += 10) set_add(Y, i);
    
    OrderedSet* sums = set_create();
    SetIterator x_it = set_iterator_begin(X);
    while (set_iterator_has_next(&x_it)) {
        int x = set_iterator_next(&x_it);
        SetIterator y_it = set_iterator_begin(Y);
        while (set_iterator_has_next(&y_it)) {
            int y = set_iterator_next(&y_it);
            set_add(sums, x + y);
        }
    }
    
    int expected_sums[] = {11, 12, 13, 21, 22, 23};
    
    EXPECT_EQ(set_size(sums), 6);
    for (int i = 0; i < 6; i++) {
        EXPECT_TRUE(set_contains(sums, expected_sums[i]));
    }
    
    set_destroy(X);
    set_destroy(Y);
    set_destroy(sums);
}

TEST(OrderedSetTest, PerfectNumbers_no13) {
    OrderedSet* perfect_numbers = set_create();
    
    int perfects[] = {6, 28, 496, 8128};
    int perfect_count = 4;
    
    for (int i = 0; i < perfect_count; i++) {
        set_add(perfect_numbers, perfects[i]);
    }
    
    OrderedSet* triangular = set_create();
    for (int n = 1; n * (n + 1) / 2 <= 10000; n++) {
        set_add(triangular, n * (n + 1) / 2);
    }
    
    for (int i = 0; i < perfect_count; i++) {
        EXPECT_TRUE(set_contains(triangular, perfects[i]));
    }
    
    OrderedSet* intersection = set_intersection(perfect_numbers, triangular);
    EXPECT_EQ(set_size(intersection), perfect_count);
    
    set_destroy(perfect_numbers);
    set_destroy(triangular);
    set_destroy(intersection);
}

TEST(OrderedSetTest, ModularSets_no14) {
    OrderedSet* mod5_eq0 = set_create();
    OrderedSet* mod5_eq2 = set_create();
    
    for (int i = 0; i < 100; i++) {
        if (i % 5 == 0) set_add(mod5_eq0, i);
        if (i % 5 == 2) set_add(mod5_eq2, i);
    }
    
    OrderedSet* intersection = set_intersection(mod5_eq0, mod5_eq2);
    EXPECT_TRUE(set_is_empty(intersection));
    
    OrderedSet* union_set = set_union(mod5_eq0, mod5_eq2);
    
    for (int i = 0; i < 100; i++) {
        bool should_be_in = (i % 5 == 0) || (i % 5 == 2);
        EXPECT_EQ(set_contains(union_set, i), should_be_in);
    }
    
    EXPECT_EQ(set_size(mod5_eq0), 20);
    EXPECT_EQ(set_size(mod5_eq2), 20);
    EXPECT_EQ(set_size(union_set), 40);
    
    set_destroy(mod5_eq0);
    set_destroy(mod5_eq2);
    set_destroy(intersection);
    set_destroy(union_set);
}

TEST(OrderedSetTest, LargeSetOperations_no15) {
    OrderedSet* large_set = set_create();
    
    for (int i = 0; i < 10000; i++) {
        set_add(large_set, i * 3 % 10007);
    }
    
    OrderedSet* copy = set_create();
    SetIterator it = set_iterator_begin(large_set);
    while (set_iterator_has_next(&it)) {
        set_add(copy, set_iterator_next(&it));
    }
    
    OrderedSet* union_self = set_union(large_set, copy);
    OrderedSet* intersect_self = set_intersection(large_set, copy);
    
    EXPECT_EQ(set_size(large_set), set_size(copy));
    EXPECT_EQ(set_size(large_set), set_size(union_self));
    EXPECT_EQ(set_size(large_set), set_size(intersect_self));
    
    set_destroy(large_set);
    set_destroy(copy);
    set_destroy(union_self);
    set_destroy(intersect_self);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
