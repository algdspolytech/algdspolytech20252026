cmake_minimum_required(VERSION 4.0)
project(algdspolytech20252026_ C)

set(CMAKE_C_STANDARD 11)

include_directories(lab-A)

add_executable(lab1_directory_tree
        ../algdspolytech20252026-/lab-A/main.c
        ../algdspolytech20252026-/lab-A/tree.c
)

add_executable(lab1_tests
        ../algdspolytech20252026-/lab-A/tests.c
        ../algdspolytech20252026-/lab-A/tree.c
)

# Убедимся что у каждого target уникальное имя output
set_target_properties(lab1_directory_tree PROPERTIES
        OUTPUT_NAME "lab1_directory_tree"
)

set_target_properties(lab1_tests PROPERTIES
        OUTPUT_NAME "lab1_tests"
)