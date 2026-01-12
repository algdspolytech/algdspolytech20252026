#ifndef SUDOKU_DLX_H
#define SUDOKU_DLX_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct Node {
        struct Node* left, * right, * up, * down;
        struct ColumnHeader* col;
        int row_id;
    } Node;

    typedef struct ColumnHeader {
        Node base;
        int size;
        int id;
    } ColumnHeader;

    typedef struct DLX {
        ColumnHeader* header;
        Node** solution;  // Динамический массив
        int solution_size;
        int solution_capacity;
    } DLX;

    DLX* dlx_create(int cols);
    void dlx_add_row(DLX* dlx, int row_id, int cols[], int count);
    bool dlx_solve(DLX* dlx);
    void dlx_free(DLX* dlx);

    int** read_sudoku(const char* filename, int* N);
    void free_sudoku(int** grid, int N);
    DLX* sudoku_to_exact_cover(int** grid, int N);
    void save_solution(DLX* dlx, int** grid, int N);
    bool solve_sudoku_dlx(const char* input_file, const char* output_file);

#ifdef __cplusplus
}
#endif

#endif // SUDOKU_DLX_H