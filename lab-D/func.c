#include "func.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool search(const char* A, long long B, char* result) {
    result[0] = '\0';

    if (A == NULL || A[0] == '\0') {
        return false;
    }

    return solver(A, 0, 0, 0, "", B, result);
}

bool solver(const char* digits, int index, long long current,
    long long last, const char* expr, long long target,
    char* result) {
    int len = strlen(digits);

    if (index == len) {
        if (current == target) {
            strcpy(result, expr);
            return true;
        }
        return false;
    }

    long long num = 0;
    char newExpr[MAX_LENGTH];
    char numStr[MAX_DIGITS];

    for (int i = index; i < len; i++) {
        num = num * 10 + (digits[i] - '0');

        int numLen = i - index + 1;
        strncpy(numStr, digits + index, numLen);
        numStr[numLen] = '\0';

        if (index == 0) {
            snprintf(newExpr, sizeof(newExpr), "%s", numStr);
            if (solver(digits, i + 1, num, num, newExpr, target, result)) {
                return true;
            }
        }
        else {
            char ops[] = "+-*/";
            for (int j = 0; j < 4; j++) {
                snprintf(newExpr, sizeof(newExpr), "%s%c%s", expr, ops[j], numStr);

                long long newCurrent = 0;
                long long newLast = 0;

                switch (ops[j]) {
                case '+':
                    newCurrent = current + num;
                    newLast = num;
                    break;
                case '-':
                    newCurrent = current - num;
                    newLast = -num;
                    break;
                case '*':
                    newCurrent = current - last + last * num;
                    newLast = last * num;
                    break;
                case '/':
                    if (num == 0) continue;
                    if (last % num != 0) continue;
                    newCurrent = current - last + last / num;
                    newLast = last / num;
                    break;
                }

                if (solver(digits, i + 1, newCurrent, newLast, newExpr, target, result)) {
                    return true;
                }
            }
        }

        if (digits[index] == '0') {
            break;
        }
    }

    return false;
}

long long calculator(long long a, long long b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) return 0;
        return a / b;
    default: return 0;
    }
}