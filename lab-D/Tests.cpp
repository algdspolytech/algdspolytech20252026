#define _CRT_SECURE_NO_WARNINGS
#include "gtest/gtest.h"

extern "C" {
#include <stdio.h>
#include <stdlib.h>

#define MAXV 1000

    typedef struct {
        int V, K;
        int** adj;
        int* deg;
        int* used;
        int* best;
        int found;
    } GraphData;

    // function declarations
    void free_graph(GraphData* g);
    int all_edges_covered(GraphData* g);
    void backtrack(GraphData* g, int vertex, int chosen);
    int solve_vertex_cover(const char* input_file, const char* output_file);

    // if you have separate function for reading graph
    int read_graph_from_file(const char* filename, GraphData* g);
}

// === Test helper functions ===

// Create empty graph with given number of vertices and K
GraphData make_empty_graph(int V, int K) {
    GraphData g;
    g.V = V;
    g.K = K;
    g.adj = (int**)malloc((V + 1) * sizeof(int*));
    g.deg = (int*)calloc(V + 1, sizeof(int));
    g.used = (int*)calloc(V + 1, sizeof(int));
    g.best = (int*)calloc(V + 1, sizeof(int));
    g.found = 0;
    for (int i = 1; i <= V; i++) g.adj[i] = nullptr;
    return g;
}

// === Tests for all_edges_covered ===

TEST(all_edges_covered_NoUsedVertices_ReturnFalse) {
    GraphData g = make_empty_graph(3, 2);
    for (int i = 1; i <= 3; i++)
        g.adj[i] = (int*)malloc(3 * sizeof(int));
    // edges 1-2, 2-3
    g.adj[1][0] = 2; g.deg[1] = 1;
    g.adj[2][0] = 1; g.adj[2][1] = 3; g.deg[2] = 2;
    g.adj[3][0] = 2; g.deg[3] = 1;

    EXPECT_EQ(all_edges_covered(&g), 0);
    free_graph(&g);
}

TEST(all_edges_covered_AllUsedVertices_ReturnTrue) {
    GraphData g = make_empty_graph(2, 1);
    for (int i = 1; i <= 2; i++)
        g.adj[i] = (int*)malloc(2 * sizeof(int));
    g.adj[1][0] = 2; g.deg[1] = 1;
    g.adj[2][0] = 1; g.deg[2] = 1;

    g.used[1] = 1; g.used[2] = 1;

    EXPECT_EQ(all_edges_covered(&g), 1);
    free_graph(&g);
}

TEST(all_edges_covered_EmptyGraph_ReturnTrue) {
    GraphData g = make_empty_graph(0, 0);
    EXPECT_EQ(all_edges_covered(&g), 1);
    free_graph(&g);
}

// === Tests for backtrack ===

TEST(backtrack_SmallGraph_FoundVertexCover) {
    GraphData g = make_empty_graph(2, 1);
    for (int i = 1; i <= 2; i++)
        g.adj[i] = (int*)malloc(2 * sizeof(int));
    g.adj[1][0] = 2; g.deg[1] = 1;
    g.adj[2][0] = 1; g.deg[2] = 1;

    backtrack(&g, 1, 0);
    EXPECT_EQ(g.found, 1);
    int sum = g.best[1] + g.best[2];
    EXPECT_EQ(sum, 1);
    free_graph(&g);
}

TEST(backtrack_TooSmallK_NoSolutionFound) {
    GraphData g = make_empty_graph(2, 0);
    for (int i = 1; i <= 2; i++)
        g.adj[i] = (int*)malloc(2 * sizeof(int));
    g.adj[1][0] = 2; g.deg[1] = 1;
    g.adj[2][0] = 1; g.deg[2] = 1;

    backtrack(&g, 1, 0);
    EXPECT_EQ(g.found, 0);
    free_graph(&g);
}

TEST(backtrack_MediumGraph_FindMinimalCover) {
    GraphData g = make_empty_graph(3, 2);
    for (int i = 1; i <= 3; i++)
        g.adj[i] = (int*)malloc(3 * sizeof(int));
    g.adj[1][0] = 2; g.deg[1] = 1;
    g.adj[2][0] = 1; g.adj[2][1] = 3; g.deg[2] = 2;
    g.adj[3][0] = 2; g.deg[3] = 1;

    backtrack(&g, 1, 0);
    EXPECT_EQ(g.found, 1);
    int sum = g.best[1] + g.best[2] + g.best[3];
    EXPECT_EQ(sum, 2); // minimal vertex cover
    free_graph(&g);
}

// === Tests for free_graph ===

TEST(free_graph_NormalGraph_MemoryFreed) {
    GraphData g = make_empty_graph(2, 1);
    for (int i = 1; i <= 2; i++)
        g.adj[i] = (int*)malloc(2 * sizeof(int));

    free_graph(&g);
    EXPECT_EQ(g.V, 0);
    EXPECT_EQ(g.adj, nullptr);
    EXPECT_EQ(g.deg, nullptr);
    EXPECT_EQ(g.used, nullptr);
    EXPECT_EQ(g.best, nullptr);
}

// === Tests for read_graph_from_file ===

TEST(read_graph_from_file_EmptyFile_ReturnFalse) {
    const char* filename = "empty_test_file.txt";
    FILE* f = fopen(filename, "w"); fclose(f);

    GraphData g;
    int result = read_graph_from_file(filename, &g);
    EXPECT_EQ(result, 0);
}

TEST(read_graph_from_file_ValidGraph_ReturnTrue) {
    const char* filename = "valid_test_file.txt";
    FILE* f = fopen(filename, "w");
    fprintf(f, "2 1\n2\n1\n");
    fclose(f);

    GraphData g;
    int result = read_graph_from_file(filename, &g);
    EXPECT_EQ(result, 1);
    EXPECT_EQ(g.V, 2);
    EXPECT_EQ(g.K, 1);
    EXPECT_EQ(g.deg[1], 1);
    EXPECT_EQ(g.adj[1][0], 2);
    EXPECT_EQ(g.deg[2], 1);
    EXPECT_EQ(g.adj[2][0], 1);

    free_graph(&g);
}

TEST(read_graph_from_file_InvalidVertex_ReturnFalse) {
    const char* filename = "invalid_vertex.txt";
    FILE* f = fopen(filename, "w");
    fprintf(f, "2 1\n3\n1\n"); // vertex 3 doesn't exist
    fclose(f);

    GraphData g;
    int result = read_graph_from_file(filename, &g);
    EXPECT_EQ(result, 0);
}

// === Test for read_graph_from_file with empty edge line ===

TEST(read_graph_from_file_EmptyEdgeLine_ReturnFalse) {
    const char* filename = "empty_edge_line.txt";
    FILE* f = fopen(filename, "w");
    fprintf(f, "2 1\n\n\n"); // empty lines
    fclose(f);

    GraphData g;
    int result = read_graph_from_file(filename, &g);

    // Expect reading to fail due to empty lines
    EXPECT_EQ(result, 0);

    // After failed reading, graph should be empty
    EXPECT_EQ(g.V, 0);
    EXPECT_EQ(g.K, 0);
    EXPECT_EQ(g.adj, nullptr);
    EXPECT_EQ(g.deg, nullptr);
    EXPECT_EQ(g.used, nullptr);
    EXPECT_EQ(g.best, nullptr);
}