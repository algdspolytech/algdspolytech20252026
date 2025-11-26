#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wagon.h"

static int run_case(const char *name,
                    int W, const int *times,
                    int D, int K,
                    const int (*edges)[2], int m_edges,
                    int expect_len, const int *expect_order )
{
    int *out = (int*)malloc(sizeof(int)*(W > 0 ? W : 1));
    int out_len = 0;
    int res = solve_instance(W, times, D, K, edges, m_edges, out, &out_len);

    int ok = 1;

    if ((expect_len == 0 && res != 0) ||
        (expect_len > 0 && res != expect_len))
    {
        ok = 0;
    }

    if (ok && expect_len > 0 && expect_order != NULL)
    {
        for (int i = 0; i < expect_len; ++i) {
            int need = expect_order[i];
            int found = 0;
            for (int j = 0; j < out_len; ++j) {
                if (out[j] == need) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                ok = 0;
                break;
            }
        }
    }

    printf("%s : %s\n", name, ok ? "PASS" : "FAIL");

    if (!ok) {
        printf("  Expected length: %d  Got: %d\n", expect_len, res);
        if (res > 0) {
            printf("  Got order:");
            for (int i = 0; i < out_len; ++i) printf(" %d", out[i]);
            printf("\n");
        }
    }

    free(out);
    return ok;
}


int main(void)
{
    int total = 0, passed = 0;

    {
        total++;
        int W = 10, D = 40, K = 3;
        int times[] = {5,3,3,3,6,7,7,9,10,10};
        int edges[][2] = { {3,2}, {4,2}, {10,7}, {7,9} };
        int expect_len = 7;
        int expect_order[] = {1,2,3,4,5,6,7};
        passed += run_case("TestExample_no1",
                           W, times, D, K, edges, 4,
                           expect_len, expect_order);
    }

    {
        total++;
        int W = 5, D = 5, K = 1;
        int times[] = {3,3,3,3,3};
        int edges[][2] = { {1,2} };
        passed += run_case("TestImpossible_due_to_time_no2",
                           W, times, D, K, edges, 1,
                           0, NULL);
    }


    {
        total++;
        int W = 6, D = 100, K = 2;
        int times[] = {10,1,1,5,2,3};
        int expect_len = 4;
        int expect_order[] = {2,3,5,6};
        passed += run_case("TestNoOrder_choose_smallest_no3",
                           W, times, D, K,
                           NULL, 0,
                           expect_len, expect_order);
    }

    {
        total++;
        int W = 4, D = 20, K = 0;
        int times[] = {5,5,5,5};
        int edges[][2] = { {1,2}, {2,3} };
        int expect_len = 4;
        int expect_order[] = {1,2,3,4};
        passed += run_case("TestAllMustBeAttached_no4",
                           W, times, D, K, edges, 2,
                           expect_len, expect_order);
    }

    {
        total++;
        int W = 3, D = 0, K = 3;
        int times[] = {100,100,100};
        passed += run_case("TestK_ge_W_no5",
                           W, times, D, K,
                           NULL, 0,
                           0, NULL);
    }

    {
        total++;
        int W = 5, D = 20, K = 2; // M=3
        int times[] = {1,9,9,9,9};
        int edges[][2] = { {5,1}, {4,2}, {2,3} };
        int expect_len = 3;
        int expect_order[] = {1,2,3};
        passed += run_case("TestEdgesFromExcluded_no6",
                           W, times, D, K, edges, 3,
                           expect_len, expect_order);
    }

    {
        total++;
        int W = 6, D = 8, K = 2; // M=4
        int times[] = {2,2,2,2,5,9};
        int expect_len = 4;
        int expect_order[] = {1,2,3,4};
        passed += run_case("TestEqualTimes_stable_no7",
                           W, times, D, K,
                           NULL, 0,
                           expect_len, expect_order);
    }

    {
        total++;
        int W = 1, D = 5, K = 0;
        int times[] = {5};
        int expect_len = 1;
        int expect_order[] = {1};
        passed += run_case("TestW1_single_no8",
                           W, times, D, K,
                           NULL, 0,
                           expect_len, expect_order);
    }

    {
        total++;
        int W = 7, D = 100, K = 4; // M=3
        int times[] = {1,1,1,10,10,10,10};
        int edges[][2] = { {1,2}, {2,3}, {3,4}, {4,5} };
        int expect_len = 3;
        int expect_order[] = {1,2,3};
        passed += run_case("TestChain_dependency_no9",
                           W, times, D, K,
                           edges, 4,
                           expect_len, expect_order);
    }

    {
        total++;
        int W = 3, D = 100, K = 0;
        int times[] = {1,1,1};
        int edges[][2] = { {1,2}, {2,3}, {3,1} };
        passed += run_case("TestCycle_in_input_no10",
                           W, times, D, K,
                           edges, 3,
                           0, NULL);
    }

    {
        total++;
        int W = 20, D = 1000, K = 5;
        int times[20];
        for (int i = 0; i < 20; ++i) times[i] = i+1;
        int expect_len = 15;
        int expect_order[15];
        for (int i = 0; i < 15; ++i) expect_order[i] = i+1;

        passed += run_case("TestLarge_simple_no11",
                           W, times, D, K,
                           NULL, 0,
                           expect_len, expect_order);
    }

    printf("Passed %d / %d\n", passed, total);

    return (passed == total) ? 0 : 1;
}
