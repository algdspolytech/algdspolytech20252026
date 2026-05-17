#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#pragma warning(disable : 4996)

#ifndef GRAPH_LIB_H
extern "C" {
#include "graph_lib.h"
}
#endif

#define INF HUGE_VAL

#define read_existing_graph()                                                  \
  graph_t *graph = read_graph("matrices/matrix1.txt");

#define read_graph_with_negloop()
graph_t *graph = read_graph("matrices/matrix_with_neg_loop.txt");

#define free_all()                                                             \
  free_graph(graph);                                                           \
  free_path(path);

using ::testing::IsNan;

TEST(ReadGraphTest, ReadExistingGraph_5Expected_no1) {
  read_existing_graph();
  double testVal = graph->adjacency[0][2];
  free_graph(graph);
  ASSERT_EQ(testVal, 5);
}

TEST(ReadGraphTest, ReadNonExistingGraph_NULLExpected_no2) {
  graph_t *graph = read_graph("matrices/matrix_error.txt");
  ASSERT_FALSE(graph);
}

TEST(RelaxTest, RelaxNodes1_6_CanImprove_15Expected_no3) {
  read_existing_graph();
  path_t *path = make_path(graph->n, 1);
  relax(graph, 0, 5, path->d, path->pi);

  double testVal = path->d[5];

  free_all();

  ASSERT_EQ(testVal, 15);
}

TEST(RelaxTest, RelaxNodes1_6_CannotImprove_13Expected_no4) {
  read_existing_graph();
  path_t *path = make_path(graph->n, 1);

  bellman_ford(graph, path, 1, 6);

  double valBefore = path->d[5];
  relax(graph, 1, 6, path->d, path->pi);
  double valAfter = path->d[5];
  free_all();

  ASSERT_EQ(valBefore, valAfter);
}

TEST(BellmanFordTest, NoNegativeLoops_TrueExpected_no5) {
  read_existing_graph();
  path_t *path = make_path(graph->n, 1);
  bool testVal = bellman_ford(graph, path, 1, 6);
  free_all();
  ASSERT_TRUE(testVal);
}

TEST(BellmanFordTest, IsNegativeLoop_FalseExpected_no6) {
  read_graph_with_negloop();
  path_t *path = make_path(graph->n, 1);
  bool testVal = bellman_ford(graph, path, 1, 2);
  free_all();
  ASSERT_FALSE(testVal);
}

TEST(NodeDistanceTest, NormalGraph_1to6distance_13Expected_no7) {

  double testVal = nodes_distance(1, 6, "matrices/matrix1.txt");

  ASSERT_EQ(testVal, 13);
}

TEST(NodeDistanceTest, IsNegativeLoop_MinusInfExpected_no8) {

  double testVal = nodes_distance(1, 6, "matrices/matrix_with_neg_loop.txt");

  ASSERT_EQ(testVal, -INF);
}

TEST(NodeDistanceTest, NegativeLoopNotReachedFromSource_5Expected_no9) {
  double testVal = nodes_distance(1, 2, "matrices/matrix_negloop_not_used.txt");
  printf("%f\n", testVal);
  ASSERT_EQ(testVal, 5);
}

TEST(NodeDistanceTest, NoGraph_NAN_Expected_no10) {
  double testVal = nodes_distance(2, 5, "matrices/matrix_error.txt");

  EXPECT_THAT(testVal, IsNan());
}

int main(int argc, char **argv) {

  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}