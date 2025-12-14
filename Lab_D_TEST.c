#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

extern int n;
extern int graph[1000][1000];
extern int path[1000];
extern int used[1000];
extern int find_hamiltonian_path(void);

void init_test_graph(int vertex_count) {
    n = vertex_count;
    for (int i = 0; i < vertex_count; i++) {
        used[i] = 0;
        path[i] = -1;
        for (int j = 0; j < vertex_count; j++) {
            graph[i][j] = 0;
        }
    }
}

void add_edge(int a, int b) {
    graph[a][b] = 1;
    graph[b][a] = 1;
}

void test1() {
    printf("1. Пример из задания -> ");
    init_test_graph(3);
    add_edge(0, 1);
    add_edge(1, 2);
    add_edge(2, 0);

    int result = find_hamiltonian_path();

    if (result == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", path[i] + 1);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    else {
        printf("0\n");
    }
}

void test2() {
    printf("2. Линия 1-2-3-4 -> ");
    init_test_graph(4);
    add_edge(0, 1);
    add_edge(1, 2);
    add_edge(2, 3);

    int result = find_hamiltonian_path();

    if (result == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", path[i] + 1);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    else {
        printf("0\n");
    }
}

void test3() {
    printf("3. Две изолированные вершины -> ");
    init_test_graph(2);

    int result = find_hamiltonian_path();

    if (result == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", path[i] + 1);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    else {
        printf("0\n");
    }
}

void test4() {
    printf("4. Одна вершина -> ");
    init_test_graph(1);

    int result = find_hamiltonian_path();

    if (result == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", path[i] + 1);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    else {
        printf("0\n");
    }
}

void test5() {
    printf("5. Полный граф K4 -> ");
    init_test_graph(4);
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            add_edge(i, j);
        }
    }

    int result = find_hamiltonian_path();

    if (result == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", path[i] + 1);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    else {
        printf("0\n");
    }
}

void test6() {
    printf("6. Звезда -> ");
    init_test_graph(5);
    for (int i = 1; i < 5; i++) {
        add_edge(0, i);
    }

    int result = find_hamiltonian_path();

    if (result == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", path[i] + 1);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    else {
        printf("0\n");
    }
}

void test7() {
    printf("7. Цикл из 5 вершин -> ");
    init_test_graph(5);
    for (int i = 0; i < 5; i++) {
        add_edge(i, (i + 1) % 5);
    }

    int result = find_hamiltonian_path();

    if (result == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", path[i] + 1);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    else {
        printf("0\n");
    }
}

void test8() {
    printf("8. Несвязный граф -> ");
    init_test_graph(4);
    add_edge(0, 1);
    add_edge(2, 3);

    int result = find_hamiltonian_path();

    if (result == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", path[i] + 1);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    else {
        printf("0\n");
    }
}

void test9() {
    printf("9. Граф, где путь начинается с вершины 2 -> ");
    init_test_graph(4);
    add_edge(1, 0);
    add_edge(0, 2);
    add_edge(2, 3);

    int result = find_hamiltonian_path();

    if (result == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", path[i] + 1);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    else {
        printf("0\n");
    }
}

void test10() {
    printf("10. Большой граф  ->  ");
    init_test_graph(6);
    add_edge(0, 1);
    add_edge(1, 2);
    add_edge(3, 4);
    add_edge(4, 5);
    add_edge(0, 3);
    add_edge(1, 4);
    add_edge(2, 5);

    int result = find_hamiltonian_path();

    if (result == 1) {
        for (int i = 0; i < n; i++) {
            printf("%d", path[i] + 1);
            if (i < n - 1) printf(" ");
        }
        printf("\n");
    }
    else {
        printf("0\n");
    }
}

int main(void) {
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

    return 0;
}