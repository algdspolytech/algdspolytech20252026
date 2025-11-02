#define _CRT_SECURE_NO_WARNINGS
#include "topological_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//  Вспомогательные функции для тестов

void create_test_file(const char* filename, const char* content) {
    FILE* f = fopen(filename, "w");
    assert(f != NULL);
    fprintf(f, "%s", content);
    fclose(f);
}

void remove_test_file(const char* filename) {
    remove(filename);
}

// Функция для запуска теста

void RUN_TEST(void (*test_func)(void), const char* test_name) {
    printf("Running %s ... ", test_name);
    test_func();
    printf("PASSED\n");
}

// Тесты 

void test_create_graph_from_file_HappyPath_returnValidGraph_no1() {
    const char* content = "a b c d\na b\nb c\nc d\n";
    create_test_file("temp_input_valid.txt", content);

    Graph* g = create_graph_from_file("temp_input_valid.txt");
    assert(g != NULL);
    assert(g->vertices == 4);
    assert(strcmp(g->words[0], "a") == 0);
    assert(strcmp(g->words[1], "b") == 0);
    assert(strcmp(g->words[2], "c") == 0);
    assert(strcmp(g->words[3], "d") == 0);
    assert(g->adj_matrix[0][1] == 1); 
    assert(g->adj_matrix[1][2] == 1); 
    assert(g->adj_matrix[2][3] == 1); 
    free(g);
    remove_test_file("temp_input_valid.txt");
}

void test_create_graph_from_file_Cycle_returnValidGraph_no2() {
    const char* content = "a b c\na b\nb c\nc a\n";
    create_test_file("temp_input_cycle.txt", content);

    Graph* g = create_graph_from_file("temp_input_cycle.txt");
    assert(g != NULL);
    assert(g->vertices == 3);
    assert(strcmp(g->words[0], "a") == 0);
    assert(strcmp(g->words[1], "b") == 0);
    assert(strcmp(g->words[2], "c") == 0);
    assert(g->adj_matrix[0][1] == 1); 
    assert(g->adj_matrix[1][2] == 1); 
    assert(g->adj_matrix[2][0] == 1); 
    free(g);
    remove_test_file("temp_input_cycle.txt");
}


void test_create_graph_from_file_NullFilename_returnNull_no3() {
    Graph* g = create_graph_from_file(NULL);
    assert(g == NULL);
}

void test_create_graph_from_file_NonExistentFile_returnNull_no4() {
    Graph* g = create_graph_from_file("non_existent_file.txt");
    assert(g == NULL);
}

void test_topological_sort_HappyPath_returnSuccess_no5() {
    Graph g = { 0 };
    g.vertices = 4;
    g.word_count = 4;
    strcpy(g.words[0], "a");
    strcpy(g.words[1], "b");
    strcpy(g.words[2], "c");
    strcpy(g.words[3], "d");
    g.adj_matrix[0][1] = 1; 
    g.adj_matrix[1][2] = 1; 
    g.adj_matrix[2][3] = 1; 

    int result[MAX_WORDS];
    int res = topological_sort(&g, result);
    assert(res == 0);
    int a_idx = -1, b_idx = -1, c_idx = -1, d_idx = -1;
    for (int i = 0; i < 4; i++) {
        if (g.words[result[i]][0] == 'a') a_idx = i;
        if (g.words[result[i]][0] == 'b') b_idx = i;
        if (g.words[result[i]][0] == 'c') c_idx = i;
        if (g.words[result[i]][0] == 'd') d_idx = i;
    }
    assert(a_idx < b_idx);
    assert(b_idx < c_idx);
    assert(c_idx < d_idx);
}

void test_topological_sort_WithCycle_returnError_no6() {
    Graph g = { 0 };
    g.vertices = 3;
    g.word_count = 3;
    strcpy(g.words[0], "a");
    strcpy(g.words[1], "b");
    strcpy(g.words[2], "c");
    g.adj_matrix[0][1] = 1; 
    g.adj_matrix[1][2] = 1; 
    g.adj_matrix[2][0] = 1; 

    int result[MAX_WORDS];
    int res = topological_sort(&g, result);
    assert(res == -1); 
}

void test_topological_sort_EmptyGraph_returnSuccess_no7() {
    Graph g = { 0 };
    g.vertices = 0;
    g.word_count = 0;

    int result[MAX_WORDS];
    int res = topological_sort(&g, result);
    assert(res == 0); 
}

void test_topological_sort_SingleVertex_returnSuccess_no8() {
    Graph g = { 0 };
    g.vertices = 1;
    g.word_count = 1;
    strcpy(g.words[0], "single");

    int result[MAX_WORDS];
    int res = topological_sort(&g, result);
    assert(res == 0); 
    assert(result[0] == 0); 
}

