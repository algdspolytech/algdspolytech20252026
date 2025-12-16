cmake_minimum_required(VERSION 3.15)
project(VertexCover C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Основная программа
add_executable(vertex_cover main.c cov.c)

# Тесты
add_executable(simple_tests program_tests.c cov.c)