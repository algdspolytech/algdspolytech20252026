cmake_minimum_required(VERSION 3.10)
project(LabC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(graph_cmp main.c graph.c
)
add_executable(test_graph test_graph.c graph.c)
