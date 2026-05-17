cmake_minimum_required(VERSION 3.7)

project(graph)

set(SOURCE_LIB graph_lib.c)

add_library(graph STATIC ${SOURCE_LIB})

