#include <assert.h>
#include <stdio.h>

#include "tree_bal.h"

// Вспомогательная функция: получить размер поддерева (0 если NULL)
static int sz(Node* n) { return node_size(n); }

// Теты для вставки tree_insert
// Вставка в пустое дерево - корень создаётся корректно
void TestInsert_EmptyTree_NodeCreated_no1() {
    Node* root = NULL;
    Node* n = tree_insert(&root, 42);
    assert(root == n);
    assert(n->value == 42);
    assert(n->size == 1);
    assert(n->left == NULL && n->right == NULL && n->parent == NULL);
    tree_free(root);
}

// Вставка второго узла - выбор поддерева с меньшим числом узлов (оба 0,
// идём влево)
void TestInsert_TwoNodes_GoesLeft_no2() {
    Node* root = NULL;
    Node* n1 = tree_insert(&root, 10);
    Node* n2 = tree_insert(&root, 20);
    // Второй узел должен стать левым ребёнком (т.к. left_size == right_size ==
    // 0)
    assert(root->left == n2);
    assert(root->right == NULL);
    assert(n2->parent == root);
    assert(root->size == 2);
    tree_free(root);
}

// Вставка третьего узла - левое поддерево имеет 1 узел, правое 0 - идём в
// правое.
void TestInsert_ThirdNode_GoesRight_no3() {
    Node* root = NULL;
    tree_insert(&root, 10);             // корень
    tree_insert(&root, 20);             // левый
    Node* n3 = tree_insert(&root, 30);  // должен пойти в правое
    assert(root->right == n3);
    assert(root->size == 3);
    assert(root->left->size == 1);
    assert(root->right->size == 1);
    tree_free(root);
}

// Проверка обновления size после серии вставок
void TestInsert_SizeUpdateCorrect_no4() {
    Node* root = NULL;
    Node* n1 = tree_insert(&root, 100);
    Node* n2 = tree_insert(&root, 200);  // левый
    Node* n3 = tree_insert(&root, 300);  // правый
    Node* n4 = tree_insert(&root, 400);
    Node* n5 = tree_insert(&root, 500);
    assert(sz(root) == 5);
    assert(sz(root->left) == 2);
    assert(sz(root->right) == 2);
    assert(sz(root->left->left) == 1);
    assert(sz(root->right->left) == 1);
    tree_free(root);
}

// Parent указатели корректны после вставок
void TestInsert_ParentPointersCorrect_no5() {
    Node* root = NULL;
    Node* a = tree_insert(&root, 1);
    Node* b = tree_insert(&root, 2);
    Node* c = tree_insert(&root, 3);
    Node* d = tree_insert(&root, 4);
    assert(a->parent == NULL);
    assert(b->parent == a);
    assert(c->parent == a);
    assert(d->parent == b);
    tree_free(root);
}

// Тесты для удаления (tree_delete)
// Удаление листа - корректное переподключение узлов
void TestDelete_LeafNode_RemovedAndSizeUpdated_no6() {
    Node* root = NULL;
    Node* n1 = tree_insert(&root, 10);
    Node* n2 = tree_insert(&root, 20);  // левый лист
    tree_delete(&root, n2);
    assert(root->left == NULL);
    assert(root->size == 1);
    assert(n1->size == 1);
    tree_free(root);
}

// Удаление узла с одним левым ребёнком.
void TestDelete_NodeWithLeftChild_ChildLifted_no7() {
    Node* root = NULL;
    Node* n1 = tree_insert(&root, 10);
    Node* n2 = tree_insert(&root, 20);  // левый
    Node* n3 = tree_insert(&root, 30);  // правый -> корень
    Node* n4 = tree_insert(&root, 40);  // идёт в левое поддерево
    // Удаляем n2 (у него есть левый ребёнок n4)
    tree_delete(&root, n2);
    assert(root->left == n4);
    assert(n4->parent == root);
    assert(root->size == 3);
    assert(n4->size == 1);
    tree_free(root);
}

