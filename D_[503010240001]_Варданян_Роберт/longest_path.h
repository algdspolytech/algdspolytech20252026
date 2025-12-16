#ifndef LONGEST_PATH_H
#define LONGEST_PATH_H

int find_path(int v_count, int **adj, int *deg,
              int s, int t, int k,
              int *result, int *res_len);

#endif
