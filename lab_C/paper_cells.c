#include "paper_cells.h"
#include <stdlib.h>

PaperGrid* create_paper(int rows, int cols)
{
    if (rows <= 0 || cols <= 0) return NULL;

    PaperGrid* paper = malloc(sizeof(PaperGrid));
    if (!paper) return NULL;

    paper->rows = rows;
    paper->cols = cols;
    paper->grid = malloc(rows * sizeof(int*));

    if (!paper->grid)
    {
        free(paper);
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        paper->grid[i] = malloc(cols * sizeof(int));
        if (!paper->grid[i]) {
            for (int j = 0; j < i; j++)
            {
                free(paper->grid[j]);
            }
            free(paper->grid);
            free(paper);
            return NULL;
        }
        for (int j = 0; j < cols; j++)
        {
            paper->grid[i][j] = 1;
        }
    }
    return paper;
}

void destroy_paper(PaperGrid* paper)
{
    if (!paper) return;

    for (int i = 0; i < paper->rows; i++)
    {
        free(paper->grid[i]);
    }
    free(paper->grid);
    free(paper);
}

void remove_cells(PaperGrid* paper, int k, int coords[][2])
{
    if (!paper || k <= 0) return;

    for (int i = 0; i < k; i++)
    {
        int x = coords[i][0];
        int y = coords[i][1];
        if (x >= 0 && x < paper->rows && y >= 0 && y < paper->cols)
        {
            paper->grid[x][y] = 0;
        }
    }
}

static void dfs(PaperGrid* paper, int x, int y, int** visited)
{
    if (x < 0 || x >= paper->rows || y < 0 || y >= paper->cols) return;
    if (visited[x][y] || paper->grid[x][y] == 0) return;

    visited[x][y] = 1;
    dfs(paper, x + 1, y, visited);
    dfs(paper, x - 1, y, visited);
    dfs(paper, x, y + 1, visited);
    dfs(paper, x, y - 1, visited);
}

int count_fragments(PaperGrid* paper)
{
    if (!paper) return 0;

    int count = 0;
    int** visited = malloc(paper->rows * sizeof(int*));
    if (!visited) return 0;

    for (int i = 0; i < paper->rows; i++)
    {
        visited[i] = malloc(paper->cols * sizeof(int));
        if (!visited[i])
        {
            for (int j = 0; j < i; j++) free(visited[j]);
            free(visited);
            return 0;
        }
        for (int j = 0; j < paper->cols; j++)
        {
            visited[i][j] = 0;
        }
    }

    for (int i = 0; i < paper->rows; i++)
    {
        for (int j = 0; j < paper->cols; j++)
        {
            if (paper->grid[i][j] == 1 && !visited[i][j])
            {
                dfs(paper, i, j, visited);
                count++;
            }
        }
    }

    for (int i = 0; i < paper->rows; i++)
    {
        free(visited[i]);
    }
    free(visited);

    return count;
}
