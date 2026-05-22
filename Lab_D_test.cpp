
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef NQUEENS_H
extern "C" {
#include "nqueens.h"
}
#endif

#define free_all()                                                             \
  free_board(b);                                                               \
  free_placement(p);

#define make_units(n)                                                          \
  board_t *b = make_board(n);                                                  \
  placement_t *p = make_placement(n);

// Проверяет возможность расположения ферзей из board
bool possible_placement(board_t *board, placement_t *p) {
  bool ans = true;
  int i = 0;
  while (i < board->n && ans) {
    for (int j = 0; j < board->n; j++) {
      if (board->squares[i][j] == 1) {
        if (check_square(j, i, p)) {
          place_queen(j, i, p);
        } else {

          for (int i = 0; i < board->n; i++) {
            p->x[i] = -1;
            p->a[i] = true;
          }
          for (int i = 0; i < 2 * board->n - 1; i++) {
            p->b[i] = true;
            p->c[i] = true;
          }

          ans = false;
          printf("Impossible placement!\n");
          break;
        }
      }
    }
    i++;
  }
  return ans;
}

// 1) Попытка размещения ферзей на одной диагонали
TEST(CheckSquareTest, SameDiagonal_FalseExpected_no1) {
  make_units(4);
  b->squares[0][1] = 1;
  b->squares[1][2] = 1;
  EXPECT_FALSE(possible_placement(b, p));
  free_all();
}

// 2) Попытка размещения ферзей в одном ряду
TEST(CheckSquareTest, SameRowTest_FalseExpected_no2) {
  make_units(4);
  b->squares[0][0] = 1;
  b->squares[0][3] = 1;
  EXPECT_FALSE(possible_placement(b, p));
  free_all();
}

// 3) Проверка возможного расположения ферзей
TEST(CheckSquareTest, PossibleQueenPlacement_no3) {
  make_units(4);
  b->squares[0][0] = 1;
  b->squares[1][2] = 1;
  EXPECT_TRUE(possible_placement(b, p));
  free_all();
}

// 4) Размещение ферзя в столбец 1, строку 4 (нумерация с 0)
// Проверяет возможность расположения в одной диагонали, на возможной позиции
TEST(PlaceQueenTest, PlaceTo1_4_PlacingPossibilityCheck_no4) {
  make_units(5);
  place_queen(1, 4, p);
  EXPECT_FALSE(check_square(2, 3, p));
  EXPECT_TRUE(check_square(2, 2, p));
  free_all();
}

// 5) Удаление ферзя с позиции, проверка новых допустимых позиций
TEST(RemoveQueenTest, RemovingQueen_PlacingPossibilityCheck_no5) {
  make_units(5);
  place_queen(0, 0, p);
  place_queen(1, 4, p);
  place_to_board(b, p);
  print_board(b);
  EXPECT_FALSE(check_square(2, 3, p));
  remove_queen(1, 4, p);
  place_to_board(b, p);
  print_board(b);
  EXPECT_TRUE(check_square(2, 3, p));
  free_all();
}

// 6) Проверка метода try_placement на допустимом поле
TEST(TryPlacementTest, TryPossiblePlacement_TrueExpected_no6) {
  make_units(4);
  b->squares[2][0] = 1;
  b->squares[0][1] = 1;
  b->squares[3][2] = 1;
  print_board(b);
  bool qv = false, *q = &qv;
  if (possible_placement(b, p)) {
    try_placement(3, q, p);
    if (*q) {
      place_to_board(b, p);
      print_board(b);
    }
  }
  EXPECT_TRUE(*q);
  free_all();
}

// 7) Проверка try_placement для заведомо проигрышной позиции
TEST(TryPlacementTest, TryImpossiblePlacement_FalseExpected_no7) {
  make_units(3);
  b->squares[0][0] = 1;
  b->squares[2][1] = 1;
  print_board(b);
  bool qv = false, *q = &qv;
  if (possible_placement(b, p)) {
    try_placement(2, q, p);
    EXPECT_FALSE(*q);
  }
  free_all();
}

// 8) Расположение ферзей на доске с доступным числом клеток
TEST(QueenPlacementTest, PossibleNumberOfSquares_TrueExpected_no8) {
  board_t *b = make_board(10);
  EXPECT_TRUE(queen_placement(b));
  free_board(b);
}

// 9) Расположение на доске с недопустимым числом клеток
TEST(QueenPlacementTest, ImpossibleNumberOfSquares_FalseExpected_no9) {
  board_t *b = make_board(3);
  EXPECT_FALSE(queen_placement(b));
  free_board(b);
}

// 10) Поведение при ошибке создания доски
TEST(QueenPlacementTest, EmptyPointerScenerio_no10) {
  board_t *board = make_board(0);
  EXPECT_FALSE(queen_placement(board));
}

// 11) Неправильный формат входных данных
// Генерация output.txt отсутствует
TEST(OutputTest, DefectedInput_NoOutputExpected_no11) {
  int read = output("Input/bad_input.txt");
  EXPECT_FALSE(read);
}

// 12) Отсутствие необходимого файла
// Генерация output.txt отсутствует
TEST(OutputTest, NoInput_NoOutputExpected_no12) {
  int read = output("Input/no_input.txt");
  EXPECT_FALSE(read);
}

// 13) Допустимый файл input, создается файл output.txt
TEST(OutputTest, NormalInput_NormalOutputCheck_no13) {
  int read = output("Input/input.txt");
  EXPECT_TRUE(read);
}

int main(int argc, char **argv) {

  output("Input/input.txt");

  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}