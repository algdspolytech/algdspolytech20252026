#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>
#include "Functions.h"
#pragma warning(disable: 4996)

void Test_safe_add_PositiveNumbers_NoOverflow_ReturnSuccess() {
    printf("Test 1: Safe add positive numbers no overflow\n");

    long long res;
    int result = safe_add(100, 200, &res);

    assert(result == 1);
    assert(res == 300);
    printf("Success!\n\n");
}

void Test_safe_add_NegativeNumbers_NoOverflow_ReturnSuccess() {
    printf("Test 2: Safe add negative numbers no overflow\n");

    long long res;
    int result = safe_add(-100, -200, &res);

    assert(result == 1);
    assert(res == -300);
    printf("Success!\n\n");
}

void Test_safe_add_Overflow_ReturnFailure() {
    printf("Test 3: Safe add overflow\n");

    long long res;
    int result = safe_add(LLONG_MAX, 1, &res);

    assert(result == 0);
    printf("Success!\n\n");
}

void Test_safe_sub_PositiveNumbers_NoOverflow_ReturnSuccess() {
    printf("Test 4: Safe sub positive numbers no overflow\n");

    long long res;
    int result = safe_sub(500, 200, &res);

    assert(result == 1);
    assert(res == 300);
    printf("Success!\n\n");
}

void Test_safe_sub_NegativeToPositive_NoOverflow_ReturnSuccess() {
    printf("Test 5: Safe sub negative to positive\n");

    long long res;
    int result = safe_sub(-100, -200, &res);

    assert(result == 1);
    assert(res == 100);
    printf("Success!\n\n");
}

void Test_safe_sub_Underflow_ReturnFailure() {
    printf("Test 6: Safe sub underflow\n");

    long long res;
    int result = safe_sub(LLONG_MIN, 1, &res);

    assert(result == 0);
    printf("Success!\n\n");
}

void Test_safe_mul_PositiveNumbers_NoOverflow_ReturnSuccess() {
    printf("Test 7: Safe mul positive numbers no overflow\n");

    long long res;
    int result = safe_mul(100, 200, &res);

    assert(result == 1);
    assert(res == 20000);
    printf("Success!\n\n");
}

void Test_safe_mul_Zero_ReturnSuccess() {
    printf("Test 8: Safe mul with zero\n");

    long long res;
    int result = safe_mul(100, 0, &res);

    assert(result == 1);
    assert(res == 0);
    printf("Success!\n\n");
}

void Test_safe_mul_Overflow_ReturnFailure() {
    printf("Test 9: Safe mul overflow\n");

    long long res;
    int result = safe_mul(LLONG_MAX, 2, &res);

    assert(result == 0);
    printf("Success!\n\n");
}


void Test_dfs_SimpleAddition_ReturnCorrectExpression() {
    printf("Test 10: DFS simple addition case\n");

    char A[] = "123";
    long long B = 6;
    char out[820];
    char expr[820];

    Ctx ctx;
    ctx.a = A;
    ctx.n = strlen(A);
    ctx.target = B;
    ctx.expr = expr;
    ctx.out = out;
    ctx.out_cap = sizeof(out);
    ctx.found = 0;

    dfs(&ctx, 0, 0, 0, 0);

    assert(ctx.found == 1);
    assert(strcmp(ctx.out, "1+2+3") == 0);
    printf("Success!\n\n");
}

void Test_dfs_WithMultiplication_ReturnCorrectExpression() {
    printf("Test 11: DFS with multiplication\n");

    char A[] = "236";
    long long B = 36;
    char out[820];
    char expr[820];

    Ctx ctx;
    ctx.a = A;
    ctx.n = strlen(A);
    ctx.target = B;
    ctx.expr = expr;
    ctx.out = out;
    ctx.out_cap = sizeof(out);
    ctx.found = 0;

    dfs(&ctx, 0, 0, 0, 0);

    assert(ctx.found == 1);
    assert(strlen(ctx.out) > 0);
    printf("Success!\n\n");
}

