// tests.c
#include "tree.h"
#include <assert.h>
#include <string.h>
#include <locale.h>

#define RUN_TESTS

#ifdef RUN_TESTS

int are_trees_equal(TreeNode* tree1, TreeNode* tree2) {
    if (!tree1 && !tree2) return 1;
    if (!tree1 || !tree2) return 0;
    if (strcmp(tree1->name, tree2->name) != 0) return 0;

    return are_trees_equal(tree1->child, tree2->child) &&
           are_trees_equal(tree1->next, tree2->next);
}

void TestNodeCreation_ValidName_Test1() {
    printf("Тест 1: Создание узла с корректным именем... ");
    TreeNode* node = create_node("test");
    assert(node != NULL);
    assert(strcmp(node->name, "test") == 0);
    assert(node->next == NULL);
    assert(node->child == NULL);
    free(node);
    printf("ПРОЙДЕН\n");
}


void TestNodeCreation_NullName_Test2() {
    printf("Тест 2: Создание узла с NULL именем... ");
    TreeNode* node = create_node(NULL);
    assert(node == NULL);
    printf("ПРОЙДЕН\n");
}


void TestNodeCreation_EmptyName_Test3() {
    printf("Тест 3: Создание узла с пустым именем... ");
    TreeNode* node = create_node("");
    assert(node != NULL);
    assert(strcmp(node->name, "") == 0);
    free(node);
    printf("ПРОЙДЕН\n");
}


void TestChildSearch_ExistingChild_Test4() {
    printf("Тест 4: Поиск существующей дочерней папки... ");
    TreeNode* parent = create_node("parent");
    TreeNode* childA = create_node("childA");
    TreeNode* childB = create_node("childB");

    add_child(parent, childA);
    add_child(parent, childB);

    TreeNode* found = find_child(parent, "childA");
    assert(found != NULL);
    assert(strcmp(found->name, "childA") == 0);

    free_tree(parent);
    printf("ПРОЙДЕН\n");
}

void TestChildSearch_NonExistingChild_Test5() {
    printf("Тест 5: Поиск несуществующей дочерней папки... ");
    TreeNode* parent = create_node("parent");
    TreeNode* child = create_node("child");

    add_child(parent, child);

    TreeNode* found = find_child(parent, "missing");
    assert(found == NULL);

    free_tree(parent);
    printf("ПРОЙДЕН\n");
}


void TestPathAddition_SingleLevel_Test6() {
    printf("Тест 6: Добавление одноуровневого пути... ");
    TreeNode* root = create_node("");

    add_path_to_tree(root, "docs");

    assert(root->child != NULL);
    assert(strcmp(root->child->name, "docs") == 0);
    assert(root->child->child == NULL);

    free_tree(root);
    printf("ПРОЙДЕН\n");
}

void TestPathAddition_MultiLevel_Test7() {
    printf("Тест 7: Добавление многоуровневого пути... ");
    TreeNode* root = create_node("");

    add_path_to_tree(root, "root\\fold\\sub\\file");

    assert(root->child != NULL);
    assert(strcmp(root->child->name, "root") == 0);
    assert(root->child->child != NULL);
    assert(strcmp(root->child->child->name, "fold") == 0);
    assert(root->child->child->child != NULL);
    assert(strcmp(root->child->child->child->name, "sub") == 0);
    assert(root->child->child->child->child != NULL);
    assert(strcmp(root->child->child->child->child->name, "file") == 0);

    free_tree(root);
    printf("ПРОЙДЕН\n");
}

void TestChildrenSorting_Unsorted_Test8() {
    printf("Тест 8: Сортировка дочерних элементов... ");
    TreeNode* parent = create_node("parent");
    TreeNode* nodeC = create_node("ccc");
    TreeNode* nodeA = create_node("aaa");
    TreeNode* nodeB = create_node("bbb");

    add_child(parent, nodeC);
    add_child(parent, nodeA);
    add_child(parent, nodeB);

    sort_children(parent);

    assert(parent->child != NULL);
    assert(strcmp(parent->child->name, "aaa") == 0);
    assert(parent->child->next != NULL);
    assert(strcmp(parent->child->next->name, "bbb") == 0);
    assert(parent->child->next->next != NULL);
    assert(strcmp(parent->child->next->next->name, "ccc") == 0);

    free_tree(parent);
    printf("ПРОЙДЕН\n");
}