void test_topological_sort_DisconnectedComponents_returnSuccess_no9() {
    Graph g = { 0 };
    g.vertices = 4;
    g.word_count = 4;
    strcpy(g.words[0], "a");
    strcpy(g.words[1], "b");
    strcpy(g.words[2], "c");
    strcpy(g.words[3], "d");
    g.adj_matrix[0][1] = 1; 
    g.adj_matrix[2][3] = 1; 

    int result[MAX_WORDS];
    int res = topological_sort(&g, result);
    assert(res == 0); 
    int a_idx = -1, b_idx = -1, c_idx = -1, d_idx = -1;
    for (int i = 0; i < 4; i++) {
        if (g.words[result[i]][0] == 'a') a_idx = i;
        if (g.words[result[i]][0] == 'b') b_idx = i;
        if (g.words[result[i]][0] == 'c') c_idx = i;
        if (g.words[result[i]][0] == 'd') d_idx = i;
    }
    assert(a_idx < b_idx);
    assert(c_idx < d_idx);
}

void test_topological_sort_NullGraph_returnError_no10() {
    int result[MAX_WORDS];
    int res = topological_sort(NULL, result);
    assert(res == -1);
}

void test_find_word_index_WordExists_returnIndex_no11() {
    Graph g = { 0 };
    g.vertices = 3;
    g.word_count = 3;
    strcpy(g.words[0], "first");
    strcpy(g.words[1], "second");
    strcpy(g.words[2], "third");

    int index = find_word_index(&g, "second");
    assert(index == 1);
}

void test_find_word_index_WordDoesNotExist_returnMinusOne_no12() {
    Graph g = { 0 };
    g.vertices = 2;
    g.word_count = 2;
    strcpy(g.words[0], "alpha");
    strcpy(g.words[1], "beta");

    int index = find_word_index(&g, "gamma");
    assert(index == -1);
}

void test_find_word_index_NullGraph_returnMinusOne_no13() {
    int index = find_word_index(NULL, "word");
    assert(index == -1);
}

void test_add_word_NewWord_success_no14() {
    Graph g = { 0 };
    g.vertices = 0;
    g.word_count = 0;

    int res = add_word(&g, "new_word");
    assert(res == 0);
    assert(g.word_count == 1);
    assert(strcmp(g.words[0], "new_word") == 0);
}

void test_topological_sort_NullResult_returnError_no15() {
    Graph g = { 0 };
    g.vertices = 1;
    g.word_count = 1;
    strcpy(g.words[0], "test");

    int res = topological_sort(&g, NULL);
    assert(res == -1);
}

int main() {
    RUN_TEST(test_create_graph_from_file_HappyPath_returnValidGraph_no1, "test_create_graph_from_file_HappyPath_returnValidGraph_no1");
    RUN_TEST(test_create_graph_from_file_Cycle_returnValidGraph_no2, "test_create_graph_from_file_Cycle_returnValidGraph_no2");
    RUN_TEST(test_create_graph_from_file_NullFilename_returnNull_no3, "test_create_graph_from_file_NullFilename_returnNull_no3");
    RUN_TEST(test_create_graph_from_file_NonExistentFile_returnNull_no4, "test_create_graph_from_file_NonExistentFile_returnNull_no4");
    RUN_TEST(test_topological_sort_HappyPath_returnSuccess_no5, "test_topological_sort_HappyPath_returnSuccess_no5");
    RUN_TEST(test_topological_sort_WithCycle_returnError_no6, "test_topological_sort_WithCycle_returnError_no6");
    RUN_TEST(test_topological_sort_EmptyGraph_returnSuccess_no7, "test_topological_sort_EmptyGraph_returnSuccess_no7");
    RUN_TEST(test_topological_sort_SingleVertex_returnSuccess_no8, "test_topological_sort_SingleVertex_returnSuccess_no8");
    RUN_TEST(test_topological_sort_DisconnectedComponents_returnSuccess_no9, "test_topological_sort_DisconnectedComponents_returnSuccess_no9");
    RUN_TEST(test_topological_sort_NullGraph_returnError_no10, "test_topological_sort_NullGraph_returnError_no10");
    RUN_TEST(test_find_word_index_WordExists_returnIndex_no11, "test_find_word_index_WordExists_returnIndex_no11");
    RUN_TEST(test_find_word_index_WordDoesNotExist_returnMinusOne_no12, "test_find_word_index_WordDoesNotExist_returnMinusOne_no12");
    RUN_TEST(test_find_word_index_NullGraph_returnMinusOne_no13, "test_find_word_index_NullGraph_returnMinusOne_no13");
    RUN_TEST(test_add_word_NewWord_success_no14, "test_add_word_NewWord_success_no14");
    RUN_TEST(test_topological_sort_NullResult_returnError_no15, "test_topological_sort_NullResult_returnError_no15");

    printf("All tests passed!\n");

    Graph* graph = create_graph_from_file("input.txt");
    if (!graph) {
        FILE* out = fopen("output.txt", "w");
        if (out) {
            fprintf(out, "[Error]\n");
            fclose(out);
        }
        return 1;
    }

    int sorted_indices[MAX_WORDS];
    int sort_result = topological_sort(graph, sorted_indices);

    if (sort_result == 0) {
        write_result_to_file(graph, sorted_indices, "output.txt");
    }
    else {
        FILE* out = fopen("output.txt", "w");
        if (out) {
            fprintf(out, "[Error]\n");
            fclose(out);
        }
    }

    free(graph);
    return 0;
}