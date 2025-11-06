#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#ifdef __cplusplus
extern "C" {
#endif

    // Структура монома
    typedef struct Term {
        int coeff;
        int pow;
        struct Term* next;
    } Term;

    // Создание нового монома
    Term* create_term(int coeff, int pow);

    // Добавление монома в полином (суммирование с существующим, если степень совпадает)
    Term* add_term(Term* poly, int coeff, int pow);

    // Освобождение памяти полинома
    void free_polynomial(Term* poly);

    // Сумма двух полиномов
    Term* sum_polynomials(Term* p1, Term* p2);

    // Произведение двух полиномов
    Term* multiply_polynomials(Term* p1, Term* p2);

    // Производная полинома
    Term* derivative_polynomial(Term* poly);

    // Парсинг строки полинома в связанный список
    Term* parse_polynomial(const char* str);

    // Преобразование полинома в строку
    void polynomial_to_string(Term* poly, char* buffer, int size);

    // Сортировка полинома по степеням (от x^0 к старшей)
    Term* sort_polynomial(Term* poly);

#ifdef __cplusplus
}
#endif

#endif // POLYNOMIAL_H
