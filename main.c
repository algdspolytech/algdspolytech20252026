#include <stdio.h>

#include "tree_diff.h"

int main() {
    // Строим дерево
    TreeNode* root = createNode(5);
    root->left = createNode(3);
    root->left->left = createNode(2);
    root->left->right = createNode(4);
    root->left->left->left = createNode(1);
    root->right = createNode(8);
    root->right->right = createNode(9);
    int node_str_width = 4;

    printf("Original tree:\n");
    printTree(root, node_str_width);
    printf("Height of tree: %d\n", getHeight(root));

    fillDiff(root);
    printf("\nTree with diff in each node (key[diff]):\n");
    printTree(root, node_str_width);
    freeTree(root);
    return 0;
}