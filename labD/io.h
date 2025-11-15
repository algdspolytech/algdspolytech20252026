#ifndef IO_H
#define IO_H

int read_input(const char* filename, int* n, int* B, int* K, int** w, int** v);
void write_output(const char* filename, int* indices, int count);

#endif