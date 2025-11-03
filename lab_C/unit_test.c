#include "unit_test.h"

#pragma warning(disable : 4996)

void create_test_file(const char* filename, const char* content)
{
    FILE* file = fopen(filename, "w");
    if (file)
    {
        fprintf(file, "%s", content);
        fclose(file);
    }
}

void test_normal_case_no1()
{
    printf("Test 1: Normal case - graphs match\n");
    create_test_file("test_list1.txt", "1 2 3\n2 1 3\n3 1 2\n");
    create_test_file("test_matrix1.txt", "0 1 1\n1 0 1\n1 1 0\n");

    int n1 = vertices_list("test_list1.txt");
    int n2 = matrix_size("test_matrix1.txt");

    assert(n1 == 3);
    assert(n2 == 3);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list1.txt", m1, n1);
    read_matrix("test_matrix1.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 1);
    printf("PASSED\n");
}

void test_graphs_different_no2()
{
    printf("Test 2: Graphs are different\n");
    create_test_file("test_list2.txt", "1 2\n2 1 3\n3 2\n");
    create_test_file("test_matrix2.txt", "0 1 0\n1 0 1\n0 1 0\n");

    int n1 = vertices_list("test_list2.txt");
    int n2 = matrix_size("test_matrix2.txt");

    assert(n1 == 3);
    assert(n2 == 3);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list2.txt", m1, n1);
    read_matrix("test_matrix2.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 0);
    printf("PASSED\n");
}

void test_different_vertex_count_no3()
{
    printf("Test 3: Different number of vertices\n");
    create_test_file("test_list3.txt", "1 2\n2 1\n");
    create_test_file("test_matrix3.txt", "0 1 0\n1 0 1\n0 1 0\n");

    int n1 = vertices_list("test_list3.txt");
    int n2 = matrix_size("test_matrix3.txt");

    assert(n1 == 2);
    assert(n2 == 3);
    assert(n1 != n2);
    printf("PASSED\n");
}

void test_single_vertex_no4()
{
    printf("Test 4: Single isolated vertex\n");
    create_test_file("test_list4.txt", "1\n");
    create_test_file("test_matrix4.txt", "0\n");

    int n1 = vertices_list("test_list4.txt");
    int n2 = matrix_size("test_matrix4.txt");

    assert(n1 == 1);
    assert(n2 == 1);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list4.txt", m1, n1);
    read_matrix("test_matrix4.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 1);
    printf("PASSED\n");
}

void test_complete_graph_no5()
{
    printf("Test 5: Complete graph K4\n");
    create_test_file("test_list5.txt", "1 2 3 4\n2 1 3 4\n3 1 2 4\n4 1 2 3\n");
    create_test_file("test_matrix5.txt", "0 1 1 1\n1 0 1 1\n1 1 0 1\n1 1 1 0\n");

    int n1 = vertices_list("test_list5.txt");
    int n2 = matrix_size("test_matrix5.txt");

    assert(n1 == 4);
    assert(n2 == 4);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list5.txt", m1, n1);
    read_matrix("test_matrix5.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 1);
    printf("PASSED\n");
}

void test_self_loops_no6()
{
    printf("Test 6: Graph with self-loops\n");
    create_test_file("test_list6.txt", "1 1 2\n2 1 2\n");
    create_test_file("test_matrix6.txt", "1 1\n1 1\n");

    int n1 = vertices_list("test_list6.txt");
    int n2 = matrix_size("test_matrix6.txt");

    assert(n1 == 2);
    assert(n2 == 2);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list6.txt", m1, n1);
    read_matrix("test_matrix6.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 1);
    printf("PASSED\n");
}

void test_disconnected_graph_no7()
{
    printf("Test 7: Disconnected graph\n");
    create_test_file("test_list7.txt", "1 2\n2 1\n3 4\n4 3\n");
    create_test_file("test_matrix7.txt", "0 1 0 0\n1 0 0 0\n0 0 0 1\n0 0 1 0\n");

    int n1 = vertices_list("test_list7.txt");
    int n2 = matrix_size("test_matrix7.txt");

    assert(n1 == 4);
    assert(n2 == 4);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list7.txt", m1, n1);
    read_matrix("test_matrix7.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 1);
    printf("PASSED\n");
}

void test_directed_graph_no8()
{
    printf("Test 8: Directed graph\n");
    create_test_file("test_list8.txt", "1 2\n2 3\n3 1\n");
    create_test_file("test_matrix8.txt", "0 1 0\n0 0 1\n1 0 0\n");

    int n1 = vertices_list("test_list8.txt");
    int n2 = matrix_size("test_matrix8.txt");

    assert(n1 == 3);
    assert(n2 == 3);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list8.txt", m1, n1);
    read_matrix("test_matrix8.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 1);
    printf("PASSED\n");
}

void test_large_graph_no9()
{
    printf("Test 9: Large graph\n");

    FILE* list_file = fopen("test_list9.txt", "w");
    FILE* matrix_file = fopen("test_matrix9.txt", "w");

    for (int i = 1; i <= 10; i++)
    {
        fprintf(list_file, "%d", i);
        for (int j = 1; j <= 10; j++)
        {
            if (i != j) fprintf(list_file, " %d", j);
        }
        fprintf(list_file, "\n");
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            fprintf(matrix_file, "%d", (i != j) ? 1 : 0);
            if (j < 9) fprintf(matrix_file, " ");
        }
        fprintf(matrix_file, "\n");
    }

    fclose(list_file);
    fclose(matrix_file);

    int n1 = vertices_list("test_list9.txt");
    int n2 = matrix_size("test_matrix9.txt");

    assert(n1 == 10);
    assert(n2 == 10);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list9.txt", m1, n1);
    read_matrix("test_matrix9.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 1);
    printf("PASSED\n");
}

void test_weighted_graph_binary_no10()
{
    printf("Test 10: Weighted graph treated as binary\n");
    create_test_file("test_list10.txt", "1 2 3\n2 1 3\n3 1 2\n");
    create_test_file("test_matrix10.txt", "0 5 8\n5 0 3\n8 3 0\n");

    int n1 = vertices_list("test_list10.txt");
    int n2 = matrix_size("test_matrix10.txt");

    assert(n1 == 3);
    assert(n2 == 3);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list10.txt", m1, n1);
    read_matrix("test_matrix10.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 0);
    printf("PASSED\n");
}

void test_extra_spaces_no11()
{
    printf("Test 11: Files with extra spaces and tabs\n");
    create_test_file("test_list11.txt", "  1   2   3  \n  2     1     3  \n  3   1   2  \n");
    create_test_file("test_matrix11.txt", "  0   1   1  \n  1   0   1  \n  1   1   0  \n");

    int n1 = vertices_list("test_list11.txt");
    int n2 = matrix_size("test_matrix11.txt");

    assert(n1 == 3);
    assert(n2 == 3);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list11.txt", m1, n1);
    read_matrix("test_matrix11.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 1);
    printf("PASSED\n");
}

void test_empty_lines_no12()
{
    printf("Test 12: Files with empty lines\n");
    create_test_file("test_list12.txt", "1 2\n\n2 1\n\n");
    create_test_file("test_matrix12.txt", "0 1\n\n1 0\n\n");

    int n1 = vertices_list("test_list12.txt");
    int n2 = matrix_size("test_matrix12.txt");

    assert(n1 == 2);
    assert(n2 == 2);

    int m1[MAX_VERTICES][MAX_VERTICES];
    int m2[MAX_VERTICES][MAX_VERTICES];

    read_list("test_list12.txt", m1, n1);
    read_matrix("test_matrix12.txt", m2, n2);

    int result = compare_results(n1, m1, m2);
    assert(result == 1);
    printf("PASSED\n");
}

int main()
{
    printf("Running unit tests...\n\n");

    test_normal_case_no1();
    test_graphs_different_no2();
    test_different_vertex_count_no3();
    test_single_vertex_no4();
    test_complete_graph_no5();
    test_self_loops_no6();
    test_disconnected_graph_no7();
    test_directed_graph_no8();
    test_large_graph_no9();
    test_weighted_graph_binary_no10();
    test_extra_spaces_no11();
    test_empty_lines_no12();

    printf("\nAll tests passed successfully!\n");

    for (int i = 1; i <= 12; i++)
    {
        char filename[50];
        sprintf(filename, "test_list%d.txt", i);
        remove(filename);
        sprintf(filename, "test_matrix%d.txt", i);
        remove(filename);
    }

    return 0;
}