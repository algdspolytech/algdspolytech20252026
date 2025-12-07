cmake_minimum_required(VERSION 3.12)

set(GOOGLETEST_VERSION 1.17.0)

project(labc)

enable_testing()

add_subdirectory(googletest)

include_directories(googletest/include)

# 1. Сначала создаём библиотеку из вашего основного кода
add_library(graph_lib Homework_C.c)

# 2. Создаём исполняемый файл для тестов
add_executable(mytests mytests.cpp)

# 3. Связываем тесты с вашей библиотекой и gtest
target_link_libraries(mytests PRIVATE graph_lib gtest)

include(GoogleTest)
gtest_discover_tests(mytests)