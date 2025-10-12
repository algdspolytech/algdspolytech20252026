#define _CRT_SECURE_NO_WARNINGS

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#define ELEM_IN_ARR 4

struct node_ {
    struct node_* next;
    int data[ELEM_IN_ARR];
    int filled_num;  
};
typedef struct node_ node;

struct UnrolledList_ {
    node* head;
};
typedef struct UnrolledList_ UnrolledList;

node* create_node() {
    node* new_node = malloc(sizeof(node));
    new_node->next = NULL;
    new_node->filled_num = 0;
    return new_node;
}

void add_to_list(UnrolledList* list, int x) {
    if (list->head == NULL) {  // если список пустой то создаем узел
        list->head = create_node();
    }

    node* last = list->head;  // ищем последний узел
    while (last->next != NULL) {
        last = last->next;
    }

    if (last->filled_num <
        ELEM_IN_ARR) {  // если место в последней ноде есть, то закидываем х
        last->data[last->filled_num] = x;
        last->filled_num++;
    }
    else {  // иначе создаем новую ноду
        node* new_node = create_node();
        new_node->data[0] = x;
        new_node->filled_num = 1;
        last->next = new_node;
    }
}

int count_elem(UnrolledList* list) {  // Подсчитать количество элементов
    if (list == NULL || list->head == NULL) {
        return 0;
    }

    int num_elem = 0;
    node* now_node = list->head;
    while (now_node != NULL) {
        num_elem += now_node->filled_num;
        now_node = now_node->next;
    }
    return num_elem;
}

int num_by_key(UnrolledList* list, int key) {  // Найти номер элемента по ключу
    node* now_node = list->head;
    int num = 0;
    while (now_node != NULL) {
        for (int i = 0; i < now_node->filled_num; i++) {
            if (now_node->data[i] == key) {
                return num;
            }
            num++;
        }
        now_node = now_node->next;
    }
    return -1;
}

int delete_by_num(UnrolledList* list, int num) {  // удаление по номеру
    int num_elem = count_elem(list);
    if (num < 0 || num + 1 > num_elem) {
        return -1;
    }

    node* now_node = list->head;
    int index = num;
    while (index >=
        now_node->filled_num) {  // пока не придем у нужной ноде отнимаем
        // количество чисел в массиве
        index -= now_node->filled_num;
        now_node = now_node->next;
    }

    for (int i = index; i < now_node->filled_num - 1; i++) {
        now_node->data[i] =
            now_node->data[i + 1];  // в конце массиива будет два повторяющихся
        // элемента, но филед уменьшаем на 1 и
        // фактически в массиве будет 3 числа
    }

    now_node->filled_num--;
}

int elem_by_num(UnrolledList* list,
    int num) {  // Найти элемент с заданным номером
    int num_elem = count_elem(list);
    if (num < 0 || num + 1 > num_elem) {
        return -1;
    }
    node* now_node = list->head;
    int index = num;
    while (index >= now_node->filled_num) {
        index -= now_node->filled_num;
        now_node = now_node->next;
    }

    return now_node->data[index];
}

int next_by_num(UnrolledList* list, int num) {  // итерирование
    int num_elem = count_elem(list);
    if (num < 0 || num + 2 > num_elem) {  //+2 потому что нужно проверить не
        //последний индекс, а предпоследний
        return -1;
    }
    return elem_by_num(list, num + 1);
}
