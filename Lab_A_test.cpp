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
// 1) Сравнение строк "please" > "abc",  ответ: 1
TEST(StrCompareTest, AGreaterThanB_1Expected_no1) {
  declare_strings();
  char *a = arr[3];
  char *b = arr[2];
  ASSERT_EQ(str_compare(a, b), 1);
}

// 2) Сравнение строк "please" = "please", ответ:  -1
TEST(StrCompareTest, AEqualsB_Minus1Expected_no2) {
  declare_strings();
  char *a = arr[3];
  char *b = "please";
  ASSERT_EQ(str_compare(a, b), -1);
}

// 3) Сравнение строк "apps" < "please", ответ: 0
TEST(StrCompareTest, ASmallerThanB_ZeroExpected_no3) {
  declare_strings();
  char *a = arr[1];
  char *b = arr[3];
  ASSERT_FALSE(str_compare(a, b));
}

// 4) Длина непустой строки "buy", ответ 4
TEST(StrLenTest, NonEmptyStr_3Expected_no4) {
  declare_strings();
  char *testStr = arr[4];
  ASSERT_EQ(string_length(testStr), 3);
}

// 5) Длина пустой строки, ответ 0
TEST(StrLenTest, EmptyStr_0Expected_no5) {
  declare_strings();
  char *emptyStr = arr[5];
  ASSERT_EQ(string_length(emptyStr), 0);
}

// 6) Создание односвязного списка из массива строк
TEST(ArrToListTest, MakeList_EqualityCheck_TrueExpected_no6) {
  declare_strings();
  linked_str_t *list = arr_to_list(arr, ARR_SIZE);
  bool testVal = true;
  node_t *cur = list->first;
  for (int i = 0; i < ARR_SIZE; i++) {
    if (str_compare(cur->str, arr[i]) != -1) {
      testVal = false;
      break;
    }
    cur = cur->next;
  }
  EXPECT_TRUE(testVal);
  print_list(list);
  free_list(list);
}

// 7) Добавление в начало непустого списка
TEST(PushToStartTest, AddNode_ExistenceCheck_TrueExpected_no7) {
  declare_strings();
  char *a = "Test";
  node_t *node = make_node(a);
  linked_str_t *list = arr_to_list(arr, ARR_SIZE);
  push_to_start(list, node);
  print_list(list);
  node_t *cur = node;
  int i = 0;
  while (cur) {
    cur = cur->next;
    i++;
  }
  EXPECT_EQ(i, ARR_SIZE + 1);
  EXPECT_EQ(list->first, node);
  EXPECT_EQ(str_compare(list->first->str, a), -1);
  free_list(list);
}

// 8) Добавление в начало пустого списка
TEST(PushToStartTest, AddNode_EmptyListCase_no8) {
  linked_str_t *list = make_list();
  char *a = "Test";
  node_t *node = make_node(a);
  push_to_start(list, node);
  print_list(list);
  EXPECT_EQ(list_length(list), 1);
  EXPECT_STREQ(list->first->str, a);
  free_list(list);
}

// 9) Добавление в конец непустого списка
TEST(PushToEndTest, AddNode_ExistenceCheck_TrueExpected_no9) {
  declare_strings();
  char *text = "Test";
  node_t *node = make_node(text);
  linked_str_t *list = arr_to_list(arr, ARR_SIZE);
  push_to_end(list, node);
  print_list(list);
  node_t *cur = list->first;
  int i = 1;
  while (cur->next != nullptr) {
    cur = cur->next;
    i++;
  }
  EXPECT_EQ(i, ARR_SIZE + 1);
  EXPECT_EQ(cur, node);
  EXPECT_EQ(str_compare(cur->str, text), -1);
  free_list(list);
}

// 10) Добавление в конец пустого списка
TEST(PushToEndTest, AddNode_EmptyList_no10) {
  linked_str_t *list = make_list();
  char *text = "Test";
  node_t *node = make_node(text);
  push_to_end(list, node);
  EXPECT_EQ(list_length(list), 1);
  EXPECT_STREQ(list->first->str, text);
  free_list(list);
}

// 11) Удаление начального элемента, проверка на отсутствие потери указателя на
// начало списка
TEST(DeleteNodeTest, DeleteFirstNode_no11) {
  declare_strings();
  linked_str_t *list = arr_to_list(arr, ARR_SIZE);
  node_t *node = delete_node(list, 0), *second = list->first;
  print_list(list);
  EXPECT_EQ(str_compare(node->str, arr[0]), -1);
  EXPECT_EQ(list_length(list), ARR_SIZE - 1);
  EXPECT_EQ(str_compare(list->first->str, second->str), -1);
  free_list(list);
  free(node);
}

