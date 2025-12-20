// phonebook.h
/**
 * @file phonebook.h
 * @brief Заголовочный файл для работы с записной книгой
 *
 * Файл с определениями функций для работы с записной книгой
 *
 * @version 1.0
 * @date 2025.12.20
 * @author Д.Смирнов
 */

#pragma once

// Константы
#define BUF 256

// Структура односвязного списка
typedef struct Node {
    char* lastName;
    char* firstName;
    char* patronymic;
    struct Node* next;
} Node; 

// Прототипы функций

char* StrDup(const char* s);
Node* CreateNode(const char* ln, const char* fn, const char* pn);
int PersonCompare(const Node* a, const Node* b);
void InsertSortion(Node** head, Node* node);
int StartsWith(const char* s, const char* pref);
int match(const Node* p, const char* ln, const char* fn, const char* pn);
void PrintNotes(const Node* head);
void SearchAndPrint(const Node* head, const char* ln, const char* fn, const char* pn);
void FreeList(Node* head);
void phonebook(void);