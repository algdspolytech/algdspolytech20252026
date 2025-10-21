cmake_minimum_required(VERSION 3.10)
project(PriorityQueue C)

set(CMAKE_C_STANDARD 11)

add_executable(priority_queue_demo
    main.c
    priority_queue.c
    priority_queue.h
)

add_executable(priority_queue_tests
    test_priority_queue.c
    priority_queue.c
    priority_queue.h
)