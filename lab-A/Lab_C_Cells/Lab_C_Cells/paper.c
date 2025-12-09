#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "paper.h"

// определение структуры "лист"
struct Paper {
    int rows;
    int cols;
    // true = клетка сущ, false = удалена
    bool** grid;
    // true = клетка посещена в ходе DFS
    bool** visited;
};

// вспомогательные функции
// проверка, нахождени€ клетки в пределах, сущ и не посещена
static bool is_valid_cell(Paper* paper, int row, int col) {
    if (!paper) {
        return false;
    }

    // проверка границ, сущ и посещени€
    return (row >= 0 && row < paper->rows &&
        col >= 0 && col < paper->cols &&
        paper->grid[row][col] &&
        !paper->visited[row][col]);
}

// рекурсивный поиск в глубину (DFS) дл€ маркировки св€зных клеток
static void dfs(Paper* paper, int row, int col) {
    if (!paper) {
        return;
    }

    // помечаем текущую клетку как посещенную
    paper->visited[row][col] = true;

    // массив направлений: вверх, вниз, влево, вправо
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (int i = 0; i < 4; i++) {
        int new_row = row + directions[i][0];
        int new_col = col + directions[i][1];

        if (is_valid_cell(paper, new_row, new_col)) {
            dfs(paper, new_row, new_col);
        }
    }
}

// осн функ API

// @brief —оздает и инициализирует лист клетчатой бумаги M x N
Paper* create_paper(int m, int n) {
    if (m <= 0 || n <= 0) {
        return NULL;
    }

    Paper* paper = (Paper*)malloc(sizeof(Paper));
    if (!paper) return NULL;

    paper->rows = m;
    paper->cols = n;

    // выделение пам€ти дл€ указателей на строки
    paper->grid = (bool**)malloc(m * sizeof(bool*));
    paper->visited = (bool**)malloc(m * sizeof(bool*));

    if (!paper->grid || !paper->visited) {
        // очистка при ошибке
        free(paper->grid);
        free(paper->visited);
        free(paper);
        return NULL;
    }

    // выделение пам€ти дл€ каждой строки и инициализаци€
    for (int i = 0; i < m; i++) {
        paper->grid[i] = (bool*)malloc(n * sizeof(bool));
        paper->visited[i] = (bool*)malloc(n * sizeof(bool));

        if (!paper->grid[i] || !paper->visited[i]) {
            // очистка ранее выделенных строк при ошибке
            for (int j = 0; j <= i; j++) {
                free(paper->grid[j]);
                free(paper->visited[j]);
            }
            free(paper->grid);
            free(paper->visited);
            free(paper);
            return NULL;
        }
    }

    // инициализаци€: все клетки существуют (true) и не посещены (false)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            paper->grid[i][j] = true;
            paper->visited[i][j] = false;
        }
    }

    return paper;
}

// @brief ќсвобождает всю пам€ть, выделенную дл€ листа.
void destroy_paper(Paper* paper) {
    if (!paper) return;

    for (int i = 0; i < paper->rows; i++) {
        free(paper->grid[i]);
        free(paper->visited[i]);
    }
    free(paper->grid);
    free(paper->visited);
    free(paper);
}

/**
 * @brief ”дал€ет указанные клетки из листа.
 * @param paper ”казатель на структуру Paper.
 * @param k  оличество удал€емых клеток.
 * @param x_coords ћассив X-координат (0-индексаци€).
 * @param y_coords ћассив Y-координат (0-индексаци€).
 */
void remove_cells(Paper* paper, int k, int* x_coords, int* y_coords) {
    if (!paper || !x_coords || !y_coords || k <= 0) return;

    for (int i = 0; i < k; i++) {
        int x = x_coords[i];
        int y = y_coords[i];

        // проверка границ перед удалением
        if (x >= 0 && x < paper->rows && y >= 0 && y < paper->cols) {
            paper->grid[x][y] = false; // ”становка false = удалено
        }
    }
}

/**
 * @brief ѕодсчитывает количество св€зных кусков (компонент).
 * @param paper ”казатель на структуру Paper.
 * @return  оличество св€зных кусков.
 */
int count_connected_components(Paper* paper) {
    if (!paper) return 0;

    // сброс массива посещений перед началом нового поиска
    for (int i = 0; i < paper->rows; i++) {
        for (int j = 0; j < paper->cols; j++) {
            paper->visited[i][j] = false;
        }
    }

    int count = 0;

    // обход всего пол€ дл€ поиска не посещенных, сущ клеток
    for (int i = 0; i < paper->rows; i++) {
        for (int j = 0; j < paper->cols; j++) {
            // если клетка сущ и еще не посещена
            if (paper->grid[i][j] && !paper->visited[i][j]) {
                dfs(paper, i, j); // начало DFS, маркиру€ всю компоненту
                count++;           // увеличение счетчка кусков
            }
        }
    }

    return count;
}