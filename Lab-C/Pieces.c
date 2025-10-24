#include<stdio.h>
#include"Pieces.h"
#pragma warning (disable:4996)


int* ReadFile(const char* File, const int* H, const int* W)
{
    FILE* F = fopen(File, "r");

    if (!F || !fscanf(F, "%d %d", H, W))
        return NULL;

    int* Mass = malloc((*H) * (*W) * sizeof(int));

    int x, y;
    while (fscanf(F, "%d %d", &y, &x) == 2)
        Mass[y * (*W) + x] = 0;

    fclose(F);
    return Mass;
}

void DrawGroups(const int* M, const int H, const int W)
{
    for (int y = 0; y < H; y++, printf("\n"))
        for (int x = 0; x < W; x++)
            if (M[y * W + x])
                printf("%2d", M[y * W + x] % 100);
            else
                printf("%c%c", 219, 219);
}

void DrawPicture(const int* M, const int H, const int W)
{
    for (int y = 0; y < H; y++, printf("\n"))
        for (int x = 0; x < W; x++)
            if (M[y * W + x])
                printf("%c%c", 219, 219);
            else
                printf("  ");
}


int GetParts(int* M, const int H, const int W)
{
    if (M == NULL)
        return -1;

    int n = 1;
    int k = 0;

    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            if (M[y * W + x] != 0)
                if (x > 0 && M[y * W + x - 1] != 0)
                {
                    if (y > 0 && M[(y - 1) * W + x] != 0 && M[(y - 1) * W + x] != M[y * W + x - 1])
                        if (M[(y - 1) * W + x] != M[y * W + x - 1])
                        {
                            k++;

                            for (int x2 = x - 1; x2 > -W; x2--)
                                if (M[y * W + x2 - 1] == M[y * W + x - 1])
                                    M[y * W + x2 - 1] = M[(y - 1) * W + x];

                            M[y * W + x - 1] = M[(y - 1) * W + x];
                        }
                    M[y * W + x] = M[y * W + x - 1];
                }
                else
                    if (M[(y - 1) * W + x] != 0 && y > 0)
                        M[y * W + x] = M[(y - 1) * W + x];
                    else
                        M[y * W + x] = n++;

    return n - k - 1;
}

