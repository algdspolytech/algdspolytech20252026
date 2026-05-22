#include "nqueens.h"
#include <stdio.h>
#include <stdlib.h>

#define STRLEN 256
#define NUMLEN 7

board_t *make_board(int n) {
  if (n <= 0) {
    return nullptr;
  }
  board_t *ans = (board_t *)malloc(sizeof(board_t));
  int **squares = (int **)malloc(sizeof(int *) * n);
  for (int i = 0; i < n; i++) {
    squares[i] = (int *)malloc(sizeof(int) * n);
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      squares[i][j] = 0;
    }
  }

  ans->n = n;
  ans->squares = squares;
  return ans;
}

void free_board(board_t *board) {
  int n = board->n;
  for (int i = 0; i < n; i++) {
    free(*(board->squares + i));
  }
  free(board->squares);
  free(board);
}

void print_board(board_t *board) {
  int n = board->n;
  for (int i = 0; i < n + 2; i++) {
    printf("-");
  }
  printf("\n");
  for (int i = 0; i < n; i++) {
    printf("|");
    for (int j = 0; j < n; j++) {
      if (board->squares[i][j] == 0) {
        printf("0");
      } else {
        printf("x");
      }
    }
    printf("|\n");
  }
  for (int i = 0; i < n + 2; i++) {
    printf("-");
  }
  printf("\n");
}

placement_t *make_placement(int n) {
  if (n <= 0) {
    return nullptr;
  }
  placement_t *p = (placement_t *)malloc(sizeof(placement_t));
  p->n = n;
  p->x = (int *)malloc(sizeof(int) * n);
  p->a = (bool *)malloc(sizeof(bool) * n);
  p->b = (bool *)malloc(sizeof(bool) * (2 * n - 1));
  p->c = (bool *)malloc(sizeof(bool) * (2 * n - 1));
  for (int i = 0; i < n; i++) {
    p->x[i] = -1;
    p->a[i] = true;
  }
  for (int i = 0; i < 2 * n - 1; i++) {
    p->b[i] = true;
    p->c[i] = true;
  }
  return p;
}

void free_placement(placement_t *p) {
  free(p->x);
  free(p->a);
  free(p->b);
  free(p->c);
  free(p);
}

void place_queen(int i, int j, placement_t *p) {
  int n = p->n;
  p->x[i] = j;
  p->a[j] = false;
  p->b[i + j] = false;
  p->c[i - j + n - 1] = false;
}

void remove_queen(int i, int j, placement_t *p) {
  int n = p->n;
  p->x[i] = -1;
  p->a[j] = true;
  p->b[i + j] = true;
  p->c[i - j + n - 1] = true;
}

bool check_square(int i, int j, placement_t *p) {
  int n = p->n;
  bool ans = p->a[j] && p->b[i + j] && p->c[i - j + n - 1];
  return ans;
}

void try_placement(int i, bool *q, placement_t *p) {
  int n = p->n;
  int j = -1;
  do {
    j += 1;
    *q = false;
    if (check_square(i, j, p)) {
      p->x[i] = j;
      place_queen(i, j, p);
      if (i < n - 1) {
        try_placement(i + 1, q, p);
        if (!*q)
          remove_queen(i, j, p);
      } else
        *q = true;
    }
  } while (!(*q || (j == n - 1)));
}

void place_to_board(board_t *board, placement_t *p) {
  for (int i = 0; i < board->n; i++) {
    for (int j = 0; j < board->n; j++) {
      board->squares[i][j] = 0;
    }
    if (p->x[i] != -1) {
      board->squares[i][p->x[i]] = 1;
    }
  }
}

int queen_placement(board_t *board) {
  if (board) {
    int n = board->n;
    placement_t *p = make_placement(n);
    bool qv = false, *q = &qv;
    try_placement(0, q, p);
    if (*q) {
      place_to_board(board, p);
      print_board(board);
      free_placement(p);
      return 1;
    } else {
      printf("Is not possible to place\n");
      free_placement(p);
      return 0;
    }
  } else {
    printf("No board!\n");
    return 0;
  }
}

int read_number(char *filename) {
  FILE *F = fopen(filename, "r");
  if (!F) {
    return -1;
  }
  char buffer[STRLEN];
  if (fgets(buffer, STRLEN, F)) {
    int n = strtol(buffer, NULL, 10);
    fclose(F);
    return n;
  }
  fclose(F);
  return -1;
}

int output(char *filename) {
  int n = read_number(filename);
  if (n == -1) {
    printf("Error in reading number!\n");
    return 0;
  }
  printf("The number is: %i\n", n);
  board_t *board = make_board(n);
  if (!board) {
    printf("Error while creating the board!\n");
    return 0;
  }
  if (!queen_placement(board)) {
    free_board(board);
    return 0;
  }
  FILE *F = fopen("output.txt", "w");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board->squares[i][j] == 1) {
        fprintf(F, "%i %i\n", i, j);
        break;
      }
    }
  }
  free_board(board);
  return 1;
}
