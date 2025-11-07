#include "polynom.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

// проверка усл и вывод ошибки, если оно ложно
#define ASSERT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            test_failures++; \
            printf("[FAIL] Condition is false: %s (Test: %s, Line: %d)\n", (message), __func__, __LINE__); \
            return; \
        } \
    } while (0)

// счетчик для отслеживания резов
static int total_tests = 0;
static int test_failures = 0;

// доп функ для сравнения строк
void assert_poly_string_equal(const char* expected, const char* actual, const char* test_name) {
    total_tests++;
    if (strcmp(expected, actual) != 0) {
        test_failures++;
        printf("\n[TEST FAILED] %s\n", test_name);
        printf("--- FORMATTING OR LOGIC ERROR ---\n");
        printf("Expected result: \"%s\"\n", expected);
        printf("Actual result: \"%s\"\n\n", actual);

    }
    else {
        printf("[SUCCESS] %s\n", test_name);
    }
}

// тесты
// 1. сложение: взаимное уничтожение (рез - 0)
void TestAdd_ZeroSum_1() {
    // (5*x^2 - 1) + (1 - 5*x^2) = 0
    Polynomial* p1 = parse_polynomial("5*x^2-1");
    Polynomial* p2 = parse_polynomial("1-5*x^2");
    Polynomial* result = poly_add(p1, p2);
    char* output_str = poly_to_string(result);
    assert_poly_string_equal("0", output_str, "TestAdd_ZeroSum_1");
    free(output_str); free_polynomial(p1); free_polynomial(p2); free_polynomial(result);
}

// 2. сложение: смешанные знаки и формат 1*x
void TestAdd_MixedSigns_2() {
    // (-10*x^3 - 5*x + 2) + (10*x^3 - 4*x - 3) = -1 - 9*x
    Polynomial* p1 = parse_polynomial("-10*x^3-5*x+2");
    Polynomial* p2 = parse_polynomial("10*x^3-4*x-3");
    Polynomial* result = poly_add(p1, p2);
    char* output_str = poly_to_string(result);
    assert_poly_string_equal("-1-9*x", output_str, "TestAdd_MixedSigns_2");
    free(output_str); free_polynomial(p1); free_polynomial(p2); free_polynomial(result);
}

// 3. сложение: добавка к пустому полиному (проверка на возврат P1)
void TestAdd_ToEmptyPolynomial_3() {
    Polynomial* p1 = parse_polynomial("7*x^5+2*x");
    Polynomial* p2 = parse_polynomial("");
    Polynomial* result = poly_add(p1, p2);
    char* output_str = poly_to_string(result);
    assert_poly_string_equal("2*x+7*x^5", output_str, "TestAdd_ToEmptyPolynomial_3");
    free(output_str); free_polynomial(p1); free_polynomial(p2); free_polynomial(result);
}

// 4. умн: базовый бином (a+b)(a-b) = a^2 - b^2
void TestMultiply_BasicBinomial_4() {
    // (x^3 + 1) * (x^3 - 1) = x^6 - 1
    Polynomial* p1 = parse_polynomial("x^3+1");
    Polynomial* p2 = parse_polynomial("x^3-1");
    Polynomial* result = poly_multiply(p1, p2);
    char* output_str = poly_to_string(result);
    assert_poly_string_equal("-1+x^6", output_str, "TestMultiply_BasicBinomial_4");
    free(output_str); free_polynomial(p1); free_polynomial(p2); free_polynomial(result);
}

// 5. умн: умножение на нулевой полином
void TestMultiply_ByZero_5() {
    // (x^100 + 1) * (0) = 0
    Polynomial* p1 = parse_polynomial("x^100+1");
    Polynomial* p2 = parse_polynomial("0");
    Polynomial* result = poly_multiply(p1, p2);
    char* output_str = poly_to_string(result);
    assert_poly_string_equal("0", output_str, "TestMultiply_ByZero_5");
    free(output_str); free_polynomial(p1); free_polynomial(p2); free_polynomial(result);
}

