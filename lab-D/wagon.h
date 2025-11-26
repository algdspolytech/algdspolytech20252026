#ifndef WAGON_H
#define WAGON_H

#include <stddef.h>

int solve_instance(int W,
                   const int *times,
                   int D,
                   int K,
                   const int (*edges)[2],
                   int m_edges,
                   int *out_order /* length W, 1-based indices stored */,
                   int *out_len /* actual written length */);

#endif // WAGON_H
