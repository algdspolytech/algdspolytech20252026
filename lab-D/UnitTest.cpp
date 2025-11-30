#define _CRT_SECURE_NO_WARNINGS
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* left, * right, * up, * down, * column;
    int row_id, size;
} Node;

typedef struct {
    Node head, ** columns, ** rows, ** column_nodes;
    int* solution, solution_count, row_count, col_count, board_size, box_size;
} DLX;

typedef struct {
    int N, board_size, box_size, ** board;
} Sudoku;

int* row_to_r, * row_to_c, * row_to_num, total_rows;

void init_dlx(DLX* dlx, int cols, int board_size, int box_size) {
    dlx->head.left = dlx->head.right = dlx->head.up = dlx->head.down = &dlx->head;
    dlx->col_count = cols; dlx->row_count = dlx->solution_count = 0;
    dlx->board_size = board_size; dlx->box_size = box_size;

    dlx->columns = (Node**)malloc(sizeof(Node*) * cols);
    dlx->rows = (Node**)malloc(sizeof(Node*) * (board_size * board_size * board_size));
    dlx->column_nodes = (Node**)malloc(sizeof(Node*) * cols);
    dlx->solution = (int*)malloc(sizeof(int) * board_size * board_size);

    row_to_r = (int*)malloc(sizeof(int) * (board_size * board_size * board_size));
    row_to_c = (int*)malloc(sizeof(int) * (board_size * board_size * board_size));
    row_to_num = (int*)malloc(sizeof(int) * (board_size * board_size * board_size));
    total_rows = 0;

    for (int i = 0; i < cols; i++) {
        Node* col_node = (Node*)malloc(sizeof(Node));
        col_node->left = &dlx->head; col_node->right = dlx->head.right;
        dlx->head.right->left = col_node; dlx->head.right = col_node;
        col_node->up = col_node->down = col_node->column = col_node;
        col_node->row_id = -1; col_node->size = 0;
        dlx->column_nodes[i] = col_node;
    }
}

void add_row(DLX* dlx, int* cols, int col_count, int r, int c, int num) {
    Node* first = NULL, * prev = NULL;
    for (int i = 0; i < col_count; i++) {
        Node* col_node = dlx->column_nodes[cols[i]];
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->column = col_node; new_node->row_id = total_rows;
        new_node->up = col_node->up; new_node->down = col_node;
        col_node->up->down = new_node; col_node->up = new_node;
        col_node->size++;

        if (!first) first = new_node->left = new_node->right = new_node;
        else {
            new_node->left = prev; new_node->right = first;
            prev->right = new_node; first->left = new_node;
        }
        prev = new_node;
    }
    if (first) {
        row_to_r[total_rows] = r; row_to_c[total_rows] = c;
        row_to_num[total_rows] = num; dlx->rows[dlx->row_count++] = first; total_rows++;
    }
}

void cover(Node* col) {
    col->right->left = col->left; col->left->right = col->right;
    for (Node* i = col->down; i != col; i = i->down)
        for (Node* j = i->right; j != i; j = j->right) {
            j->down->up = j->up; j->up->down = j->down; j->column->size--;
        }
}

void uncover(Node* col) {
    for (Node* i = col->up; i != col; i = i->up)
        for (Node* j = i->left; j != i; j = j->left) {
            j->column->size++; j->down->up = j; j->up->down = j;
        }
    col->right->left = col; col->left->right = col;
}

int search(DLX* dlx, int depth) {
    if (dlx->head.right == &dlx->head) { dlx->solution_count = depth; return 1; }

    Node* min_col = dlx->head.right;
    for (Node* j = min_col->right; j != &dlx->head; j = j->right)
        if (j->size < min_col->size) min_col = j;

    if (min_col->size == 0) return 0;

    cover(min_col);
    for (Node* r = min_col->down; r != min_col; r = r->down) {
        dlx->solution[depth] = r->row_id;
        for (Node* j = r->right; j != r; j = j->right) cover(j->column);
        if (search(dlx, depth + 1)) return 1;
        for (Node* j = r->left; j != r; j = j->left) uncover(j->column);
    }
    uncover(min_col);
    return 0;
}

