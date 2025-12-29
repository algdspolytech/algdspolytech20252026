#include "labA.h"
#include <assert.h>

void test_insert_empty_no1() {
  WordInfo words[MAX_WORDS];
  int count = 0;

  insert_sorted(words, &count, "test");

  assert(count == 1);
  assert(strcmp(words[0].word, "test") == 0);
  assert(words[0].length == 4);
  printf("Test 1 PASSED: Insert into empty array\n");
}

void test_sort_by_length_no2() {
  WordInfo words[MAX_WORDS];
  int count = 0;

  insert_sorted(words, &count, "elephant");
  insert_sorted(words, &count, "cat");
  insert_sorted(words, &count, "bird");

  assert(count == 3);
  assert(strcmp(words[0].word, "cat") == 0);
  assert(strcmp(words[1].word, "bird") == 0);
  assert(strcmp(words[2].word, "elephant") == 0);
  printf("Test 2 PASSED: Sort by word length\n");
}

void test_alphabetical_order_no3() {
  WordInfo words[MAX_WORDS];
  int count = 0;

  insert_sorted(words, &count, "dog");
  insert_sorted(words, &count, "cat");
  insert_sorted(words, &count, "ant");

  assert(count == 3);
  assert(strcmp(words[0].word, "ant") == 0);
  assert(strcmp(words[1].word, "cat") == 0);
  assert(strcmp(words[2].word, "dog") == 0);
  printf("Test 3 PASSED: Alphabetical order for same length\n");
}

void test_compare_function_no4() {
  WordInfo w1 = {"cat", 3};
  WordInfo w2 = {"dog", 3};
  WordInfo w3 = {"elephant", 8};
  WordInfo w4 = {"ant", 3};

  assert(compare_words(&w1, &w2) < 0);
  assert(compare_words(&w2, &w1) > 0);
  assert(compare_words(&w1, &w3) < 0);
  assert(compare_words(&w4, &w1) < 0);
  printf("Test 4 PASSED: Compare words function\n");
}

void test_mixed_sorting_no5() {
  WordInfo words[MAX_WORDS];
  int count = 0;

  insert_sorted(words, &count, "zoo");
  insert_sorted(words, &count, "apple");
  insert_sorted(words, &count, "banana");
  insert_sorted(words, &count, "cat");

  assert(count == 4);
  assert(strcmp(words[0].word, "cat") == 0);
  assert(strcmp(words[1].word, "zoo") == 0);
  assert(strcmp(words[2].word, "apple") == 0);
  assert(strcmp(words[3].word, "banana") == 0);
  printf("Test 5 PASSED: Mixed length sorting\n");
}

void test_max_length_word_no6() {
  WordInfo words[MAX_WORDS];
  int count = 0;

  char long_word[MAX_WORD_LENGTH];
  memset(long_word, 'a', MAX_WORD_LENGTH - 1);
  long_word[MAX_WORD_LENGTH - 1] = '\0';

  insert_sorted(words, &count, long_word);

  assert(count == 1);
  assert(strlen(words[0].word) == MAX_WORD_LENGTH - 1);
  assert(words[0].length == MAX_WORD_LENGTH - 1);
  printf("Test 6 PASSED: Max length word\n");
}

void test_multiple_insertions_no7() {
  WordInfo words[MAX_WORDS];
  int count = 0;

  insert_sorted(words, &count, "cat");
  insert_sorted(words, &count, "ant");
  insert_sorted(words, &count, "dog");
  insert_sorted(words, &count, "bat");

  assert(count == 4);
  assert(strcmp(words[0].word, "ant") == 0);
  assert(strcmp(words[1].word, "bat") == 0);
  assert(strcmp(words[2].word, "cat") == 0);
  assert(strcmp(words[3].word, "dog") == 0);
  printf("Test 7 PASSED: Multiple insertions\n");
}

void test_duplicate_words_no8() {
  WordInfo words[MAX_WORDS];
  int count = 0;

  insert_sorted(words, &count, "test");
  insert_sorted(words, &count, "test");
  insert_sorted(words, &count, "test");

  assert(count == 3);
  assert(strcmp(words[0].word, "test") == 0);
  assert(strcmp(words[1].word, "test") == 0);
  assert(strcmp(words[2].word, "test") == 0);
  printf("Test 8 PASSED: Duplicate words\n");
}

void test_boundary_lengths_no9() {
  WordInfo words[MAX_WORDS];
  int count = 0;

  insert_sorted(words, &count, "a");
  insert_sorted(words, &count, "ab");
  insert_sorted(words, &count, "abc");
  insert_sorted(words, &count, "abcd");

  assert(count == 4);
  assert(strcmp(words[0].word, "a") == 0);
  assert(strcmp(words[1].word, "ab") == 0);
  assert(strcmp(words[2].word, "abc") == 0);
  assert(strcmp(words[3].word, "abcd") == 0);
  printf("Test 9 PASSED: Boundary lengths\n");
}

void test_complex_sorting_no10() {
  WordInfo words[MAX_WORDS];
  int count = 0;

  insert_sorted(words, &count, "programming");
  insert_sorted(words, &count, "code");
  insert_sorted(words, &count, "test");
  insert_sorted(words, &count, "algorithm");
  insert_sorted(words, &count, "data");
  insert_sorted(words, &count, "function");

  assert(count == 6);
  assert(strcmp(words[0].word, "code") == 0);
  assert(strcmp(words[1].word, "data") == 0);
  assert(strcmp(words[2].word, "test") == 0);
  assert(strcmp(words[3].word, "function") == 0);
  assert(strcmp(words[4].word, "algorithm") == 0);
  assert(strcmp(words[5].word, "programming") == 0);
  printf("Test 10 PASSED: Complex mixed sorting\n");
}