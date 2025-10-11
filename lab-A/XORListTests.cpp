#include "XORList.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// для проверки утечки памяти
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#pragma warning(disable : 4996)

// Добавляем gtest только если компилируем тесты
#ifdef TESTING
#include <gtest/gtest.h>
#endif

int len(const char *str) {
  int length = 0;
  while (*str != '\0') {
    length++;
    str++;
  }
  return length;
}

char *copy(const char *str, int ln) {
  char *newStr = (char *)malloc(ln + 1);
  for (int i = 0; i <= ln; i++) {
    newStr[i] = str[i];
  }
  return (newStr);
}

elm *XOR(elm *a, elm *b) { return (elm *)((uintptr_t)a ^ (uintptr_t)b); }

elm *CreateEl(const char *c) {
  elm *a = (elm *)malloc(sizeof(elm));
  a->s = copy(c, len(c));
  a->p = NULL;
  return (a);
}

void Add(elm **head, elm **tail, elm *el) {
  if (*head == NULL) {
    *head = el;
    *tail = el;
    el->p = XOR(NULL, NULL);
  } else {
    el->p = XOR(*tail, NULL);
    elm *prev = XOR((*tail)->p, NULL);
    (*tail)->p = XOR(prev, el);
    *tail = el;
  }
}

void Print(elm *head, elm *tail) {
  if (head == NULL) {
    printf("Список пуст\n");
    return;
  }

  elm *n = head;
  elm *l = NULL;
  elm *nex;

  while (n != NULL) {
    printf("%s\n", n->s);
    nex = XOR(l, n->p);
    l = n;
    n = nex;
    if (n == NULL)
      break;
  }
}

void del(elm **head, elm **tail, elm *q) {
  if (q == NULL)
    return;

  elm *n = *head;
  elm *l = NULL;
  elm *nex = NULL;

  while (n != NULL && n != q) {
    nex = XOR(l, n->p);
    l = n;
    n = nex;
  }

  if (n == NULL)
    return;

  nex = XOR(l, n->p);

  if (l != NULL) {
    elm *lp = XOR(n, l->p);
    l->p = XOR(lp, nex);
  } else {
    *head = nex;
  }

  if (nex != NULL) {
    elm *nn = XOR(n, nex->p);
    nex->p = XOR(l, nn);
  } else {
    *tail = l;
  }

  free(n->s);
  free(n);
}

int sr(const char *a, const char *b) {
  if (a == NULL || b == NULL)
    return 0;

  int la = len(a), lb = len(b);
  if (la != lb)
    return 0;

  for (int i = 0; i < la; i++) {
    if (a[i] != b[i])
      return 0;
  }
  return 1;
}

elm *Find(elm *head, elm *tail, const char *a) {
  if (head == NULL)
    return NULL;

  elm *n = head;
  elm *l = NULL;
  elm *nex;

  while (n != NULL) {
    if (sr(n->s, a)) {
      return n;
    }
    nex = XOR(l, n->p);
    l = n;
    n = nex;
  }
  return NULL;
}

void RemoveByKey(elm **head, elm **tail, const char *key) {
  elm *found = Find(*head, *tail, key);
  if (found != NULL) {
    del(head, tail, found);
  }
}

void FreeList(elm **head, elm **tail) {
  if (*head == NULL)
    return;

  elm *current = *head;
  elm *prev = NULL;
  elm *next;

  while (current != NULL) {
    next = XOR(prev, current->p);
    free(current->s);
    free(current);
    prev = current;
    current = next;
  }

  *head = NULL;
  *tail = NULL;
}

// ТЕСТЫ
#ifdef TESTING

// Тест 1 (добавление одного элемента)
TEST(XORListTest, AddSingleElement) {
  elm *head = NULL;
  elm *tail = NULL;

  Add(&head, &tail, CreateEl("first"));

  EXPECT_TRUE(head != NULL);
  EXPECT_TRUE(tail != NULL);
  EXPECT_TRUE(head == tail); // Для одного элемента голова и хвост совпадают
  EXPECT_EQ(sr(head->s, "first"), 1);

  FreeList(&head, &tail);
}

// Тест 2 (добавление нескольких элементов)
TEST(XORListTest, AddMultipleElements) {
  elm *head = NULL;
  elm *tail = NULL;

  Add(&head, &tail, CreateEl("first"));
  Add(&head, &tail, CreateEl("second"));
  Add(&head, &tail, CreateEl("third"));

  EXPECT_TRUE(head != NULL);
  EXPECT_TRUE(tail != NULL);
  EXPECT_TRUE(head != tail); // Для нескольких элементов голова и хвост разные
  EXPECT_EQ(sr(head->s, "first"), 1);
  EXPECT_EQ(sr(tail->s, "third"), 1);

  FreeList(&head, &tail);
}

// Тест 3 (поиск существующего элемента)
TEST(XORListTest, FindExistingElement) {
  elm *head = NULL;
  elm *tail = NULL;

  Add(&head, &tail, CreateEl("first"));
  Add(&head, &tail, CreateEl("second"));
  Add(&head, &tail, CreateEl("third"));

  elm *found = Find(head, tail, "third");
  EXPECT_TRUE(found != NULL);
  EXPECT_EQ(sr(found->s, "third"), 1);

  FreeList(&head, &tail);
}