void sudoku_to_exact_cover(DLX* dlx, Sudoku* sudoku) {
    int constraints[4], bs = sudoku->board_size, bx = sudoku->box_size;
    for (int r = 0; r < bs; r++) for (int c = 0; c < bs; c++) {
        if (sudoku->board[r][c]) {
            int n = sudoku->board[r][c] - 1;
            constraints[0] = r * bs + c;
            constraints[1] = bs * bs + r * bs + n;
            constraints[2] = 2 * bs * bs + c * bs + n;
            constraints[3] = 3 * bs * bs + ((r / bx) * bx + (c / bx)) * bs + n;
            add_row(dlx, constraints, 4, r, c, n);
        }
        else for (int n = 0; n < bs; n++) {
            constraints[0] = r * bs + c;
            constraints[1] = bs * bs + r * bs + n;
            constraints[2] = 2 * bs * bs + c * bs + n;
            constraints[3] = 3 * bs * bs + ((r / bx) * bx + (c / bx)) * bs + n;
            add_row(dlx, constraints, 4, r, c, n);
        }
    }
}

void solution_to_sudoku(DLX* dlx, Sudoku* sudoku) {
    for (int i = 0; i < dlx->solution_count; i++) {
        int id = dlx->solution[i];
        sudoku->board[row_to_r[id]][row_to_c[id]] = row_to_num[id] + 1;
    }
}

void read_sudoku(const char* filename, Sudoku* sudoku) {
    FILE* file = fopen(filename, "r");
    fscanf(file, "%d", &sudoku->N);
    sudoku->board_size = sudoku->N * sudoku->N;
    sudoku->box_size = sudoku->N;
    sudoku->board = (int**)malloc(sizeof(int*) * sudoku->board_size);
    for (int i = 0; i < sudoku->board_size; i++) {
        sudoku->board[i] = (int*)malloc(sizeof(int) * sudoku->board_size);
        for (int j = 0; j < sudoku->board_size; j++)
            fscanf(file, "%d", &sudoku->board[i][j]);
    }
    fclose(file);
}

void write_sudoku(const char* filename, Sudoku* sudoku) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < sudoku->board_size; i++) {
        for (int j = 0; j < sudoku->board_size; j++)
            fprintf(file, "%d ", sudoku->board[i][j]);
        fprintf(file, "\n");
    }
    fclose(file);
}

void write_no_solution(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;
    fprintf(file, "0\n");
    fclose(file);
}

void free_dlx(DLX* dlx) {
    if (!dlx) return;
    for (int i = 0; i < dlx->row_count; i++) {
        if (dlx->rows[i]) {
            Node* node = dlx->rows[i];
            Node* current = node->right;
            while (current != node) {
                Node* temp = current;
                current = current->right;
                free(temp);
            }
            free(node);
        }
    }
    for (int i = 0; i < dlx->col_count; i++) {
        if (dlx->column_nodes[i]) free(dlx->column_nodes[i]);
    }
    if (dlx->columns) free(dlx->columns);
    if (dlx->rows) free(dlx->rows);
    if (dlx->column_nodes) free(dlx->column_nodes);
    if (dlx->solution) free(dlx->solution);

    if (row_to_r) free(row_to_r);
    if (row_to_c) free(row_to_c);
    if (row_to_num) free(row_to_num);
}

void free_sudoku(Sudoku* sudoku) {
    if (!sudoku) return;
    for (int i = 0; i < sudoku->board_size; i++) {
        if (sudoku->board[i]) free(sudoku->board[i]);
    }
    if (sudoku->board) free(sudoku->board);
}

void create_test_file(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%s", content);
        fclose(file);
    }
}

TEST(SudokuTest, init_dlx_ValidParameters_InitializesCorrectly_no1) {
    DLX dlx;
    init_dlx(&dlx, 100, 9, 3);

    EXPECT_EQ(dlx.col_count, 100);
    EXPECT_EQ(dlx.board_size, 9);
    EXPECT_EQ(dlx.box_size, 3);
    EXPECT_NE(dlx.column_nodes, nullptr);

    free_dlx(&dlx);
}

TEST(SudokuTest, init_dlx_ZeroColumns_HandlesCorrectly_no2) {
    DLX dlx;
    init_dlx(&dlx, 0, 9, 3);

    EXPECT_EQ(dlx.col_count, 0);
    EXPECT_EQ(dlx.board_size, 9);
    EXPECT_NE(dlx.columns, nullptr);

    free_dlx(&dlx);
}

