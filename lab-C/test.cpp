#include <gtest/gtest.h>
#include "func.h"

TEST(Read, ReadMatrix_EmptyFile_returnValidVal_no1){
    FILE* f = fopen("Matrix1.txt", "r");
    EXPECT_EQ(ReadMatrix(f), nullptr);
    fclose(f);
}

TEST(Read, ReadMatrix_OrdinaryFile_returnValidVal_no2){
    FILE* f = fopen("Matrix2.txt", "r");
    EXPECT_NE(ReadMatrix(f), nullptr);
    fclose(f);
}

TEST(Read, ReadMatrix_UncorrectFile_returnValidVal_no3){
    FILE* f = fopen("Matrix3.txt", "r");
    EXPECT_EQ(ReadMatrix(f), nullptr);
    fclose(f);
}

TEST(DFS, FindPath_UnconnectVertices_returnFalse_no4){
    // int **arr = (int**)malloc(N * N * sizeof(int));
    int arr[N][N] = {
        {0, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {0, 1, 1, 0, 0, 1},
        {1, 0, 0, 1, 1, 0}
    };
    int **ptr_arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        ptr_arr[i] = arr[i];
    }

    EXPECT_EQ(ExistPath(ptr_arr, 0, 2), 1);
    free(ptr_arr);
}

TEST(DFS, FindPath_UnconnectVertices_returnTrue_no5){
    int arr[N][N] = {
        {0, 1, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 0}
    };
    int **ptr_arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        ptr_arr[i] = arr[i];
    }

    EXPECT_EQ(ExistPath(ptr_arr, 1, 5), 0);
    free(ptr_arr);
}

TEST(DFS, FindPath_OverNumberVertices_returnTrue_no6){
    int arr[N][N] = {
        {0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 0, 1},
        {1, 0, 0, 1, 1, 0}
    };
    int **ptr_arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        ptr_arr[i] = arr[i];
    }

    EXPECT_EQ(ExistPath(ptr_arr, 10, 4), -1);
    free(ptr_arr);
}

TEST(DFS, FindPath_UnderNumberVertices_returnTrue_no7){
    int arr[N][N] = {
        {0, 1, 0, 0, 0, 1},
        {1, 0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1},
        {0, 1, 1, 0, 0, 1},
        {1, 0, 0, 1, 1, 0}
    };

    int **ptr_arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        ptr_arr[i] = arr[i];
    }

    EXPECT_EQ(ExistPath(ptr_arr, 3, -5), -1);
    free(ptr_arr);
}

TEST(DFS, FindPath_LinearTree_returnTrue_no8){
    int arr[N][N] = {
        {0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0}
    };

    int **ptr_arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        ptr_arr[i] = arr[i];
    }

    EXPECT_EQ(ExistPath(ptr_arr, 0, 5), 1);
    free(ptr_arr);

}

TEST(DFS, FindPath_CircleTree_returnTrue_no9){
    int arr[N][N] = {
        {0, 1, 0, 0, 1, 1},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0}
    };

    int **ptr_arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        ptr_arr[i] = arr[i];
    }

    EXPECT_EQ(ExistPath(ptr_arr, 0, 5), 1);
    free(ptr_arr);
}

TEST(DFS, FindPath_AllConnectedVer_returnTrue_no10){
    int arr[N][N] = {
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1}
    };

    int **ptr_arr = (int**)malloc(N * sizeof(int*));
    for(int i = 0; i < N; i++){
        ptr_arr[i] = arr[i];
    }

    EXPECT_EQ(ExistPath(ptr_arr, 4, 5), 1);
    free(ptr_arr);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}