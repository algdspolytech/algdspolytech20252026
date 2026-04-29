#include "tree_bal.h"
#include <stdio.h>

int main() {
    Node* root = NULL;

    // Вставляем несколько узлов и сохраняем указатели
    Node* n1 = tree_insert(&root, 10);
    Node* n2 = tree_insert(&root, 20);
    Node* n3 = tree_insert(&root, 30);
    Node* n4 = tree_insert(&root, 40);
    Node* n5 = tree_insert(&root, 50);

    printf("Размер дерева после вставок: %d\n", root->size);

    // Удаляем лист (40)
    tree_delete(&root, n4);
    printf("После удаления листа 40, размер: %d\n", root->size); // 4

    // Удаляем узел с одним ребёнком (20)
    tree_delete(&root, n2);
    printf("После удаления узла 20 (1 ребёнок), размер: %d\n", root->size); // 3

    // Удаляем узел с двумя детьми
    tree_delete(&root, n1);
    printf("После удаления узла 10 (2 ребёнка), размер: %d\n", root->size); // 2

    tree_free(root);
    return 0;
}