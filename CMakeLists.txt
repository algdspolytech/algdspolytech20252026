cmake_minimum_required(VERSION 3.10)
project(GraphColoring)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Исполняемый файл основной программы
add_executable(graph_coloring main.c graph_coloring.c)

# # Исполняемый файл для тестов
add_executable(run_tests tests.c graph_coloring.c)

target_compile_options(graph_coloring PRIVATE -Wall)
target_compile_options(run_tests PRIVATE -Wall)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/input.txt"
    "${CMAKE_CURRENT_BINARY_DIR}/input.txt"
    COPYONLY
)