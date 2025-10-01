#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "btree.h"

// Глобальные указатели функций 
extern split_t const* split_func_ptr;
extern insertNotFull_t const* insert_not_full_ptr;

B_node* CreateNode(B_node* parentNode, bool isLeaf) {
    B_node* newNode = (B_node*)malloc(sizeof(B_node));
    if (!newNode) {
        return NULL;
    }

    newNode->parent = parentNode;
    newNode->keys_count = 0;
    newNode->is_leaf = isLeaf;

    for (int idx = 0; idx < MAX_CHILDREN; idx++) {
        newNode->children[idx] = NULL;
    }

    return newNode;
}

B_search_result Search(B_tree* tree, int key) {
    if (!tree || !tree->root) {
        return MISSING;
    }

    B_node* currentNode = tree->root;
    while (currentNode) {
        int index = 0;
        while (index < currentNode->keys_count && key > currentNode->keys[index]) {
            index++;
        }
        if (index < currentNode->keys_count && key == currentNode->keys[index]) {
            return EXISTS;
        }
        if (currentNode->is_leaf) {
            return MISSING;
        }

        currentNode = currentNode->children[index];
    }

    return MISSING;
}

void split(B_node* parentNode, int splitIndex) {
    B_node* childNode = parentNode->children[splitIndex];
    B_node* siblingNode = CreateNode(parentNode, childNode->is_leaf);

    int middleIndex = T - 1;
    siblingNode->is_leaf = childNode->is_leaf;
    siblingNode->keys_count = middleIndex;

    for (int offset = 0; offset < middleIndex; offset++) {
        siblingNode->keys[offset] = childNode->keys[middleIndex + 1 + offset];
    }

    if (!childNode->is_leaf) {
        for (int offset = 0; offset < middleIndex + 1; offset++) {
            siblingNode->children[offset] = childNode->children[middleIndex + 1 + offset];
            if (siblingNode->children[offset]) {
                siblingNode->children[offset]->parent = siblingNode;
            }
        }
    }

    childNode->keys_count = middleIndex;

    for (int pos = parentNode->keys_count; pos > splitIndex; pos--) {
        parentNode->keys[pos] = parentNode->keys[pos - 1];
        parentNode->children[pos + 1] = parentNode->children[pos];
    }

    parentNode->keys[splitIndex] = childNode->keys[middleIndex];
    parentNode->children[splitIndex + 1] = siblingNode;
    parentNode->keys_count++;
}

void insertNotFull(B_node* currentNode, int key) {
    int index = currentNode->keys_count - 1;

    if (currentNode->is_leaf) {
        while (index >= 0 && key < currentNode->keys[index]) {
            currentNode->keys[index + 1] = currentNode->keys[index];
            index--;
        }

        currentNode->keys[index + 1] = key;
        currentNode->keys_count++;
    } else {
        while (index >= 0 && key < currentNode->keys[index]) {
            index--;
        }
        index++;

        if (currentNode->children[index]->keys_count == MAX_KEYS) {
            (*split_func_ptr)(currentNode, index);
            if (key > currentNode->keys[index]) {
                index++;
            }
        }

        (*insert_not_full_ptr)(currentNode->children[index], key);
    }
}

void Insert(B_tree* tree, int key) {
    if (!split_func_ptr) {
        split_func_ptr = (split_t const*)(void*)&split;
    }
    if (!insert_not_full_ptr) {
        insert_not_full_ptr = (insertNotFull_t const*)(void*)&insertNotFull;
    }

    if (Search(tree, key) == EXISTS) {
        return;
    }

    if (!tree->root) {
        tree->root = CreateNode(NULL, true);
        (*insert_not_full_ptr)(tree->root, key);
        return;
    }

    if (tree->root->keys_count == MAX_KEYS) {
        B_node* newRoot = CreateNode(NULL, false);
        newRoot->children[0] = tree->root;
        tree->root->parent = newRoot;
        tree->root = newRoot;

        (*split_func_ptr)(newRoot, 0);
    }

    B_node* currentNode = tree->root;
    while (!currentNode->is_leaf) {
        int index = 0;
        while (index < currentNode->keys_count && key > currentNode->keys[index]) {
            index++;
        }

        if (currentNode->children[index]->keys_count == MAX_KEYS) {
            (*split_func_ptr)(currentNode, index);
            if (key > currentNode->keys[index]) {
                index++;
            }
        }

        currentNode = currentNode->children[index];
    }

    (*insert_not_full_ptr)(currentNode, key);
}

void FreeNode(B_node* currentNode) {
    if (!currentNode) return;

    if (!currentNode->is_leaf) {
        for (int idx = 0; idx <= currentNode->keys_count; idx++) {
            FreeNode(currentNode->children[idx]);
        }
    }

    free(currentNode);
}

void Free(B_tree* tree) {
    if (!tree) return;

    if (tree->root) {
        FreeNode(tree->root);
        tree->root = NULL;
    }
}

B_tree_iterator IteratorBegin(B_tree* tree) {
    B_tree_iterator iterator = { 0 };

    if (!tree->root) {
        iterator.node = NULL;
        iterator.position = -1;
        return iterator;
    }

    B_node* currentNode = tree->root;
    while (!currentNode->is_leaf) {
        currentNode = currentNode->children[0];
    }
    iterator.node = currentNode;
    iterator.position = -1;
    return iterator;
}

int Next(B_tree_iterator* iterator) {
    if (!iterator->node) return 0;

    B_node* currentNode = iterator->node;
    int position = iterator->position;

    if (currentNode->is_leaf) {
        if (position + 1 < currentNode->keys_count) {
            iterator->position = position + 1;
            return 1;
        }
    } else {
        if (position + 1 <= currentNode->keys_count && currentNode->children[position + 1]) {
            B_node* nextLeaf = currentNode->children[position + 1];
            while (!nextLeaf->is_leaf) {
                nextLeaf = nextLeaf->children[0];
            }
            iterator->node = nextLeaf;
            iterator->position = 0;
            return 1;
        }
    }

    B_node* childNode = currentNode;
    while (childNode->parent) {
        B_node* parentNode = childNode->parent;
        int idx = 0;
        while (idx <= parentNode->keys_count && parentNode->children[idx] != childNode) {
            idx++;
        }
        if (idx < parentNode->keys_count) {
            iterator->node = parentNode;
            iterator->position = idx;
            return 1;
        }
        childNode = parentNode;
    }

    iterator->node = NULL;
    return 0;
}

int Key(B_tree_iterator* iterator) {
    if (!iterator || !iterator->node || iterator->position < 0 ||
        iterator->position >= iterator->node->keys_count) {
        return INT_MIN;
    }
    return iterator->node->keys[iterator->position];
}
