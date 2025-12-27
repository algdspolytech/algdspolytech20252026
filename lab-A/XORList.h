#pragma once
#ifndef XOR_LIST_H
#define XOR_LIST_H

#include <stdint.h>

typedef struct elm {
  char *s;
  struct elm *p;
} elm;

// Объявления функций
int len(const char *str);
char *copy(const char *str, int ln);
elm *XOR(elm *a, elm *b);
elm *CreateEl(const char *c);
void Add(elm **head, elm **tail, elm *el);
void Print(elm *head, elm *tail);
void del(elm **head, elm **tail, elm *q);
int sr(const char *a, const char *b);
elm *Find(elm *head, elm *tail, const char *a);
void RemoveByKey(elm **head, elm **tail, const char *key);
void FreeList(elm **head, elm **tail);

#endif
