#pragma warning(disable : 4996)

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <gtest/gtest.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "Lab_D.h"
}

class GraphSearchTest : public ::testing::Test {
 protected:
  void SetUp() override {
    test_input = fopen("test_labd_R.txt", "w+");
    test_output = fopen("test_labd_W.txt", "w+");
  }

  void TearDown() override {
    if (test_input) fclose(test_input);
    if (test_output) fclose(test_output);
    remove("test_labd_R.txt");
    remove("test_labd_W.txt");
  }

  void CreateTestFile(const char* content) {
    rewind(test_input);
    fputs(content, test_input);
    fflush(test_input);
    rewind(test_input);
  }

  FILE* test_input = nullptr;
  FILE* test_output = nullptr;
  GrphStrc graph;
};

TEST_F(GraphSearchTest, BasicPathMinLength_no1) {
  const char* content =
      "3 1 3 1\n"
      "2 3\n"
      "1 3\n"
      "1 2\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  EXPECT_EQ(V, 3);
  EXPECT_EQ(s, 1);
  EXPECT_EQ(t, 3);
  EXPECT_EQ(K, 1);

  DeepSearc(&graph, s, 0, V, t, K);

  rewind(test_output);
  Write(test_output, &graph);

  EXPECT_EQ(graph.flag, 1);
  EXPECT_GE(graph.ptl, K + 1);

  FreeGraph(&graph, V);
}

TEST_F(GraphSearchTest, NoPathExist_no2) {
  const char* content =
      "4 1 4 1\n"
      "2\n"
      "1 3\n"
      "2\n"
      "\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  DeepSearc(&graph, s, 0, V, t, K);

  rewind(test_output);
  Write(test_output, &graph);

  EXPECT_EQ(graph.flag, 0);

  FreeGraph(&graph, V);
}

TEST_F(GraphSearchTest, PathShort_no3) {
  const char* content =
      "3 1 3 3\n"
      "2\n"
      "1 3\n"
      "2\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  DeepSearc(&graph, s, 0, V, t, K);

  EXPECT_EQ(graph.flag, 0);

  FreeGraph(&graph, V);
}

TEST_F(GraphSearchTest, SingleTopGraph_no4) {
  const char* content =
      "1 1 1 0\n"
      "\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  DeepSearc(&graph, s, 0, V, t, K);

  EXPECT_EQ(graph.flag, 1);
  EXPECT_EQ(graph.ptl, 1);
  EXPECT_EQ(graph.path[0], 1);

  FreeGraph(&graph, V);
}

TEST_F(GraphSearchTest, ZeroKLength_no5) {
  const char* content =
      "3 1 3 0\n"
      "2 3\n"
      "1\n"
      "1\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  DeepSearc(&graph, s, 0, V, t, K);

  EXPECT_EQ(graph.flag, 1);

  FreeGraph(&graph, V);
}

TEST_F(GraphSearchTest, CyclicGraph_no6) {
  const char* content =
      "4 1 4 2\n"
      "2 3\n"
      "1 4\n"
      "1 4\n"
      "2 3\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  DeepSearc(&graph, s, 0, V, t, K);

  EXPECT_EQ(graph.flag, 1);
  EXPECT_GE(graph.ptl, K + 1);

  FreeGraph(&graph, V);
}

TEST_F(GraphSearchTest, LargeK_no7) {
  const char* content =
      "3 1 3 10\n"
      "2\n"
      "1 3\n"
      "2\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  DeepSearc(&graph, s, 0, V, t, K);

  EXPECT_EQ(graph.flag, 0);

  FreeGraph(&graph, V);
}

TEST_F(GraphSearchTest, GraphWithIsolVertice_no8) {
  const char* content =
      "4 1 4 1\n"
      "2\n"
      "1\n"
      "\n"
      "\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  DeepSearc(&graph, s, 0, V, t, K);

  EXPECT_EQ(graph.flag, 0);

  FreeGraph(&graph, V);
}

TEST_F(GraphSearchTest, InvalidInput_no9) {
  const char* content = "0 1 1 1\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  if (V > 0) {
    FreeGraph(&graph, V);
  }
}

TEST_F(GraphSearchTest, GraphWithSelfLoops_no10) {
  const char* content =
      "3 1 3 1\n"
      "1 2\n"
      "1 3\n"
      "2\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  DeepSearc(&graph, s, 0, V, t, K);

  EXPECT_EQ(graph.flag, 1);

  FreeGraph(&graph, V);
}

TEST_F(GraphSearchTest, MultiplePathsDifferentLengths_no11) {
  const char* content =
      "5 1 5 3\n"
      "2 3\n"
      "1 4\n"
      "1 5\n"
      "2 5\n"
      "3 4\n";
  CreateTestFile(content);

  int V, s, t, K;
  ReadLst(test_input, &graph, &V, &s, &t, &K);

  DeepSearc(&graph, s, 0, V, t, K);

  EXPECT_EQ(graph.flag, 1);
  EXPECT_GE(graph.ptl, K + 1);

  FreeGraph(&graph, V);
}

// int main(int argc, char** argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }