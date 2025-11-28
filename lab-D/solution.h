#ifndef SOLUTION_H
#define SOLUTION_H

#include <stdbool.h>


typedef struct {
    int* elements;      
    int count;          
    bool found;         
} SubsetResult;

/**
 * @param B Указатель на переменную для сохранения целевой суммы.
 * @param N Указатель на переменную для сохранения количества элементов.
 * @param A Указатель на указатель, куда будет записан массив элементов.
 * @return true, если чтение успешно, false в случае ошибки.
 */
bool read_input(int* B, int* N, int** A);

/**
 * @param A Массив элементов.
 * @param N Количество элементов.
 * @param B Целевая сумма.
 * @return Структура SubsetResult с результатом поиска.
 */
SubsetResult find_subset_sum(const int* A, int N, int B);

/**
 * @param result Структура с результатом поиска.
 * @return true, если запись успешна, false в случае ошибки.
 */
bool write_output(const SubsetResult* result);

/**
 * @param result Структура, память которой нужно освободить.
 */
void free_subset_result(SubsetResult* result);

#endif // SOLUTION_H