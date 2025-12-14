#pragma once

#include <stdio.h>
#include <stdlib.h>

long long read_input(const char* filename);
void write_output(const char* filename, long long* cols, long long N);
void generate_solution(long long* cols, long long N);
