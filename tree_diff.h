#ifndef TREE_DIFF_H
#define TREE_DIFF_H

// Структура узла бинарного дерева
typedef struct TreeNode {
    int key;   // ключ (своего рода уникальное содержимое)
    int diff;  // разность высот левого и правого поддеревьев
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Создание нового свободного узла
TreeNode* createNode(int key);

// Вспомогательная функция: высота поддерева (0 если NULL)
int getHeight(TreeNode* root);

// Основная функция: заполняет в каждом узле diff = height(left) - height(right)
// Возвращает высоту корня (используется внутренне)
int fillDiff(TreeNode* root);

// Печать дерева. cell_width - ширина строки-узла и строки-пробела
void printTree(TreeNode* root, int cell_width);

// Освобождение памяти
void freeTree(TreeNode* root);

#endif