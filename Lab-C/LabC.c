#include<stdio.h>
#include"unity/unity.h"
#include"Pieces.h"
#pragma warning (disable:4996)


void setUp(void)
{
}
void tearDown(void)
{
}


void TestNoDeletedCells_no1(void)
{
    int M[20] = { 1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1 };

    TEST_ASSERT_EQUAL_INT(GetParts(M, 4, 5), 1);
}
void TestAllDeletedCells_no2(void)
{
    int M[20] = { 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0 };

    TEST_ASSERT_EQUAL_INT(GetParts(M, 4, 5), 0);
}
void TestChessBoard_no3(void)
{
    int M[25] = { 0, 1, 0, 1, 0,
                  1, 0, 1, 0, 1,
                  0, 1, 0, 1, 0,
                  1, 0, 1, 0, 1,
                  0, 1, 0, 1, 0 };

    TEST_ASSERT_EQUAL_INT(GetParts(M, 5, 5), 12);
}
void TestGetPartsFromNull_no4(void)
{
    TEST_ASSERT_EQUAL_INT(GetParts(NULL, 5 ,5), -1);
}
void TestReadFile_no5(void)
{
    int H, W, n = 0;
    int* M1 = ReadFile("List5.txt", &H, &W);
    int M2[35] = { 0, 1, 1, 1, 1, 1, 0,
                   1, 1, 0, 1, 0, 1, 1,
                   1, 0, 1, 1, 1, 1, 0,
                   1, 1, 1, 1, 1, 0, 1,
                   1, 0, 1, 1, 0, 1, 1 };

    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            if ((M1[y * W + x] == 0 && M2[y * W + x] == 0) || (M1[y * W + x] != 0 && M2[y * W + x] != 0))
                n++;

    TEST_ASSERT_EQUAL_INT(n, 35);
}
void TestReadEmptyFile_no6(void)
{
    int H, W;
    int* M = ReadFile("FILE_DOESNT_EXIST.txt", &H, &W);

    TEST_ASSERT_EQUAL_INT(M, NULL);
}
void TestGetPartsFromFile_no7(void)
{
    int H, W;
    int* M = ReadFile("List7.txt", &H, &W);

    TEST_ASSERT_EQUAL_INT(GetParts(M, H, W), 27);
}
void TestGetPartsFromImage_no8(void)
{
    int H, W;
    int* M = ReadFile("List8.txt", &H, &W);

    TEST_ASSERT_EQUAL_INT(GetParts(M, H, W), 6);
}
void TestGetPartsMaze_no9(void)
{
    int H, W;
    int* M = ReadFile("List9.txt", &H, &W);

    TEST_ASSERT_EQUAL_INT(GetParts(M, H, W), 1);
}
void TestGetPartsFromBigImage_no10(void)
{
    int H, W;
    int* M = ReadFile("List10.txt", &H, &W);

    TEST_ASSERT_EQUAL_INT(GetParts(M, H, W), 18);
}
void RUN_ALL_TESTS(void)
{
    RUN_TEST(TestNoDeletedCells_no1);
    RUN_TEST(TestAllDeletedCells_no2);
    RUN_TEST(TestChessBoard_no3);
    RUN_TEST(TestGetPartsFromNull_no4);
    RUN_TEST(TestReadFile_no5);
    RUN_TEST(TestReadEmptyFile_no6);
    RUN_TEST(TestGetPartsFromFile_no7);
    RUN_TEST(TestGetPartsFromImage_no8);
    RUN_TEST(TestGetPartsMaze_no9);
    RUN_TEST(TestGetPartsFromBigImage_no10);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_ALL_TESTS();

    return UNITY_END();
}