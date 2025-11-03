#pragma once
#define UNIT_TEST_H

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void create_test_file(const char* filename, const char* content);
void test_normal_case_no1();
void test_graphs_different_no2();
void test_different_vertex_count_no3();
void test_single_vertex_no4();
void test_complete_graph_no5();
void test_self_loops_no6();
void test_disconnected_graph_no7();
void test_directed_graph_no8();
void test_large_graph_no9();
void test_weighted_graph_binary_no10();
void test_extra_spaces_no11();
void test_empty_lines_no12();