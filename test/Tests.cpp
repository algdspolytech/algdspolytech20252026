#include <gtest/gtest.h>

extern "C" {
#include "../knapsack.h"
}

// 1. Пример из условия
TEST(KnapsackTest, ExampleFromStatement) {
  int w[] = {1, 2, 2, 2, 3};
  int v[] = {7, 1, 1, 4, 10};
  int res[10], sz;

  EXPECT_EQ(solve_knapsack(w, v, 5, 5, 20, res, &sz), 0);
}

// 2. Один предмет подходит
TEST(KnapsackTest, SingleItemEnough) {
  int w[] = {5};
  int v[] = {10};
  int res[10], sz;

  EXPECT_EQ(solve_knapsack(w, v, 1, 5, 10, res, &sz), 1);
  EXPECT_EQ(sz, 1);
}

// 3. Несколько предметов
TEST(KnapsackTest, MultipleItems) {
  int w[] = {2, 3, 4};
  int v[] = {4, 5, 6};
  int res[10], sz;

  EXPECT_EQ(solve_knapsack(w, v, 3, 5, 9, res, &sz), 1);
}

// 4. Недостаточная вместимость
TEST(KnapsackTest, TooSmallCapacity) {
  int w[] = {5, 6};
  int v[] = {10, 12};
  int res[10], sz;

  EXPECT_EQ(solve_knapsack(w, v, 2, 4, 5, res, &sz), 0);
}

// 5. K = 0 (всегда возможно)
TEST(KnapsackTest, ZeroK) {
  int w[] = {3, 4};
  int v[] = {5, 6};
  int res[10], sz;

  EXPECT_EQ(solve_knapsack(w, v, 2, 0, 0, res, &sz), 1);
}

// 6. Все предметы нужны
TEST(KnapsackTest, AllItemsNeeded) {
  int w[] = {1, 1, 1};
  int v[] = {2, 2, 2};
  int res[10], sz;

  EXPECT_EQ(solve_knapsack(w, v, 3, 3, 6, res, &sz), 1);
  EXPECT_EQ(sz, 3);
}

// 7. Большая стоимость одного предмета
TEST(KnapsackTest, OneBigValue) {
  int w[] = {10, 1};
  int v[] = {100, 1};
  int res[10], sz;

  EXPECT_EQ(solve_knapsack(w, v, 2, 10, 50, res, &sz), 1);
}

// 8. Невозможно по стоимости
TEST(KnapsackTest, ValueTooLarge) {
  int w[] = {1, 1, 1};
  int v[] = {1, 1, 1};
  int res[10], sz;

  EXPECT_EQ(solve_knapsack(w, v, 3, 3, 10, res, &sz), 0);
}

// 9. Граничный случай: n = 0
TEST(KnapsackTest, EmptySet) {
  int res[10], sz;
  EXPECT_EQ(solve_knapsack(nullptr, nullptr, 0, 10, 1, res, &sz), 0);
}

// 10. Несколько решений — любое допустимо
TEST(KnapsackTest, AnyValidSolution) {
  int w[] = {2, 2, 2};
  int v[] = {3, 3, 3};
  int res[10], sz;

  EXPECT_EQ(solve_knapsack(w, v, 3, 4, 6, res, &sz), 1);
}
