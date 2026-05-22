cmake_minimum_required(VERSION 3.7)

project(queens_lib)

set(SOURCE_LIB nqueens.c)

add_library(queens STATIC ${SOURCE_LIB})