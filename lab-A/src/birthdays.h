#pragma once
#ifndef BIRTHDAYS_H
#define BIRTHDAYS_H

typedef struct {
    char last_name[50];
    char first_name[50];
    char patronymic[50];
    int day;
    int month;
    int year;
} Person;

typedef struct Node {
    Person data;
    struct Node* next;
} Node;

// основные функции
Node* create_node(Person p);
void insert_sorted(Node** head, Person p);
void print_list(Node* head);
void find_by_date(Node* head, int day, int month);
void free_list(Node* head);
// объявление функции сравнения дат
int compare_dates(Person p1, Person p2);
#endif