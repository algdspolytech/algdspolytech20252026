cmake_minimum_required(VERSION 3.7)

project(sort_lib)

set(SOURCE_LIB str_sort.c)

add_library(sort STATIC ${SOURCE_LIB})