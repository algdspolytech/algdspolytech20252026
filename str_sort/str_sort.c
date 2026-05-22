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

node_t *make_node(char *str) {
  node_t *ans = (node_t *)malloc(sizeof(node_t));
  ans->str = str;
  ans->next = nullptr;
  return ans;
}

linked_str_t *make_list() {
  linked_str_t *ans = (linked_str_t *)malloc(sizeof(linked_str_t));
  ans->first = nullptr;
  return ans;
}

void free_list(linked_str_t *list) {
  node_t *node = list->first, *next;
  while (node) {
    next = node->next;
    // printf("free: %s\n", node->str);
    free(node);
    node = next;
  }
  free(list);
}

void print_list(linked_str_t *list) {
  node_t *current = list->first;
  char *cur_str;
  int counter = 1;
  printf("-------------------------------\n");
  while (current) {
    cur_str = current->str;
    printf("%i: \"", counter++);
    int c = 0;
    while (cur_str[c] != '\0') {
      printf("%c", cur_str[c++]);
    }
    printf("\"\n");
    current = current->next;
  };
  printf("-------------------------------\n");
}

linked_str_t *arr_to_list(char *arr[], int n) {
  if (n > 0) {
    linked_str_t *ans = make_list();
    node_t *cur = make_node(arr[0]), *next;
    ans->first = cur;
    for (int i = 1; i < n; i++) {
      next = make_node(arr[i]);
      cur->next = next;
      cur = next;
    }
    return ans;
  }
  return nullptr;
}

void push_to_start(linked_str_t *list, node_t *node) {
  node->next = list->first;
  list->first = node;
}

void push_to_end(linked_str_t *list, node_t *node) {
  node_t *cur = list->first;
  if (!cur) {
    list->first = node;
    return;
  }
  while (cur->next != nullptr) {
    cur = cur->next;
  }
  cur->next = node;
}

node_t *get_node(linked_str_t *list, int n) {
  node_t *cur = list->first;
  int i = 0;
  while (i < n && cur->next != nullptr) {
    cur = cur->next;
    i++;
  }
  return cur;
}

node_t *delete_node(linked_str_t *list, int n) {
  node_t *del;
  if (n == 0) {
    del = list->first;
    list->first = del->next;
    del->next = nullptr;
  } else {
    node_t *cur = get_node(list, n - 1);

    if (cur->next == nullptr) {
      return cur->next;
    }
    del = cur->next;
    cur->next = del->next;
    return del;
  }
}

void switch_nodes(linked_str_t *list, int i, int j) {
  if (i == j) {
    return;
  }
  node_t *n1, *n2, *cur;
  if (i == 0 || j == 0) {
    j = i + j;
    i = 0;
    n1 = delete_node(list, 0);
    n2 = delete_node(list, j - 1);
    push_to_start(list, n2);
    cur = get_node(list, j - 1);
    n1->next = cur->next;
    cur->next = n1;
  } else {
    if (i > j) {
      i = i + j;
      j = i - j;
      i = i - j;
    }
    n1 = delete_node(list, i);
    cur = get_node(list, j - 2);
    n1->next = cur->next;
    cur->next = n1;
    n2 = delete_node(list, j);
    cur = get_node(list, i - 1);
    n2->next = cur->next;
    cur->next = n2;
  }
}

int partition_list(linked_str_t *list, int p, int r) {
  node_t *x = get_node(list, r), *cur;
  int i = p;
  for (int j = p; j < r + 1; j++) {
    cur = get_node(list, j);
    if (!str_compare(cur->str, x->str)) {
      switch_nodes(list, i, j);
      i++;
    }
  }
  switch_nodes(list, i, r);
  return i;
}

void quicksort_list(linked_str_t *list, int p, int r) {
  if (p < r) {
    int q = partition_list(list, p, r);
    quicksort_list(list, p, q - 1);
    quicksort_list(list, q, r);
  }
}

int list_length(linked_str_t *list) {
  int i = 0;
  node_t *node = list->first;
  while (node) {
    node = node->next;
    i++;
  }
  return i;
}
