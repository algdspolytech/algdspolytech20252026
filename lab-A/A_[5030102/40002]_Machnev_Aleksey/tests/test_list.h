#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

// Тест 1: Создание узла с валидной строкой
void TestCreateNode_ValidString_no1() {
    printf("Test 1: Create node with valid string... ");
    struct Node* node = create_node("test");
    assert(node != NULL);
    assert(strcmp(node->data, "test") == 0);
    assert(node->prev == NULL);
    assert(node->next == NULL);
    free(node->data);
    free(node);
    printf("PASSED\n");
}

// Тест 2: Создание узла с NULL строкой
void TestCreateNode_NullString_no2() {
    printf("Test 2: Create node with NULL string... ");
    struct Node* node = create_node(NULL);
    assert(node == NULL);
    printf("PASSED\n");
}

// Тест 3: Добавление в пустой список
void TestAddToList_EmptyList_no3() {
    printf("Test 3: Add to empty list... ");
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    add_to_list(&head, &tail, "first");
    assert(head != NULL);
    assert(tail != NULL);
    assert(head == tail);
    assert(strcmp(head->data, "first") == 0);
    
    free_list(head);
    printf("PASSED\n");
}

// Тест 4: Добавление нескольких элементов
void TestAddToList_MultipleElements_no4() {
    printf("Test 4: Add multiple elements... ");
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    add_to_list(&head, &tail, "first");
    add_to_list(&head, &tail, "second");
    add_to_list(&head, &tail, "third");
    
    assert(list_size(head) == 3);
    assert(strcmp(head->data, "first") == 0);
    assert(strcmp(tail->data, "third") == 0);
    assert(head->next->data != NULL);
    assert(strcmp(head->next->data, "second") == 0);
    
    free_list(head);
    printf("PASSED\n");
}

// Тест 5: Сортировка пустого списка
void TestSortList_EmptyList_no5() {
    printf("Test 5: Sort empty list... ");
    struct Node* head = NULL;
    
    sort_list(&head);
    assert(head == NULL);
    printf("PASSED\n");
}

// Тест 6: Сортировка списка из одного элемента
void TestSortList_SingleElement_no6() {
    printf("Test 6: Sort single element list... ");
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    add_to_list(&head, &tail, "single");
    sort_list(&head);
    
    assert(list_size(head) == 1);
    assert(strcmp(head->data, "single") == 0);
    assert(is_sorted(head) == 1);
    
    free_list(head);
    printf("PASSED\n");
}

// Тест 7: Сортировка уже отсортированного списка
void TestSortList_AlreadySorted_no7() {
    printf("Test 7: Sort already sorted list... ");
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    add_to_list(&head, &tail, "apple");
    add_to_list(&head, &tail, "banana");
    add_to_list(&head, &tail, "cherry");
    
    sort_list(&head);
    assert(is_sorted(head) == 1);
    assert(strcmp(get_node_data(head, 0), "apple") == 0);
    assert(strcmp(get_node_data(head, 1), "banana") == 0);
    assert(strcmp(get_node_data(head, 2), "cherry") == 0);
    
    free_list(head);
    printf("PASSED\n");
}

// Тест 8: Сортировка обратно отсортированного списка
void TestSortList_ReverseSorted_no8() {
    printf("Test 8: Sort reverse sorted list... ");
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    add_to_list(&head, &tail, "cherry");
    add_to_list(&head, &tail, "banana");
    add_to_list(&head, &tail, "apple");
    
    sort_list(&head);
    assert(is_sorted(head) == 1);
    assert(strcmp(get_node_data(head, 0), "apple") == 0);
    assert(strcmp(get_node_data(head, 1), "banana") == 0);
    assert(strcmp(get_node_data(head, 2), "cherry") == 0);
    
    free_list(head);
    printf("PASSED\n");
}

// Тест 9: Сортировка списка с дубликатами
void TestSortList_WithDuplicates_no9() {
    printf("Test 9: Sort list with duplicates... ");
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    add_to_list(&head, &tail, "banana");
    add_to_list(&head, &tail, "apple");
    add_to_list(&head, &tail, "banana");
    add_to_list(&head, &tail, "apple");
    
    sort_list(&head);
    assert(is_sorted(head) == 1);
    assert(list_size(head) == 4);
    
    free_list(head);
    printf("PASSED\n");
}

// Тест 10: Сортировка большого списка
void TestSortList_LargeList_no10() {
    printf("Test 10: Sort large list... ");
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    add_to_list(&head, &tail, "zebra");
    add_to_list(&head, &tail, "apple");
    add_to_list(&head, &tail, "mango");
    add_to_list(&head, &tail, "banana");
    add_to_list(&head, &tail, "cherry");
    add_to_list(&head, &tail, "date");
    
    sort_list(&head);
    assert(is_sorted(head) == 1);
    assert(list_size(head) == 6);
    assert(strcmp(get_node_data(head, 0), "apple") == 0);
    assert(strcmp(get_node_data(head, 5), "zebra") == 0);
    
    free_list(head);
    printf("PASSED\n");
}

// Тест 11: Проверка связей после сортировки
void TestSortList_CheckLinks_no11() {
    printf("Test 11: Check links after sorting... ");
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    add_to_list(&head, &tail, "cherry");
    add_to_list(&head, &tail, "apple");
    add_to_list(&head, &tail, "banana");
    
    sort_list(&head);
    
    // Проверяем forward links
    assert(strcmp(head->data, "apple") == 0);
    assert(strcmp(head->next->data, "banana") == 0);
    assert(strcmp(head->next->next->data, "cherry") == 0);
    
    // Проверяем backward links
    assert(head->prev == NULL);
    assert(head->next->prev == head);
    assert(head->next->next->prev == head->next);
    
    free_list(head);
    printf("PASSED\n");
}

// Тест 12: Добавление NULL строки
void TestAddToList_NullString_no12() {
    printf("Test 12: Add NULL string to list... ");
    struct Node* head = NULL;
    struct Node* tail = NULL;
    
    add_to_list(&head, &tail, "valid");
    add_to_list(&head, &tail, NULL);
    add_to_list(&head, &tail, "another");
    
    assert(list_size(head) == 2); // NULL не должен добавиться
    assert(strcmp(head->data, "valid") == 0);
    assert(strcmp(head->next->data, "another") == 0);
    
    free_list(head);
    printf("PASSED\n");
}