TEST(SudokuTest, add_row_ValidParameters_AddsRowCorrectly_no3) {
    DLX dlx;
    init_dlx(&dlx, 10, 9, 3);

    int cols[] = { 0, 1, 2, 3 };
    add_row(&dlx, cols, 4, 0, 0, 5);

    EXPECT_EQ(dlx.row_count, 1);
    EXPECT_EQ(total_rows, 1);

    free_dlx(&dlx);
}

TEST(SudokuTest, add_row_SingleColumn_AddsRowCorrectly_no4) {
    DLX dlx;
    init_dlx(&dlx, 5, 9, 3);

    int cols[] = { 2 };
    add_row(&dlx, cols, 1, 1, 1, 3);

    EXPECT_EQ(dlx.row_count, 1);
    EXPECT_EQ(total_rows, 1);

    free_dlx(&dlx);
}

TEST(SudokuTest, read_sudoku_ValidFile_ReadsCorrectly_no5) {
    const char* input = "3\n5 3 0 0 7 0 0 0 0\n6 0 0 1 9 5 0 0 0\n0 9 8 0 0 0 0 6 0\n";
    create_test_file("test_input.txt", input);

    Sudoku sudoku;
    read_sudoku("test_input.txt", &sudoku);

    EXPECT_EQ(sudoku.N, 3);
    EXPECT_EQ(sudoku.board_size, 9);
    EXPECT_EQ(sudoku.box_size, 3);
    EXPECT_EQ(sudoku.board[0][0], 5);
    EXPECT_EQ(sudoku.board[0][1], 3);

    free_sudoku(&sudoku);
    remove("test_input.txt");
}

TEST(SudokuTest, read_sudoku_MinimalSize_ReadsCorrectly_no6) {
    const char* input = "1\n1\n";
    create_test_file("test_minimal.txt", input);

    Sudoku sudoku;
    read_sudoku("test_minimal.txt", &sudoku);

    EXPECT_EQ(sudoku.N, 1);
    EXPECT_EQ(sudoku.board_size, 1);
    EXPECT_EQ(sudoku.board[0][0], 1);

    free_sudoku(&sudoku);
    remove("test_minimal.txt");
}

TEST(SudokuTest, write_sudoku_ValidBoard_WritesFile_no7) {
    Sudoku sudoku;
    sudoku.N = 2;
    sudoku.board_size = 4;
    sudoku.box_size = 2;
    sudoku.board = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; i++) {
        sudoku.board[i] = (int*)malloc(sizeof(int) * 4);
        for (int j = 0; j < 4; j++) {
            sudoku.board[i][j] = (i * 4 + j) % 4 + 1;
        }
    }

    write_sudoku("test_output.txt", &sudoku);

    FILE* file = fopen("test_output.txt", "r");
    EXPECT_NE(file, nullptr);
    if (file) fclose(file);

    free_sudoku(&sudoku);
    remove("test_output.txt");
}

TEST(SudokuTest, write_no_solution_CreatesFileWithZero_no8) {
    write_no_solution("test_no_solution.txt");

    FILE* file = fopen("test_no_solution.txt", "r");
    EXPECT_NE(file, nullptr);
    if (file) {
        int value;
        fscanf(file, "%d", &value);
        EXPECT_EQ(value, 0);
        fclose(file);
    }

    remove("test_no_solution.txt");
}

TEST(SudokuTest, cover_uncover_Column_WorksCorrectly_no9) {
    DLX dlx;
    init_dlx(&dlx, 5, 9, 3);

    Node* col = dlx.column_nodes[2];
    int original_size = col->size;

    cover(col);
    uncover(col);

    EXPECT_EQ(col->size, original_size);

    free_dlx(&dlx);
}

TEST(SudokuTest, search_EmptyBoard2x2_FindsSolution_no10) {
    Sudoku sudoku;
    sudoku.N = 2;
    sudoku.board_size = 4;
    sudoku.box_size = 2;
    sudoku.board = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; i++) {
        sudoku.board[i] = (int*)calloc(4, sizeof(int));
    }

    DLX dlx;
    init_dlx(&dlx, 4 * 4 * 4, 4, 2);
    sudoku_to_exact_cover(&dlx, &sudoku);

    int result = search(&dlx, 0);
    EXPECT_TRUE(result == 1);

    free_dlx(&dlx);
    free_sudoku(&sudoku);
}