void TestPathList_Addition_Test9() {
    printf("Тест 9: Добавление элементов в список путей... ");
    PathList* head = NULL;

    head = add_to_path_list(head, "path1");
    head = add_to_path_list(head, "path2");

    assert(head != NULL);
    assert(strcmp(head->path, "path2") == 0);
    assert(head->next != NULL);
    assert(strcmp(head->next->path, "path1") == 0);

    free_path_list(head);
    printf("ПРОЙДЕН\n");
}

void TestNullHandling_Safety_Test10() {
    printf("Тест 10: Обработка NULL параметров... ");

    // Эти вызовы не должны вызывать сбоев
    add_child(NULL, NULL);
    find_child(NULL, NULL);
    add_path_to_tree(NULL, NULL);
    sort_children(NULL);
    sort_tree(NULL);
    print_tree_to_file(NULL, 0, NULL);

    printf("ПРОЙДЕН\n");
}


void TestMemoryManagement_NoLeaks_Test11() {
    printf("Тест 11: Проверка освобождения памяти... ");

    TreeNode* root = create_node("");
    add_path_to_tree(root, "a\\b\\c");
    add_path_to_tree(root, "x\\y\\z");

    free_tree(root);

    PathList* paths = NULL;
    paths = add_to_path_list(paths, "path1");
    paths = add_to_path_list(paths, "path2");

    free_path_list(paths);

    printf("ПРОЙДЕН\n");
}

void TestNameLength_Maximum_Test12() {
    printf("Тест 12: Граничный случай - имя из 8 символов... ");
    TreeNode* node = create_node("ABCDEFGH");
    assert(node != NULL);
    assert(strcmp(node->name, "ABCDEFGH") == 0);
    assert(strlen(node->name) == 8);
    free(node);
    printf("ПРОЙДЕН\n");
}

void TestSpecialCharacters_Valid_Test13() {
    printf("Тест 13: Специальные символы в именах... ");
    TreeNode* node = create_node("!#$%&()-");
    assert(node != NULL);
    assert(strcmp(node->name, "!#$%&()-") == 0);
    free(node);
    printf("ПРОЙДЕН\n");
}

void TestDuplicateFolders_Handling_Test14() {
    printf("Тест 14: Обработка дублирующихся папок... ");
    TreeNode* root = create_node("");

    add_path_to_tree(root, "shared\\folder");
    add_path_to_tree(root, "shared\\folder");  // Дубликат

    // Должна быть только одна папка folder
    assert(root->child != NULL);
    assert(strcmp(root->child->name, "shared") == 0);
    assert(root->child->child != NULL);
    assert(strcmp(root->child->child->name, "folder") == 0);
    // Не должно быть дубликата
    assert(root->child->child->next == NULL);

    free_tree(root);
    printf("ПРОЙДЕН\n");
}

int main() {
    setlocale(LC_ALL, "Russian");
    printf("=== ЗАПУСК ТЕСТОВОГО НАБОРА ===\n\n");

    TestNodeCreation_ValidName_Test1();
    TestNodeCreation_NullName_Test2();
    TestNodeCreation_EmptyName_Test3();
    TestChildSearch_ExistingChild_Test4();
    TestChildSearch_NonExistingChild_Test5();
    TestPathAddition_SingleLevel_Test6();
    TestPathAddition_MultiLevel_Test7();
    TestChildrenSorting_Unsorted_Test8();
    TestPathList_Addition_Test9();
    TestNullHandling_Safety_Test10();
    TestMemoryManagement_NoLeaks_Test11();
    TestNameLength_Maximum_Test12();
    TestSpecialCharacters_Valid_Test13();
    TestDuplicateFolders_Handling_Test14();

    printf("\n=== ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ! ===\n");
    return 0;
}
#endif