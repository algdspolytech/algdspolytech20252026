cmake_minimum_required(VERSION 3.31)
project(Lab_D C)

set(CMAKE_C_STANDARD 11)

set(SOURCE VertexCover.c)

set(TESTS tests_VertexCover.c)

add_library(LIB STATIC ${SOURCE})

add_executable(WORK ${TESTS})

target_link_libraries(WORK LIB)