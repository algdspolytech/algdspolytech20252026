cmake_minimum_required(VERSION 3.7)

project(Lab_C)

set(SOURCE Lab_C_test.cpp)

include_directories(graph_lib)

file(COPY matrices/matrix1.txt matrices/matrix_with_neg_loop.txt matrices/matrix_negloop_not_used.txt DESTINATION matrices)

add_executable(main ${SOURCE})

add_subdirectory(graph_lib)

target_link_libraries(main graph gtest gmock)

target_compile_options(main PUBLIC -lm)