cmake_minimum_required(VERSION 3.10)
project(ListSort)

set(CMAKE_C_STANDARD 11)

# Основная программа
add_executable(RunProgram main.c list_sort.c)

# Юнит-тесты
add_executable(RunTests tests_list_sort.c list_sort.c)