// Тест 4 (поиск несуществующего элемента)
TEST(XORListTest, FindNonExistingElement) {
  elm *head = NULL;
  elm *tail = NULL;

  Add(&head, &tail, CreateEl("first"));
  Add(&head, &tail, CreateEl("second"));

  elm *found = Find(head, tail, "third");
  EXPECT_TRUE(found == NULL);

  FreeList(&head, &tail);
}

// Тест 5 (удаление по ключу существующего элемента)
TEST(XORListTest, RemoveByKeyExisting) {
  elm *head = NULL;
  elm *tail = NULL;

  Add(&head, &tail, CreateEl("first"));
  Add(&head, &tail, CreateEl("second"));
  Add(&head, &tail, CreateEl("three"));

  RemoveByKey(&head, &tail, "second");

  EXPECT_TRUE(Find(head, tail, "second") == NULL);
  EXPECT_TRUE(Find(head, tail, "first") != NULL);
  EXPECT_TRUE(Find(head, tail, "three") != NULL);

  FreeList(&head, &tail);
}

// Тест 6 (удаление по ключу несуществующего элемента)
TEST(XORListTest, RemoveByKeyNonExisting) {
  elm *head = NULL;
  elm *tail = NULL;

  Add(&head, &tail, CreateEl("first"));
  Add(&head, &tail, CreateEl("second"));

  RemoveByKey(&head, &tail, "third");

  EXPECT_TRUE(Find(head, tail, "first") != NULL);
  EXPECT_TRUE(Find(head, tail, "second") != NULL);

  FreeList(&head, &tail);
}

// Тест 7 (удаление головы списка)
TEST(XORListTest, DeleteHeadByAddress) {
  elm *head = NULL;
  elm *tail = NULL;

  elm *first = CreateEl("first");
  elm *second = CreateEl("second");
  elm *third = CreateEl("third");

  Add(&head, &tail, first);
  Add(&head, &tail, second);
  Add(&head, &tail, third);

  del(&head, &tail, first);

  EXPECT_EQ(sr(head->s, "second"), 1);
  EXPECT_EQ(sr(tail->s, "third"), 1);
  EXPECT_TRUE(Find(head, tail, "first") == NULL);

  FreeList(&head, &tail);
}

// Тест 8 (удаление хвоста списка)
TEST(XORListTest, DeleteTailByAddress) {
  elm *head = NULL;
  elm *tail = NULL;

  elm *first = CreateEl("first");
  elm *second = CreateEl("second");
  elm *third = CreateEl("third");

  Add(&head, &tail, first);
  Add(&head, &tail, second);
  Add(&head, &tail, third);

  del(&head, &tail, third);

  EXPECT_EQ(sr(head->s, "first"), 1);
  EXPECT_EQ(sr(tail->s, "second"), 1);
  EXPECT_TRUE(Find(head, tail, "third") == NULL);

  FreeList(&head, &tail);
}

// Тест 9 (удаление среднего элемента)
TEST(XORListTest, DeleteMiddleByAddress) {
  elm *head = NULL;
  elm *tail = NULL;

  elm *first = CreateEl("first");
  elm *second = CreateEl("second");
  elm *third = CreateEl("third");

  Add(&head, &tail, first);
  Add(&head, &tail, second);
  Add(&head, &tail, third);

  del(&head, &tail, second);

  EXPECT_EQ(sr(head->s, "first"), 1);
  EXPECT_EQ(sr(tail->s, "third"), 1);
  EXPECT_TRUE(Find(head, tail, "second") == NULL);

  FreeList(&head, &tail);
}

// Тест 10 (работа с пустым списком)
TEST(XORListTest, EmptyListOperations) {
  elm *head = NULL;
  elm *tail = NULL;

  EXPECT_TRUE(Find(head, tail, "first") == NULL);

  RemoveByKey(&head, &tail, "second");

  EXPECT_TRUE(head == NULL);
  EXPECT_TRUE(tail == NULL);

  FreeList(&head, &tail);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#else
int main() {
  setlocale(LC_CTYPE, "Russian");

  elm *head = NULL; // первый элемент
  elm *tail = NULL; // последний элементB

  char *big = (char *)malloc(256);
  char c;
  long n = 0, t = 255;
  printf("Введите строки (для выхода введите пустую строку): ");

  int exFlag = 0, col = 0;
  do {
    (c = getchar());
    if (n >= t) {
      big = (char *)realloc(big, t + 256);
      t += 256;
    }

    if (c == '\n') {
      if (n == 0) {
        exFlag = 1;
      } else {
        big[n] = '\0';
        Add(&head, &tail, CreateEl(big));
        free(big);
        char *big = (char *)malloc(256);
        n = 0;
        t = 255;
        col += 1;
      }
    } else {
      big[n] = c;
      n++;
    }

  } while (!exFlag);
}

#endif