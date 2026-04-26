cmake_minimum_required(VERSION 3.10)
project(TreeBal)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(tree_bal main.c tree_bal.c)
add_executable(run_tests tests.c tree_bal.c)

target_compile_options(tree_bal PRIVATE -Wall)
target_compile_options(run_tests PRIVATE -Wall)
