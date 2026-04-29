#include "tree_diff.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TreeNode* createNode(int key) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->key = key;
    node->diff = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(TreeNode* root) {
    if (!root) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int getHeight(TreeNode* root) {
    if (!root) {
        return 0;
    }
    int leftH = getHeight(root->left);
    int rightH = getHeight(root->right);
    if (leftH > rightH) {
        return leftH + 1;
    } else {
        return rightH + 1;
    }
}

int fillDiff(TreeNode* root) {
    if (!root) {
        return 0;
    }
    int leftH = fillDiff(root->left);
    int rightH = fillDiff(root->right);
    root->diff = leftH - rightH;
    if (leftH > rightH) {
        return leftH + 1;
    } else {
        return rightH + 1;
    }
}

/*
---------------1---------------
-------1---------------1-------
---1-------2-------1-------2---
-1---2---3---4---1---2---3---4-
1-2-3-4-5-6-7-8-1-2-3-4-5-6-7-8

Длина строки: cols = 2^h - 1, где h - высота корня
Прямая формула нахождения положения детей для parent[depth][col] (его высота -
curHeight): расстояние между left и right: distance = 2^(curHeight - 1)
left[depth + 1][col - distance/2]
right[depth + 1][col + distance/2]
*/

static void formatNodeString(TreeNode* node, char* out) {
    sprintf(out, "%d[%d]", node->key, node->diff);
}

static void populateGrid(TreeNode* node, char*** grid, int depth, int col,
                         int curHeight) {
    if (!node) {
        return;
    }

    // Формируем строку для вывода узла
    char buffer[9];  // Самое длинное допустимое значение "999[999]" + '\0'
                     // равно 9 символов
    formatNodeString(node, buffer);
    grid[depth][col] = strdup(buffer);  // Не забыть free

    if (!node->left && !node->right) {
        return;
    }

    int nextHeight = curHeight - 1;
    // Имеет ли смысл проверять высоту, если у нас уже проверяется остутств.
    // детей
    if (nextHeight <= 0) {
        return;
    }

    int distance = 1 << (curHeight - 1);  // 2^(curHeight - 1)
    if (node->left) {
        populateGrid(node->left, grid, depth + 1, col - distance / 2,
                     curHeight - 1);
    }
    if (node->right) {
        populateGrid(node->right, grid, depth + 1, col + distance / 2,
                     curHeight - 1);
    }
}

void printTree(TreeNode* root, int cell_width) {
    if (!root) {
        printf("Empty tree\n");
        return;
    }

    int h = getHeight(root);
    int cols = (1 << h) - 1;  // 2^h - 1

    // Выделяем сетку h*cols указателей char* (указатели на начало строк)
    char*** grid = (char***)malloc(h * sizeof(char**));
    for (int i = 0; i < h; i++) {
        grid[i] = (char**)malloc(cols * sizeof(char*));
        for (int j = 0; j < cols; j++) {
            grid[i][j] = NULL;
        }
    }

    int rootCol = (cols - 1) / 2;
    populateGrid(root, grid, 0, rootCol, h);

    // Печать
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Здесь cellwidth - ширина строки с узлом и ширина строки-пробела
            // (но если cell_width меньше строчки с узлом, то ничего не
            // обрезается, просто уменьшается размер строки-пробела)
            printf("%-*s", cell_width, grid[i][j] ? grid[i][j] : "");
        }
        // Обязательный перевод строки после вывода полной строчки с узлами
        printf("\n");
        // i = 0,...,h - 1; cur_h = h,...,1 => cur_h = h - i
        int cur_h = h - i;
        // int new_line_count = (cur_h >= 2) ? ((1 << (cur_h - 2)) - 1) : 0;
        // for (int k = 0; k < new_line_count; k++){
        //     printf("\n");
        // }

        // Решил сделать линейный рост количества пустых строк между строками с
        // узлами для лучшей читаемости
        int empty_line_count = cur_h - 1;
        for (int k = 0; k < empty_line_count; k++) {
            printf("\n");
        }
    }

    // Освобождение всеё памяти
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < cols; ++j) free(grid[i][j]);
        free(grid[i]);
    }
    free(grid);
}