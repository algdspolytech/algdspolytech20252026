#define _CRT_SECURE_NO_WARNINGS
#define main main_program
#include "../Project7/source.c"
#undef main
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>


void create_file(const char* filename, const char* content) {
    FILE* f = fopen(filename, "w");
    if (f) {
        fprintf(f, "%s", content);
        fclose(f);
    }
}

void cleanup() {
    remove("test1.txt");
    remove("test2.txt");
    remove("test3.txt");
    remove("test4.txt");
}

// ТЕСТ 1: Чтение списка смежности
void test1() {
    create_file("test1.txt", "1 2\n0 2\n0 1\n");

    GraphList graph;
    bool result = read_list("test1.txt", &graph);

    assert(result == true);
    assert(graph.n == 3);
    assert(graph.sizes[0] == 2);
    printf("Тест 1 пройден\n");
}

// ТЕСТ 2: Чтение пустого списка
void test2() {
    create_file("test2.txt", "");

    GraphList graph;
    bool result = read_list("test2.txt", &graph);

    assert(result == true);
    assert(graph.n == 0);
    printf("Тест 2 пройден\n");
}

// ТЕСТ 3: Чтение несуществующего списка
void test3() {
    GraphList graph;
    bool result = read_list("nonexistent.txt", &graph);
    assert(result == false);
    printf("Тест 3 пройден\n");
}

// ТЕСТ 4: Чтение матрицы
void test4() {
    create_file("test3.txt", "0 1 1\n1 0 1\n1 1 0\n");

    GraphMatrix graph;
    bool result = read_matrix("test3.txt", &graph);

    assert(result == true);
    assert(graph.n == 3);
    assert(graph.matrix[0][1] == 1);
    printf("Тест 4 пройден\n");
}

// ТЕСТ 5: Матрица 1x1
void test5() {
    create_file("test4.txt", "0\n");

    GraphMatrix graph;
    bool result = read_matrix("test4.txt", &graph);

    assert(result == true);
    assert(graph.n == 1);
    printf("Тест 5 пройден\n");
}

// ТЕСТ 6: Несуществующая матрица
void test6() {
    GraphMatrix graph;
    bool result = read_matrix("nonexistent_matrix.txt", &graph);
    assert(result == false);
    printf("Тест 6 пройден\n");
}

// ТЕСТ 7: Идентичные графы
void test7() {
    GraphList list;
    GraphMatrix matrix;

    list.n = 3;
    list.sizes[0] = 2; list.list[0][0] = 1; list.list[0][1] = 2;
    list.sizes[1] = 2; list.list[1][0] = 0; list.list[1][1] = 2;
    list.sizes[2] = 2; list.list[2][0] = 0; list.list[2][1] = 1;

    matrix.n = 3;
    matrix.matrix[0][1] = 1; matrix.matrix[0][2] = 1;
    matrix.matrix[1][0] = 1; matrix.matrix[1][2] = 1;
    matrix.matrix[2][0] = 1; matrix.matrix[2][1] = 1;

    assert(graphs_equal(&list, &matrix) == true);
    printf("Тест 7 пройден\n");
}

// ТЕСТ 8: Разное число вершин
void test8() {
    GraphList list;
    GraphMatrix matrix;

    list.n = 2;
    matrix.n = 3;

    assert(graphs_equal(&list, &matrix) == false);
    printf("Тест 8 пройден\n");
}

// ТЕСТ 9: Разные ребра
void test9() {
    GraphList list;
    GraphMatrix matrix;

    list.n = 2;
    list.sizes[0] = 1; list.list[0][0] = 1;
    list.sizes[1] = 0;

    matrix.n = 2;
    matrix.matrix[0][1] = 1;
    matrix.matrix[1][0] = 1;

    assert(graphs_equal(&list, &matrix) == false);
    printf("Тест 9 пройден\n");
}

// ТЕСТ 10: Пустые графы
void test10() {
    GraphList list;
    GraphMatrix matrix;

    list.n = 0;
    matrix.n = 0;

    assert(graphs_equal(&list, &matrix) == true);
    printf("Тест 10 пройден\n");
}

// ТЕСТ 11: Петли
void test11() {
    GraphList list;
    GraphMatrix matrix;

    list.n = 2;
    list.sizes[0] = 2; list.list[0][0] = 0; list.list[0][1] = 1;
    list.sizes[1] = 1; list.list[1][0] = 1;

    matrix.n = 2;
    matrix.matrix[0][0] = 1; matrix.matrix[0][1] = 1;
    matrix.matrix[1][1] = 1;

    assert(graphs_equal(&list, &matrix) == true);
    printf("Тест 11 пройден\n");
}

// ТЕСТ 12: Изолированные вершины
void test12() {
    GraphList list;
    GraphMatrix matrix;

    list.n = 3;
    list.sizes[0] = 0;
    list.sizes[1] = 0;
    list.sizes[2] = 0;

    matrix.n = 3;

    assert(graphs_equal(&list, &matrix) == true);
    printf("Тест 12 пройден\n");
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    cleanup();
    printf("\nВсе 12 тестов пройдены!\n");
    return 0;
}