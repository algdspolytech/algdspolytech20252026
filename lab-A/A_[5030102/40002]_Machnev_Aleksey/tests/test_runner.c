#include <stdio.h>
#include "test_list.h"

void run_all_tests() {
    printf("Running tests for doubly linked list...\n\n");
    
    TestCreateNode_ValidString_no1();
    TestCreateNode_NullString_no2();
    TestAddToList_EmptyList_no3();
    TestAddToList_MultipleElements_no4();
    TestSortList_EmptyList_no5();
    TestSortList_SingleElement_no6();
    TestSortList_AlreadySorted_no7();
    TestSortList_ReverseSorted_no8();
    TestSortList_WithDuplicates_no9();
    TestSortList_LargeList_no10();
    TestSortList_CheckLinks_no11();
    TestSortList_NullString_no12();
    
    printf("\nAll tests PASSED!\n");
}

int main() {
    run_all_tests();
    return 0;
}