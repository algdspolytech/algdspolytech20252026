
#include "list_sort.h"
#include <assert.h>
#include <string.h>

// Test 1: CreateNode_ValidString_ReturnsNode_no1
void test_CreateNode_ValidString_ReturnsNode_no1() {
    Node* n = create_node("test");
    assert(n && strcmp(n->data, "test") == 0 && n->next == NULL);
    free_list(n);
}

// Test 2: MergeSort_EmptyList_ReturnsNull_no2
void test_MergeSort_EmptyList_ReturnsNull_no2() {
    Node* list = NULL;
    merge_sort(&list);
    assert(list == NULL);
}

// Test 3: MergeSort_SingleElement_ReturnsSame_no3
void test_MergeSort_SingleElement_ReturnsSame_no3() {
    const char* arr[] = { "one" };
    Node* list = create_list(arr, 1);
    merge_sort(&list);
    Node* expected = create_list(arr, 1);
    assert(compare_lists(list, expected));
    free_list(list); free_list(expected);
}

// Test 4: MergeSort_TwoElementsSorted_NoChange_no4
void test_MergeSort_TwoElementsSorted_NoChange_no4() {
    const char* arr[] = { "a", "b" };
    Node* list = create_list(arr, 2);
    merge_sort(&list);
    Node* expected = create_list(arr, 2);
    assert(compare_lists(list, expected));
    free_list(list); free_list(expected);
}

// Test 5: MergeSort_TwoElementsUnsorted_ReturnsSorted_no5
void test_MergeSort_TwoElementsUnsorted_ReturnsSorted_no5() {
    const char* arr[] = { "b", "a" }, * exp[] = { "a", "b" };
    Node* list = create_list(arr, 2);
    merge_sort(&list);
    Node* expected = create_list(exp, 2);
    assert(compare_lists(list, expected));
    free_list(list); free_list(expected);
}

// Test 6: MergeSort_SeveralElements_ReturnsSorted_no6
void test_MergeSort_SeveralElements_ReturnsSorted_no6() {
    const char* input[] = { "pear","orange","banana","apple" };
    const char* expected[] = { "apple","banana","orange","pear" };
    Node* list = create_list(input, 4);
    merge_sort(&list);
    Node* exp_list = create_list(expected, 4);
    assert(compare_lists(list, exp_list));
    free_list(list); free_list(exp_list);
}

// Test 7: MergeSort_DuplicateElements_ReturnsSorted_no7
void test_MergeSort_DuplicateElements_ReturnsSorted_no7() {
    const char* arr[] = { "orange","apple","orange","banana" };
    const char* exp[] = { "apple","banana","orange","orange" };
    Node* list = create_list(arr, 4);
    merge_sort(&list);
    Node* expected = create_list(exp, 4);
    assert(compare_lists(list, expected));
    free_list(list); free_list(expected);
}

// Test 8: MergeSort_AllEqualElements_NoChange_no8
void test_MergeSort_AllEqualElements_NoChange_no8() {
    const char* arr[] = { "a","a","a" };
    Node* list = create_list(arr, 3);
    merge_sort(&list);
    Node* expected = create_list(arr, 3);
    assert(compare_lists(list, expected));
    free_list(list); free_list(expected);
}

// Test 9: MergeSort_ReverseSorted_ReturnsSorted_no9
void test_MergeSort_ReverseSorted_ReturnsSorted_no9() {
    const char* arr[] = { "d","c","b","a" };
    const char* exp[] = { "a","b","c","d" };
    Node* list = create_list(arr, 4);
    merge_sort(&list);
    Node* expected = create_list(exp, 4);
    assert(compare_lists(list, expected));
    free_list(list); free_list(expected);
}

// Test 10: MergeSort_MixedCaseStrings_AsciiOrder_no10
void test_MergeSort_MixedCaseStrings_AsciiOrder_no10() {
    const char* arr[] = { "Banana","apple","banana","Apple" };
    const char* exp[] = { "Apple","Banana","apple","banana" };
    Node* list = create_list(arr, 4);
    merge_sort(&list);
    Node* expected = create_list(exp, 4);
    assert(compare_lists(list, expected));
    free_list(list); free_list(expected);
}

int main(void) {
    test_CreateNode_ValidString_ReturnsNode_no1();
    test_MergeSort_EmptyList_ReturnsNull_no2();
    test_MergeSort_SingleElement_ReturnsSame_no3();
    test_MergeSort_TwoElementsSorted_NoChange_no4();
    test_MergeSort_TwoElementsUnsorted_ReturnsSorted_no5();
    test_MergeSort_SeveralElements_ReturnsSorted_no6();
    test_MergeSort_DuplicateElements_ReturnsSorted_no7();
    test_MergeSort_AllEqualElements_NoChange_no8();
    test_MergeSort_ReverseSorted_ReturnsSorted_no9();
    test_MergeSort_MixedCaseStrings_AsciiOrder_no10();
    return 0;
}