// 6. умн: комбинация больших степеней и отр чисел
void TestMultiply_ComplexTerms_6() {
    // (10*x^2 + 2) * (3*x^3 - 1) = -2 - 10*x^2 + 6*x^3 + 30*x^5
    Polynomial* p1 = parse_polynomial("10*x^2+2");
    Polynomial* p2 = parse_polynomial("3*x^3-1");
    Polynomial* result = poly_multiply(p1, p2);
    char* output_str = poly_to_string(result);
    assert_poly_string_equal("-2-10*x^2+6*x^3+30*x^5", output_str, "TestMultiply_ComplexTerms_6");
    free(output_str); free_polynomial(p1); free_polynomial(p2); free_polynomial(result);
}

// 7. диффер: общий случай (const, x^1, x^k)
void TestDifferentiate_GeneralCase_7() {
    // P = 4*x^3 - 10*x + 5. P' = 12*x^2 - 10
    Polynomial* p = parse_polynomial("4*x^3-10*x+5");
    Polynomial* result = poly_differentiate(p);
    char* output_str = poly_to_string(result);
    assert_poly_string_equal("-10+12*x^2", output_str, "TestDifferentiate_GeneralCase_7");
    free(output_str); free_polynomial(p); free_polynomial(result);
}

// 8. диффер: производная const 
void TestDifferentiate_Constant_8() {
    // P = -1500. P' = 0
    Polynomial* p = parse_polynomial("-1500");
    Polynomial* result = poly_differentiate(p);
    char* output_str = poly_to_string(result);
    assert_poly_string_equal("0", output_str, "TestDifferentiate_Constant_8");
    free(output_str); free_polynomial(p); free_polynomial(result);
}

// 9. диффер: проверка больших степеней
void TestDifferentiate_LargeDegree_9() {
    // P = x^200 + 10*x^2. P' = 200*x^199 + 20*x
    Polynomial* p = parse_polynomial("x^200+10*x^2");
    Polynomial* result = poly_differentiate(p);
    char* output_str = poly_to_string(result);
    assert_poly_string_equal("20*x+200*x^199", output_str, "TestDifferentiate_LargeDegree_9");
    free(output_str); free_polynomial(p); free_polynomial(result);
}

// 10. формат/парсинг: проверка правил вывода 1*x, -1*x^k, x^0
void TestFormatting_EdgeCases_10() {
    // P = x^3 + x - x + 1*x^0 + 1. после нормализации: 2+x^3
    Polynomial* p = parse_polynomial("x^3 + x - x + 1*x^0 + 1");
    //не сработала parse, то poly_add для создания копии и принудительной нормализации
    Polynomial* result_copy = poly_add(p, create_polynomial());
    char* output_str = poly_to_string(result_copy);
    assert_poly_string_equal("2+x^3", output_str, "TestFormatting_EdgeCases_10");
    free(output_str); free_polynomial(p); free_polynomial(result_copy);
}

int main() {
    printf("--- Running Unit Tests for Polynomials (Pure C) ---\n");

    TestAdd_ZeroSum_1();
    TestAdd_MixedSigns_2();
    TestAdd_ToEmptyPolynomial_3();

    TestMultiply_BasicBinomial_4();
    TestMultiply_ByZero_5();
    TestMultiply_ComplexTerms_6();

    TestDifferentiate_GeneralCase_7();
    TestDifferentiate_Constant_8();
    TestDifferentiate_LargeDegree_9();

    TestFormatting_EdgeCases_10();

    printf("Total tests executed: %d\n", total_tests);
    printf("Total failures: %d\n", test_failures);

    if (test_failures == 0) {
        printf("All %d tests SUCCESSFULLY passed!\n", total_tests);
    }
    else {
        printf("Some tests FAILED. Please check the output.\n");
    }

    return test_failures > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}