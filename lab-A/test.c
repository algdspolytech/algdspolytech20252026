#include "set.h"
#include <assert.h>
#include <stdio.h>

void TestAddToEmptySet_HappyPath_no1() {
    Set* s = set_create();
    assert(set_add(s, 10));
    assert(set_contains(s, 10));
    set_destroy(s);
}

void TestAddDuplicateElement_no2() {
    Set* s = set_create();
    set_add(s, 5);
    assert(!set_add(s, 5));
    set_destroy(s);
}

void TestAddElementsOrdered_no3() {
    Set* s = set_create();
    set_add(s, 10);
    set_add(s, 1);
    set_add(s, 5);
    assert(set_contains(s, 1));
    assert(set_contains(s, 5));
    assert(set_contains(s, 10));
    set_destroy(s);
}

void TestRemoveExistingElement_no4() {
    Set* s = set_create();
    set_add(s, 7);
    assert(set_remove(s, 7));
    assert(!set_contains(s, 7));
    set_destroy(s);
}

void TestRemoveNonExistingElement_no5() {
    Set* s = set_create();
    assert(!set_remove(s, 42));
    set_destroy(s);
}

void TestContainsEmptySet_no6() {
    Set* s = set_create();
    assert(!set_contains(s, 1));
    set_destroy(s);
}

void TestUnionDisjointSets_no7() {
    Set* a = set_create();
    Set* b = set_create();
    set_add(a, 1);
    set_add(b, 2);

    Set* u = set_union(a, b);
    assert(set_contains(u, 1));
    assert(set_contains(u, 2));

    set_destroy(a);
    set_destroy(b);
    set_destroy(u);
}

void TestUnionWithOverlap_no8() {
    Set* a = set_create();
    Set* b = set_create();
    set_add(a, 1);
    set_add(a, 2);
    set_add(b, 2);
    set_add(b, 3);

    Set* u = set_union(a, b);
    assert(set_contains(u, 1));
    assert(set_contains(u, 2));
    assert(set_contains(u, 3));

    set_destroy(a);
    set_destroy(b);
    set_destroy(u);
}

void TestIntersectionEmptyResult_no9() {
    Set* a = set_create();
    Set* b = set_create();
    set_add(a, 1);
    set_add(b, 2);

    Set* i = set_intersection(a, b);
    assert(!set_contains(i, 1));
    assert(!set_contains(i, 2));

    set_destroy(a);
    set_destroy(b);
    set_destroy(i);
}

void TestIntersectionWithCommonElements_no10() {
    Set* a = set_create();
    Set* b = set_create();
    set_add(a, 1);
    set_add(a, 2);
    set_add(b, 2);
    set_add(b, 3);

    Set* i = set_intersection(a, b);
    assert(set_contains(i, 2));
    assert(!set_contains(i, 1));
    assert(!set_contains(i, 3));

    set_destroy(a);
    set_destroy(b);
    set_destroy(i);
}

int main() {
    TestAddToEmptySet_HappyPath_no1();
    TestAddDuplicateElement_no2();
    TestAddElementsOrdered_no3();
    TestRemoveExistingElement_no4();
    TestRemoveNonExistingElement_no5();
    TestContainsEmptySet_no6();
    TestUnionDisjointSets_no7();
    TestUnionWithOverlap_no8();
    TestIntersectionEmptyResult_no9();
    TestIntersectionWithCommonElements_no10();

    printf("ALL TESTS PASSED\n");
    return 0;
}
