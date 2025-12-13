#include "unrolled_list.h"
#include <stdio.h>
#include <string.h>

#define MU_ASSERT(message, test) do { if (!(test)) return message; } while (0)
#define MU_RUN_TEST(test) do { char* message = test(); tests_run++; \
                            if (message) return message; } while (0)

int tests_run = 0;


static char* test_create_destroy_no1() {
	UnrolledList* list = unrolled_list_create();
	MU_ASSERT("Failed to create list", list != NULL);
	MU_ASSERT("List should be empty", unrolled_list_size(list) == 0);
	MU_ASSERT("Head should be NULL", list->head == NULL);
	MU_ASSERT("Tail should be NULL", list->tail == NULL);

	unrolled_list_destroy(list);
	return 0;
}

static char* test_add_to_empty_list_no2() {
	UnrolledList* list = unrolled_list_create();

	bool result = unrolled_list_add(list, 42);
	MU_ASSERT("Add should succeed", result == true);
	MU_ASSERT("Size should be 1", unrolled_list_size(list) == 1);
	MU_ASSERT("Head should not be NULL", list->head != NULL);
	MU_ASSERT("Tail should equal head", list->tail == list->head);
	MU_ASSERT("Node count should be 1", list->head->count == 1);
	MU_ASSERT("First element should be 42", list->head->data[0] == 42);

	unrolled_list_destroy(list);
	return 0;
}

static char* test_add_multiple_in_one_block_no3() {
	UnrolledList* list = unrolled_list_create();

	for (int i = 0; i < BLOCK_CAPACITY; i++) {
		bool result = unrolled_list_add(list, i * 10);
		MU_ASSERT("Add should succeed", result == true);
	}

	MU_ASSERT("Size should equal BLOCK_CAPACITY",
		unrolled_list_size(list) == BLOCK_CAPACITY);
	MU_ASSERT("Should have only one node", list->head == list->tail);
	MU_ASSERT("Node should be full", list->head->count == BLOCK_CAPACITY);

	for (int i = 0; i < BLOCK_CAPACITY; i++) {
		int value;
		bool found = unrolled_list_get_at(list, i, &value);
		MU_ASSERT("Element should be found", found);
		MU_ASSERT("Value should match", value == i * 10);
	}

	unrolled_list_destroy(list);
	return 0;
}

static char* test_create_second_block_no4() {
	UnrolledList* list = unrolled_list_create();

	for (int i = 0; i < BLOCK_CAPACITY; i++) {
		unrolled_list_add(list, i);
	}

	bool result = unrolled_list_add(list, 100);
	MU_ASSERT("Add should succeed", result == true);

	MU_ASSERT("Size should be BLOCK_CAPACITY + 1",
		unrolled_list_size(list) == BLOCK_CAPACITY + 1);
	MU_ASSERT("Should have two nodes", list->head != list->tail);
	MU_ASSERT("First node should be full", list->head->count == BLOCK_CAPACITY);
	MU_ASSERT("Second node should have 1 element", list->tail->count == 1);
	MU_ASSERT("Second node value should be 100", list->tail->data[0] == 100);

	unrolled_list_destroy(list);
	return 0;
}

static char* test_find_index_no5() {
	UnrolledList* list = unrolled_list_create();

	for (int i = 0; i < 5; i++) {
		unrolled_list_add(list, i * 5);
	}

	MU_ASSERT("Find 0 should return 0", unrolled_list_find_index(list, 0) == 0);
	MU_ASSERT("Find 10 should return 2", unrolled_list_find_index(list, 10) == 2);
	MU_ASSERT("Find 20 should return 4", unrolled_list_find_index(list, 20) == 4);
	MU_ASSERT("Find non-existent should return -1",
		unrolled_list_find_index(list, 99) == -1);

	unrolled_list_destroy(list);
	return 0;
}

static char* test_get_at_no6() {
	UnrolledList* list = unrolled_list_create();

	for (int i = 0; i < 7; i++) {
		unrolled_list_add(list, i * 3);
	}

	int value;
	bool result;

	result = unrolled_list_get_at(list, 0, &value);
	MU_ASSERT("Get at 0 should succeed", result);
	MU_ASSERT("Value at 0 should be 0", value == 0);

	result = unrolled_list_get_at(list, 3, &value);
	MU_ASSERT("Get at 3 should succeed", result);
	MU_ASSERT("Value at 3 should be 9", value == 9);

	result = unrolled_list_get_at(list, 6, &value);
	MU_ASSERT("Get at 6 should succeed", result);
	MU_ASSERT("Value at 6 should be 18", value == 18);

	result = unrolled_list_get_at(list, -1, &value);
	MU_ASSERT("Get at -1 should fail", !result);

	result = unrolled_list_get_at(list, 10, &value);
	MU_ASSERT("Get at 10 should fail", !result);

	result = unrolled_list_get_at(NULL, 0, &value);
	MU_ASSERT("Get with NULL list should fail", !result);

	unrolled_list_destroy(list);
	return 0;
}

