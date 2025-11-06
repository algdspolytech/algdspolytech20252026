#define _CRT_SECURE_NO_WARNINGS
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

char* read_line(FILE* file) {
    if (file == NULL) return NULL;
    int buffer_size = 128;
    int len = 0;
    char* buffer = (char*)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) return NULL;
    int t;
    while ((t = fgetc(file)) != EOF && t != '\n') {
        if (len + 1 >= buffer_size) {
            buffer_size *= 2;
            char* temp = (char*)realloc(buffer, buffer_size);
            if (temp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
        buffer[len++] = t;
    }
    if (len == 0 && t == EOF) {
        free(buffer);
        return NULL;
    }
    buffer[len] = '\0';
    return buffer;
}

void graph_list(FILE* file) {
    if (file == NULL) return;
    rewind(file);
    int numb = 0;
    int node = 1;
    char* line;
    while ((line = read_line(file)) != NULL) {
        printf("%d:", node);
        for (int i = 0; i <= strlen(line) - 1; i++) {
            if (line[i] == '1') {
                printf("%d ", (numb + 1));
                numb++;
            }
            if (line[i] == '0') numb++;
        }
        printf("\n");
        numb = 0;
        free(line);
        node++;
    }
}

// Вспомогательные функции
FILE* create_test_file(const char* content) {
    FILE* file = fopen("test_temp.txt", "w+");
    if (file && content) {
        fputs(content, file);
        rewind(file);
    }
    return file;
}

void close_test_file(FILE* file) {
    if (file) {
        fclose(file);
        remove("test_temp.txt");
    }
}

// Тест 1: Крайний случай - NULL файл
TEST(GraphTest, ReadLine_NullFile_ReturnNull_no1) {
    EXPECT_EQ(read_line(nullptr), nullptr);
}

// Тест 2: Крайний случай - пустой файл
TEST(GraphTest, ReadLine_EmptyFile_ReturnNull_no2) {
    FILE* file = create_test_file("");
    EXPECT_EQ(read_line(file), nullptr);
    close_test_file(file);
}

// Тест 3: Крайний случай - очень длинная строка (проверка динамического буфера)
TEST(GraphTest, ReadLine_VeryLongLine_ReturnCompleteString_no3) {
    std::string long_line(1000, 'X'); // Строка из 1000 символов
    FILE* file = create_test_file(long_line.c_str());
    char* result = read_line(file);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, long_line.c_str());
    free(result);
    close_test_file(file);
}

// Тест 4: Алгоритмический случай - строка без перевода строки (EOF)
TEST(GraphTest, ReadLine_LineWithoutNewline_ReturnValidString_no4) {
    FILE* file = create_test_file("No newline here");
    char* result = read_line(file);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "No newline here");
    free(result);
    close_test_file(file);
}

// Тест 5: Алгоритмический случай - несколько строк подряд
TEST(GraphTest, ReadLine_MultipleLines_ReadSequentially_no5) {
    FILE* file = create_test_file("First\nSecond\nThird");
    char* line1 = read_line(file);
    ASSERT_NE(line1, nullptr);
    EXPECT_STREQ(line1, "First");
    free(line1);
    char* line2 = read_line(file);
    ASSERT_NE(line2, nullptr);
    EXPECT_STREQ(line2, "Second");
    free(line2);
    char* line3 = read_line(file);
    ASSERT_NE(line3, nullptr);
    EXPECT_STREQ(line3, "Third");
    free(line3);
    EXPECT_EQ(read_line(file), nullptr);
    close_test_file(file);
}

// Тест 6: Крайний случай - NULL файл
TEST(GraphTest, GraphList_NullFile_NoOutput_no6) {
    testing::internal::CaptureStdout();
    graph_list(nullptr);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.empty());
}

// Тест 7: Крайний случай - пустой файл
TEST(GraphTest, GraphList_EmptyFile_NoOutput_no7) {
    FILE* file = create_test_file("");
    testing::internal::CaptureStdout();
    graph_list(file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.empty());
    close_test_file(file);
}

