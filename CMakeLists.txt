cmake_minimum_required(VERSION 3.10)
project(TreeDiff)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(tree_diff main.c tree_diff.c)
# add_executable(run_tests tests.c tree_diff.c)

target_compile_options(tree_diff PRIVATE -Wall)
# target_compile_options(run_tests PRIVATE -Wall)