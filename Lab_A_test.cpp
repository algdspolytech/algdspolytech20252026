#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#ifndef STR_SORT_H
extern "C" {
#include "str_sort.h"
}
#endif

#define ARR_SIZE 9

#define declare_strings()                                                      \
  char *arr[] = {"apple", "apps", "abc",  "please", "buy",                     \
                 "",      "DAY",  "game", "Integer"};

#define declare_sorted_strings()                                               \
  char *arr_sorted[]{"",     "DAY",   "abc",    "buy",    "apps",              \
                     "game", "apple", "please", "Integer"};

TEST(StrCompareTest, AGreaterThanB_1Expected_no1) {
  declare_strings();
  char *a = arr[3];
  char *b = arr[2];
  ASSERT_EQ(str_compare(a, b), 1);
}

TEST(StrCompareTest, AEqualsB_Minus1Expected_no2) {
  declare_strings();
  char *a = arr[3];
  char *b = "please";
  ASSERT_EQ(str_compare(a, b), -1);
}

TEST(StrCompareTest, ALessThanB_ZeroExpected_no3) {
  declare_strings();
  char *a = arr[1];
  char *b = arr[3];
  ASSERT_FALSE(str_compare(a, b));
}

TEST(StrLenTest, NonEmptyStr_3Expected_no4) {
  declare_strings();
  char *testStr = arr[4];
  ASSERT_EQ(string_length(testStr), 3);
}

TEST(StrLenTest, EmptyStr_0Expected_no5) {
  declare_strings();
  char *emptyStr = arr[5];
  ASSERT_EQ(string_length(emptyStr), 0);
}

TEST(SwitchStrTest, Switch2_4_TrueExpected_no6) {
  declare_strings();
  char **copy = (char **)malloc(sizeof(char *) * ARR_SIZE);
  for (int i = 0; i < ARR_SIZE; i++) {
    copy[i] = arr[i];
  }
  print_strings(copy, ARR_SIZE);
  switch_str(copy, 2, 4);
  print_strings(copy, ARR_SIZE);

  EXPECT_STREQ(arr[2], copy[4]);
  EXPECT_STREQ(arr[4], copy[2]);
  free(copy);
}

TEST(PartitionTest, UnsortedHalfArrayPartition_no7) {
  declare_strings();
  print_strings(arr, ARR_SIZE);
  char *b = arr[4];
  partition_str(arr, 0, 4);
  print_strings(arr, ARR_SIZE);
  int isEqual = 1, i = 0;
  while (arr[i] != b) {
    if (!str_compare(b, arr[i++])) {
      isEqual = 0;
      break;
    }
  }
  ASSERT_TRUE(isEqual);
}

TEST(PartitionTest, SortedHalfArrayPartition_NoChangeExpected_no8) {
  declare_sorted_strings();
  char **copy = (char **)malloc(sizeof(char *) * ARR_SIZE);
  for (int i = 0; i < ARR_SIZE; i++) {
    copy[i] = arr_sorted[i];
  }
  print_strings(copy, ARR_SIZE);
  char *b = copy[4];
  partition_str(copy, 0, 4);
  print_strings(copy, ARR_SIZE);
  int isEqual = 1, i = 0;
  while (copy[i] != b) {
    if (copy[i] != arr_sorted[i]) {
      isEqual = 0;
      break;
    }
    i++;
  }
  free(copy);
  ASSERT_TRUE(isEqual);
}

TEST(QuickSortTest, SortNotSorted_EqualityCheck_no9) {
  declare_strings();
  declare_sorted_strings();
  quicksort_str(arr, 0, ARR_SIZE - 1);
  int areEqual = 1;
  for (int i = 0; i < ARR_SIZE - 1; i++) {
    if (str_compare(arr[i], arr_sorted[i]) != -1) {
      areEqual = 0;
      break;
    }
  }
  ASSERT_TRUE(areEqual);
}

TEST(QuickSortTest, SortSorted_EqualityCheck_no10) {
  declare_sorted_strings();
  char **copy = (char **)malloc(sizeof(char *) * ARR_SIZE);
  for (int i = 0; i < ARR_SIZE; i++) {
    copy[i] = arr_sorted[i];
  }
  quicksort_str(arr_sorted, 0, ARR_SIZE - 1);
  int areEqual = 1;
  for (int i = 0; i < ARR_SIZE - 1; i++) {
    if (str_compare(copy[i], arr_sorted[i]) != -1) {
      areEqual = 0;
      break;
    }
  }
  free(copy);
  ASSERT_TRUE(areEqual);
}

int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}