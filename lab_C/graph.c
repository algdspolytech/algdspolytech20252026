#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)


int matrix_list[MAX_VERTICES][MAX_VERTICES];
int matrix[MAX_VERTICES][MAX_VERTICES];

int vertices_list(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("Error of open file\n");
        exit(1);
    }

    int maxVertex = 0;
    char line[1000];

    while (fgets(line, sizeof(line), file))
    {
        int vertex;

        if (sscanf(line, "%d", &vertex) == 1)
        {
            if (vertex > maxVertex)
            {
                maxVertex = vertex;
            }

            char* token = strtok(line, " \t\n");
            while (token != NULL)
            {
                int num = atoi(token);
                if (num > maxVertex)
                {
                    maxVertex = num;
                }
                token = strtok(NULL, " \t\n");
            }
        }
    }

    fclose(file);
    return maxVertex;
}

int matrix_size(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("Error of open file\n");
        exit(1);
    }

    int size = 0;
    char line[1000];

    if (fgets(line, sizeof(line), file))
    {
        char* token = strtok(line, " \t\n");
        while (token != NULL)
        {
            size++;
            token = strtok(NULL, " \t\n");
        }
    }

    fclose(file);
    return size;
}

void read_list(const char* filename, int matrix[][MAX_VERTICES], int n)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("Error of open file\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
        }
    }

    char line[1000];

    while (fgets(line, sizeof(line), file))
    {
        int vertex;

        if (sscanf(line, "%d", &vertex) == 1)
        {
            vertex--;

            char* token = strtok(line, " \t\n");
            token = strtok(NULL, " \t\n");

            while (token != NULL)
            {
                int neighbor = atoi(token) - 1;
                if (neighbor >= 0 && neighbor < n)
                {
                    matrix[vertex][neighbor] = 1;
                }
                token = strtok(NULL, " \t\n");
            }
        }
    }

    fclose(file);
}

void read_matrix(const char* filename, int matrix[][MAX_VERTICES], int n)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("Error of open file\n");
        exit(1);
    }

    char line[1000];
    int row = 0;

    while (fgets(line, sizeof(line), file) && row < n)
    {
        char* token = strtok(line, " \t\n");
        int col = 0;

        while ((token != NULL) && (col < n))
        {
            matrix[row][col] = atoi(token);
            token = strtok(NULL, " \t\n");
            col++;
        }
        row++;
    }

    fclose(file);
}

int compare_results(int n, int m1[][MAX_VERTICES], int m2[][MAX_VERTICES])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (m1[i][j] != m2[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    int n1 = vertices_list("list.txt");
    int n2 = matrix_size("matrix.txt");

    printf("Number of vertices in list: %d\n", n1);
    printf("Matrix size: %dx%d\n", n2, n2);

    if (n1 != n2)
    {
        printf("Different number of vertices (%d vs %d)\n", n1, n2);
        printf("False\n");
        return 1;
    }

    read_list("list.txt", matrix_list, n1);
    read_matrix("matrix.txt", matrix, n2);

    if (compare_results(n1, matrix_list, matrix))
    {
        printf("True");
    }
    else
    {
        printf("False");
    }

    return 0;
}