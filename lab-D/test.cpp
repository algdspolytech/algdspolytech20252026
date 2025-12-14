#include <gtest/gtest.h>
#include "func.h"


TEST(Read, ReadFile_ValidInput_returnTrue_no1)
{
    FILE* f = fopen("test1.txt", "w");
    fprintf(f, "2 10\n1 5 1\n2 6 2\n");
    fclose(f);

    f = fopen("test1.txt", "r");
    Data data;
    InitData(&data);

    EXPECT_TRUE(ReadFile(f, &data));
    EXPECT_EQ(data.T, 2);
    EXPECT_EQ(data.K, 10);

    fclose(f);
    FreeData(&data);
}

TEST(Read, ReadFile_ZeroTasks_returnFalse_no2)
{
    FILE* f = fopen("test2.txt", "w");
    fprintf(f, "0 5\n");
    fclose(f);

    f = fopen("test2.txt", "r");
    Data data;
    InitData(&data);

    EXPECT_FALSE(ReadFile(f, &data));

    fclose(f);
}

TEST(Read, ReadFile_CorrectIdAssignment_no3)
{
    FILE* f = fopen("test3.txt", "w");
    fprintf(f, "3 5\n1 1 1\n1 1 1\n1 1 1\n");
    fclose(f);

    f = fopen("test3.txt", "r");
    Data data;
    InitData(&data);
    ReadFile(f, &data);

    EXPECT_EQ(data.tel[0].id, 1);
    EXPECT_EQ(data.tel[2].id, 3);

    fclose(f);
    FreeData(&data);
}

TEST(FindPath, Backtrack_ExistValidOrder_returnTrue_no4)
{
    Data data;
    InitData(&data);

    data.T = 2;
    data.K = 10;

    data.tel = (Telegram*)malloc(2 * sizeof(Telegram));
    data.tel[0] = {1, 1, 5, 1};
    data.tel[1] = {2, 1, 5, 1};

    data.used = (int*)calloc(2, sizeof(int));
    data.order = (int*)malloc(2 * sizeof(int));
    data.result = (int*)malloc(2 * sizeof(int));

    EXPECT_TRUE(Backtrack(0, &data));

    FreeData(&data);
}

TEST(FindPath, Backtrack_NoValidOrder_returnFalse_no5)
{
    Data data;
    InitData(&data);

    data.T = 1;
    data.K = 0;

    data.tel = (Telegram*)malloc(sizeof(Telegram));
    data.tel[0] = {1, 10, 1, 10};

    data.used = (int*)calloc(1, sizeof(int));
    data.order = (int*)malloc(sizeof(int));
    data.result = (int*)malloc(sizeof(int));

    EXPECT_FALSE(Backtrack(0, &data));

    FreeData(&data);
}

TEST(FindPath, Backtrack_RestoreTimeAfterFail_no6)
{
    Data data;
    InitData(&data);

    data.T = 1;
    data.K = 0;

    data.tel = (Telegram*)malloc(sizeof(Telegram));
    data.tel[0] = {1, 5, 1, 1};

    data.used = (int*)calloc(1, sizeof(int));
    data.order = (int*)malloc(sizeof(int));
    data.result = (int*)malloc(sizeof(int));

    Backtrack(0, &data);
    EXPECT_EQ(data.cur_time, 0);

    FreeData(&data);
}

TEST(FindPath, Backtrack_RestorePenaltyAfterFail_no7)
{
    Data data;
    InitData(&data);

    data.T = 1;
    data.K = 0;

    data.tel = (Telegram*)malloc(sizeof(Telegram));
    data.tel[0] = {1, 5, 1, 1};

    data.used = (int*)calloc(1, sizeof(int));
    data.order = (int*)malloc(sizeof(int));
    data.result = (int*)malloc(sizeof(int));

    Backtrack(0, &data);
    EXPECT_EQ(data.cur_tax, 0);

    FreeData(&data);
}

TEST(FindPath, Backtrack_FoundFlagSet_no9)
{
    Data data;
    InitData(&data);

    data.T = 1;
    data.K = 5;

    data.tel = (Telegram*)malloc(sizeof(Telegram));
    data.tel[0] = {1, 1, 5, 1};

    data.used = (int*)calloc(1, sizeof(int));
    data.order = (int*)malloc(sizeof(int));
    data.result = (int*)malloc(sizeof(int));

    Backtrack(0, &data);
    EXPECT_EQ(data.found, 1);

    FreeData(&data);
}

TEST(FindPath, Backtrack_SingleTask_no10)
{
    Data data;
    InitData(&data);

    data.T = 1;
    data.K = 100;

    data.tel = (Telegram*)malloc(sizeof(Telegram));
    data.tel[0] = {1, 1, 1, 1};

    data.used = (int*)calloc(1, sizeof(int));
    data.order = (int*)malloc(sizeof(int));
    data.result = (int*)malloc(sizeof(int));

    EXPECT_TRUE(Backtrack(0, &data));
    EXPECT_EQ(data.result[0], 1);

    FreeData(&data);
}

TEST(Print, PrintPath_PrintDoesNotCrash_no11)
{
    int arr[3] = {1, 2, 3};
    EXPECT_NO_THROW(PrintPath(arr, 3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}