cmake_minimum_required(VERSION 3.10)
project(GraphSearch)

set(CMAKE_C_STANDARD 11)

# Основная программа
add_executable(RunProgram main.c graph.c)

# Юнит-тесты
add_executable(RunTests test_graph.c graph.c)

# Настройки для Visual Studio
if(MSVC)
    target_compile_options(RunProgram PRIVATE /W4)
    target_compile_options(RunTests PRIVATE /W4)
else()
    target_compile_options(RunProgram PRIVATE -Wall -Wextra)
    target_compile_options(RunTests PRIVATE -Wall -Wextra)
endif()