// 12) Удаление внутреннего элемента, проверка сохранения структуры списка для
// последующих элементов
TEST(DeleteNodeTest, DeleteInternalNode_no12) {
  declare_strings();
  linked_str_t *list = arr_to_list(arr, ARR_SIZE);
  node_t *node = delete_node(list, 3);
  print_list(list);
  EXPECT_EQ(str_compare(node->str, arr[3]), -1);
  EXPECT_EQ(list_length(list), ARR_SIZE - 1);
  free_list(list);
  free(node);
}

// 13) Обмен позициями 0 и 4 элементов без потери указателя на начальный
TEST(SwitchNodesTest, SwitchWithNodeZero_0and4Switch_no13) {
  declare_strings();
  linked_str_t *list = arr_to_list(arr, ARR_SIZE);
  switch_nodes(list, 0, 4);
  print_list(list);
  EXPECT_STREQ(list->first->str, arr[4]);
  EXPECT_STREQ(get_node(list, 4)->str, arr[0]);
  free_list(list);
}

// 14) Обмен позициями внутренних элементов списка
TEST(SwitchNodesTest, InternalNodesSwitch_3and8Switch_no14) {
  declare_strings();
  linked_str_t *list = arr_to_list(arr, ARR_SIZE);
  switch_nodes(list, 3, 8);
  print_list(list);
  EXPECT_STREQ(get_node(list, 3)->str, arr[8]);
  EXPECT_STREQ(get_node(list, 8)->str, arr[3]);
  free_list(list);
}

// 15) Процедура partition для неотсортированного списка, проверка корректности
// расположения элементов после процедуры
TEST(PartitionListTest, UnsortedList_HalfListPartition_no15) {
  declare_strings();
  linked_str_t *list = arr_to_list(arr, ARR_SIZE);
  node_t *four = get_node(list, 4), *cur = list->first;
  int q = partition_list(list, 0, 4);
  EXPECT_EQ(q, 1);
  print_list(list);
  bool testVal = true;
  for (int i = 0; i < q; i++) {
    if (!str_compare(cur->str, four->str)) {
      testVal = false;
    }
    cur = cur->next;
  }
  for (int i = q + 1; i < 4; i++) {
    if (!str_compare(cur->str, four->str)) {
      testVal = false;
    }
    cur = cur->next;
  }
  EXPECT_TRUE(testVal);
  free_list(list);
}

// 16) Процедура partition для отсортированного списка, проверка отсутствия
// изменений
TEST(PartitionListTest, SortedList_HalfListPartition_no16) {
  declare_sorted_strings();
  linked_str_t *list = arr_to_list(arr_sorted, ARR_SIZE);
  node_t *four = get_node(list, 4), *cur = list->first;
  int q = partition_list(list, 0, 4);
  EXPECT_EQ(q, 4);
  bool testVal = true;
  for (int i = 0; i < q; i++) {
    if (!str_compare(get_node(list, 4)->str, cur->str)) {
      testVal = false;
    }
    cur = cur->next;
  }
  EXPECT_TRUE(testVal);
  free_list(list);
}

// 17) Быстрая сортировка для случайного списка
TEST(QuicksortListTest, RandomlyUnsortedList_EqualityCheck_no17) {
  declare_strings();
  declare_sorted_strings();
  linked_str_t *list = arr_to_list(arr, ARR_SIZE);
  int j, k;
  for (int i = 0; i < 20; i++) {
    j = rand() % 9, k = rand() % 9;
    switch_nodes(list, j, k);
  }
  quicksort_list(list, 0, ARR_SIZE - 1);
  print_list(list);
  node_t *cur = list->first;
  bool testVal = true;
  for (int i = 0; i < ARR_SIZE; i++) {
    if (str_compare(cur->str, arr_sorted[i]) != -1) {
      testVal = false;
    }
    cur = cur->next;
  }
  EXPECT_TRUE(testVal);
  free_list(list);
}

// 18) Быстрая сортировка отсортированного списка
TEST(QuicksortListTest, SortedList_NoChangeExpected_no16) {
  declare_sorted_strings();
  linked_str_t *list = arr_to_list(arr_sorted, ARR_SIZE);
  quicksort_list(list, 0, ARR_SIZE - 1);
  print_list(list);
  node_t *cur = list->first;
  bool testVal = true;
  for (int i = 0; i < ARR_SIZE; i++) {
    if (str_compare(cur->str, arr_sorted[i]) != -1) {
      testVal = false;
    }
    cur = cur->next;
  }
  EXPECT_TRUE(testVal);
  free_list(list);
}

int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}