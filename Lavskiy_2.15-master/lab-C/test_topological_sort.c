#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
#include <locale.h>
#include "topological_sort.h"

// Простая система тестирования
int tests_passed = 0;
int tests_failed = 0;

#define TEST(name) void test_##name()
#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s:%d: %s\n", __FILE__, __LINE__, #condition); \
            tests_failed++; \
            return; \
        } \
    } while(0)

#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("FAIL: %s:%d: Expected %d, got %d\n", __FILE__, __LINE__, (expected), (actual)); \
            tests_failed++; \
            return; \
        } \
    } while(0)

#define ASSERT_STREQ(expected, actual) \
    do { \
        if (strcmp((expected), (actual)) != 0) { \
            printf("FAIL: %s:%d: Expected '%s', got '%s'\n", __FILE__, __LINE__, (expected), (actual)); \
            tests_failed++; \
            return; \
        } \
    } while(0)

#define RUN_TEST(test_function) \
    do { \
        printf("Running " #test_function "... "); \
        test_function(); \
        if (tests_failed == 0) { \
            printf("PASS\n"); \
            tests_passed++; \
        } else { \
            printf("FAILED\n"); \
        } \
    } while(0)

// Вспомогательные функции
void create_test_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s", content);
        fclose(file);
    }
}

char* read_output_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(length + 1);
    fread(content, 1, length, file);
    content[length] = '\0';

    fclose(file);
    return content;
}

