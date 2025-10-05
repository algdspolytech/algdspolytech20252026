#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include"unity/unity.h"
#include"DayInfo.h"
#pragma warning (disable:4996)


int ConvertDate(char* Date)
{
    int Y = 0, M = 0, D = 0;
    int i = 0;

    while (Date[i] != '.')
        D = D * 10 + Date[i++] - 48;
    while (Date[++i] != '.')
        M = M * 10 + Date[i] - 48;
    while (Date[++i] != '\0')
        Y = Y * 10 + Date[i] - 48;
    return Y * 1e4 + M * 1e2 + D;
}
DayInfo *ReadFileSorted(char *FileName)
{
    FILE* F = fopen(FileName, "r");
    double Temp;
    char *TextDate[11];
    DayInfo *Root = malloc(sizeof(DayInfo));
    Root->Back = NULL;
    Root->Next = NULL;
    Root->Date = 0;
    Root->Temp = 0;

    if (F)
    {
        while (fscanf(F, "%s %lf", TextDate, &Temp) == 2)
        {
            int Date = ConvertDate(TextDate);
            AddToListSorted(Root, Date, Temp);
        }
        fclose(F);
    }
    else
        printf("File doesn`t exist\n");
    return Root;
}


void setUp(void)
{
}
void tearDown(void)
{
}


void TestAddToEmptyList_no1(void)
{
    DayInfo Root = {0, 0, NULL, NULL};
    AddToListSorted(&Root, 20251004, 20);
    AddToListSorted(&Root, 20251005, 10);
    AddToListSorted(&Root, 20251006, 13);
    AddToListSorted(&Root, 20251007, 21);
    AddToListSorted(&Root, 20251008, 9);
    AddToListSorted(&Root, 20251010, 18);
    AddToListSorted(&Root, 20251009, 18);

    TEST_ASSERT_EQUAL_INT(IsSorted(&Root), 1);
}
void TestReadFileInt_no2(void)
{
    DayInfo* Root = ReadFileSorted("Base02.txt");
    TEST_ASSERT_EQUAL_INT(IsSorted(Root), 1);
}
void TestReadFileDouble_no3(void)
{
    DayInfo* Root = ReadFileSorted("Base03.txt");
    TEST_ASSERT_EQUAL_INT(IsSorted(Root), 1);
}
void TestAddToSortedList_no4(void)
{
    DayInfo* Root = ReadFileSorted("Base04.txt");
    AddToListSorted(Root, ConvertDate("01.01.2026"), -15);
    TEST_ASSERT_EQUAL_INT(IsSorted(Root), 1);
}
void TestRealDataCheck_no5(void)
{
    DayInfo* Root = ReadFileSorted("Base05.txt");
    TEST_ASSERT_EQUAL_INT(IsSorted(Root), 1);
}
void TestCheckStrangeDats_no6(void)
{
    DayInfo* Root = ReadFileSorted("Base06.txt");
    TEST_ASSERT_EQUAL_INT(IsSorted(Root), 1);
}
void TestCheckSameTemperatures_no7(void)
{
    DayInfo* Root = ReadFileSorted("Base07.txt");
    TEST_ASSERT_EQUAL_INT(IsSorted(Root), 1);
}
void TestCheckSameTemperaturesDateReverse_no8(void)
{
    DayInfo* Root = ReadFileSorted("Base08.txt");
    TEST_ASSERT_EQUAL_INT(IsSorted(Root), 1);
}
void TestReverseSorted_no9(void)
{
    DayInfo* Root = ReadFileSorted("Base09.txt");
    TEST_ASSERT_EQUAL_INT(IsSorted(Root), 1);
}
void TestReadEmptyFile_no10(void)
{
    DayInfo* Root = ReadFileSorted("Base10.txt");
    TEST_ASSERT_EQUAL_INT(Root->Next, NULL);
}
void TestCheckCounter_no11(void)
{
    DayInfo* Root = ReadFileSorted("Base07.txt");
    TEST_ASSERT_EQUAL_INT(CheckTemperature(Root, 1, 0, 0), 31);
}



void RUN_ALL_TESTS(void)
{
    RUN_TEST(TestAddToEmptyList_no1);
    RUN_TEST(TestReadFileInt_no2);
    RUN_TEST(TestReadFileDouble_no3);
    RUN_TEST(TestAddToSortedList_no4);
    RUN_TEST(TestRealDataCheck_no5);
    RUN_TEST(TestCheckStrangeDats_no6);
    RUN_TEST(TestCheckSameTemperatures_no7);
    RUN_TEST(TestCheckSameTemperaturesDateReverse_no8);
    RUN_TEST(TestReverseSorted_no9);
    RUN_TEST(TestReadEmptyFile_no10);
    RUN_TEST(TestCheckCounter_no11);
}

void Connection(void)
{
    char* FileName[10];
    double Temp;

    printf("List of Files:\n");
    printf("Base02.txt - File with INT temperature for 1 month\n");
    printf("Base03.txt - File with DOUBLE temperature for 3 months\n");
    printf("Base04.txt - File with DOUBLE temperature for 1 year\n");
    printf("Base05.txt - File with real temperature in Saint Petersburg for 2024 (Source: rp5.ru)\n");
    printf("Base06.txt - File with incorrect dates formates for 1 month*\n");
    printf("Base07.txt - File with the same temperature throughout 1 month\n");
    printf("Base08.txt - Base07.txt with dates sorted in reverse order\n");
    printf("Base09.txt - Base02.txt with temperatures sorted in reverse order\n");
    printf("Base10.txt - Empty File\n");

    printf("Enter the file name you want to check:\n");
    scanf("%s", FileName);

    DayInfo* Root = ReadFileSorted(FileName);
    DrawStatBelowTemperature(Root, 0);

    printf("Find the temperature in the list:\n");

    scanf("%lf", &Temp);
    printf("%d in this file\n\n", CheckTemperature(Root, Temp, 0, 1));
}


int main(void) 
{
    Connection();

    UNITY_BEGIN();
    RUN_ALL_TESTS();
    return UNITY_END();
}