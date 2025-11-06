#include <gtest/gtest.h>
#include "polynomial.h"
#include <string.h>

// Вспомогательная функция для проверки полинома на соответствие массиву коэффициентов и степеней
void check_polynomial(Term* poly, int coeffs[], int powers[], int size) {
    Term* current = poly;
    for (int i = 0; i < size; i++) {
        ASSERT_NE(current, nullptr);
        ASSERT_EQ(current->coeff, coeffs[i]);
        ASSERT_EQ(current->pow, powers[i]);
        current = current->next;
    }
    ASSERT_EQ(current, nullptr);
}

// Создание одного монома
TEST(CreateTerm_HappyPath_no1, WorksCorrectly) {
    Term* t = create_term(5, 2);
    ASSERT_NE(t, nullptr);
    ASSERT_EQ(t->coeff, 5);
    ASSERT_EQ(t->pow, 2);
    ASSERT_EQ(t->next, nullptr);
    free_polynomial(t);
}

// Добавление монома к пустому полиному
TEST(AddTerm_EmptyPoly_no2, WorksCorrectly) {
    Term* poly = NULL;
    poly = add_term(poly, 3, 1);
    int coeffs[] = { 3 };
    int powers[] = { 1 };
    check_polynomial(poly, coeffs, powers, 1);
    free_polynomial(poly);
}

// Добавление монома с той же степенью (сложение коэффициентов)
TEST(AddTerm_SamePow_no3, WorksCorrectly) {
    Term* poly = create_term(2, 2);
    poly = add_term(poly, 5, 2);
    int coeffs[] = { 7 };
    int powers[] = { 2 };
    check_polynomial(poly, coeffs, powers, 1);
    free_polynomial(poly);
}

// Сумма двух полиномов
TEST(SumPolynomials_HappyPath_no4, WorksCorrectly) {
    Term* p1 = create_term(1, 1);
    Term* p2 = create_term(2, 1);
    Term* sum = sum_polynomials(p1, p2);
    int coeffs[] = { 3 };
    int powers[] = { 1 };
    check_polynomial(sum, coeffs, powers, 1);
    free_polynomial(p1);
    free_polynomial(p2);
    free_polynomial(sum);
}

// Произведение двух полиномов
TEST(MultiplyPolynomials_HappyPath_no5, WorksCorrectly) {
    Term* p1 = create_term(2, 1);
    Term* p2 = create_term(3, 2);
    Term* prod = multiply_polynomials(p1, p2);
    int coeffs[] = { 6 };
    int powers[] = { 3 };
    check_polynomial(prod, coeffs, powers, 1);
    free_polynomial(p1);
    free_polynomial(p2);
    free_polynomial(prod);
}

// Производная полинома
TEST(DerivativePolynomial_HappyPath_no6, WorksCorrectly) {
    Term* poly = create_term(3, 3);
    Term* deriv = derivative_polynomial(poly);
    int coeffs[] = { 9 };
    int powers[] = { 2 };
    check_polynomial(deriv, coeffs, powers, 1);
    free_polynomial(poly);
    free_polynomial(deriv);
}

// Парсинг строки полинома
TEST(ParsePolynomial_HappyPath_no7, WorksCorrectly) {
    Term* poly = parse_polynomial("2x^2 + 3x^1 + 1");
    int coeffs[] = { 2, 3, 1 };
    int powers[] = { 2, 1, 0 };
    check_polynomial(poly, coeffs, powers, 3);
    free_polynomial(poly);
}

// Преобразование полинома в строку
TEST(PolynomialToString_HappyPath_no8, WorksCorrectly) {
    Term* poly = parse_polynomial("1x^1 + 2");
    char buffer[50];
    polynomial_to_string(poly, buffer, sizeof(buffer));
    ASSERT_STREQ(buffer, "1x^1+2");
    free_polynomial(poly);
}

// Сортировка полинома по степеням
TEST(SortPolynomial_HappyPath_no9, WorksCorrectly) {
    Term* poly = parse_polynomial("3x^2+1+2x^1");
    Term* sorted = sort_polynomial(poly);
    int coeffs[] = { 1, 2, 3 };
    int powers[] = { 0, 1, 2 };
    check_polynomial(sorted, coeffs, powers, 3);
    free_polynomial(sorted);
}

// Освобождение полинома
TEST(FreePolynomial_HappyPath_no10, WorksCorrectly) {
    Term* poly = parse_polynomial("1x^1+2x^2");
    free_polynomial(poly);
    SUCCEED(); // Проверяем, что free не ломается
}
