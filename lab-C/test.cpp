#include <gtest/gtest.h>
#include "cell.h"
#include <stdio.h>

// Тесты для функции CreateGrid
TEST(CellTest, CreateGrid_ValidValues_ReturnValidGrid_no1) {
    Grid* grid = CreateGrid(3, 4);
    ASSERT_NE(grid, nullptr);
    FreeGrid(grid);
}

TEST(CellTest, CreateGrid_ZeroValues_ReturnNull_no2) {
    Grid* grid = CreateGrid(0, 0);
    EXPECT_EQ(grid, nullptr);
}

TEST(CellTest, CreateGrid_NegativeValues_ReturnNull_no3) {
    Grid* grid = CreateGrid(-1, 4);
    EXPECT_EQ(grid, nullptr);
}

// Тесты для функции RemoveCell
TEST(CellTest, RemoveCell_ValidCell_CellMarkedRemoved_no4) {
    Grid* grid = CreateGrid(3, 3);
    RemoveCell(grid, 1, 1);
    EXPECT_EQ(grid->grid[1][1], -1);
    FreeGrid(grid);
}

TEST(CellTest, RemoveCell_SingleCell_returnValidVal_no5) {
    Grid* grid = CreateGrid(3, 3);
    RemoveCell(grid, 1, 1);

    EXPECT_EQ(grid->grid[1][1], -1);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (i != 1 && j != 1){
                EXPECT_EQ(grid->grid[i][j], 0);
            }
        }
    }
    FreeGrid(grid);
}

// Тесты для функции ConnectComponents
TEST(CellTest, ConnectComponents_ZeroCellsRemove_returnValidVal_no6) {
    Grid* grid = CreateGrid(3, 3);
    int components = ConnectComponents(grid);
    EXPECT_EQ(components, 1);
    FreeGrid(grid);
}

TEST(CellTest, ConnectComponents_AllCellsRemove_ReturnZero_no7) {
    Grid* grid = CreateGrid(2, 2);
    
    // Удаляем все клетки
    RemoveCell(grid, 0, 0);
    RemoveCell(grid, 0, 1);
    RemoveCell(grid, 1, 0);
    RemoveCell(grid, 1, 1);
    
    int components = ConnectComponents(grid);
    EXPECT_EQ(components, 0);
    FreeGrid(grid);
}

TEST(CellTest, ConnectComponents_MiddleRowRemove_returnValidVal_no8) {
    Grid* grid = CreateGrid(3, 3);

    RemoveCell(grid, 0, 1);
    RemoveCell(grid, 1, 1);
    RemoveCell(grid, 2, 1);
    
    int components = ConnectComponents(grid);
    EXPECT_EQ(components, 2);
    FreeGrid(grid);
}

TEST(CellTest, ConnectComponents_SingleCellGrid_returnValidVal_no9) {
    Grid* grid = CreateGrid(1, 1);
    int components = ConnectComponents(grid);
    EXPECT_EQ(components, 1);
    FreeGrid(grid);
}

TEST(CellTest, ConnectComponents_SingleCellRemove_ReturnZero_no10) {
    Grid* grid = CreateGrid(1, 1);
    RemoveCell(grid, 0, 0);
    int components = ConnectComponents(grid);
    EXPECT_EQ(components, 0);
    FreeGrid(grid);
}

TEST(CellTest, ConnectComponents_NullGrid_ReturnZero_no11) {
    int components = ConnectComponents(nullptr);
    EXPECT_EQ(components, 0);
}

// Тесты для сложных паттернов
TEST(CellTest, ConnectComponents_CheckerboardPattern_returnValidVal_no12) {
    Grid* grid = CreateGrid(8, 8);
    
    // Удаляем клетки в шахматном порядке
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                RemoveCell(grid, i, j);
            }
        }
    }
    
    int components = ConnectComponents(grid);
    EXPECT_EQ(components, 32);
    FreeGrid(grid);
}

TEST(CellTest, ConnectComponents_DiagonalLine_returnValidVal_no13) {
    Grid* grid = CreateGrid(5, 5);
    
    // Удаляем диагональ
    for (int i = 0; i < 5; i++) {
        RemoveCell(grid, i, i);
    }
    
    int components = ConnectComponents(grid);
    EXPECT_GE(components, 2);
    FreeGrid(grid);
}

TEST(CellTest, ConnectComponents_CrossPattern_returnValidVal_no24) {
    Grid* grid = CreateGrid(5, 5);
    
    for (int i = 0; i < 5; i++) {
        RemoveCell(grid, 2, i); // вертикальная линия
        RemoveCell(grid, i, 2); // горизонтальная линия
    }
    
    int components = ConnectComponents(grid);
    EXPECT_EQ(components, 4); // 4 квадрата по углам
    FreeGrid(grid);
}
    int components = ConnectComponents(grid);
    EXPECT_EQ(components, 4);  // 4 квадрата по углам
    
    FreeGrid(grid);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
