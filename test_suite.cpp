#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "Adj_Graph_to_list.h"

using namespace std;
using namespace std::chrono;

#define TEST_SUITE_NAME "AdjacencyListTests"
#define FILENAME \
  "adjacency_matrix.txt"  // Определяем FILENAME, если он не определен в .h

// --- Прототипы тестовых функций ---
void EmptyFileReturnsNull();
void SingleVertexIsolated();
void TwoVerticesNoEdges();
void TwoVerticesWithEdge();
void LoopIgnoredInMatrix();
void Standard4x4Matrix();
void Uneven3x2Matrix();
void NonBinaryValuesIgnored();
void TabsAsDelimiters();
void Large10x10Matrix();

// Вспомогательные функции
void create_test_file(const char* content) {
  ofstream outFile(FILENAME);
  if (!outFile.is_open()) {
    cerr << "Не удалось создать тестовый файл " << FILENAME << endl;
    exit(EXIT_FAILURE);
  }
  outFile << content;
  outFile.close();
}

void cleanup_test_file() { remove(FILENAME); }

bool has_edge(Graph* graph, int src, int dest) {
  AdjListNode* current = graph->head[src];
  while (current != NULL) {
    if (current->dest == dest) {
      return true;
    }
    current = current->next;
  }
  return false;
}

// Макросы для форматированного вывода

#define RUN_TEST(name)                                                \
  cout << "[ RUN      ] " << TEST_SUITE_NAME << "." << #name << endl; \
  auto start_time_##name = high_resolution_clock::now();              \
  name(); /* Вызываем функцию теста */

#define END_TEST_OK(name)                                              \
  auto end_time_##name = high_resolution_clock::now();                 \
  auto duration_##name =                                               \
      duration_cast<milliseconds>(end_time_##name - start_time_##name) \
          .count();                                                    \
  cout << "[       OK ] " << TEST_SUITE_NAME << "." << name << " ("    \
       << duration_##name << " ms)" << endl;

// Основная функция запуска тестов
void run_tests() {
  int total_count = 10;
  auto suite_start_time = high_resolution_clock::now();

  cout << "[----------] " << total_count << " tests from " << TEST_SUITE_NAME
       << endl;

  // --- Вызовы тестов ---
  RUN_TEST(EmptyFileReturnsNull);
  END_TEST_OK(EmptyFileReturnsNull);

  RUN_TEST(SingleVertexIsolated);
  END_TEST_OK(SingleVertexIsolated);

  RUN_TEST(TwoVerticesNoEdges);
  END_TEST_OK(TwoVerticesNoEdges);

  RUN_TEST(TwoVerticesWithEdge);
  END_TEST_OK(TwoVerticesWithEdge);

  RUN_TEST(LoopIgnoredInMatrix);
  END_TEST_OK(LoopIgnoredInMatrix);

  RUN_TEST(Standard4x4Matrix);
  END_TEST_OK(Standard4x4Matrix);

  RUN_TEST(Uneven3x2Matrix);
  END_TEST_OK(Uneven3x2Matrix);

  RUN_TEST(NonBinaryValuesIgnored);
  END_TEST_OK(NonBinaryValuesIgnored);

  RUN_TEST(TabsAsDelimiters);
  END_TEST_OK(TabsAsDelimiters);

  RUN_TEST(Large10x10Matrix);
  END_TEST_OK(Large10x10Matrix);

  // --- Сводка результатов ---
  auto suite_end_time = high_resolution_clock::now();
  auto suite_duration =
      duration_cast<milliseconds>(suite_end_time - suite_start_time).count();

  cout << "[----------] " << total_count << " tests from " << TEST_SUITE_NAME
       << " (" << suite_duration << " ms total)" << endl;
  cout << "[==========] " << total_count << " tests from 1 test suite ran. ("
       << suite_duration << " ms total)" << endl;
  cout << "[  PASSED  ] " << total_count << " tests."
       << endl;  // Если assertы не упали, все passed
}

// --- Определения тестовых функций ---

void EmptyFileReturnsNull() {
  create_test_file("");
  Graph* g1 = matrixToList();
  assert(g1 == NULL);
  cleanup_test_file();
}

void SingleVertexIsolated() {
  create_test_file("0");
  Graph* g2 = matrixToList();
  assert(g2 != NULL && g2->V == 1);
  cleanup_test_file();
}

void TwoVerticesNoEdges() {
  create_test_file("0 0\n0 0");
  Graph* g3 = matrixToList();

  assert(g3 != NULL && g3->V == 2 && g3->head[0] == NULL &&
         g3->head[1] == NULL);
  cleanup_test_file();
}

void TwoVerticesWithEdge() {
  create_test_file("0 1\n1 0");
  Graph* g4 = matrixToList();
  assert(g4 != NULL && g4->V == 2);
  assert(has_edge(g4, 0, 1) && has_edge(g4, 1, 0));
  cleanup_test_file();
}

void LoopIgnoredInMatrix() {
  create_test_file("1 1 0\n1 0 1\n0 1 0");
  Graph* g5 = matrixToList();
  assert(g5 != NULL && g5->V == 3);
  assert(has_edge(g5, 0, 1) && !has_edge(g5, 0, 0));
  cleanup_test_file();
}

void Standard4x4Matrix() {
  const char* matrix_4x4 = "0 1 0 0\n1 0 1 1\n0 1 0 1\n0 1 1 0";
  create_test_file(matrix_4x4);
  Graph* g6 = matrixToList();
  assert(g6 != NULL && g6->V == 4);
  assert(has_edge(g6, 1, 3) && has_edge(g6, 2, 3) && has_edge(g6, 0, 1));
  cleanup_test_file();
}

void Uneven3x2Matrix() {
  create_test_file("0 1\n1 0\n0 1");
  Graph* g7 = matrixToList();
  assert(g7 != NULL && g7->V == 3);
  assert(has_edge(g7, 0, 1) && has_edge(g7, 1, 0));
  cleanup_test_file();
}

void NonBinaryValuesIgnored() {
  create_test_file("0 10\n20 0");
  Graph* g8 = matrixToList();

  assert(g8 != NULL && g8->V == 2 && g8->head[0] == NULL &&
         g8->head[1] == NULL);
  cleanup_test_file();
}

void TabsAsDelimiters() {
  create_test_file("0\t1\t0\n1\t0\t1\n0\t1\t0");
  Graph* g9 = matrixToList();
  assert(g9 != NULL && g9->V == 3);
  assert(has_edge(g9, 0, 1) && has_edge(g9, 1, 2));
  cleanup_test_file();
}

void Large10x10Matrix() {
  string big_matrix_content = "";
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      big_matrix_content += (i == j ? "0" : "1");
      if (j < 9) big_matrix_content += " ";
    }
    if (i < 9) big_matrix_content += "\n";
  }
  create_test_file(big_matrix_content.c_str());
  Graph* g10 = matrixToList();
  assert(g10 != NULL && g10->V == 10);
  int count = 0;

  AdjListNode* curr = g10->head[0];
  while (curr) {
    count++;
    curr = curr->next;
  }
  assert(count == 9);

  cleanup_test_file();
}

// --- Главная функция программы ---
int main() {
  run_tests();
  return 0;
}
