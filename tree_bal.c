#include "tree_bal.h"

#include <stdlib.h>
#define MAX_NODE_COUNT 1024

// Создание узла и его инициализация
Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) return NULL;
    node->value = value;
    node->size = 1;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

// Обновление размера одного узла на основе его детей
static void update_size(Node* node) {
    if (!node) return;
    int left_size = node->left ? node->left->size : 0;
    int right_size = node->right ? node->right->size : 0;
    node->size = 1 + left_size + right_size;
}

// Итеративная вставка узла
Node* tree_insert(Node** root, int value) {
    Node* new_node = create_node(value);
    if (!new_node) return NULL;
    if (*root == NULL) {
        *root = new_node;
        return new_node;
    }

    Node* cur = *root;
    while (1) {
        int left_size = cur->left ? cur->left->size : 0;
        int right_size = cur->right ? cur->right->size : 0;
        if (left_size <= right_size) {
            // Идём в левое поддерево
            if (cur->left != NULL) {
                cur = cur->left;
            } else {
                // Попали сюда - вешаем узел и выходим из цикла
                cur->left = new_node;
                new_node->parent = cur;
                break;
            }
        } else {
            // Идём в правое поддерево
            if (cur->right != NULL) {
                cur = cur->right;
            } else {
                // Попали сюда - вешаем узел и выходим из цикла
                cur->right = new_node;
                new_node->parent = cur;
                break;
            }
        }
    }
    // Осталось обновить размеры поддеревьев от родителя new_node вверх до корня
    Node* p = new_node->parent;
    while (p) {
        update_size(p);
        p = p->parent;
    }
    return new_node;
}

// Вспомогатнльная функция для удаления узла: найти самый правый подузел в
// дереве
static Node* find_rightmost(Node* node) {
    while (node && node->right) {
        node = node->right;
    }
    return node;
}

// Удаление узла
void tree_delete(Node** root, Node* node) {
    if (!node || !root) return;

    // Случай 1: узел - лист (нет детей)
    if (node->left == NULL && node->right == NULL) {
        Node* parent = node->parent;
        if (parent) {
            if (parent->left == node) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else {
            *root = NULL;  // удаляем корень
        }
        free(node);
        // обновляем размеры по пути к корню
        Node* p = parent;
        while (p) {
            update_size(p);
            p = p->parent;
        }
        return;
    }

    // Случай 2: только левый ребёнок
    if (node->left != NULL && node->right == NULL) {
        Node* child = node->left;
        Node* parent = node->parent;
        child->parent = parent;
        if (parent) {
            if (parent->left == node) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            *root = child;
        }
        free(node);
        // обновляем размеры от child->parent до корня
        Node* p = child->parent;
        while (p) {
            update_size(p);
            p = p->parent;
        }
        return;
    }

    // Случай 3: только правый ребёнок (вроде в нашеё реализации такой случай не
    // выполняется)
    if (node->right != NULL && node->left == NULL) {
        Node* child = node->right;
        Node* parent = node->parent;
        child->parent = parent;
        if (parent) {
            if (parent->left == node) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            *root = child;
        }
        free(node);
        Node* p = child->parent;
        while (p) {
            update_size(p);
            p = p->parent;
        }
        return;
    }

    // Случай 4: есть оба ребёнка.
    // В качестве приемника на место удалённого узла будем брать самый правый
    // узел в левом поддереве. Он нам удобен хотя бы потому, что не имеет
    // правого ребёнка
    // Здесь мы формально не удаляем node узел (в отличие от других случаев), мы
    // перезаписываем его значение на значение преемнике, а затем уже удаляем
    // самого преемника
    Node* replacement = find_rightmost(node->left);
    node->value = replacement->value;
    Node* repl_parent = replacement->parent;
    Node* repl_child = replacement->left;
    if (repl_parent) {
        if (repl_parent->left == replacement) {
            repl_parent->left = repl_child;
        } else {
            repl_parent->right = repl_child;
        }
    }
    if (repl_child) {
        repl_child->parent = repl_parent;
    }
    free(replacement);

    // Обновляем размеры от repl_parent до корня
    Node* p = repl_parent;
    while (p) {
        update_size(p);
        p = p->parent;
    }
}

// Итеративное освобождение дерева (обход в ширину)
void tree_free(Node* root) {
    if (!root) return;
    // Используем простой стек (массив указателей)
    Node** stack = (Node**)malloc(MAX_NODE_COUNT * sizeof(Node*));
    int top = 0;
    stack[top] = root;
    top += 1;
    while (top > 0) {
        top -= 1;
        Node* cur = stack[top];
        if (cur->left) {
            stack[top] = cur->left;
            top += 1;
        }
        if (cur->right) {
            stack[top] = cur->right;
            top += 1;
        }
        free(cur);
    }
    free(stack);
}

// Вспомогательные для тестов
int node_size(Node* node) { return node ? node->size : 0; }

Node* node_parent(Node* node) { return node ? node->parent : NULL; }