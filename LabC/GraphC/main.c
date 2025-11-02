#include <stdio.h>
#include "adj.h"



int main(void) {
    const char list_path[] = "adjlist.txt";
    const char matrix_equal_path[] = "adjmatrix.txt";
    const char matrix_diff_path[] = "adjmatrix_not_equal.txt";
   

    Graph g_list, g_matrix_equal, g_matrix_diff;
    init_graph(&g_list);
    init_graph(&g_matrix_equal);
    init_graph(&g_matrix_diff);

    if (!read_adjlist_file(list_path, &g_list)|| !read_adjmatrix_file(matrix_equal_path, &g_matrix_equal)||
        !read_adjmatrix_file(matrix_diff_path, &g_matrix_diff)) {
        printf("Failed to read file");
        graph_free(&g_list);
        graph_free(&g_matrix_equal);
        graph_free(&g_matrix_diff);
        return 1;
    }


    printf("Adjacency list graph:\n", list_path);
    print_graph(&g_list);

    printf("\nadjacency matrix 1 graph\n", matrix_equal_path);
    print_graph(&g_matrix_equal);

    printf("\nadjacency matrix 2 graph\n", matrix_diff_path);
    print_graph(&g_matrix_diff);

    int equal_test = graphs_equal(&g_list, &g_matrix_equal);
    int diff_test = graphs_equal(&g_list, &g_matrix_diff);

    if (equal_test) {
        printf("\nResult from adjacency list and matrix 1 :Equal\n");
    }
    else {
        printf("\nResult from adjacency list and matrix 1 :Not equal\n");
    }
    if (diff_test) {
        printf("\nResult from adjacency list and matrix 1 :Equal\n");
    }
    else {
        printf("\nResult from adjacency list and matrix 1 :Not equal\n");
    }
    graph_free(&g_list);
    graph_free(&g_matrix_equal);
    graph_free(&g_matrix_diff);
    return 0;
}