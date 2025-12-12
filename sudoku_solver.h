#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Структуры данных
typedef struct DLXNode {
    struct DLXNode* L, * R, * U, * D, * C;
    int rowIdx, cnt;
} DLXNode;

typedef struct {
    DLXNode hdr;
    DLXNode** colArr, ** rowArr, ** colHdrs;
    int* ans, ansCnt, rows, cols, gridDim, subDim;
} DLXSolver;

typedef struct {
    int order, dim, sub, ** data;
} Puzzle;

typedef struct {
    int* rowMap, * colMap, * valMap;
    int total;
} RowMapper;

// Функции инициализации и очистки
void initMapper(int maxRows);
void cleanupMapper();

// Функции работы с DLX
void setupSolver(DLXSolver* s, int colNum, int gridDim, int subDim);
void cleanupSolver(DLXSolver* s);
int backtrack(DLXSolver* s, int level);

// Функции работы с судоку
void loadPuzzle(const char* fname, Puzzle* p);
void storePuzzle(const char* fname, Puzzle* p);
void cleanupPuzzle(Puzzle* p);
bool solveSudoku(Puzzle* puzzle);

// Вспомогательные функции
int validateSudoku(Puzzle* p);
void printSudoku(Puzzle* p);

#endif#pragma once
