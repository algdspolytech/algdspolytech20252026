#define _CRT_SECURE_NO_WARNINGS
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <header.h>

const char* read_output(const char* filename) {
    static char line[256];
    FILE* f = fopen(filename, "r");
    fgets(line, sizeof(line), f);
    fclose(f);
    line[strcspn(line, "\n")] = '\0';
    return line;
}

TEST(SolverTest, Triangle_k2_no1) {
    // Проверка полного покрытия треугольника при K=2
    EXPECT_EQ(1, run_solver("Triangle_k2.txt", "out1.txt"));
    EXPECT_STRNE("0", read_output("out1.txt"));
}

TEST(SolverTest, Triangle_k1_no2) {
    // Проверка невозможности покрыть треугольник при K=1
    EXPECT_EQ(0, run_solver("Triangle_k1.txt", "out2.txt"));
    EXPECT_STREQ("0", read_output("out2.txt"));
}

TEST(SolverTest, Star_k1_no3) {
    // Проверка покрытия звезды центральной вершиной
    EXPECT_EQ(1, run_solver("Star_k1.txt", "out3.txt"));
    EXPECT_STRNE("0", read_output("out3.txt"));
}

TEST(SolverTest, NoEdges_k0_no4) {
    // Проверка пустого графа без ребер
    EXPECT_EQ(1, run_solver("NoEdges_k0.txt", "out4.txt"));
    EXPECT_STREQ("", read_output("out4.txt"));
}

TEST(SolverTest, Line_k2_no5) {
    // Проверка покрытия пути при K=2
    EXPECT_EQ(1, run_solver("Line_k2.txt", "out5.txt"));
    EXPECT_STRNE("0", read_output("out5.txt"));
}

TEST(SolverTest, Full_k3_no6) {
    // Проверка невозможности покрыть полный граф при K=3
    EXPECT_EQ(0, run_solver("Full_k3.txt", "out6.txt"));
    EXPECT_STREQ("0", read_output("out6.txt"));
}

TEST(SolverTest, Excess_k10_no7) {
    // Проверка избыточного K для маленького графа
    EXPECT_EQ(1, run_solver("Excess_k10.txt", "out7.txt"));
    EXPECT_STRNE("0", read_output("out7.txt"));
}

TEST(SolverTest, SingleEdge_k1_no8) {
    // Проверка покрытия одного ребра
    EXPECT_EQ(1, run_solver("SingleEdge_k1.txt", "out8.txt"));
    EXPECT_STRNE("0", read_output("out8.txt"));
}

TEST(SolverTest, Disconnected_k2_no9) {
    // Проверка покрытия несвязного графа с двумя компонентами
    EXPECT_EQ(1, run_solver("Disconnected_k2.txt", "out9.txt"));
    EXPECT_STRNE("0", read_output("out9.txt"));
}

TEST(SolverTest, SingleVertex_k0_no10) {
    // Проверка графа с одной вершиной без ребер
    EXPECT_EQ(1, run_solver("SingleVertex_k0.txt", "out10.txt"));
    EXPECT_STRNE("0", read_output("out10.txt"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}