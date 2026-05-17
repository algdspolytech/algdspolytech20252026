
#ifndef STR_SORT_H
#define STR_SORT_H

// Сравнение строк а и b (возвращает 1 : (a>b), 0: (a<b), -1: (a==b))
int str_compare(char *a, char *b);

// Выводит в консоль массив строк
void print_strings(char **, int);

// Возвращает длину строки a(в символах без '\0')
int string_length(char *a);

// Меняет местами строки под номером i и j
void switch_str(char **s, int i, int j);

// Рабзбиение массива(опорный элемент - последний)
int partition_str(char **strings, int p, int r);

// Алгоритм быстрой сортировки
void quicksort_str(char **strings, int p, int r);

#endif