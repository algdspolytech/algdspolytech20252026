#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern "C" {
    #include "LabC.h"
}

class GraphTest : public ::testing::Test {
protected:
    void SetUp() override {
    }
};


// readgraph tests
TEST_F(GraphTest, readgraph_ValidFile_ValidGraph_no1) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertices, 10);
    freegraph(graph);
}

TEST_F(GraphTest, readgraph_emptyFile_Null_no2) {
    Graph* graph = readgraph("empty_file.txt");
    EXPECT_EQ(graph, nullptr);
}

// shortpath tests
TEST_F(GraphTest, shortpath_SameStartEnd_ZeroDistance_no3) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);

    PathResult* result = shortpath(graph, 5, 5);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->distance, 0);
    EXPECT_EQ(result->length, 1);
    EXPECT_EQ(result->path[0], 5);

    freeresult(result);
    freegraph(graph);
}

TEST_F(GraphTest, shortpath_DirectlyConnected_ValidPath_no4) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);

    PathResult* result = shortpath(graph, 0, 1);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->distance, 2);
    EXPECT_EQ(result->length, 2);

    freeresult(result);
    freegraph(graph);
}

TEST_F(GraphTest, shortpath_MultipleHops_ValidPath_no5) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);

    PathResult* result = shortpath(graph, 0, 9);
    ASSERT_NE(result, nullptr);
    EXPECT_GT(result->distance, 0);
    EXPECT_GT(result->length, 2);

    freeresult(result);
    freegraph(graph);
}

TEST_F(GraphTest, shortpath_NullGraph_Null_no6) {
    PathResult* result = shortpath(nullptr, 0, 5);
    EXPECT_EQ(result, nullptr);
}

TEST_F(GraphTest, shortpath_NegativeStartVertex_Null_no7) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);

    PathResult* result = shortpath(graph, -1, 5);
    EXPECT_EQ(result, nullptr);
    freegraph(graph);
}

TEST_F(GraphTest, shortpath_OutOfBoundsStartVertex_Null_no8) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);

    PathResult* result = shortpath(graph, 15, 5);
    EXPECT_EQ(result, nullptr);
    freegraph(graph);
}

TEST_F(GraphTest, shortpath_NegativeEndVertex_Null_no9) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);

    PathResult* result = shortpath(graph, 0, -5);
    EXPECT_EQ(result, nullptr);
    freegraph(graph);
}

TEST_F(GraphTest, shortpath_OutOfBoundsEndVertex_Null_no10) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);

    PathResult* result = shortpath(graph, 0, 20);
    EXPECT_EQ(result, nullptr);
    freegraph(graph);
}

TEST_F(GraphTest, shortpath_SpecificPath_CorrectDistance_no11) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);

    // Test path from vertex 0 to 4: should be 0->3->4 with distance 1+2=3
    PathResult* result = shortpath(graph, 0, 4);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->distance, 3);

    freeresult(result);
    freegraph(graph);
}

// freeresult tests
TEST_F(GraphTest, freeresult_NullInput_NoCrash_no12) {
    freeresult(nullptr);
    SUCCEED();
}

TEST_F(GraphTest, freeresult_ValidInput_NoCrash_no13) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);

    PathResult* result = shortpath(graph, 0, 1);
    ASSERT_NE(result, nullptr);

    freeresult(result);
    freegraph(graph);
    SUCCEED();
}

// freegraph tests
TEST_F(GraphTest, freegraph_NullInput_NoCrash_no14) {
    freegraph(nullptr);
    SUCCEED();
}

TEST_F(GraphTest, freegraph_ValidInput_NoCrash_no15) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);
    freegraph(graph);
    SUCCEED();
}

// print tests (we can't easily test output, but we can test it doesn't crash)
TEST_F(GraphTest, print_NullInput_NoCrash_no16) {
    print(nullptr);
    SUCCEED();
}

TEST_F(GraphTest, print_ValidInput_NoCrash_no17) {
    Graph* graph = readgraph("graph.txt");
    ASSERT_NE(graph, nullptr);

    PathResult* result = shortpath(graph, 0, 2);
    ASSERT_NE(result, nullptr);

    print(result);

    freeresult(result);
    freegraph(graph);
    SUCCEED();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}