// Удаление узла с двумя детьми (замена на самый правый в левом поддереве)
void TestDelete_NodeWithTwoChildren_ReplacedWithRightmostLeft_no8() {
    Node* root = NULL;
    // Построим дерево, где у корня есть оба ребёнка
    Node* a = tree_insert(&root, 100);
    Node* b = tree_insert(&root, 200);  // левый
    Node* c = tree_insert(&root, 300);  // правый
    // Добавим ещё узлов, чтобы левое поддерево имело depth > 1
    Node* d = tree_insert(&root, 400);  // идёт в левое (b)
    Node* e = tree_insert(&root, 500);  // идёт в левое (d)
    tree_delete(&root, a);
    assert(root == a);
    assert(root->value == 200);
    assert(root->left == d);
    assert(root->right == c);
    assert(d->parent == root);
    assert(c->parent == root);
    assert(root->size == 4);
    tree_free(root);
}

// Удаление корня, когда он является листом
void TestDelete_RootLeaf_EmptyTree_no9() {
    Node* root = NULL;
    Node* only = tree_insert(&root, 999);
    tree_delete(&root, only);
    assert(root == NULL);
}

// Удаление корня с одним ребёнком.
void TestDelete_RootWithOneChild_CorrectRootChange_no10() {
    Node* root = NULL;
    Node* n1 = tree_insert(&root, 10);
    Node* n2 = tree_insert(&root, 20);  // идёт влево
    tree_delete(&root, n1);
    assert(root == n2);
    assert(n2->parent == NULL);
    assert(root->size == 1);
    tree_free(root);
}

// Удаление узла с двумя детьми, когда заменяющий узел - лист
void TestDelete_TwoChildren_ReplacementIsLeaf_no11() {
    Node* root = NULL;
    Node* r = tree_insert(&root, 10);
    Node* l = tree_insert(&root, 5);    // левый
    Node* rr = tree_insert(&root, 15);  // правый
    // Добавим узел в левое, чтобы левое поддерево имело глубину
    Node* ll = tree_insert(&root, 3);
    tree_delete(&root, r);
    assert(root == r);
    assert(root->value == 5);
    assert(root->left == ll);
    assert(root->right == rr);
    assert(ll->parent == r);
    assert(rr->parent == r);
    assert(root->size == 3);
    tree_free(root);
}

// Удаление нескольких узлов подряд - проверка целостности size
void TestDelete_MultipleDeletes_SizeConsistent_no12() {
    Node* root = NULL;
    Node* nodes[10];
    for (int i = 0; i < 8; ++i) nodes[i] = tree_insert(&root, i * 10);
    // Удаляем узлы в разном порядке
    tree_delete(&root, nodes[3]);
    tree_delete(&root, nodes[5]);
    tree_delete(&root, nodes[0]);
    tree_delete(&root, nodes[7]);
    assert(sz(root) == 4);
    tree_free(root);
}

int main() {
    TestInsert_EmptyTree_NodeCreated_no1();
    TestInsert_TwoNodes_GoesLeft_no2();
    TestInsert_ThirdNode_GoesRight_no3();
    TestInsert_SizeUpdateCorrect_no4();
    TestInsert_ParentPointersCorrect_no5();
    TestDelete_LeafNode_RemovedAndSizeUpdated_no6();
    TestDelete_NodeWithLeftChild_ChildLifted_no7();
    TestDelete_NodeWithTwoChildren_ReplacedWithRightmostLeft_no8();
    TestDelete_RootLeaf_EmptyTree_no9();
    TestDelete_RootWithOneChild_CorrectRootChange_no10();
    TestDelete_TwoChildren_ReplacementIsLeaf_no11();
    TestDelete_MultipleDeletes_SizeConsistent_no12();

    printf("All tests passed successfully!\n");
    return 0;
}