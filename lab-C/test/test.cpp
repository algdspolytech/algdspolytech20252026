#include <gtest/gtest.h>

extern "C" {
#include "main.h"
}
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS

void clearAll() {
  wordCount = 0;
  for (int i = 0; i < MAX_V; i++) {
    used[i] = inDegree[i] = 0;
    for (int j = 0; j < MAX_V; j++)
      adj[i][j] = 0;
  }
}

TEST(TopoTest, EmptyGraph_no1) {
  clearAll();
  int res[MAX_V];
  EXPECT_TRUE(stableTopoSort(res));
}

TEST(TopoTest, SingleVertex_no2) {
  clearAll();
  strcpy(words[wordCount++], "a");
  int res[MAX_V];
  EXPECT_TRUE(stableTopoSort(res));
  EXPECT_EQ(res[0], 0);
}

TEST(TopoTest, SimpleChain_no3) {
  clearAll();
  strcpy(words[wordCount++], "a");
  strcpy(words[wordCount++], "b");

  adj[0][1] = 1;
  inDegree[1] = 1;

  int res[MAX_V];
  EXPECT_TRUE(stableTopoSort(res));
  EXPECT_EQ(res[0], 0);
  EXPECT_EQ(res[1], 1);
}

TEST(TopoTest, ExampleFromTask_no4) {
  clearAll();
  const char *w[] = {"a", "b", "c", "d", "e", "f"};
  for (int i = 0; i < 6; i++)
    strcpy(words[wordCount++], w[i]);

  adj[0][1] = 1;
  inDegree[1]++;
  adj[3][2] = 1;
  inDegree[2]++;
  adj[1][3] = 1;
  inDegree[3]++;

  int res[MAX_V];
  ASSERT_TRUE(stableTopoSort(res));

  int expected[] = {0, 1, 4, 3, 2, 5};
  for (int i = 0; i < 6; i++)
    EXPECT_EQ(res[i], expected[i]);
}

TEST(TopoTest, CycleSimple_no5) {
  clearAll();
  strcpy(words[wordCount++], "a");
  strcpy(words[wordCount++], "b");

  adj[0][1] = adj[1][0] = 1;
  inDegree[0] = inDegree[1] = 1;

  int res[MAX_V];
  EXPECT_FALSE(stableTopoSort(res));
}

TEST(TopoTest, CycleLong_no6) {
  clearAll();
  strcpy(words[wordCount++], "a");
  strcpy(words[wordCount++], "b");
  strcpy(words[wordCount++], "c");

  adj[0][1] = adj[1][2] = adj[2][0] = 1;
  inDegree[0] = inDegree[1] = inDegree[2] = 1;

  int res[MAX_V];
  EXPECT_FALSE(stableTopoSort(res));
}

TEST(TopoTest, IndependentVertices_no7) {
  clearAll();
  strcpy(words[wordCount++], "x");
  strcpy(words[wordCount++], "y");
  strcpy(words[wordCount++], "z");

  int res[MAX_V];
  EXPECT_TRUE(stableTopoSort(res));
  EXPECT_EQ(res[0], 0);
  EXPECT_EQ(res[1], 1);
  EXPECT_EQ(res[2], 2);
}

TEST(TopoTest, TwoZeroIndegreeChoice_no8) {
  clearAll();
  strcpy(words[wordCount++], "a");
  strcpy(words[wordCount++], "b");
  strcpy(words[wordCount++], "c");

  adj[1][2] = 1;
  inDegree[2] = 1;

  int res[MAX_V];
  EXPECT_TRUE(stableTopoSort(res));
  EXPECT_EQ(res[0], 0);
}

TEST(TopoTest, LateZeroIndegree_no9) {
  clearAll();
  strcpy(words[wordCount++], "a");
  strcpy(words[wordCount++], "b");

  adj[0][1] = 1;
  inDegree[1] = 1;

  int res[MAX_V];
  EXPECT_TRUE(stableTopoSort(res));
  EXPECT_EQ(res[1], 1);
}

TEST(TopoTest, FindIndex_no10) {
  clearAll();
  strcpy(words[wordCount++], "cat");
  strcpy(words[wordCount++], "dog");

  EXPECT_EQ(findIndex("dog"), 1);
  EXPECT_EQ(findIndex("bird"), -1);
}