TEST(SudokuTest, search_FilledBoard_ReturnsSolution_no11) {
    Sudoku sudoku;
    sudoku.N = 2;
    sudoku.board_size = 4;
    sudoku.box_size = 2;
    sudoku.board = (int**)malloc(sizeof(int*) * 4);
    int valid_board[4][4] = {
        {1, 2, 3, 4},
        {3, 4, 1, 2},
        {2, 1, 4, 3},
        {4, 3, 2, 1}
    };

    for (int i = 0; i < 4; i++) {
        sudoku.board[i] = (int*)malloc(sizeof(int) * 4);
        for (int j = 0; j < 4; j++) {
            sudoku.board[i][j] = valid_board[i][j];
        }
    }

    DLX dlx;
    init_dlx(&dlx, 4 * 4 * 4, 4, 2);
    sudoku_to_exact_cover(&dlx, &sudoku);

    int result = search(&dlx, 0);
    EXPECT_TRUE(result == 1);

    free_dlx(&dlx);
    free_sudoku(&sudoku);
}

TEST(SudokuTest, solution_to_sudoku_ValidSolution_FillsBoard_no12) {
    Sudoku sudoku;
    sudoku.N = 2;
    sudoku.board_size = 4;
    sudoku.box_size = 2;
    sudoku.board = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; i++) {
        sudoku.board[i] = (int*)calloc(4, sizeof(int));
    }

    DLX dlx;
    init_dlx(&dlx, 64, 4, 2);
    row_to_r[0] = 0; row_to_c[0] = 0; row_to_num[0] = 0;
    dlx.solution[0] = 0;
    dlx.solution_count = 1;

    solution_to_sudoku(&dlx, &sudoku);

    EXPECT_EQ(sudoku.board[0][0], 1);

    free_dlx(&dlx);
    free_sudoku(&sudoku);
}

TEST(SudokuTest, free_dlx_ValidStructure_FreesMemory_no13) {
    DLX dlx;
    init_dlx(&dlx, 10, 9, 3);
    int cols[] = { 0, 1, 2 };
    add_row(&dlx, cols, 3, 0, 0, 1);

    free_dlx(&dlx);
    SUCCEED();
}

TEST(SudokuTest, free_sudoku_ValidStructure_FreesMemory_no14) {
    Sudoku sudoku;
    sudoku.N = 3;
    sudoku.board_size = 9;
    sudoku.box_size = 3;
    sudoku.board = (int**)malloc(sizeof(int*) * 9);
    for (int i = 0; i < 9; i++) {
        sudoku.board[i] = (int*)malloc(sizeof(int) * 9);
    }

    free_sudoku(&sudoku);
    SUCCEED();
}

TEST(SudokuTest, add_row_MultipleRows_AddsCorrectly_no15) {
    DLX dlx;
    init_dlx(&dlx, 10, 9, 3);

    int cols1[] = { 0, 1, 2 };
    int cols2[] = { 3, 4, 5 };
    add_row(&dlx, cols1, 3, 0, 0, 1);
    add_row(&dlx, cols2, 3, 0, 1, 2);

    EXPECT_EQ(dlx.row_count, 2);
    EXPECT_EQ(total_rows, 2);

    free_dlx(&dlx);
}

TEST(SudokuTest, sudoku_to_exact_cover_PartialBoard_CreatesRows_no16) {
    Sudoku sudoku;
    sudoku.N = 2;
    sudoku.board_size = 4;
    sudoku.box_size = 2;
    sudoku.board = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; i++) {
        sudoku.board[i] = (int*)calloc(4, sizeof(int));
    }
    sudoku.board[0][0] = 1;
    sudoku.board[1][1] = 2;

    DLX dlx;
    init_dlx(&dlx, 64, 4, 2);
    sudoku_to_exact_cover(&dlx, &sudoku);

    EXPECT_GT(dlx.row_count, 0);

    free_dlx(&dlx);
    free_sudoku(&sudoku);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
