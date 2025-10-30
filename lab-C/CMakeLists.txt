cmake_minimum_required(VERSION 3.10)
project(DFS_Path_Finder C)

set(CMAKE_C_STANDARD 11)

add_executable(dfs_program 
    main.c 
    dfs.c
)

add_executable(dfs_tests 
    test_dfs.c 
    dfs.c
)

target_include_directories(dfs_program PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(dfs_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})