static char* test_remove_at_no7() {
	UnrolledList* list = unrolled_list_create();

	for (int i = 0; i < 6; i++) {
		unrolled_list_add(list, i + 1);
	}

	bool result = unrolled_list_remove_at(list, 1);
	MU_ASSERT("Remove should succeed", result);
	MU_ASSERT("Size should be 5", unrolled_list_size(list) == 5);
	MU_ASSERT("Element 1 should be 1", unrolled_list_find_index(list, 1) == 0);
	MU_ASSERT("Element 2 should not exist", unrolled_list_find_index(list, 2) == -1);
	MU_ASSERT("Element 3 should be at index 1", unrolled_list_find_index(list, 3) == 1);

	result = unrolled_list_remove_at(list, 4);
	MU_ASSERT("Remove last should succeed", result);
	MU_ASSERT("Size should be 4", unrolled_list_size(list) == 4);
	MU_ASSERT("Element 6 should not exist", unrolled_list_find_index(list, 6) == -1);

	result = unrolled_list_remove_at(list, 10);
	MU_ASSERT("Remove invalid should fail", !result);

	unrolled_list_destroy(list);
	return 0;
}

static char* test_remove_from_empty_no8() {
	UnrolledList* list = unrolled_list_create();

	bool result = unrolled_list_remove_at(list, 0);
	MU_ASSERT("Remove from empty should fail", !result);

	unrolled_list_destroy(list);
	return 0;
}

static char* test_get_next_no9() {
	UnrolledList* list = unrolled_list_create();

	for (int i = 0; i < 5; i++) {
		unrolled_list_add(list, i * 2);
	}

	int next_value;
	bool result;

	result = unrolled_list_get_next(list, 2, &next_value);
	MU_ASSERT("Get next for 2 should succeed", result);
	MU_ASSERT("Next after 2 should be 4", next_value == 4);

	result = unrolled_list_get_next(list, 4, &next_value);
	MU_ASSERT("Get next for 4 should succeed", result);
	MU_ASSERT("Next after 4 should be 6", next_value == 6);

	result = unrolled_list_get_next(list, 8, &next_value);
	MU_ASSERT("Get next for last element should fail", !result);

	result = unrolled_list_get_next(list, 99, &next_value);
	MU_ASSERT("Get next for non-existent should fail", !result);

	unrolled_list_destroy(list);
	return 0;
}

static char* test_remove_makes_block_empty_no10() {
	UnrolledList* list = unrolled_list_create();

	for (int i = 0; i < BLOCK_CAPACITY + 1; i++) {
		unrolled_list_add(list, i);
	}

	MU_ASSERT("Should have 2 nodes", list->head != list->tail);

	bool result = unrolled_list_remove_at(list, BLOCK_CAPACITY);
	MU_ASSERT("Remove should succeed", result);
	MU_ASSERT("Should have 1 node now", list->head == list->tail);
	MU_ASSERT("Size should be BLOCK_CAPACITY",
		unrolled_list_size(list) == BLOCK_CAPACITY);

	unrolled_list_destroy(list);
	return 0;
}

static char* test_comprehensive_no11() {
	UnrolledList* list = unrolled_list_create();

	for (int i = 0; i < 10; i++) {
		unrolled_list_add(list, i * 2);
	}

	MU_ASSERT("Size should be 10", unrolled_list_size(list) == 10);

	int value;
	unrolled_list_get_at(list, 7, &value);
	MU_ASSERT("Element at index 7 should be 14", value == 14);

	unrolled_list_remove_at(list, 3);
	unrolled_list_remove_at(list, 4);

	MU_ASSERT("Size after removal should be 8", unrolled_list_size(list) == 8);

	MU_ASSERT("Find 12 should work", unrolled_list_find_index(list, 12) != -1);
	MU_ASSERT("Find 6 should not exist (removed)",
		unrolled_list_find_index(list, 6) == -1);

	int next_value;
	bool has_next = unrolled_list_get_next(list, 8, &next_value);
	MU_ASSERT("Should have next after 8", has_next);

	unrolled_list_destroy(list);
	return 0;
}

char* all_tests() {
	MU_RUN_TEST(test_create_destroy_no1);
	MU_RUN_TEST(test_add_to_empty_list_no2);
	MU_RUN_TEST(test_add_multiple_in_one_block_no3);
	MU_RUN_TEST(test_create_second_block_no4);
	MU_RUN_TEST(test_find_index_no5);
	MU_RUN_TEST(test_get_at_no6);
	MU_RUN_TEST(test_remove_at_no7);
	MU_RUN_TEST(test_remove_from_empty_no8);
	MU_RUN_TEST(test_get_next_no9);
	MU_RUN_TEST(test_remove_makes_block_empty_no10);
	MU_RUN_TEST(test_comprehensive_no11);
	return 0;
}