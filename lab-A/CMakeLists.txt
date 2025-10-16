cmake_minimum_required(VERSION 3.31)
project(Long_Arif C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_EXE  LongArfInt_tests.c)

set(SOURCE_LIB  LongAriInt.c)

add_library(Long_Arif STATIC ${SOURCE_LIB})

add_executable(Long_Arif_Tests ${SOURCE_EXE})

target_link_libraries(Long_Arif_Tests Long_Arif)