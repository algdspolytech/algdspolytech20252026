#include "sudoku.h"
#include <stdlib.h>
#include <string.h>

static void createColumnHeaders(SudokuDLX* s);
static void appendNode(SudokuDLX* s, int rowID, int colID);
static void coverColumn(Node* col);
static void uncoverColumn(Node* col);
static Node* chooseColumn(SudokuDLX* s);
static int search(SudokuDLX* s, int depth);
static void addSudokuRow(SudokuDLX* s, int r, int c, int num);

void initSudoku(SudokuDLX* s, int N) {
    s->N = N;
    s->size = N * N;
    s->nodeCount = 0;
    s->solSize = 0;
    memset(s->grid, 0, sizeof(s->grid));
    memset(s->solution, 0, sizeof(s->solution));
}

static void createColumnHeaders(SudokuDLX* s) {
    Node* header = &s->header;
    header->left = header->right = header->up = header->down = header;
    header->colID = -1;
    header->rowID = -1;
    header->count = 0;

    Node* prev = header;
    for (int i = 0; i < 4 * s->size * s->size; i++) {
        Node* col = &s->nodes[s->nodeCount++];
        col->colID = i;
        col->rowID = -1;
        col->count = 0;
        col->up = col->down = col;

        // Вставляем в конец списка заголовков
        col->left = prev;
        col->right = header;
        prev->right = col;
        header->left = col;
        prev = col;
    }
}

static void appendNode(SudokuDLX* s, int rowID, int colID) {
    // Находим заголовок столбца
    Node* col = &s->header;
    for (int i = 0; i <= colID; i++) {
        col = col->right;
    }
    col->count++;

    Node* node = &s->nodes[s->nodeCount++];
    node->rowID = rowID;
    node->colID = colID;
    node->colHeader = col;

    // Вставляем в столбец
    node->up = col->up;
    node->down = col;
    col->up->down = node;
    col->up = node;

    // Если это заголовок столбца, выходим
    if (rowID == -1) {
        node->left = node->right = node;
        return;
    }

    // Ищем начало строки
    Node* rowStart = node;
    int nodesInRow = 0;

    // Проходим по уже добавленным узлам для этой строки
    for (int i = s->nodeCount - 2; i >= 0; i--) {
        if (s->nodes[i].rowID == rowID) {
            rowStart = &s->nodes[i];
            nodesInRow++;
            break;
        }
    }

    if (nodesInRow == 0) {
        // Первый узел в строке
        node->left = node;
        node->right = node;
    }
    else {
        // Вставляем в конец строки (после rowStart)
        node->left = rowStart;
        node->right = rowStart->right;
        rowStart->right->left = node;
        rowStart->right = node;
    }
}

static void coverColumn(Node* col) {
    // Удаляем столбец из списка заголовков
    col->right->left = col->left;
    col->left->right = col->right;

    // Проходим по всем строкам в столбце
    for (Node* row = col->down; row != col; row = row->down) {
        // Проходим по всем узлам в строке
        for (Node* node = row->right; node != row; node = node->right) {
            // Удаляем узел из его столбца
            node->down->up = node->up;
            node->up->down = node->down;
            node->colHeader->count--;
        }
    }
}

static void uncoverColumn(Node* col) {
    // Восстанавливаем строки в обратном порядке
    for (Node* row = col->up; row != col; row = row->up) {
        for (Node* node = row->left; node != row; node = node->left) {
            // Восстанавливаем узел в его столбце
            node->colHeader->count++;
            node->down->up = node;
            node->up->down = node;
        }
    }
    // Восстанавливаем столбец в списке заголовков
    col->right->left = col;
    col->left->right = col;
}

static Node* chooseColumn(SudokuDLX* s) {
    Node* best = s->header.right;
    for (Node* c = best->right; c != &s->header; c = c->right) {
        if (c->count < best->count) {
            best = c;
        }
    }
    return best;
}

static int search(SudokuDLX* s, int depth) {
    if (s->header.right == &s->header) {
        s->solSize = depth;
        return 1;
    }

    Node* col = chooseColumn(s);
    if (col->count == 0) return 0;

    coverColumn(col);

    for (Node* row = col->down; row != col; row = row->down) {
        s->solution[depth] = row->rowID;

        // Cover все столбцы, связанные с этой строкой
        for (Node* node = row->right; node != row; node = node->right) {
            coverColumn(node->colHeader);
        }

        if (search(s, depth + 1)) {
            return 1;
        }

        // Uncover в обратном порядке
        for (Node* node = row->left; node != row; node = node->left) {
            uncoverColumn(node->colHeader);
        }
    }

    uncoverColumn(col);
    return 0;
}

static void addSudokuRow(SudokuDLX* s, int r, int c, int num) {
    int rowID = r * s->size * s->size + c * s->size + (num - 1);

    // 4 типа ограничений:
    // 1. Ячейка (r,c) должна содержать ровно одно число
    int col1 = r * s->size + c;

    // 2. Число num должно быть ровно один раз в строке r
    int col2 = s->size * s->size + r * s->size + (num - 1);

    // 3. Число num должно быть ровно один раз в столбце c
    int col3 = 2 * s->size * s->size + c * s->size + (num - 1);

    // 4. Число num должно быть ровно один раз в блоке
    int block = (r / s->N) * s->N + (c / s->N);
    int col4 = 3 * s->size * s->size + block * s->size + (num - 1);

    appendNode(s, rowID, col1);
    appendNode(s, rowID, col2);
    appendNode(s, rowID, col3);
    appendNode(s, rowID, col4);
}

void buildExactCover(SudokuDLX* s) {
    createColumnHeaders(s);

    for (int r = 0; r < s->size; r++) {
        for (int c = 0; c < s->size; c++) {
            if (s->grid[r][c] != 0) {
                // Если ячейка уже заполнена, добавляем только это число
                addSudokuRow(s, r, c, s->grid[r][c]);
            }
            else {
                // Если ячейка пуста, добавляем все возможные числа
                for (int num = 1; num <= s->size; num++) {
                    addSudokuRow(s, r, c, num);
                }
            }
        }
    }
}

int solveSudoku(SudokuDLX* s) {
    return search(s, 0);
}

void fillSolution(SudokuDLX* s) {
    for (int i = 0; i < s->solSize; i++) {
        int rowID = s->solution[i];
        int num = rowID % s->size + 1;
        rowID /= s->size;
        int c = rowID % s->size;
        int r = rowID / s->size;
        s->grid[r][c] = num;
    }
}
