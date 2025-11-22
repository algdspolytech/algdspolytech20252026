#pragma once
#include <stdio.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

    void Read_From_File(FILE* file, int T, int* size_of_operation_new, int** connect_new, int* in_degree_new, int* cnt_new);

    bool MinMaxRates2(int summ, int step, int** connect, int* size_of_operation, int* cnt, int* in_degree, int T, int K, int* seq);

    void Add_To_File(FILE* file, int* items, int T, bool flag);

    void Full_Rates(FILE* file, FILE* file_in);

#ifdef __cplusplus
}
#endif



