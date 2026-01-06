
#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
extern "C"
{
  #include "Header.h"
}
TEST(SubsetSumTest, Test1)
{
    FILE* f;
    fopen_s(&f, "t1.txt", "w");
    fprintf_s(f, "10\n5\n2 3 4 5 9");
    fclose(f);
    Solve_Sum("t1.txt", "o1.txt");
    FILE* o;
    fopen_s(&o, "o1.txt", "r");
    int a, b, c;
    int count = fscanf_s(o, "%d %d %d", &a, &b, &c);
    fclose(o);
    EXPECT_EQ(count, 3);
    EXPECT_EQ(a + b + c, 10);
    remove("t1.txt");
    remove("o1.txt");
}
TEST(SubsetSumTest, Test2)
{
    FILE* f;
    fopen_s(&f, "t2.txt", "w");
    fprintf_s(f, "100\n3\n2 3 5");
    fclose(f);
    Solve_Sum("t2.txt", "o2.txt");
    FILE* o;
    fopen_s(&o, "o2.txt", "r");
    int val;
    fscanf_s(o, "%d", &val);
    fclose(o);
    EXPECT_EQ(val, 0);
    remove("t2.txt");
    remove("o2.txt");
}
TEST(SubsetSumTest, Test3)
{
    FILE* f;
    fopen_s(&f, "t2.txt", "w");
    fprintf_s(f, "7\n3\n2 3 5");
    fclose(f);
    Solve_Sum("t2.txt", "o2.txt");
    FILE* o;
    fopen_s(&o, "o2.txt", "r");
    int val;
    fscanf_s(o, "%d", &val);
    fclose(o);
    EXPECT_EQ(val, 2);
    remove("t2.txt");
    remove("o2.txt");
}
TEST(SubsetSumTest, Test4)
{
    FILE* f;
    fopen_s(&f, "t4.txt", "w");
    fprintf_s(f, "0\n5\n1 2 3 4 5");
    fclose(f);
    Solve_Sum("t4.txt", "o4.txt");
    FILE* o;
    fopen_s(&o, "o4.txt", "r");
    int val;
    fscanf_s(o, "%d", &val);
    fclose(o);
    EXPECT_EQ(val, 0);
    remove("t4.txt");
    remove("o4.txt");
}
TEST(SubsetSumTest, Test5)
{
    FILE* f;
    fopen_s(&f, "t5.txt", "w");
    fprintf_s(f, "15\n3\n5 5 5");
    fclose(f);
    Solve_Sum("t5.txt", "o5.txt");
    FILE* o;
    fopen_s(&o, "o5.txt", "r");
    int a, b, c;
    int count = fscanf_s(o, "%d %d %d", &a, &b, &c);
    fclose(o);
    EXPECT_EQ(count, 3);
    EXPECT_EQ(a + b + c, 15);
    remove("t5.txt");
    remove("o5.txt");
}
TEST(SubsetSumTest, Test6)
{
    FILE* f;
    fopen_s(&f, "t6.txt", "w");
    fprintf_s(f, "50\n10\n");
    for (int i = 0; i < 10; i++)
    {
        fprintf_s(f, "5 ");
    }
    fclose(f);
    Solve_Sum("t6.txt", "o6.txt");
    FILE* o;
    fopen_s(&o, "o6.txt", "r");
    int sum = 0, val;
    while (fscanf_s(o, "%d", &val) == 1)
    {
        sum += val;
    }
    fclose(o);
    EXPECT_EQ(sum, 50);
    remove("t6.txt");
    remove("o6.txt");
}
TEST(SubsetSumTest, Test7)
{
    FILE* f;
    fopen_s(&f, "t7.txt", "w");
    fprintf_s(f, "1\n1\n1");
    fclose(f);
    Solve_Sum("t7.txt", "o7.txt");
    FILE* o;
    fopen_s(&o, "o7.txt", "r");
    int val;
    fscanf_s(o, "%d", &val);
    fclose(o);
    EXPECT_EQ(val, 1);
    remove("t7.txt");
    remove("o7.txt");
}
TEST(SubsetSumTest, Test8)
{
    FILE* f;
    fopen_s(&f, "t8.txt", "w");
    fprintf_s(f, "999999999\n1\n1000000");
    fclose(f);
    Solve_Sum("t8.txt", "o8.txt");
    FILE* o;
    fopen_s(&o, "o8.txt", "r");
    int val;
    fscanf_s(o, "%d", &val);
    fclose(o);
    EXPECT_EQ(val, 0);
    remove("t8.txt");
    remove("o8.txt");
}
TEST(SubsetSumTest, Test9)
{
    FILE* f;
    fopen_s(&f, "t9.txt", "w");
    fprintf_s(f, "6\n3\n7 8 9");
    fclose(f);
    Solve_Sum("t9.txt", "o9.txt");
    FILE* o;
    fopen_s(&o, "o9.txt", "r");
    int val;
    fscanf_s(o, "%d", &val);
    fclose(o);
    EXPECT_EQ(val, 0);
    remove("t9.txt");
    remove("o9.txt");
}
TEST(SubsetSumTest, Test10)
{
    FILE* f;
    fopen_s(&f, "t10.txt", "w");
    fprintf_s(f, "500\n500\n");
    for (int i = 0; i < 500; i++)
    {
        fprintf_s(f, "1 ");
    }
    fclose(f);
    Solve_Sum("t10.txt", "o10.txt");
    FILE* o;
    fopen_s(&o, "o10.txt", "r");
    int sum = 0, val;
    while (fscanf_s(o, "%d", &val) == 1)
    {
        sum += val;
    }
    fclose(o);
    EXPECT_EQ(sum, 500);
    remove("t10.txt");
    remove("o10.txt");
}
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}