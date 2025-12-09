#ifndef PAPER_H
#define PAPER_H

#include <stdbool.h>
#include <stddef.h>

// ќбъ€вление непрозрачной структуры
typedef struct Paper Paper;

// ќсновные функции API
Paper* create_paper(int m, int n);
void destroy_paper(Paper* paper);

void remove_cells(Paper* paper, int k, int* x_coords, int* y_coords);
int count_connected_components(Paper* paper);

#endif // PAPER_H