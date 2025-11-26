cmake_minimum_required(VERSION 3.10)
project(WagonAssembler C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lab-D)

add_executable(wagon_main
        lab-D/main.c
        lab-D/wagon.c
)

add_executable(wagon_tests
        lab-D/tests.c
        lab-D/wagon.c
)

