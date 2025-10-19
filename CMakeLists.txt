cmake_minimum_required(VERSION 4.0)
project(algdspolytech20252026__ C)

set(CMAKE_C_STANDARD 11)

include_directories(lab-C)

# Основная программа
add_executable(main_program
        ../algdspolytech20252026--/lab-C/graph.c
        ../algdspolytech20252026--/lab-C/graph.h
        ../algdspolytech20252026--/lab-C/main.c
)

# Юнит-тесты
add_executable(test_program
        ../algdspolytech20252026--/lab-C/graph.c
        ../algdspolytech20252026--/lab-C/graph.h
        ../algdspolytech20252026--/lab-C/test_graph.c
)

# Копируем graph.txt в директорию сборки
configure_file(${CMAKE_SOURCE_DIR}/graph.txt ${CMAKE_BINARY_DIR}/graph.txt COPYONLY)