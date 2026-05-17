#include "str_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_length(char *a) {
  int counter = 0;
  while (*(a++) != '\0') {
    counter++;
  }
  return counter;
}

int str_compare(char *ptr_a, char *ptr_b) {
  int la = string_length(ptr_a), lb = string_length(ptr_b);

  if (la > lb) {
    return 1;
  }
  if (lb > la) {
    return 0;
  }

  while (*ptr_a != '\0') {
    if (*(ptr_a) != *(ptr_b)) {
      break;
    }
    ptr_a++;
    ptr_b++;
  }
  if (*ptr_a > *ptr_b) {
    return 1;
  } else if (*ptr_b == '\0') {
    return -1;
  } else
    return 0;
}

void print_strings(char **arr, int num) {

  char *current = *arr;
  int counter = 1;
  printf("-------------------------------\n");
  for (int i = 0; i < num; i++) {
    current = *arr;
    printf("%i: \"", counter++);
    int c = 0;
    while (current[c] != '\0') {
      printf("%c", current[c++]);
    }
    printf("\"\n");
    arr++;
  };
  printf("-------------------------------\n");
}

void switch_str(char **strings, int i, int j) {
  char *t = strings[i];
  strings[i] = strings[j];
  strings[j] = t;
}

int partition_str(char **strings, int p, int r) {
  char *x = *(strings + r);
  int i = p;
  for (int j = p; j < r + 1; j++) {
    if (!str_compare(strings[j], x)) {
      switch_str(strings, i, j);
      i++;
    }
  }
  switch_str(strings, i, r);
  return i;
}

void quicksort_str(char **strings, int p, int r) {
  if (p < r) {
    int q = partition_str(strings, p, r);
    quicksort_str(strings, p, q - 1);
    quicksort_str(strings, q, r);
  }
}
