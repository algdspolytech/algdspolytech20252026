#pragma warning(disable:4996)

#include "Lab-A.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Тест 1: Создание узла с обычным именем
void TestCreateNodeWithValidName_no1() {
    printf("Test 1: Create node with valid name... ");
    FolderTree* node = create_node("Folder1");
    assert(node != NULL);
    assert(strcmp(node->name, "Folder1") == 0);
    assert(node->child_count == 0);
    assert(node->child != NULL);
    free_tree(node);
    printf("PASS\n");
}

// Тест 2: Создание узла с именем из специальных символов
void TestCreateNodeWithSpecialCharacters_no2() {
    printf("Test 2: Create node with special characters... ");
    FolderTree* node = create_node("!#$%&'()");
    assert(node != NULL);
    assert(strcmp(node->name, "!#$%&'()") == 0);
    assert(node->child_count == 0);
    free_tree(node);
    printf("PASS\n");
}

// Тест 3: Создание узла с именем длиннее 8 символов (должно обрезаться)
void TestCreateNodeWithLongNameTruncated_no3() {
    printf("Test 4: Create node with long name (truncated)... ");
    FolderTree* node = create_node("VeryLongName");
    assert(node != NULL);
    assert(strlen(node->name) == 8);
    assert(strcmp(node->name, "VeryLong") == 0);
    free_tree(node);
    printf("PASS\n");
}

// Тест 4: Добавление первого ребенка в пустой узел
void TestAddFirstChildToEmptyNode_no4() {
    printf("Test 5: Add first child to empty node... ");
    FolderTree* root = create_node("root");
    FolderTree* child = create_node("Child1");
    assert(child != NULL);

    add_child(root, child);
    assert(root->child_count == 1);
    assert(strcmp(root->child[0]->name, "Child1") == 0);

    free_tree(root);
    printf("PASS\n");
}

// Тест 5: Добавление множества детей с расширением size
void TestAddMultipleChildrenWithSizeExpansion_no5() {
    printf("Test 6: Add multiple children with size expansion... ");
    FolderTree* root = create_node("root");
    const int num_children = 10;

    for (int i = 0; i < num_children; i++) {
        char name[16];
        sprintf(name, "Child%d", i);
        FolderTree* child = create_node(name);
        assert(child != NULL);
        add_child(root, child);
    }

    assert(root->child_count == num_children);
    assert(root->size >= num_children);

    free_tree(root);
    printf("PASS\n");
}

// Тест 6: Поиск существующего и несуществующего ребенка
void TestFindExistingAndNonExistingChild_no6() {
    printf("Test 7: Find existing and non-existing child... ");
    FolderTree* root = create_node("root");
    FolderTree* child1 = create_node("First");
    FolderTree* child2 = create_node("Second");

    add_child(root, child1);
    add_child(root, child2);

    FolderTree* found = find_child(root, "First");
    assert(found != NULL);
    assert(strcmp(found->name, "First") == 0);

    found = find_child(root, "Second");
    assert(found != NULL);
    assert(strcmp(found->name, "Second") == 0);

    found = find_child(root, "NonExisting");
    assert(found == NULL);

    free_tree(root);
    printf("PASS\n");
}

// Тест 7: Вставка сложного пути с созданием промежуточных узлов
void TestInsertComplexPathWithIntermediateNodes_no7() {
    printf("Test 8: Insert complex path with intermediate nodes... ");
    FolderTree* root = create_node("");

    insert_path(root, "Level1\\Level2\\Level3\\Level4");

    FolderTree* level1 = find_child(root, "Level1");
    assert(level1 != NULL);

    FolderTree* level2 = find_child(level1, "Level2");
    assert(level2 != NULL);

    FolderTree* level3 = find_child(level2, "Level3");
    assert(level3 != NULL);

    FolderTree* level4 = find_child(level3, "Level4");
    assert(level4 != NULL);

    free_tree(root);
    printf("PASS\n");
}

// Тест 8: Вставка дублирующихся путей
void TestInsertDuplicatePaths_no8() {
    printf("Test 9: Insert duplicate paths... ");
    FolderTree* root = create_node("");

    insert_path(root, "A\\B\\C");
    insert_path(root, "A\\B\\C");

    FolderTree* a = find_child(root, "A");
    assert(a != NULL);
    assert(a->child_count == 1);

    FolderTree* b = find_child(a, "B");
    assert(b != NULL);
    assert(b->child_count == 1);

    free_tree(root);
    printf("PASS\n");
}

// Тест 9: Вставка путей с общими префиксами
void TestInsertPathsWithCommonPrefixes_no9() {
    printf("Test 10: Insert paths with common prefixes... ");
    FolderTree* root = create_node("");

    insert_path(root, "Common\\Path\\First");
    insert_path(root, "Common\\Path\\Second");
    insert_path(root, "Common\\Different");

    FolderTree* common = find_child(root, "Common");
    assert(common != NULL);
    assert(common->child_count >= 1);

    free_tree(root);
    printf("PASS\n");
}

