// phonebook.c
/**
 * @file phonebook.c
 * @brief Реализация функций для работы с записной книгой
 *
 * @version 1.0
 * @date 2025.12.20
 * @author Д.Смирнов
 */

#pragma warning(disable:4996)

#include "phonebook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /**
  * @brief Создание копии строки в динамической памяти
  *
  * @param[in] s - исходная строка для копирования
  *
  * @return указатель на новую строку или NULL при ошибке
  */
char* StrDup(const char* s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s);
    char* p = (char*)malloc(len + 1);
    if (!p) return NULL;
    memcpy(p, s, len + 1);
    return p;
}


/**
 * @brief Создание нового узла списка
 *
 * @param[in] ln - фамилия
 * @param[in] fn - имя
 * @param[in] pn - отчество
 *
 * @return указатель на созданный узел или NULL при ошибке
 */
Node* CreateNode(const char* ln, const char* fn, const char* pn) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return NULL;

    n->lastName = StrDup(ln);
    n->firstName = StrDup(fn);
    n->patronymic = StrDup(pn);
    n->next = NULL;

    if (!n->lastName || !n->firstName || !n->patronymic) {
        free(n->lastName);
        free(n->firstName);
        free(n->patronymic);
        free(n);
        return NULL;
    }
    return n;
}


/**
 * @brief Сравнение двух записей о людях
 *
 * @param[in] a - первый узел для сравнения
 * @param[in] b - второй узел для сравнения
 *
 * @return отрицательное число если a < b, 0 если равны, положительное если a > b
 */
int PersonCompare(const Node* a, const Node* b) {
    int r = strcmp(a->lastName, b->lastName);
    if (r != 0) return r;

    r = strcmp(a->firstName, b->firstName);
    if (r != 0) return r;

    return strcmp(a->patronymic, b->patronymic);
}


/**
 * @brief Вставка узла в отсортированный односвязный список
 *
 * @param[in,out] head - указатель на начало списка
 * @param[in] node - узел для вставки
 */
void InsertSortion(Node** head, Node* node) {
    if (!node) return;

    if (*head == NULL || PersonCompare(node, *head) < 0) {
        node->next = *head;
        *head = node;
        return;
    }

    Node* cur = *head;
    while (cur->next && PersonCompare(cur->next, node) <= 0) {
        cur = cur->next;
    }
    node->next = cur->next;
    cur->next = node;
}


/**
 * @brief Проверка, начинается ли строка с указанного префикса
 *
 * @param[in] s - строка для проверки
 * @param[in] pref - префикс
 *
 * @return 1 если строка начинается с префикса, иначе 0
 */
int StartsWith(const char* s, const char* pref) {
    size_t lp = strlen(pref);
    return strncmp(s, pref, lp) == 0;
}


/**
 * @brief Проверка совпадения записи с шаблоном поиска
 *
 * @param[in] p - узел для проверки
 * @param[in] ln - шаблон фамилии ("-" для любого значения)
 * @param[in] fn - шаблон имени ("-" для любого значения)
 * @param[in] pn - шаблон отчества ("-" для любого значения)
 *
 * @return 1 если запись соответствует шаблону, иначе 0
 */
int match(const Node* p, const char* ln, const char* fn, const char* pn) {
    if (strcmp(ln, "-") != 0 && !StartsWith(p->lastName, ln)) return 0;
    if (strcmp(fn, "-") != 0 && !StartsWith(p->firstName, fn)) return 0;
    if (strcmp(pn, "-") != 0 && !StartsWith(p->patronymic, pn)) return 0;
    return 1;
}


/**
 * @brief Вывод всех фамилий из списка
 *
 * @param[in] head - указатель на начало списка
 */
void PrintNotes(const Node* head) {
    printf("Все записи в книге:\n");
    while (head) {
        printf("%s %s %s\n", head->lastName, head->firstName, head->patronymic);
        head = head->next;
    }
}


/**
 * @brief Поиск и вывод записей по шаблону
 *
 * @param[in] head - указатель на начало списка
 * @param[in] ln - шаблон фамилии
 * @param[in] fn - шаблон имени
 * @param[in] pn - шаблон отчества
 */
void SearchAndPrint(const Node* head, const char* ln, const char* fn, const char* pn) {
    if (head == NULL) return;

    int found = 0;
    printf("\nРезультаты поиска:\n");

    while (head) {
        if (match(head, ln, fn, pn)) {
            printf("%s %s %s\n", head->lastName, head->firstName, head->patronymic);
            found = 1;
        }
        head = head->next;
    }

    if (!found) {
        printf("Совпадений не найдено\n");
    }
}


/**
 * @brief Освобождение памяти, занятой списком
 *
 * @param[in] head - указатель на начало списка
 */
void FreeList(Node* head) {
    while (head) {
        Node* next = head->next;
        free(head->lastName);
        free(head->firstName);
        free(head->patronymic);
        free(head);
        head = next;
    }
}

/**
 * @brief Функция записной книги
 */
void phonebook(void) {

    const char* ptrFile = "Data.txt";

    FILE* f = fopen(ptrFile, "r");
    if (!f) {
        printf("Не удалось открыть файл %s\n", ptrFile);
        return 1;
    }

    Node* head = NULL;

    char ln[BUF], fn[BUF], pn[BUF];

    while (fscanf(f, "%255s %255s %255s", ln, fn, pn) == 3) {
        Node* node = CreateNode(ln, fn, pn);
        if (!node) {
            printf("Ошибка выделения памяти\n");
            fclose(f);
            FreeList(head);
            return 1;
        }
        InsertSortion(&head, node);
    }
    fclose(f);

    PrintNotes(head);

    char qln[BUF], qfn[BUF], qpn[BUF];
    printf("\nВведите начальные буквы фамилии, имени и отчества (или -): ");
    if (scanf("%255s %255s %255s", qln, qfn, qpn) != 3) {
        printf("Некорректный ввод\n");
        FreeList(head);
        return 1;
    }

    SearchAndPrint(head, qln, qfn, qpn);

    FreeList(head);
}