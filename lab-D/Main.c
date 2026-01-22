#include <stdio.h>
#include <stdlib.h>

int Solve_Sum(const char* input_file, const char* output_file)
{
    FILE* input;
    fopen_s(&input, input_file, "r");
    if (input == NULL)
    {
        return 0;
    }
    unsigned long B;
    int N;
    fscanf_s(input, "%lu", &B);
    fscanf_s(input, "%d", &N);
    unsigned long* ele = (unsigned long*)malloc(N * sizeof(unsigned long));
    for (int i = 0; i < N; i++)
    {
        fscanf_s(input, "%lu", &ele[i]);
    }
    fclose(input);
    FILE* output;
    fopen_s(&output, output_file, "w");
    if (output == NULL)
    {
        free(ele);
        return 0;
    }
    if (B == 0 || N == 0)
    {
        fprintf_s(output, "0");
        fclose(output);
        free(ele);
        return 0;
    }
    if (B > 1000000)
    {
        fprintf_s(output, "0");
        fclose(output);
        free(ele);
        return 0;
    }
    char* dp = (char*)calloc(B + 1, sizeof(char));
    int* prev = (int*)calloc(B + 1, sizeof(int));
    dp[0] = 1;
    prev[0] = -1;
    for (int i = 0; i < N; i++)
    {
        for (unsigned long j = B; j >= ele[i]; j--)
        {
            if (dp[j - ele[i]] && !dp[j])
            {
                dp[j] = 1;
                prev[j] = i;
            }
        }
        if (dp[B]) break;
    }
    if (!dp[B]) 
    {
        fprintf_s(output, "0");
    }
    else
    {
        unsigned long cur = B;
        int count = 0;
        while (cur > 0)
        {
            int idx = prev[cur];
            count++;
            cur -= ele[idx];
        }
        unsigned long* res = (unsigned long*)malloc(count * sizeof(unsigned long));
        cur = B;
        int pos = 0;
        while (cur > 0)
        {
            int idx = prev[cur];
            res[pos++] = ele[idx];
            cur -= ele[idx];
        }
        for (int i = count - 1; i >= 0; i--)
        {
            fprintf_s(output, "%lu", res[i]);
            if (i > 0) fprintf_s(output, " ");
        }
        free(res);
    }
    free(dp);
    free(prev);
    free(ele);
    fclose(output);
    return 1;
}