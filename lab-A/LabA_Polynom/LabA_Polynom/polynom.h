#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// типы данных
// коэф M < 2^15
typedef int coefficient_t;
// степень k <= 2^30
typedef unsigned int degree_t;

// моном - узел связного списка
typedef struct Monomial {
    coefficient_t coefficient;
    degree_t degree;
    struct Monomial* next;
} Monomial;

// полином - голова списка
typedef struct Polynomial {
    Monomial* head;
} Polynomial;

// управ памяти и инициализация
Monomial* create_monomial(coefficient_t coeff, degree_t deg);
Polynomial* create_polynomial();
void free_polynomial(Polynomial* poly);

// доп функции для списка
// доб монома, сложение коэф, если степень уже есть
void add_monomial_to_poly(Polynomial* poly, coefficient_t coeff, degree_t deg);
// удаление мономов с нулевым коэф
void normalize_polynomial(Polynomial* poly);
// сортировка списка по степеням от мл к ст
void sort_polynomial(Polynomial* poly);

// операции
Polynomial* parse_polynomial(const char* str);
Polynomial* poly_add(const Polynomial* p1, const Polynomial* p2);
Polynomial* poly_multiply(const Polynomial* p1, const Polynomial* p2);
Polynomial* poly_differentiate(const Polynomial* p);

// ввод/вывод и осн логика
// форматирование полинома в строку по тз
char* poly_to_string(const Polynomial* poly);
// читка input.txt, выполнение операций и output.txt
void process_file(const char* input_filename, const char* output_filename);

#endif // POLYNOMIAL_H