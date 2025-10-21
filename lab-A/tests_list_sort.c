#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_sort.h"

// Макрос для тестирования
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            printf("FAIL: %s\n", message); \
            return 0; \
        } else { \
            printf("PASS: %s\n", message); \
        } \
    } while(0)

#define RUN_TEST(test_func) \
    do { \
        printf("Running %s...\n", #test_func); \
        if (test_func()) { \
            printf("%s - PASSED\n\n", #test_func); \
            passed_tests++; \
        } else { \
            printf("%s - FAILED\n\n", #test_func); \
        } \
        total_tests++; \
    } while(0)

// Тест 1: Сортировка пустого списка
int test_empty_list_sort_no1() {
    ListNode* head = NULL;
    head = merge_sort(head);
    ASSERT(head == NULL, "An empty list should remain empty after sorting");
    return 1;
}

// Тест 2: Сортировка списка с одним элементом
int test_single_element_list_sort_no2() {
    ListNode* head = create_node("single");
    head = merge_sort(head);

    ASSERT(head != NULL, "List shouldn't be NULL");
    ASSERT(strcmp(head->data, "single") == 0, "The only element must retain the value");
    ASSERT(head->next == NULL, "There should be only one element.");

    free_list(head);
    return 1;
}

// Тест 3: Сортировка уже отсортированного списка
int test_already_sorted_list_no3() {
    ListNode* head = NULL;
    append_node(&head, "apple");
    append_node(&head, "banana");
    append_node(&head, "cherry");

    head = merge_sort(head);

    ListNode* current = head;
    ASSERT(strcmp(current->data, "apple") == 0, "First element 'apple'");
    current = current->next;
    ASSERT(strcmp(current->data, "banana") == 0, "Second element 'banana'");
    current = current->next;
    ASSERT(strcmp(current->data, "cherry") == 0, "Third element 'cherry'");

    free_list(head);
    return 1;
}

// Тест 4: Сортировка списка в обратном порядке
int test_reverse_sorted_list_no4() {
    ListNode* head = NULL;
    append_node(&head, "cherry");
    append_node(&head, "banana");
    append_node(&head, "apple");

    head = merge_sort(head);

    ListNode* current = head;
    ASSERT(strcmp(current->data, "apple") == 0, "First element 'apple'");
    current = current->next;
    ASSERT(strcmp(current->data, "banana") == 0, "Second element 'banana'");
    current = current->next;
    ASSERT(strcmp(current->data, "cherry") == 0, "Third element 'cherry'");

    free_list(head);
    return 1;
}

// Тест 5: Сортировка списка с дубликатами
int test_list_with_duplicates_no5() {
    ListNode* head = NULL;
    append_node(&head, "banana");
    append_node(&head, "apple");
    append_node(&head, "banana");
    append_node(&head, "apple");

    head = merge_sort(head);

    ListNode* current = head;
    ASSERT(strcmp(current->data, "apple") == 0, "'apple'");
    current = current->next;
    ASSERT(strcmp(current->data, "apple") == 0, "'apple'");
    current = current->next;
    ASSERT(strcmp(current->data, "banana") == 0, "'banana'");
    current = current->next;
    ASSERT(strcmp(current->data, "banana") == 0, "'banana'");

    free_list(head);
    return 1;
}

// Тест 6: Сортировка списка с числами как строками
int test_numeric_strings_no6() {
    ListNode* head = NULL;
    append_node(&head, "100");
    append_node(&head, "50");
    append_node(&head, "200");
    append_node(&head, "25");

    head = merge_sort(head);

    ListNode* current = head;
    ASSERT(strcmp(current->data, "100") == 0, "'100'");
    current = current->next;
    ASSERT(strcmp(current->data, "200") == 0, "'200'");
    current = current->next;
    ASSERT(strcmp(current->data, "25") == 0, "'25'");
    current = current->next;
    ASSERT(strcmp(current->data, "50") == 0, "'50'");

    free_list(head);
    return 1;
}

// Тест 7: Сортировка большого списка
int test_large_list_sort_no7() {
    ListNode* head = NULL;
    const char* words[] = { "zebra", "apple", "monkey", "banana", "cat", "elephant", "dog" };
    int count = sizeof(words) / sizeof(words[0]);

    for (int i = 0; i < count; i++) {
        append_node(&head, words[i]);
    }

    head = merge_sort(head);

    const char* expected[] = { "apple", "banana", "cat", "dog", "elephant", "monkey", "zebra" };
    ListNode* current = head;

    for (int i = 0; i < count; i++) {
        ASSERT(strcmp(current->data, expected[i]) == 0,
            "Elements must be sorted in alphabetical order");
        current = current->next;
    }

    free_list(head);
    return 1;
}

// Тест 8: Сортировка списка с пустыми строками
int test_list_with_empty_strings_no8() {
    ListNode* head = NULL;
    append_node(&head, "non-empty");
    append_node(&head, "");
    append_node(&head, "test");

    head = merge_sort(head);

    ListNode* current = head;
    ASSERT(strcmp(current->data, "") == 0, "The empty line should be the first one.");
    current = current->next;
    ASSERT(strcmp(current->data, "non-empty") == 0, "'non-empty'");
    current = current->next;
    ASSERT(strcmp(current->data, "test") == 0, "'test'");

    free_list(head);
    return 1;
}

// Тест 9: Сортировка списка с одинаковыми строками
int test_list_with_all_same_strings_no9() {
    ListNode* head = NULL;
    append_node(&head, "same");
    append_node(&head, "same");
    append_node(&head, "same");
    append_node(&head, "same");

    head = merge_sort(head);

    ListNode* current = head;
    int count = 0;
    while (current != NULL) {
        ASSERT(strcmp(current->data, "same") == 0, "All elements 'same'");
        count++;
        current = current->next;
    }
    ASSERT(count == 4, "There must be 4 elements");

    free_list(head);
    return 1;
}

// Тест 10: Сортировка списка со специальными символами
int test_list_with_special_characters_no10() {
    ListNode* head = NULL;
    append_node(&head, "!first");
    append_node(&head, "second");
    append_node(&head, "#third");
    append_node(&head, "alpha");

    head = merge_sort(head);

    ListNode* current = head;
    ASSERT(strcmp(current->data, "!first") == 0, "'!first'");
    current = current->next;
    ASSERT(strcmp(current->data, "#third") == 0, "'#third'");
    current = current->next;
    ASSERT(strcmp(current->data, "alpha") == 0, "'alpha'");
    current = current->next;
    ASSERT(strcmp(current->data, "second") == 0, "'second'");

    free_list(head);
    return 1;
}

// Главная функция тестирования
int main() {
    printf("=== Start Unit-tests ===\n\n");

    int total_tests = 0;
    int passed_tests = 0;

    RUN_TEST(test_empty_list_sort_no1);
    RUN_TEST(test_single_element_list_sort_no2);
    RUN_TEST(test_already_sorted_list_no3);
    RUN_TEST(test_reverse_sorted_list_no4);
    RUN_TEST(test_list_with_duplicates_no5);
    RUN_TEST(test_numeric_strings_no6);
    RUN_TEST(test_large_list_sort_no7);
    RUN_TEST(test_list_with_empty_strings_no8);
    RUN_TEST(test_list_with_all_same_strings_no9);
    RUN_TEST(test_list_with_special_characters_no10);

    printf("=== Results ===\n");
    printf("Tests: %d/%d\n", passed_tests, total_tests);
    printf("Passed: %.1f%%\n", (float)passed_tests / total_tests * 100);

    return (passed_tests == total_tests) ? 0 : 1;
}