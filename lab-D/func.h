#pragma once

#define FUNC_H
#ifdef FUNC_H

#include <stdbool.h>

#define MAX_DIGITS 100
#define MAX_LENGTH 300

bool search(const char* A, long long B, char* result);

bool solver(const char* digits, int index, long long current, long long last, const char* expr, long long target, char* result);

long long calculator(long long a, long long b, char op);

#endif