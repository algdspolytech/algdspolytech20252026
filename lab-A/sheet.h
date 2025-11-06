#pragma once
#ifndef SHEET_H
#define SHEET_H

#define MAX 50

// Глобальные переменные для размера листа
extern int M, N;

// Сетка и посещённые клетки
extern int grid[MAX][MAX];
extern int visited[MAX][MAX];

// Функции
int valid(int x, int y);       // проверка координат
void dfs(int x, int y);        // поиск в глубину
int count_connected();         // подсчёт связных кусков
void init_sheet();             // инициализация сетки и visited
void set_removed(int x, int y); // удалить клетку
void print_field();            // вывести поле

#endif
