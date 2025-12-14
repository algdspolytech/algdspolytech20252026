#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int ReadFile(FILE* file, Data* data)
{
    fscanf(file, "%d %d", &data->T, &data->K);
    if(data->T <= 0 || data->K <= 0)
        return 0;
    data->tel = malloc(data->T * sizeof(Telegram));
    int i = 0;
    while (i < data->T)
    {
        data->tel[i].id = i + 1;
        if(fscanf(file, "%d %d %d", &data->tel[i].l, &data->tel[i].d, &data->tel[i].w) != 3)
            return 0;
        i++;
    }
    return 1;
}

void InitData(Data* data)
{
    data->tel = NULL;
    data->used = NULL;
    data->order = NULL;
    data->result = NULL;

    data->T = 0;
    data->K = 0;
    data->cur_time = 0;
    data->cur_tax = 0;
    data->found = 0;
}

void FreeData(Data* data)
{
    free(data->tel);
    free(data->used);
    free(data->order);
    free(data->result);
}

void PrintPath(int* arr, int N)
{
    if(arr == NULL)
        return;
    for (int i = 0; i < N; i++)
    {
        printf("%d ", arr[i]);
    }
}

int Backtrack(int pos, Data* data)
{
    if (data->cur_tax > data->K || data->found)
        return 0;

    if (pos == data->T)
    {
        for (int i = 0; i < data->T; i++)
            data->result[i] = data->order[i];
        data->found = 1;
        return 1;
    }

    for (int i = 0; i < data->T; i++)
    {
        if (!data->used[i])
        {
            int oldTime = data->cur_time;
            int old_tax = data->cur_tax;

            data->used[i] = 1;
            data->order[pos] = data->tel[i].id;

            data->cur_time += data->tel[i].l;
            if (data->cur_time > data->tel[i].d)
                data->cur_tax += (data->cur_time - data->tel[i].d) * data->tel[i].w;

            if (Backtrack(pos + 1, data))
                return 1;

            data->used[i] = 0;
            data->cur_time = oldTime;
            data->cur_tax = old_tax;
        }
    }
    return 0;
}
