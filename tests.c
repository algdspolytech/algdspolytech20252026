#include <assert.h>
#include <stdio.h>

#include "tree_diff.h"

// Вспомогательные функции для построения деревьев (без логики)
static TreeNode* makeNode(int key) { return createNode(key); }
static void setLeft(TreeNode* p, TreeNode* c) { p->left = c; }
static void setRight(TreeNode* p, TreeNode* c) { p->right = c; }

// Высота пустого дерева (NULL) должна быть 0
void TestGetHeight_NullTree_Return0_no1() { assert(getHeight(NULL) == 0); }

// Высота дерева из одного узла должна быть 1
void TestGetHeight_SingleNode_Return1_no2() {
    TreeNode* n = makeNode(10);
    assert(getHeight(n) == 1);
    freeTree(n);
}

// Левая цепочка из 4 узлов - высота равна количеству узлов (4)
void TestGetHeight_LeftChain_HeightEqualsNodes_no3() {
    TreeNode* n1 = makeNode(1);
    TreeNode* n2 = makeNode(2);
    TreeNode* n3 = makeNode(3);
    TreeNode* n4 = makeNode(4);
    setLeft(n1, n2);
    setLeft(n2, n3);
    setLeft(n3, n4);
    assert(getHeight(n1) == 4);
    freeTree(n1);
}

// Правая цепочка из 3 узлов - высота равна 3
void TestGetHeight_RightChain_HeightEqualsNodes_no4() {
    TreeNode* n1 = makeNode(1);
    TreeNode* n2 = makeNode(2);
    TreeNode* n3 = makeNode(3);
    setRight(n1, n2);
    setRight(n2, n3);
    assert(getHeight(n1) == 3);
    freeTree(n1);
}

// Полное сбалансированное дерево высоты 3 (7 узлов) - высота 3
void TestGetHeight_BalancedTreeOfHeight3_Return3_no5() {
    TreeNode* n1 = makeNode(1);
    TreeNode* n2 = makeNode(2);
    TreeNode* n3 = makeNode(3);
    TreeNode* n4 = makeNode(4);
    TreeNode* n5 = makeNode(5);
    TreeNode* n6 = makeNode(6);
    TreeNode* n7 = makeNode(7);
    setLeft(n1, n2);
    setRight(n1, n3);
    setLeft(n2, n4);
    setRight(n2, n5);
    setLeft(n3, n6);
    setRight(n3, n7);
    assert(getHeight(n1) == 3);
    freeTree(n1);
}

// Несбалансированное лево‑тяжёлое дерево - проверка правильного подсчёта
void TestGetHeight_UnbalancedLeftHeavy_ReturnCorrect_no6() {
    TreeNode* n1 = makeNode(1);
    TreeNode* n2 = makeNode(2);
    TreeNode* n3 = makeNode(3);
    TreeNode* n4 = makeNode(4);
    TreeNode* n5 = makeNode(5);
    setLeft(n1, n2);
    setLeft(n2, n3);
    setRight(n2, n4);
    setLeft(n3, n5);
    assert(getHeight(n1) == 4);
    freeTree(n1);
}

// Тесты для функции fillDiff (заполнение разностей высот)

// fillDiff на пустом дереве должна вернуть 0 (высота) и ничего не сломать
void TestFillDiff_NullTree_Return0_no7() { assert(fillDiff(NULL) == 0); }

// Узел без детей - его разность должна быть 0
void TestFillDiff_SingleNode_Diff0_no8() {
    TreeNode* n = makeNode(42);
    fillDiff(n);
    assert(n->diff == 0);
    freeTree(n);
}

// Узел только с левым ребёнком - разность = 1
void TestFillDiff_NodeWithLeftChild_DiffPositive_no9() {
    TreeNode* p = makeNode(10);
    TreeNode* l = makeNode(20);
    setLeft(p, l);
    fillDiff(p);
    assert(p->diff == 1);
    assert(l->diff == 0);
    freeTree(p);
}

// Узел только с правым ребёнком - разность = -1
void TestFillDiff_NodeWithRightChild_DiffNegative_no10() {
    TreeNode* p = makeNode(10);
    TreeNode* r = makeNode(20);
    setRight(p, r);
    fillDiff(p);
    assert(p->diff == -1);
    assert(r->diff == 0);
    freeTree(p);
}

// Сбалансированное дерево высоты 2 (корень и два листа) - разности 0
void TestFillDiff_BalancedTwoLevels_Diff0_no11() {
    TreeNode* n1 = makeNode(1);
    TreeNode* n2 = makeNode(2);
    TreeNode* n3 = makeNode(3);
    setLeft(n1, n2);
    setRight(n1, n3);
    fillDiff(n1);
    assert(n1->diff == 0);
    assert(n2->diff == 0);
    assert(n3->diff == 0);
    freeTree(n1);
}

// Лево‑тяжёлое дерево - проверка рекурсивного вычисления разностей
void TestFillDiff_LeftHeavy_CheckRecursiveDiff_no12() {
    TreeNode* n1 = makeNode(1);
    TreeNode* n2 = makeNode(2);
    TreeNode* n3 = makeNode(3);
    TreeNode* n4 = makeNode(4);
    TreeNode* n5 = makeNode(5);
    setLeft(n1, n2);
    setLeft(n2, n3);
    setRight(n2, n4);
    setLeft(n3, n5);
    fillDiff(n1);
    assert(n1->diff == 3);
    assert(n2->diff == 1);
    assert(n3->diff == 1);
    assert(n4->diff == 0);
    assert(n5->diff == 0);
    freeTree(n1);
}

// Сложное дерево из примера в условии - проверка всех разностей
void TestFillDiff_ComplexTree_MultipleDiffs_no13() {
    TreeNode* n5 = makeNode(5);
    TreeNode* n3 = makeNode(3);
    TreeNode* n8 = makeNode(8);
    TreeNode* n2 = makeNode(2);
    TreeNode* n4 = makeNode(4);
    TreeNode* n9 = makeNode(9);
    TreeNode* n1 = makeNode(1);
    setLeft(n5, n3);
    setRight(n5, n8);
    setLeft(n3, n2);
    setRight(n3, n4);
    setRight(n8, n9);
    setLeft(n2, n1);
    fillDiff(n5);
    assert(n1->diff == 0);
    assert(n2->diff == 1);
    assert(n3->diff == 1);
    assert(n4->diff == 0);
    assert(n8->diff == -1);
    assert(n9->diff == 0);
    assert(n5->diff == 1);
    freeTree(n5);
}

int main() {
    TestGetHeight_NullTree_Return0_no1();
    TestGetHeight_SingleNode_Return1_no2();
    TestGetHeight_LeftChain_HeightEqualsNodes_no3();
    TestGetHeight_RightChain_HeightEqualsNodes_no4();
    TestGetHeight_BalancedTreeOfHeight3_Return3_no5();
    TestGetHeight_UnbalancedLeftHeavy_ReturnCorrect_no6();
    TestFillDiff_NullTree_Return0_no7();
    TestFillDiff_SingleNode_Diff0_no8();
    TestFillDiff_NodeWithLeftChild_DiffPositive_no9();
    TestFillDiff_NodeWithRightChild_DiffNegative_no10();
    TestFillDiff_BalancedTwoLevels_Diff0_no11();
    TestFillDiff_LeftHeavy_CheckRecursiveDiff_no12();
    TestFillDiff_ComplexTree_MultipleDiffs_no13();

    printf("All tests passed successfully!\n");
    return 0;
}