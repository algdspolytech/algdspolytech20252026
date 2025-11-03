void test_enqueue_dequeue_list_no1();
void test_empty_dequeue_list_no2();
void test_multiple_enqueue_dequeue_list_no3();
void test_stress_list_no4();
void test_enqueue_dequeue_array_no5();
void test_empty_dequeue_array_no6();
void test_multiple_enqueue_dequeue_array_no7();
void test_overflow_array_no8();
void test_mixed_operations_array_no9();
void test_stress_array_no10();
// в clion сильные проблемы с выводом русского языка
#include <stdio.h>
#include <assert.h>
#include "main.c"


//очередь на списке
void test_enqueue_dequeue_list_no1() {
    Ochered q;
    newochered(&q);
    enqueueList(&q, 10);
    int val;
    assert(dequeueList(&q, &val) == 1);
    assert(val == 10);
    freeQueueList(&q);
}

void test_empty_dequeue_list_no2() {
    Ochered q;
    newochered(&q);
    int val;
    assert(dequeueList(&q, &val) == 0);
}

void test_multiple_enqueue_dequeue_list_no3() {
    Ochered q;
    newochered(&q);
    enqueueList(&q, 1);
    enqueueList(&q, 2);
    enqueueList(&q, 3);
    int val;
    assert(dequeueList(&q, &val) == 1 && val == 1);
    assert(dequeueList(&q, &val) == 1 && val == 2);
    assert(dequeueList(&q, &val) == 1 && val == 3);
    assert(dequeueList(&q, &val) == 0);
    freeQueueList(&q);
}

void test_stress_list_no4() {
    Ochered q;
    newochered(&q);
    for (int i = 0; i < 1000; i++)
        enqueueList(&q, i);
    int val;
    for (int i = 0; i < 1000; i++) {
        assert(dequeueList(&q, &val) == 1);
        assert(val == i);
    }
    freeQueueList(&q);
}

// очередь на массиве

void test_enqueue_dequeue_array_no5() {
    QueueArray q;
    initQueueArray(&q);
    assert(newElement(&q, 5) == 1);
    int val;
    assert(deliteElement(&q, &val) == 1);
    assert(val == 5);
    assert(isEmptyArray(&q) == 1);
}

void test_empty_dequeue_array_no6() {
    QueueArray q;
    initQueueArray(&q);
    int val;
    assert(deliteElement(&q, &val) == 0);
}

void test_multiple_enqueue_dequeue_array_no7() {
    QueueArray q;
    initQueueArray(&q);
    newElement(&q, 1);
    newElement(&q, 2);
    newElement(&q, 3);
    int val;
    assert(deliteElement(&q, &val) == 1 && val == 1);
    assert(deliteElement(&q, &val) == 1 && val == 2);
    assert(deliteElement(&q, &val) == 1 && val == 3);
}

void test_overflow_array_no8() {
    QueueArray q;
    initQueueArray(&q);
    for (int i = 0; i < MAX_SIZE; i++)
        assert(newElement(&q, i) == 1);
    assert(newElement(&q, 999) == 0);
}

void test_mixed_operations_array_no9() {
    QueueArray q;
    initQueueArray(&q);
    newElement(&q, 1);
    newElement(&q, 2);
    int val;
    assert(deliteElement(&q, &val) == 1 && val == 1);
    newElement(&q, 3);
    assert(deliteElement(&q, &val) == 1 && val == 2);
}

void test_stress_array_no10() {
    QueueArray q;
    initQueueArray(&q);
    for (int i = 0; i < MAX_SIZE; i++) {
        assert(newElement(&q, i) == 1);
    }
    int val;
    assert(newElement(&q, 9999) == 0);
    for (int i = 0; i < MAX_SIZE; i++) {
        assert(deliteElement(&q, &val) == 1);
        assert(val == i);
    }
    assert(isEmptyArray(&q) == 1);
}

// тесты

int main() {
    printf("Running tests for linked list queue...\n");
    test_enqueue_dequeue_list_no1();
    test_empty_dequeue_list_no2();
    test_multiple_enqueue_dequeue_list_no3();
    test_stress_list_no4();
    printf("All linked list queue tests passed!\n\n");

    printf("Running tests for array queue...\n");
    test_enqueue_dequeue_array_no5();
    test_empty_dequeue_array_no6();
    test_multiple_enqueue_dequeue_array_no7();
    test_overflow_array_no8();
    test_mixed_operations_array_no9();
    test_stress_array_no10();
    printf("All array queue tests passed!\n");

    return 0;
}