#include <stdio.h>
#include <locale.h>
#include "config.h"
#include "list.h"



int tests_passed = 0;
int tests_failed = 0;


void RUN_TEST(int test_num, const char* test_name, int (*test_func)(void)) {
    printf("Тест %d: %s\n", test_num, test_name);
    if (test_func()) {
        printf("Пройден \n");
        tests_passed++;
    }
    else {
        printf("Ошибка \n");
        tests_failed++;
    }
    printf("\n");
}



bool topo_from_input(const char* vertices, const char* edges[], int edge_count, char result[][MAX_WORD_LEN]) {
    Graph graph;
    init_graph(&graph);
    char words[MAX_WORDS][MAX_WORD_LEN];

    int v_count = parse_words(vertices, words);
    for (int i = 0; i < v_count; i++) {
        add_node(&graph, words[i]);
    }

    for (int i = 0; i < edge_count; i++) {
        int e_count = parse_words(edges[i], words);
        if (e_count >= 2) {
            add_edge(&graph, words[0], words[1]);
        }
    }

    bool success = topological_sort(&graph, result);
    free_graph(&graph);
    return success;
}

// Проверка корректности результата
bool is_valid_order(const char* vertices, const char* edges[], int edge_count, char result[][MAX_WORD_LEN], int n) {
    char verts[MAX_WORDS][MAX_WORD_LEN];
    int v_count = parse_words(vertices, verts);

    bool found[MAX_WORDS] = { false };
    for (int i = 0; i < n; i++) {
        bool ok = false;
        for (int j = 0; j < v_count; j++) {
            if (strcmp(result[i], verts[j]) == 0) {
                if (found[j]) return false;
                found[j] = true;
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    for (int j = 0; j < v_count; j++) {
        if (!found[j]) return false;
    }

    for (int i = 0; i < edge_count; i++) {
        char edge_words[2][MAX_WORD_LEN];
        int cnt = parse_words(edges[i], edge_words);
        if (cnt < 2) continue;
        const char* from = edge_words[0];
        const char* to = edge_words[1];

        int pos_from = -1, pos_to = -1;
        for (int k = 0; k < n; k++) {
            if (strcmp(result[k], from) == 0) pos_from = k;
            if (strcmp(result[k], to) == 0) pos_to = k;
        }
        if (pos_from == -1 || pos_to == -1) continue;
        if (pos_from >= pos_to) return false;
    }
    return true;
}


int empty_graph() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    bool ok = topo_from_input("", NULL, 0, result);
    return ok ? 1 : 0;
}

int single_node() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    bool ok = topo_from_input("x", NULL, 0, result);
    if (!ok) return 0;
    return (strcmp(result[0], "x") == 0) ? 1 : 0;
}

int simple_chain() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    const char* edges[2] = { "a b", "b c" };
    bool ok = topo_from_input("a b c", edges, 2, result);
    if (!ok) return 0;
    return is_valid_order("a b c", edges, 2, result, 3) ? 1 : 0;
}

int example_1() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    const char* edges[3] = { "a b", "d c", "b d" };
    bool ok = topo_from_input("a b c d e f", edges, 3, result);
    if (!ok) return 0;
    return is_valid_order("a b c d e f", edges, 3, result, 6) ? 1 : 0;
}

int cycle_2() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    const char* edges[2] = { "a b", "b a" };
    bool ok = topo_from_input("a b", edges, 2, result);
    return !ok ? 1 : 0; // должен быть false
}

int cycle_3() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    const char* edges[3] = { "a b", "b c", "c a" };
    bool ok = topo_from_input("a b c", edges, 3, result);
    return !ok ? 1 : 0;
}

int independent_nodes() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    bool ok = topo_from_input("x y z", NULL, 0, result);
    if (!ok) return 0;
    // Порядок должен быть исходным: x y z
    return (strcmp(result[0], "x") == 0 &&
        strcmp(result[1], "y") == 0 &&
        strcmp(result[2], "z") == 0) ? 1 : 0;
}

int duplicate_edges() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    const char* edges[4] = { "a b", "a b", "b c", "a b" };
    bool ok = topo_from_input("a b c", edges, 4, result);
    if (!ok) return 0;
    return is_valid_order("a b c", edges, 4, result, 3) ? 1 : 0;
}

int node_with_no_edges_in_middle() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    const char* edges[2] = { "a b", "b d" };
    bool ok = topo_from_input("a b c d", edges, 2, result);
    if (!ok) return 0;
    return is_valid_order("a b c d", edges, 2, result, 4) ? 1 : 0;
}

int disconnected_components() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    const char* edges[2] = { "a b", "c d" };
    bool ok = topo_from_input("a b c d", edges, 2, result);
    if (!ok) return 0;
    return is_valid_order("a b c d", edges, 2, result, 4) ? 1 : 0;
}

int self_loop() {
    char result[MAX_WORDS][MAX_WORD_LEN];
    const char* edges[1] = { "a a" };
    bool ok = topo_from_input("a", edges, 1, result);
    return !ok ? 1 : 0;
}



void run_all_tests(void) {
    setlocale(LC_CTYPE, "Russian");
    printf("=== Тесты ===\n\n");

    RUN_TEST(1, "Тест 1: Пустой граф", empty_graph);
    RUN_TEST(2, "Тест 2: Одна вершина", single_node);
    RUN_TEST(3, "Тест 3: Простая цепочка a->b->c", simple_chain);
    RUN_TEST(4, "Тест 4: Пример из задания", example_1);
    RUN_TEST(5, "Тест 5: Цикл длины 2", cycle_2);
    RUN_TEST(6, "Тест 6: Цикл длины 3", cycle_3);
    RUN_TEST(7, "Тест 7: Независимые вершины", independent_nodes);
    RUN_TEST(8, "Тест 8: Дублирующиеся ребра", duplicate_edges);
    RUN_TEST(9, "Тест 9: Независимая вершина в середине", node_with_no_edges_in_middle);
    RUN_TEST(10, "Тест 10: Две несвязанные цепочки", disconnected_components);
    RUN_TEST(11, "Тест 11: Самопетля (a->a)", self_loop);

    printf("=== Результат ===\n");
    printf("Всего тестов: %d\n", tests_passed + tests_failed);
    printf("Пройдено: %d\n", tests_passed);
    printf("Не пройдено: %d\n", tests_failed);


    if (tests_failed == 0) {
        printf("\n Все тесты успешно пройдены!\n");
    }
    else {
        printf("\n Некоторые тесты не пройдены!\n");
    }
}