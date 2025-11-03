#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int** ReadMatrix(FILE* f)
{
    if(f == NULL){
        return NULL;
    }
    int **arr = (int**)malloc(N * sizeof(int*));
    for(int k = 0; k < N; k++){
        arr[k] = (int*)calloc(N, sizeof(int));
    }
    
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(fscanf(f, "%d", &arr[i][j]) != 1){
                for(int k = 0; k < i; k++){
                    free(arr[k]);
                }
                free(arr);
                return NULL;
                }
        }
        if(arr[i][i] != 0){
        for(int k = 0; k < i; k++){
                free(arr[k]);
            }
            free(arr);
            return NULL;
        }
    }

    return arr;
}

int ExistPath(int **Arr, int v, int k)
{
    if(v == k){
        return 1;
    }

    if(v < 0 || v >= N || k < 0 || k >= N){
        return -1;
    }

    for(int i = 0; i < N; i++)
    {
        if(Arr[v][i] != 0)
        {
            Arr[v][i] = 0;

            if(ExistPath(Arr, i, k)){
                return 1;
            }
        }
    }
    return 0;
}