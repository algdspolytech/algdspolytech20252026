#pragma once
#ifndef PAPER_CELLS_H
#define PAPER_CELLS_H

typedef struct
{
    int rows;
    int cols;
    int** grid;
} PaperGrid;

PaperGrid* create_paper(int rows, int cols);
void destroy_paper(PaperGrid* paper);
void remove_cells(PaperGrid* paper, int k, int coords[][2]);
int count_fragments(PaperGrid* paper);

#endif
