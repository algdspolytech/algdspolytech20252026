#include "priority_queue.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void check_queue_content(PriorityQueue* pq, int* expected, int size) {
    int actual_size;
    int* actual = pq_to_array(pq, &actual_size);

    assert(actual_size == size);
    for (int i = 0; i < size; i++) {
        assert(actual[i] == expected[i]);
    }
    free(actual);
}

void TestAddToEmptyQueue_no1() {
    printf("Running TestAddToEmptyQueue_no1\n");
    PriorityQueue* pq = pq_create();
    pq_enqueue(pq, 10, 5);

    assert(pq_size(pq) == 1);
    assert(pq_peek(pq) == 10);
    assert(!pq_is_empty(pq));

    pq_destroy(pq);
    printf("TestAddToEmptyQueue_no1: PASSED\n\n");
}

void TestAddDifferentPriorities_no2() {
    printf("Running TestAddDifferentPriorities_no2\n");
    PriorityQueue* pq = pq_create();
    pq_enqueue(pq, 10, 1);
    pq_enqueue(pq, 20, 5);
    pq_enqueue(pq, 30, 3);

    assert(pq_size(pq) == 3);
    assert(pq_peek(pq) == 20);

    int expected[] = { 20, 30, 10 };
    check_queue_content(pq, expected, 3);

    pq_destroy(pq);
    printf("TestAddDifferentPriorities_no2: PASSED\n\n");
}

void TestAddSamePriorities_no3() {
    printf("Running TestAddSamePriorities_no3\n");
    PriorityQueue* pq = pq_create();
    pq_enqueue(pq, 10, 5);
    pq_enqueue(pq, 20, 5);
    pq_enqueue(pq, 30, 5);

    assert(pq_size(pq) == 3);

    pq_destroy(pq);
    printf("TestAddSamePriorities_no3: PASSED\n\n");
}

void TestDequeueFromEmpty_no4() {
    printf("Running TestDequeueFromEmpty_no4\n");
    PriorityQueue* pq = pq_create();

    int result = pq_dequeue(pq);
    assert(result == -1);
    assert(pq_is_empty(pq));
    assert(pq_size(pq) == 0);

    pq_destroy(pq);
    printf("TestDequeueFromEmpty_no4: PASSED\n\n");
}

void TestSequentialEnqueueDequeue_no5() {
    printf("Running TestSequentialEnqueueDequeue_no5\n");
    PriorityQueue* pq = pq_create();

    pq_enqueue(pq, 10, 3);
    pq_enqueue(pq, 20, 1);
    pq_enqueue(pq, 30, 5);

    assert(pq_dequeue(pq) == 30);
    assert(pq_dequeue(pq) == 10);
    assert(pq_dequeue(pq) == 20);
    assert(pq_is_empty(pq));

    pq_destroy(pq);
    printf("TestSequentialEnqueueDequeue_no5: PASSED\n\n");
}

void TestPeekWithoutDequeue_no6() {
    printf("Running TestPeekWithoutDequeue_no6\n");
    PriorityQueue* pq = pq_create();
    pq_enqueue(pq, 10, 5);
    pq_enqueue(pq, 20, 3);

    assert(pq_peek(pq) == 10);
    assert(pq_size(pq) == 2);
    assert(pq_peek(pq) == 10);

    pq_destroy(pq);
    printf("TestPeekWithoutDequeue_no6: PASSED\n\n");
}

void TestClearNonEmptyQueue_no7() {
    printf("Running TestClearNonEmptyQueue_no7\n");
    PriorityQueue* pq = pq_create();
    pq_enqueue(pq, 10, 1);
    pq_enqueue(pq, 20, 2);
    pq_enqueue(pq, 30, 3);

    assert(pq_size(pq) == 3);
    pq_clear(pq);
    assert(pq_is_empty(pq));
    assert(pq_size(pq) == 0);

    pq_enqueue(pq, 40, 4);
    assert(pq_size(pq) == 1);
    assert(pq_peek(pq) == 40);

    pq_destroy(pq);
    printf("TestClearNonEmptyQueue_no7: PASSED\n\n");
}

