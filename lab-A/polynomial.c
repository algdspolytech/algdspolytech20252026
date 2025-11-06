#define _CRT_SECURE_NO_WARNINGS  
#include "polynomial.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Создание нового монома
Term* create_term(int coeff, int pow) {
    Term* t = (Term*)malloc(sizeof(Term));
    if (!t) return NULL;
    t->coeff = coeff;
    t->pow = pow;
    t->next = NULL;
    return t;
}

// Добавление монома в полином
Term* add_term(Term* poly, int coeff, int pow) {
    if (coeff == 0) return poly;

    Term* prev = NULL;
    Term* curr = poly;

    while (curr && curr->pow > pow) {
        prev = curr;
        curr = curr->next;
    }

    if (curr && curr->pow == pow) {
        curr->coeff += coeff;
        if (curr->coeff == 0) {
            if (prev) prev->next = curr->next;
            else poly = curr->next;
            free(curr);
        }
        return poly;
    }

    Term* t = create_term(coeff, pow);
    if (!t) return poly;

    t->next = curr;
    if (prev) prev->next = t;
    else poly = t;

    return poly;
}

// Освобождение памяти полинома
void free_polynomial(Term* poly) {
    while (poly) {
        Term* tmp = poly;
        poly = poly->next;
        free(tmp);
    }
}

// Сумма двух полиномов
Term* sum_polynomials(Term* p1, Term* p2) {
    Term* result = NULL;
    Term* t = p1;
    while (t) {
        result = add_term(result, t->coeff, t->pow);
        t = t->next;
    }
    t = p2;
    while (t) {
        result = add_term(result, t->coeff, t->pow);
        t = t->next;
    }
    return result;
}

// Произведение двух полиномов
Term* multiply_polynomials(Term* p1, Term* p2) {
    Term* result = NULL;
    for (Term* t1 = p1; t1; t1 = t1->next) {
        for (Term* t2 = p2; t2; t2 = t2->next) {
            result = add_term(result, t1->coeff * t2->coeff, t1->pow + t2->pow);
        }
    }
    return result;
}

// Производная полинома
Term* derivative_polynomial(Term* poly) {
    Term* result = NULL;
    while (poly) {
        if (poly->pow != 0) {
            result = add_term(result, poly->coeff * poly->pow, poly->pow - 1);
        }
        poly = poly->next;
    }
    return result;
}

// Парсинг строки полинома
Term* parse_polynomial(const char* str) {
    Term* poly = NULL;
    const char* p = str;

    while (*p) {
        int coeff = 1, pow = 0;
        int read = 0;

        // Ïðîïóñêàåì ïðîáåëû
        while (*p == ' ') p++;

        // ×èòàåì êîýôôèöèåíò
        if (sscanf_s(p, "%d%n", &coeff, &read) == 1) {
            p += read;
        }

        // ×èòàåì x^pow
        if (*p == 'x') {
            p++;
            pow = 1;
            if (*p == '^') {
                p++;
                if (sscanf_s(p, "%d%n", &pow, &read) == 1) {
                    p += read;
                }
            }
        }

        poly = add_term(poly, coeff, pow);

        // Ïðîïóñê + èëè -
        while (*p == ' ' || *p == '+' || *p == '-') p++;
    }

    return poly;
}

// Преобразование полинома в строку
void polynomial_to_string(Term* poly, char* buffer, int size) {
    if (!poly) {
        strncpy_s(buffer, size, "0", _TRUNCATE);
        return;
    }

    buffer[0] = '\0';
    char temp[50];

    while (poly) {
        if (poly->coeff > 0 && buffer[0] != '\0') {
            strncat_s(buffer, size, "+", _TRUNCATE);
        }

        if (poly->pow == 0) {
            sprintf_s(temp, sizeof(temp), "%d", poly->coeff);
        }
        else if (poly->pow == 1) {
            if (poly->coeff == 1) sprintf_s(temp, sizeof(temp), "x");
            else sprintf_s(temp, sizeof(temp), "%dx", poly->coeff);
        }
        else {
            if (poly->coeff == 1) sprintf_s(temp, sizeof(temp), "x^%d", poly->pow);
            else sprintf_s(temp, sizeof(temp), "%dx^%d", poly->coeff, poly->pow);
        }

        strncat_s(buffer, size, temp, _TRUNCATE);
        poly = poly->next;
    }
}

// Сортировка полинома по степеням (от x^0 к старшей)
Term* sort_polynomial(Term* poly) {
    if (!poly || !poly->next) return poly;

    Term* sorted = NULL;
    while (poly) {
        Term* next = poly->next;
        poly->next = NULL;
        sorted = add_term(sorted, poly->coeff, poly->pow);
        free(poly);
        poly = next;
    }
    return sorted;
}
