#include <gtest/gtest.h>
#include <cstdlib>
#include "t.h"  // здесь объявлена int find_schedule(int *, int **, int)

// Вспомогательная функция для инициализации задач
void init_tasks(int* tasks, int N) {
    for (int i = 0; i < N; i++) {
        tasks[i] = i + 1;
    }
}

// Вспомогательная функция для создания динамического массива int**
int** create_schedule(int rows, int cols) {
    int** schedule = new int* [rows];
    for (int i = 0; i < rows; i++) {
        schedule[i] = new int[cols];
        for (int j = 0; j < cols; j++)
            schedule[i][j] = 0;
    }
    return schedule;
}

// Вспомогательная функция для освобождения памяти
void delete_schedule(int** schedule, int rows) {
    for (int i = 0; i < rows; i++)
        delete[] schedule[i];
    delete[] schedule;
}

// Тесты

TEST(find_schedule_OneTask_returnValidVal, Basic) {
    int tasks[1];
    init_tasks(tasks, 1);
    int** schedule = create_schedule(1005, 1005);
    int res = find_schedule(tasks, schedule, 1);
    ASSERT_EQ(res, 1);
    delete_schedule(schedule, 1005);
}

TEST(find_schedule_TwoTasks_returnValidVal, Basic) {
    int tasks[2];
    init_tasks(tasks, 2);
    int** schedule = create_schedule(1005, 1005);
    int res = find_schedule(tasks, schedule, 2);
    ASSERT_EQ(res, 2);
    delete_schedule(schedule, 1005);
}

TEST(find_schedule_ThreeTasks_returnValidVal, Basic) {
    int tasks[3];
    init_tasks(tasks, 3);
    int** schedule = create_schedule(1005, 1005);
    int res = find_schedule(tasks, schedule, 3);
    ASSERT_EQ(res, 3);
    delete_schedule(schedule, 1005);
}

TEST(find_schedule_FourTasks_returnValidVal, Basic) {
    int tasks[4];
    init_tasks(tasks, 4);
    int** schedule = create_schedule(1005, 1005);
    int res = find_schedule(tasks, schedule, 4);
    ASSERT_EQ(res, 4);
    delete_schedule(schedule, 1005);
}

TEST(find_schedule_FiveTasks_returnValidVal, Basic) {
    int tasks[5];
    init_tasks(tasks, 5);
    int** schedule = create_schedule(1005, 1005);
    int res = find_schedule(tasks, schedule, 5);
    ASSERT_EQ(res, 5);
    delete_schedule(schedule, 1005);
}

TEST(find_schedule_TenTasks_returnValidVal, Basic) {
    int tasks[10];
    init_tasks(tasks, 10);
    int** schedule = create_schedule(1005, 1005);
    int res = find_schedule(tasks, schedule, 10);
    ASSERT_EQ(res, 10);
    delete_schedule(schedule, 1005);
}

TEST(find_schedule_EmptyTasks_returnZero, Basic) {
    int tasks[1]; // размер не важен, N=0
    int** schedule = create_schedule(1005, 1005);
    int res = find_schedule(tasks, schedule, 0);
    ASSERT_EQ(res, 0);
    delete_schedule(schedule, 1005);
}

TEST(find_schedule_LargeTasks_returnValidVal, Basic) {
    int tasks[100];
    init_tasks(tasks, 100);
    int** schedule = create_schedule(1005, 1005);
    int res = find_schedule(tasks, schedule, 100);
    ASSERT_EQ(res, 100);
    delete_schedule(schedule, 1005);
}

TEST(find_schedule_MaxTasks_returnValidVal, Basic) {
    int tasks[1005];
    init_tasks(tasks, 1005);
    int** schedule = create_schedule(1005, 1005);
    int res = find_schedule(tasks, schedule, 1005);
    ASSERT_EQ(res, 1005);
    delete_schedule(schedule, 1005);
}

TEST(find_schedule_CheckFindScheduleReturn_returnValidVal, Basic) {
    int tasks[10];
    init_tasks(tasks, 10);
    int** schedule = create_schedule(1005, 1005);
    int res = find_schedule(tasks, schedule, 10);
    ASSERT_EQ(res, 10);
    delete_schedule(schedule, 1005);
}