void TestNegativePriorities_no8() {
    printf("Running TestNegativePriorities_no8\n");
    PriorityQueue* pq = pq_create();
    pq_enqueue(pq, 10, -5);
    pq_enqueue(pq, 20, -1);
    pq_enqueue(pq, 30, -10);

    assert(pq_peek(pq) == 20);

    int expected[] = { 20, 10, 30 };
    check_queue_content(pq, expected, 3);

    pq_destroy(pq);
    printf("TestNegativePriorities_no8: PASSED\n\n");
}

void TestLargeNumberOfElements_no9() {
    printf("Running TestLargeNumberOfElements_no9\n");
    PriorityQueue* pq = pq_create();
    const int count = 100;

    for (int i = 0; i < count; i++) {
        pq_enqueue(pq, i, i); 
    }

    assert(pq_size(pq) == count);

    for (int i = count - 1; i >= 0; i--) {
        int expected_data = i;
        int actual_data = pq_dequeue(pq);
        assert(actual_data == expected_data);
    }

    assert(pq_is_empty(pq));
    pq_destroy(pq);
    printf("TestLargeNumberOfElements_no9: PASSED\n\n");
}

void TestMixedOperations_no10() {
    printf("Running TestMixedOperations_no10\n");
    PriorityQueue* pq = pq_create();

    pq_enqueue(pq, 100, 10);
    pq_enqueue(pq, 200, 5);
    assert(pq_peek(pq) == 100);

    pq_enqueue(pq, 300, 15);
    assert(pq_peek(pq) == 300);

    assert(pq_dequeue(pq) == 300);
    assert(pq_peek(pq) == 100);

    pq_enqueue(pq, 400, 8);
    pq_enqueue(pq, 500, 12);

    assert(pq_dequeue(pq) == 500);
    assert(pq_dequeue(pq) == 100);
    assert(pq_dequeue(pq) == 400);
    assert(pq_dequeue(pq) == 200);
    assert(pq_is_empty(pq));

    pq_destroy(pq);
    printf("TestMixedOperations_no10: PASSED\n\n");
}

void TestNullPointers_no11() {
    printf("Running TestNullPointers_no11\n");

    pq_enqueue(NULL, 10, 5);
    assert(pq_dequeue(NULL) == -1);
    assert(pq_peek(NULL) == -1);
    assert(pq_is_empty(NULL) == 1);
    assert(pq_size(NULL) == 0);
    pq_clear(NULL);
    pq_destroy(NULL);

    printf("TestNullPointers_no11: PASSED\n\n");
}

void TestOrderWithSamePriority_no12() {
    printf("Running TestOrderWithSamePriority_no12\n");
    PriorityQueue* pq = pq_create();

    pq_enqueue(pq, 10, 5);
    pq_enqueue(pq, 20, 5);
    pq_enqueue(pq, 30, 5);

    int expected[] = { 10, 20, 30 };
    check_queue_content(pq, expected, 3);

    pq_destroy(pq);
    printf("TestOrderWithSamePriority_no12: PASSED\n\n");
}

void TestMemoryLeaks_no13() {
    printf("Running TestMemoryLeaks_no13\n");
    PriorityQueue* pq = pq_create();

    for (int i = 0; i < 1000; i++) {
        pq_enqueue(pq, i, i % 10);
    }

    for (int i = 0; i < 500; i++) {
        pq_dequeue(pq);
    }

    int size;
    int* arr = pq_to_array(pq, &size);
    free(arr);

    pq_destroy(pq);
    printf("TestMemoryLeaks_no13: PASSED\n\n");
}

int main() {
    printf("Starting Priority Queue Unit Tests...\n\n");

    TestAddToEmptyQueue_no1();
    TestAddDifferentPriorities_no2();
    TestAddSamePriorities_no3();
    TestDequeueFromEmpty_no4();
    TestSequentialEnqueueDequeue_no5();
    TestPeekWithoutDequeue_no6();
    TestClearNonEmptyQueue_no7();
    TestNegativePriorities_no8();
    TestLargeNumberOfElements_no9();
    TestMixedOperations_no10();
    TestNullPointers_no11();
    TestOrderWithSamePriority_no12();
    TestMemoryLeaks_no13();

    printf("=========================================\n");
    printf("All 13 tests passed.\n");
    printf("=========================================\n");

    return 0;
}