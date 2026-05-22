
// Реализован алгоритм быстрой сортировки для односвязного списка из asciiz
// строк Алгоритмическая сложность -

#ifndef STR_SORT_H
#define STR_SORT_H

// Структура - элемент списка
typedef struct node_t {
  char *str;
  struct node_t *next;
} node_t;

// Структура - односвязный список
typedef struct linked_str_t {
  node_t *first;
} linked_str_t;

// Возвращает длину строки a(в символах без '\0')
int string_length(char *a);

// Сравнение строк а и b (возвращает 1 : (a>b), 0: (a<b), -1: (a==b))
// Строка a превосходит строку b, если:
// a длинее b, затем если строки равны по длине, если существует i: a[i]>b[i]
int str_compare(char *a, char *b);

// Создание элемента из строки
node_t *make_node(char *str);

// Создание пустого списка
linked_str_t *make_list();

// Очистка памяти, выделенной под список
void free_list(linked_str_t *);

// Вывод списка в консоль
void print_list(linked_str_t *);

// Преобразование массива строк из n элементов в односвязный список
linked_str_t *arr_to_list(char *arr[], int n);

// Добавление элемента в начало списка
void push_to_start(linked_str_t *list, node_t *node);

// Добавление элемента в конец списка
void push_to_end(linked_str_t *list, node_t *node);

// Получение элемента по номеру в списке
node_t *get_node(linked_str_t *list, int n);

// Удаление элемента
node_t *delete_node(linked_str_t *list, int n);

// Обмен элементов местами
void switch_nodes(linked_str_t *, int, int);

// Процедура partition для алгоритма быстрой сортировки (опорный элемент -
// последний)
int partition_list(linked_str_t *list, int p, int r);

// Алгоритм быстрой сортировки
void quicksort_list(linked_str_t *list, int p, int r);

int list_length(linked_str_t *list);

#endif