// Тест 1: Базовая топологическая сортировка
void test_basic_topological_sort_no1() {
    create_test_file("test1_input.txt",
        "a b c d e f\n"
        "a b\n"
        "d c\n"
        "b d\n");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("test1_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    for (int i = 0; i < edge_count; i++) {
        add_edge(&graph, edges[i].from, edges[i].to);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT(result_count > 0);

    // Проверяем корректность порядка
    int a_index = -1, b_index = -1, d_index = -1, c_index = -1;
    for (int i = 0; i < result_count; i++) {
        if (strcmp(result[i], "a") == 0) a_index = i;
        if (strcmp(result[i], "b") == 0) b_index = i;
        if (strcmp(result[i], "d") == 0) d_index = i;
        if (strcmp(result[i], "c") == 0) c_index = i;
    }

    ASSERT(a_index < b_index); // a перед b
    ASSERT(b_index < d_index); // b перед d  
    ASSERT(d_index < c_index); // d перед c

    free_graph(&graph);
    remove("test1_input.txt");
}

// Тест 2: Обнаружение цикла
void test_cycle_detection_no2() {
    create_test_file("test2_input.txt",
        "a b c\n"
        "a b\n"
        "b c\n"
        "c a\n");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("test2_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    for (int i = 0; i < edge_count; i++) {
        add_edge(&graph, edges[i].from, edges[i].to);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT_EQ(result_count, 0); // Должен обнаружить цикл

    free_graph(&graph);
    remove("test2_input.txt");
}

// Тест 3: Один элемент
void test_single_element_no3() {
    create_test_file("test3_input.txt", "hello\n");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("test3_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT_EQ(result_count, 1);
    ASSERT_STREQ(result[0], "hello");

    free_graph(&graph);
    remove("test3_input.txt");
}

// Тест 4: Множество без ребер
void test_no_edges_no4() {
    create_test_file("test4_input.txt", "x y z\n");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("test4_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT_EQ(result_count, 3);

    free_graph(&graph);
    remove("test4_input.txt");
}

// Тест 5: Длинная цепочка зависимостей
void test_long_chain_no5() {
    create_test_file("test5_input.txt",
        "1 2 3 4 5\n"
        "1 2\n"
        "2 3\n"
        "3 4\n"
        "4 5\n");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("test5_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    for (int i = 0; i < edge_count; i++) {
        add_edge(&graph, edges[i].from, edges[i].to);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT_EQ(result_count, 5);

    free_graph(&graph);
    remove("test5_input.txt");
}

// Тест 6: Множественные зависимости
void test_multiple_dependencies_no6() {
    create_test_file("test6_input.txt",
        "a b c d\n"
        "a b\n"
        "a c\n"
        "b d\n"
        "c d\n");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("test6_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    for (int i = 0; i < edge_count; i++) {
        add_edge(&graph, edges[i].from, edges[i].to);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT_EQ(result_count, 4);

    int a_index = -1, b_index = -1, c_index = -1, d_index = -1;
    for (int i = 0; i < result_count; i++) {
        if (strcmp(result[i], "a") == 0) a_index = i;
        if (strcmp(result[i], "b") == 0) b_index = i;
        if (strcmp(result[i], "c") == 0) c_index = i;
        if (strcmp(result[i], "d") == 0) d_index = i;
    }

    ASSERT(a_index < b_index);
    ASSERT(a_index < c_index);
    ASSERT(b_index < d_index);
    ASSERT(c_index < d_index);

    free_graph(&graph);
    remove("test6_input.txt");
}

// Тест 7: Изолированные вершины
void test_isolated_vertices_no7() {
    create_test_file("test7_input.txt",
        "p q r s t\n"
        "p q\n"
        "r s\n");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("test7_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    for (int i = 0; i < edge_count; i++) {
        add_edge(&graph, edges[i].from, edges[i].to);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT_EQ(result_count, 5);

    free_graph(&graph);
    remove("test7_input.txt");
}

// Тест 8: Дублирующиеся ребра
void test_duplicate_edges_no8() {
    create_test_file("test8_input.txt",
        "x y z\n"
        "x y\n"
        "x y\n"  // Дубликат
        "y z\n");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("test8_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    for (int i = 0; i < edge_count; i++) {
        add_edge(&graph, edges[i].from, edges[i].to);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT_EQ(result_count, 3);

    int x_index = -1, y_index = -1, z_index = -1;
    for (int i = 0; i < result_count; i++) {
        if (strcmp(result[i], "x") == 0) x_index = i;
        if (strcmp(result[i], "y") == 0) y_index = i;
        if (strcmp(result[i], "z") == 0) z_index = i;
    }

    ASSERT(x_index < y_index);
    ASSERT(y_index < z_index);

    free_graph(&graph);
    remove("test8_input.txt");
}

// Тест 9: Сложный граф без циклов
void test_complex_graph_no_cycle_no9() {
    create_test_file("test9_input.txt",
        "a b c d e f g\n"
        "a b\n"
        "a c\n"
        "b d\n"
        "c d\n"
        "d e\n"
        "d f\n"
        "e g\n"
        "f g\n");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("test9_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    for (int i = 0; i < edge_count; i++) {
        add_edge(&graph, edges[i].from, edges[i].to);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT_EQ(result_count, 7);

    free_graph(&graph);
    remove("test9_input.txt");
}

// Тест 10: Пустой ввод
void test_empty_input_no10() {
    create_test_file("test10_input.txt", "");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    int read_result = read_input("test10_input.txt", &word_set, edges, &edge_count);

    ASSERT(!read_result);
    remove("test10_input.txt");
}

// Тест 11: Интеграционный тест
void test_file_integration_test_no11() {
    create_test_file("integration_input.txt",
        "alpha beta gamma\n"
        "alpha beta\n"
        "beta gamma\n");

    // Создаем копию main функции для тестирования
    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("integration_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    for (int i = 0; i < edge_count; i++) {
        add_edge(&graph, edges[i].from, edges[i].to);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT(result_count > 0);

    // Проверяем что все слова присутствуют
    int alpha_found = 0, beta_found = 0, gamma_found = 0;
    for (int i = 0; i < result_count; i++) {
        if (strcmp(result[i], "alpha") == 0) alpha_found = 1;
        if (strcmp(result[i], "beta") == 0) beta_found = 1;
        if (strcmp(result[i], "gamma") == 0) gamma_found = 1;
    }

    ASSERT(alpha_found);
    ASSERT(beta_found);
    ASSERT(gamma_found);

    free_graph(&graph);
    remove("integration_input.txt");
}

// Тест 12: Длинные слова
void test_long_words_no12() {
    create_test_file("test12_input.txt",
        "verylongword1 verylongword2 verylongword3\n"
        "verylongword1 verylongword2\n"
        "verylongword2 verylongword3\n");

    WordSet word_set;
    Edge edges[MAX_EDGES];
    int edge_count;

    ASSERT(read_input("test12_input.txt", &word_set, edges, &edge_count));

    Graph graph;
    graph.vertex_count = 0;

    for (int i = 0; i < word_set.count; i++) {
        add_vertex(&graph, word_set.words[i]);
    }

    for (int i = 0; i < edge_count; i++) {
        add_edge(&graph, edges[i].from, edges[i].to);
    }

    char result[MAX_WORDS][MAX_WORD_LEN];
    int result_count = topological_sort(&graph, result);

    ASSERT_EQ(result_count, 3);

    free_graph(&graph);
    remove("test12_input.txt");
}

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    printf("=== Запуск тестов топологической сортировки ===\n\n");

    // Запускаем все тесты
    RUN_TEST(test_basic_topological_sort_no1);
    RUN_TEST(test_cycle_detection_no2);
    RUN_TEST(test_single_element_no3);
    RUN_TEST(test_no_edges_no4);
    RUN_TEST(test_long_chain_no5);
    RUN_TEST(test_multiple_dependencies_no6);
    RUN_TEST(test_isolated_vertices_no7);
    RUN_TEST(test_duplicate_edges_no8);
    RUN_TEST(test_complex_graph_no_cycle_no9);
    RUN_TEST(test_empty_input_no10);
    RUN_TEST(test_file_integration_test_no11);
    RUN_TEST(test_long_words_no12);

    printf("\n=== Результаты тестирования ===\n");
    printf("Пройдено: %d\n", tests_passed);
    printf("Не пройдено: %d\n", tests_failed);
    printf("Всего: %d\n", tests_passed + tests_failed);

    if (tests_failed == 0) {
        printf("\n Все тесты пройдены успешно!\n");
        return 0;
    }
    else {
        printf("\n Есть непройденные тесты!\n");
        return 1;
    }
}