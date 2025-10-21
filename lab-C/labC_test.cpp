#pragma warning(disable : 4996)

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <gtest/gtest.h>

extern "C" {
#include "labC.h"
}

void CreateTM(const char* filename, const char* content) {
  FILE* file = fopen(filename, "w");
  if (file) {
    fprintf(file, "%s", content);
    fclose(file);
  }
}

void DeleteTM(const char* filename) { remove(filename); }

TEST(ReadMTest, ReadOneElem_n1) {
  CreateTM("test.txt", "1\n1\n");
  FILE* file = fopen("test.txt", "r");
  int** A = nullptr;

  int N = ReadM(file, &A);

  EXPECT_EQ(N, 1);
  EXPECT_NE(A, nullptr);
  EXPECT_EQ(A[0][0], 1);

  FreeMatrix(A, N);
  DeleteTM("test.txt");
}

TEST(ReadMTest, InvalidFile_n2) {
  FILE* file = nullptr;
  int** A = nullptr;

  int N = ReadM(file, &A);

  EXPECT_EQ(N, 0);
  EXPECT_EQ(A, nullptr);
}

TEST(ReadMTest, EmptyFile_n3) {
  CreateTM("test.txt", "");
  FILE* file = fopen("test.txt", "r");
  int** A = nullptr;

  int N = ReadM(file, &A);

  EXPECT_EQ(N, 0);
  EXPECT_EQ(A, nullptr);

  DeleteTM("test5.txt");
}

TEST(PrintMTest, PrintOneElem_n4) {
  int** A = (int**)malloc(sizeof(int*));
  A[0] = (int*)malloc(sizeof(int));
  A[0][0] = 1;

  EXPECT_NO_FATAL_FAILURE(PrintM(A, 1));

  FreeMatrix(A, 1);
}

TEST(PrintAdjLTest, PrintAdjacencyList_n5) {
  int** A = (int**)malloc(3 * sizeof(int*));
  for (int i = 0; i < 3; i++) {
    A[i] = (int*)malloc(3 * sizeof(int));
  }

  A[0][0] = 0;
  A[0][1] = 1;
  A[0][2] = 1;
  A[1][0] = 1;
  A[1][1] = 0;
  A[1][2] = 0;
  A[2][0] = 1;
  A[2][1] = 0;
  A[2][2] = 0;

  EXPECT_NO_FATAL_FAILURE(PrintAdjL(A, 3));

  FreeMatrix(A, 3);
}

TEST(WriteAdjLTest, WriteToFile_n6) {
  int** A = (int**)malloc(2 * sizeof(int*));
  for (int i = 0; i < 2; i++) {
    A[i] = (int*)malloc(2 * sizeof(int));
  }
  A[0][0] = 0;
  A[0][1] = 1;
  A[1][0] = 1;
  A[1][1] = 0;

  FILE* File = fopen("test.txt", "w");

  EXPECT_NO_FATAL_FAILURE(WriteAdjL(File, A, 2));

  fclose(File);
  FILE* rFile = fopen("test.txt", "r");
  EXPECT_NE(rFile, nullptr);
  fseek(rFile, 0, SEEK_END);
  long filSiz = ftell(rFile);
  EXPECT_GT(filSiz, 0);
  fclose(rFile);

  FreeMatrix(A, 2);
  DeleteTM("test.txt");
}

TEST(WriteAdjLTest, WriteEmpti_n7) {
  int** A = (int**)malloc(1 * sizeof(int*));
  A[0] = (int*)malloc(1 * sizeof(int));
  A[0][0] = 0;

  FILE* File = fopen("test.txt", "w");

  EXPECT_NO_FATAL_FAILURE(WriteAdjL(File, A, 1));

  fclose(File);
  FreeMatrix(A, 1);
  DeleteTM("test.txt");
}

TEST(FreeMatrixTest, FreeNull_n8) {
  int** A = nullptr;

  EXPECT_NO_FATAL_FAILURE(FreeMatrix(A, 0));
}

TEST(PrintAdjLTest, Print_Without_edges_n9) {
  int** A = (int**)malloc(3 * sizeof(int*));
  for (int i = 0; i < 3; i++) {
    A[i] = (int*)malloc(3 * sizeof(int));
    for (int j = 0; j < 3; j++) {
      A[i][j] = 0;
    }
  }

  EXPECT_NO_FATAL_FAILURE(PrintAdjL(A, 3));

  FreeMatrix(A, 3);
}

TEST(ReadMTest, ReadNonSymmetricMatrix_n18) {
  CreateTM("test.txt", "3\n0 1 0\n0 0 1\n1 0 0\n");
  FILE* file = fopen("test.txt", "r");
  int** A = nullptr;

  int N = ReadM(file, &A);

  EXPECT_EQ(N, 3);
  EXPECT_NE(A, nullptr);

  EXPECT_EQ(A[0][1], 1);
  EXPECT_EQ(A[1][0], 0);
  EXPECT_EQ(A[1][2], 1);
  EXPECT_EQ(A[2][1], 0);
  EXPECT_EQ(A[2][0], 1);

  FreeMatrix(A, N);
  DeleteTM("test.txt");
}

TEST(ReadMTest, ReadRectangular_2x3_n11) {
  CreateTM("test.txt", "3\n2 3\n1 2 3\n4 5 6\n");
  FILE* file = fopen("test.txt", "r");
  int** A = nullptr;

  int N = ReadM(file, &A);

  EXPECT_NO_FATAL_FAILURE(PrintM(A, N));

  FreeMatrix(A, N);
  DeleteTM("test.txt");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}