void Test_dfs_NoSolution_ReturnNotFound() {
    printf("Test 12: DFS no solution\n");

    char A[] = "999";
    long long B = 1;
    char out[820];
    char expr[820];

    Ctx ctx;
    ctx.a = A;
    ctx.n = strlen(A);
    ctx.target = B;
    ctx.expr = expr;
    ctx.out = out;
    ctx.out_cap = sizeof(out);
    ctx.found = 0;

    dfs(&ctx, 0, 0, 0, 0);

    assert(ctx.found == 0);
    printf("Success!\n\n");
}

void Test_dfs_LeadingZero_ReturnValidExpression() {
    printf("Test 13: DFS with leading zero constraint\n");

    char A[] = "102";
    long long B = 3;
    char out[820];
    char expr[820];

    Ctx ctx;
    ctx.a = A;
    ctx.n = strlen(A);
    ctx.target = B;
    ctx.expr = expr;
    ctx.out = out;
    ctx.out_cap = sizeof(out);
    ctx.found = 0;

    dfs(&ctx, 0, 0, 0, 0);


    assert(ctx.found == 1);
    printf("Success!\n\n");
}

void Test_dfs_LargeNumber_ReturnValidExpression() {
    printf("Test 14: DFS with large number\n");

    char A[] = "123456789";
    long long B = 123456789;
    char out[820];
    char expr[820];

    Ctx ctx;
    ctx.a = A;
    ctx.n = strlen(A);
    ctx.target = B;
    ctx.expr = expr;
    ctx.out = out;
    ctx.out_cap = sizeof(out);
    ctx.found = 0;

    dfs(&ctx, 0, 0, 0, 0);

    assert(ctx.found == 1);
    assert(strcmp(ctx.out, "123456789") == 0);
    printf("Success!\n\n");
}

void Test_dfs_DivisionCase_ReturnValidExpression() {
    printf("Test 15: DFS with division\n");

    char A[] = "842";
    long long B = 4;
    char out[820];
    char expr[820];

    Ctx ctx;
    ctx.a = A;
    ctx.n = strlen(A);
    ctx.target = B;
    ctx.expr = expr;
    ctx.out = out;
    ctx.out_cap = sizeof(out);
    ctx.found = 0;

    dfs(&ctx, 0, 0, 0, 0);

    assert(ctx.found == 1);
    assert(strlen(ctx.out) > 0);
    printf("Success!\n\n");
}



int main(void) {
    //Тесты
    Test_safe_add_PositiveNumbers_NoOverflow_ReturnSuccess();
    Test_safe_add_NegativeNumbers_NoOverflow_ReturnSuccess();
    Test_safe_add_Overflow_ReturnFailure();
    Test_safe_sub_PositiveNumbers_NoOverflow_ReturnSuccess();
    Test_safe_sub_NegativeToPositive_NoOverflow_ReturnSuccess();
    Test_safe_sub_Underflow_ReturnFailure();
    Test_safe_mul_PositiveNumbers_NoOverflow_ReturnSuccess();
    Test_safe_mul_Zero_ReturnSuccess();
    Test_safe_mul_Overflow_ReturnFailure();
    Test_dfs_SimpleAddition_ReturnCorrectExpression();
    Test_dfs_WithMultiplication_ReturnCorrectExpression();
    Test_dfs_NoSolution_ReturnNotFound();
    Test_dfs_LeadingZero_ReturnValidExpression();
    Test_dfs_LargeNumber_ReturnValidExpression();
    Test_dfs_DivisionCase_ReturnValidExpression();
    printf("All tests passed!\n");

    //Основная функция работы с файлом
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    if (!fin || !fout) return 0;

    char A[205];
    long long B;

    if (fscanf(fin, "%204s %lld", A, &B) != 2) {
        fprintf(fout, "0");
        fclose(fin);
        fclose(fout);
        return 0;
    }

    int n = (int)strlen(A);


    char expr[820];
    char out[820];
    out[0] = '\0';

    Ctx ctx;
    ctx.a = A;
    ctx.n = n;
    ctx.target = B;
    ctx.expr = expr;
    ctx.out = out;
    ctx.out_cap = (int)sizeof(out);
    ctx.found = 0;

    dfs(&ctx, 0, 0, 0, 0);

    if (ctx.found) fprintf(fout, "%s", ctx.out);
    else fprintf(fout, "0");

    fclose(fin);
    fclose(fout);
    return 0;
}