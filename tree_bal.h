#ifndef TREE_BAL_H
#define TREE_BAL_H

// Узел бинарного дерева
typedef struct Node {
    int value;  // хранимое значение
    int size;   // количество узлов в поддереве (включая сам узел)
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

// Создание нового узла (size=1, parent=NULL, left=NULL, right=NULL)
Node* create_node(int value);

// Вставка значения в дерево. Возвращает указатель на созданный узел.
// Выбор поддерева с меньшим размером
Node* tree_insert(Node** root, int value);

// Удаление узла по указателю. Обновляет размеры родителей
void tree_delete(Node** root, Node* node);

// Освобождение всего дерева (итеративный обход без рекурсии)
void tree_free(Node* root);

// Функции для тестов (получение размера, проверка parent)
int node_size(Node* node);
Node* node_parent(Node* node);

#endif