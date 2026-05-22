cmake_minimum_required(VERSION 3.7)

project(Lab_D)

set(SOURCE Lab_D_test.cpp)

include_directories(nqueens)

file(COPY Input/input.txt Input/bad_input.txt DESTINATION Input)

add_executable(main ${SOURCE})

add_subdirectory(nqueens)

target_link_libraries(main queens gtest gmock)

target_compile_options(main PUBLIC -lm) 