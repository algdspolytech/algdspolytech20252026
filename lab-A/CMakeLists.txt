cmake_minimum_required(VERSION 3.15)
project(VertexCover C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Основная программа
add_executable(vertex_cover main.c cover.c)

# Простые тесты
add_executable(simple_tests tests.c cover.c)