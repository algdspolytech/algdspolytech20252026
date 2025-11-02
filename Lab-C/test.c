#include "lab.h"
#include <assert.h>

// functions for tests
void create_simple_graph(Graph* graph) {
	init_graph(graph);
	add_edge(graph, 0, 1);
	add_edge(graph, 1, 2);
	add_edge(graph, 2, 3);
}

void create_disconnected_graph(Graph* graph) {
	init_graph(graph);
	add_edge(graph, 0, 1);
	add_edge(graph, 1, 0);
	add_edge(graph, 2, 3);
	add_edge(graph, 3, 2);
}

// Tests for add_edge
void TestAddEdge_FirstEdge_no1() {
	Graph graph;
	init_graph(&graph);

	add_edge(&graph, 0, 1);

	assert(graph.size[0] == 1);
	assert(graph.adjacency_list[0][0] == 1);
	assert(graph.size[1] == 0);
	printf("TestAddEdge_FirstEdge_no1 - PASSED\n");
}

void TestAddEdge_MultipleEdges_no2() {
	Graph graph;
	init_graph(&graph);

	add_edge(&graph, 0, 1);
	add_edge(&graph, 0, 2);
	add_edge(&graph, 0, 3);

	assert(graph.size[0] == 3);
	assert(graph.adjacency_list[0][0] == 1);
	assert(graph.adjacency_list[0][1] == 2);
	assert(graph.adjacency_list[0][2] == 3);
	printf("TestAddEdge_MultipleEdges_no2 - PASSED\n");
}

// Tests for dfs
void TestDFS_SameVertex_no3() {
	Graph graph;
	init_graph(&graph);
	int visited[MAX_VERTICES] = { 0 };

	int result = dfs(&graph, 0, 0, visited);

	assert(result == 1);
	printf("TestDFS_SameVertex_no3 - PASSED\n");
}

void TestDFS_DirectConnection_no4() {
	Graph graph;
	init_graph(&graph);
	add_edge(&graph, 0, 1);
	int visited[MAX_VERTICES] = { 0 };

	int result = dfs(&graph, 0, 1, visited);

	assert(result == 1);
	printf("TestDFS_DirectConnection_no4 - PASSED\n");
}

void TestDFS_NoConnection_no5() {
	Graph graph;
	init_graph(&graph);
	add_edge(&graph, 0, 1);
	add_edge(&graph, 2, 3);
	int visited[MAX_VERTICES] = { 0 };

	int result = dfs(&graph, 0, 3, visited);

	assert(result == 0);
	printf("TestDFS_NoConnection_no5 - PASSED\n");
}

// Tests for path_exists
void TestPathExists_DirectPath_no6() {
	Graph graph;
	create_simple_graph(&graph);

	int result = path_exists(&graph, 1, 2);

	assert(result == 1);
	printf("TestPathExists_DirectPath_no6 - PASSED\n");
}

void TestPathExists_DisconnectedGraph_no7() {
	Graph graph;
	create_disconnected_graph(&graph);

	int result = path_exists(&graph, 0, 3);

	assert(result == 0);
	printf("TestPathExists_DisconnectedGraph_no7 - PASSED\n");
}

void TestPathExists_SameVertex_no8() {
	Graph graph;
	create_simple_graph(&graph);

	int result = path_exists(&graph, 2, 2);

	assert(result == 1);
	printf("TestPathExists_SameVertex_no8 - PASSED\n");
}

void TestPathExists_ReversePath_no9() {
	Graph graph;
	create_simple_graph(&graph);

	int result = path_exists(&graph, 3, 0);

	assert(result == 0);
	printf("TestPathExists_ReversePath_no9- PASSED\n");
}

void TestPathExists_NonExistentVertices_no10() {
	Graph graph;
	init_graph(&graph);
	add_edge(&graph, 0, 1);

	int result1 = path_exists(&graph, 99, 0);
	int result2 = path_exists(&graph, 0, 99);

	assert(result1 == 0);
	assert(result2 == 0);
	printf("TestPathExists_NonExistentVertices_no10 - PASSED\n");
}

void TestPathExists_EmptyGraph_no11() {
	Graph graph;
	init_graph(&graph);

	int result = path_exists(&graph, 0, 1);

	assert(result == 0);
	printf("TestPathExists_EmptyGraph_no11 - PASSED\n");
}

//  run all tests
void run_all_tests() {
	printf("\nunit tests...\n\n");

	TestAddEdge_FirstEdge_no1();
	TestAddEdge_MultipleEdges_no2();
	TestDFS_SameVertex_no3();
	TestDFS_DirectConnection_no4();
	TestDFS_NoConnection_no5();
	TestPathExists_DirectPath_no6();
	TestPathExists_DisconnectedGraph_no7();
	TestPathExists_SameVertex_no8();
	TestPathExists_ReversePath_no9();
	TestPathExists_NonExistentVertices_no10();
	TestPathExists_EmptyGraph_no11();

	printf("\nAll tests passed successfully!\n");
}
