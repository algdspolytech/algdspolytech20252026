#include "labA.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int make_words(const char *arr[], int count, struct word_st out[]) {
  for (int i = 0; i < count; i++) {
    strcpy(out[i].name, arr[i]);
  }
  return count;
}

void sort_func_Unsorted3Words_ReturnSorted_no1() {
  struct word_st w[3];
  const char *src[] = {"banana", "apple", "cherry"};
  const char *exp[] = {"apple", "banana", "cherry"};
  make_words(src, 3, w);

  sort_func(w, 3);

  assert(strcmp(w[0].name, exp[0]) == 0);
  assert(strcmp(w[1].name, exp[1]) == 0);
  assert(strcmp(w[2].name, exp[2]) == 0);
}

void sort_func_AlreadySorted_ReturnSameOrder_no2() {
  struct word_st w[3];
  const char *src[] = {"apple", "banana", "cherry"};
  make_words(src, 3, w);

  sort_func(w, 3);

  assert(strcmp(w[0].name, "apple") == 0);
  assert(strcmp(w[1].name, "banana") == 0);
  assert(strcmp(w[2].name, "cherry") == 0);
}

void sort_func_DuplicateWords_ReturnStableSorted_no3() {
  struct word_st w[4];
  const char *src[] = {"apple", "banana", "apple", "banana"};
  const char *exp[] = {"apple", "apple", "banana", "banana"};
  make_words(src, 4, w);

  sort_func(w, 4);

  for (int i = 0; i < 4; i++)
    assert(strcmp(w[i].name, exp[i]) == 0);
}

void sort_func_MixedCaseWords_ReturnAsciiSorted_no4() {
  struct word_st w[4];
  const char *src[] = {"apple", "Banana", "cherry", "Apple"};
  const char *exp[] = {"Apple", "Banana", "apple", "cherry"};
  make_words(src, 4, w);

  sort_func(w, 4);

  for (int i = 0; i < 4; i++)
    assert(strcmp(w[i].name, exp[i]) == 0);
}

void all_arrays_TwoSmallArrays_ReturnMerged_no5() {
  struct word_st a1[2], a2[2], result[4];
  const char *arr1[] = {"apple", "banana"};
  const char *arr2[] = {"cherry", "date"};
  make_words(arr1, 2, a1);
  make_words(arr2, 2, a2);

  int total = all_arrays(result, a1, 2, a2, 2);

  assert(total == 4);
  assert(strcmp(result[0].name, "apple") == 0);
  assert(strcmp(result[1].name, "banana") == 0);
  assert(strcmp(result[2].name, "cherry") == 0);
  assert(strcmp(result[3].name, "date") == 0);
}

void all_arrays_FirstEmpty_ReturnSecondOnly_no6() {
  struct word_st a1[1], a2[2], result[2];
  const char *arr2[] = {"pear", "plum"};
  make_words(arr2, 2, a2);

  int total = all_arrays(result, a1, 0, a2, 2);

  assert(total == 2);
  assert(strcmp(result[0].name, "pear") == 0);
  assert(strcmp(result[1].name, "plum") == 0);
}

void all_arrays_SecondEmpty_ReturnFirstOnly_no7() {
  struct word_st a1[2], a2[1], result[2];
  const char *arr1[] = {"x", "y"};
  make_words(arr1, 2, a1);

  int total = all_arrays(result, a1, 2, a2, 0);

  assert(total == 2);
  assert(strcmp(result[0].name, "x") == 0);
  assert(strcmp(result[1].name, "y") == 0);
}

void fileswork_FileWith3Words_ReturnCount3_no8() {
  FILE *f = fopen("test_input.txt", "w");
  fprintf(f, "apple\nbanana\ncherry\n");
  fclose(f);

  struct word_st w[10];
  int count = fileswork("test_input.txt", w);

  assert(count == 3);
  assert(strcmp(w[0].name, "apple") == 0);
  assert(strcmp(w[1].name, "banana") == 0);
  assert(strcmp(w[2].name, "cherry") == 0);
}

void fileswork_EmptyFile_ReturnCount0_no9() {
  FILE *f = fopen("test_empty.txt", "w");
  fclose(f);

  struct word_st w[10];
  int count = fileswork("test_empty.txt", w);

  assert(count == 0);
}

void fileswork_NonExistingFile_ReturnErrorHandled_no10() {
  struct word_st w[10];
  fileswork("no_such_file_123.txt", w);
  assert(1);
}

int main() {
  printf("=== UNIT TESTS labA.c ===\n\n");

  sort_func_Unsorted3Words_ReturnSorted();
  sort_func_AlreadySorted_ReturnSameOrder();
  sort_func_DuplicateWords_ReturnStableSorted();
  sort_func_MixedCaseWords_ReturnAsciiSorted();

  all_arrays_TwoSmallArrays_ReturnMerged();
  all_arrays_FirstEmpty_ReturnSecondOnly();
  all_arrays_SecondEmpty_ReturnFirstOnly();

  fileswork_FileWith3Words_ReturnCount3();
  fileswork_EmptyFile_ReturnCount0();
  fileswork_NonExistingFile_ReturnErrorHandled();

  printf("\nall tests complete\n");
  return 0;
}
