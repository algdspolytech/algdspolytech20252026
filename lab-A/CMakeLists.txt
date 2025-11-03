cmake_minimum_required(VERSION 3.14)
project(QueueLab C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(main main.c)

add_executable(tests tests.c)
