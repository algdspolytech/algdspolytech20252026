cmake_minimum_required(VERSION 3.7)

project(Lab_A)

set(SOURCE Lab_A_test.cpp)

include_directories(str_sort)

add_executable(main ${SOURCE})

add_subdirectory(str_sort)

target_link_libraries(main sort gtest gmock)

target_compile_options(main PUBLIC -lm) 