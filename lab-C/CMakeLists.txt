cmake_minimum_required(VERSION 3.31)
project(Lab_C C)

set(CMAKE_C_STANDARD 11)

set(SOURCE Search_Graph.c )

set(TESTS tests_Serach_Graph.c)

add_library(LIB STATIC ${SOURCE})

add_executable(WORK ${TESTS})

target_link_libraries(WORK LIB)