// Тест 10: Сортировка детей в лексикографическом порядке
void TestSortChildrenLexicographically_no10() {
    printf("Test 11: Sort children lexicographically... ");
    FolderTree* root = create_node("root");
    FolderTree* zebra = create_node("Zebra");
    FolderTree* alpha = create_node("Alpha");
    FolderTree* beta = create_node("Beta");

    add_child(root, zebra);
    add_child(root, alpha);
    add_child(root, beta);

    assert(strcmp(root->child[0]->name, "Zebra") == 0);
    assert(strcmp(root->child[1]->name, "Alpha") == 0);
    assert(strcmp(root->child[2]->name, "Beta") == 0);

    sort_tree(root);

    assert(strcmp(root->child[0]->name, "Alpha") == 0);
    assert(strcmp(root->child[1]->name, "Beta") == 0);
    assert(strcmp(root->child[2]->name, "Zebra") == 0);

    free_tree(root);
    printf("PASS\n");
}

// Тест 11: Сортировка с учетом регистра (Z перед a)
void TestSortCaseSensitive_no11() {
    printf("Test 12: Sort case sensitive... ");
    FolderTree* root = create_node("root");
    FolderTree* apple = create_node("apple");
    FolderTree* Banana = create_node("Banana");
    FolderTree* zebra = create_node("zebra");
    FolderTree* Alpha = create_node("Alpha");

    add_child(root, apple);
    add_child(root, Banana);
    add_child(root, zebra);
    add_child(root, Alpha);

    sort_tree(root);

    assert(strcmp(root->child[0]->name, "Alpha") == 0);
    assert(strcmp(root->child[1]->name, "Banana") == 0);
    assert(strcmp(root->child[2]->name, "apple") == 0);
    assert(strcmp(root->child[3]->name, "zebra") == 0);

    free_tree(root);
    printf("PASS\n");
}

// Тест 12: Обработка граничных случаев - нулевые параметры - ОБНОВЛЕН
void TestHandleNullParameters_no12() {
    printf("Test 13: Handle null parameters... ");

    // Тест 1: create_node с NULL
    FolderTree* node = create_node(NULL);
    assert(node == NULL);

    // Тест 2: add_child с разными комбинациями NULL - просто вызываем
    FolderTree* temp_node = create_node("temp");
    assert(temp_node != NULL);

    add_child(NULL, NULL);
    add_child(temp_node, NULL);
    add_child(NULL, temp_node);

    // Тест 3: find_child с NULL
    assert(find_child(NULL, "test") == NULL);
    assert(find_child(temp_node, NULL) == NULL);
    assert(find_child(NULL, NULL) == NULL);

    // Тест 4: insert_path с NULL - просто вызываем
    FolderTree* root = create_node("");
    assert(root != NULL);

    insert_path(NULL, "test");
    insert_path(root, NULL);
    insert_path(NULL, NULL);

    free_tree(root);
    free_tree(temp_node);
    printf("PASS\n");
}

// Тест 13: Обработка пустых строк
void TestHandleEmptyStrings_no13() {
    printf("Test 14: Handle empty strings... ");

    FolderTree* root = create_node("");

    insert_path(root, "");
    insert_path(root, "   ");
    insert_path(root, "\\");
    insert_path(root, "\\\\");

    free_tree(root);
    printf("PASS\n");
}

// Тест 14: Тестирование освобождения памяти (проверка на утечки)
void TestMemoryFree_no14() {
    printf("Test 15: Memory free test... ");

    FolderTree* root = create_node("");
    insert_path(root, "A\\B\\C\\D");
    insert_path(root, "X\\Y\\Z");
    insert_path(root, "M\\N");

    free_tree(root);
    printf("PASS (check with valgrind for leaks)\n");
}

// Тест 15: Тестирование очень длинного пути
void TestVeryLongPath_no15() {
    printf("Test 16: Very long path test... ");
    FolderTree* root = create_node("");

    char long_path[500] = "";
    for (int i = 0; i < 10; i++) {
        char folder[10];
        sprintf(folder, "Folder%d", i);
        if (i > 0) strcat(long_path, "\\");
        strcat(long_path, folder);
    }

    insert_path(root, long_path);

    FolderTree* current = root;
    for (int i = 0; i < 10; i++) {
        char folder[10];
        sprintf(folder, "Folder%d", i);
        current = find_child(current, folder);
        assert(current != NULL);
    }

    free_tree(root);
    printf("PASS\n");
}

// Тест 16: Вставка пути с пробелами в именах
void TestInsertPath_SpacesInNames_no16() {
    printf("Test 16: Insert path with spaces in names... ");
    FolderTree* root = create_node("");
    insert_path(root, "Folder Name With Spaces\\Sub Folder");

    FolderTree* folder = find_child(root, "Folder Name With Spaces");
    assert(folder != NULL);

    FolderTree* sub = find_child(folder, "Sub Folder");
    assert(sub != NULL);

    free_tree(root);
    printf("PASS\n");
}

int main() {
    printf("=== Running FolderTree Tests ===\n\n");

    TestCreateNodeWithValidName_no1();
    TestCreateNodeWithSpecialCharacters_no2();
    TestCreateNodeWithLongNameTruncated_no3();
    TestAddFirstChildToEmptyNode_no4();
    TestAddMultipleChildrenWithSizeExpansion_no5();
    TestFindExistingAndNonExistingChild_no6();
    TestInsertComplexPathWithIntermediateNodes_no7();
    TestInsertDuplicatePaths_no8();
    TestInsertPathsWithCommonPrefixes_no9();
    TestSortChildrenLexicographically_no10();
    TestSortCaseSensitive_no11();
    TestHandleNullParameters_no12();
    TestHandleEmptyStrings_no13();
    TestMemoryFree_no14();
    TestVeryLongPath_no15();
    TestInsertPath_SpacesInNames_no16();

    printf("\n=== All tests PASSED! ===\n");

    return 0;
}