// Тест 8: Алгоритмический случай - полный граф K3
TEST(GraphTest, GraphList_CompleteGraphK3_PrintAllConnections_no8) {
    FILE* file = create_test_file("0 1 1\n1 0 1\n1 1 0");
    testing::internal::CaptureStdout();
    graph_list(file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("1:2 3") != std::string::npos);
    EXPECT_TRUE(output.find("2:1 3") != std::string::npos);
    EXPECT_TRUE(output.find("3:1 2") != std::string::npos);
    close_test_file(file);
}

// Тест 9: Алгоритмический случай - граф с изолированными вершинами
TEST(GraphTest, GraphList_GraphWithIsolatedVertices_PrintCorrectList_no9) {
    FILE* file = create_test_file("0 1 0 0\n1 0 1 0\n0 1 0 0\n0 0 0 0");
    testing::internal::CaptureStdout();
    graph_list(file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("1:2") != std::string::npos);
    EXPECT_TRUE(output.find("2:1 3") != std::string::npos);
    EXPECT_TRUE(output.find("3:2") != std::string::npos);
    EXPECT_TRUE(output.find("4:") != std::string::npos);
    close_test_file(file);
}

// Тест 10: Алгоритмический случай - звездообразный граф
TEST(GraphTest, GraphList_StarGraph_PrintCenterAndLeaves_no10) {
    FILE* file = create_test_file("0 1 1 1\n1 0 0 0\n1 0 0 0\n1 0 0 0");
    testing::internal::CaptureStdout();
    graph_list(file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("1:2 3 4") != std::string::npos);
    EXPECT_TRUE(output.find("3:1") != std::string::npos);    
    EXPECT_TRUE(output.find("4:1") != std::string::npos);    
    EXPECT_TRUE(output.find("2:1") != std::string::npos);    
    close_test_file(file);
}

// Тест 11: Крайний случай - матрица с дополнительными пробелами
TEST(GraphTest, GraphList_MatrixWithExtraSpaces_HandleCorrectly_no11) {
    FILE* file = create_test_file("  0  1  0  1  \n  1  0  1  0  \n  0  1  0  1  \n  1  0  1  0  ");
    testing::internal::CaptureStdout();
    graph_list(file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("1:2 4") != std::string::npos);
    EXPECT_TRUE(output.find("2:1 3") != std::string::npos);
    close_test_file(file);
}

// Тест 12: Алгоритмический случай - циклический граф C4
TEST(GraphTest, GraphList_CycleGraphC4_PrintCycleConnections_no12) {
    FILE* file = create_test_file("0 1 0 1\n1 0 1 0\n0 1 0 1\n1 0 1 0");
    testing::internal::CaptureStdout();
    graph_list(file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("1:2 4") != std::string::npos);
    EXPECT_TRUE(output.find("2:1 3") != std::string::npos);
    EXPECT_TRUE(output.find("3:2 4") != std::string::npos);
    EXPECT_TRUE(output.find("4:1 3") != std::string::npos);
    close_test_file(file);
}

// Тест 13: Крайний случай - однострочная матрица (1 вершина)
TEST(GraphTest, GraphList_SingleVertexMatrix_PrintEmptyConnections_no13) {
    FILE* file = create_test_file("0");
    testing::internal::CaptureStdout();
    graph_list(file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("1:") != std::string::npos);
    close_test_file(file);
}

// Тест 14: Алгоритмический случай - двудольный граф
TEST(GraphTest, GraphList_BipartiteGraph_PrintBipartiteConnections_no14) {
    FILE* file = create_test_file("0 0 1 1\n0 0 1 1\n1 1 0 0\n1 1 0 0");
    testing::internal::CaptureStdout();
    graph_list(file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("1:3 4") != std::string::npos);
    EXPECT_TRUE(output.find("2:3 4") != std::string::npos);
    EXPECT_TRUE(output.find("3:1 2") != std::string::npos);
    EXPECT_TRUE(output.find("4:1 2") != std::string::npos);
    close_test_file(file);
}

// Тест 15: Крайний случай - все нули (полностью изолированные вершины)
TEST(GraphTest, GraphList_AllZerosMatrix_PrintNoConnections_no15) {
    FILE* file = create_test_file("0 0 0\n0 0 0\n0 0 0");
    testing::internal::CaptureStdout();
    graph_list(file);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("1:") != std::string::npos);
    EXPECT_TRUE(output.find("2:") != std::string::npos);
    EXPECT_TRUE(output.find("3:") != std::string::npos);
    close_test_file(file);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
