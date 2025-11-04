// Студенческие тесты, минимум 10 тестов нумерация по памятке
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/shortest_path.c"

static int check_arr_eq(const int *a, const int *b, int len) {
    for (int i=0;i<len;i++) if (a[i]!=b[i]) return 0; return 1;
}

static void runtest(const char *name, const int *mat, int n, int s, int t, int directed, int exp_len, const int *exp_path) {
    int got_len=0; int *got = shortest_path_bfs(mat, n, s, t, directed, &got_len);
    if (exp_len == -1) {
        if (got==NULL) printf("✅ %s: OK (no path)\n", name); else { printf("❌ %s: expected no path, got len %d\n", name, got_len); free(got); }
        return;
    }
    if (!got) { printf("❌ %s: got NULL, expected len %d\n", name, exp_len); return; }
    if (got_len != exp_len) { printf("❌ %s: expected len %d, got %d\n", name, exp_len, got_len); free(got); return; }
    if (!check_arr_eq(got, exp_path, exp_len+1)) { printf("❌ %s: path mismatch\n", name); free(got); return; }
    printf("✅ %s: OK\n", name);
    free(got);
}

int main() {
    // helper matrices
    int m3_undir[9] = {0,1,0, 1,0,1, 0,1,0}; // line: 0-1-2
    int path1[] = {0,1,2};
    runtest("TestSP_Line3_Undirected_no1", m3_undir, 3, 0, 2, 0, 2, path1);

    int m3_dir[9] = {0,1,0, 0,0,1, 0,0,0}; // 0->1->2 directed
    runtest("TestSP_Line3_Directed_no2", m3_dir, 3, 0, 2, 1, 2, path1);

    int m_noedge[4] = {0,0,0,0}; // two isolated vertices (2x2)
    runtest("TestSP_NoEdge_no3", m_noedge, 2, 0, 1, 0, -1, NULL);

    int m_same[1] = {0}; int selfp[] = {0};
    runtest("TestSP_SameVertex_no4", m_same, 1, 0, 0, 0, 0, selfp);

    int m_cycle[16] = {0,1,0,1, 1,0,1,0, 0,1,0,1, 1,0,1,0}; // 4-cycle
    int pcycle[] = {0,1,2}; runtest("TestSP_Cycle_short_no5", m_cycle, 4, 0, 2, 0, 2, pcycle);

    int m_direct_block[9] = {0,1,0, 0,0,0, 0,0,0}; // 0->1 only
    runtest("TestSP_Directed_NoPath_no6", m_direct_block, 3, 1, 2, 1, -1, NULL);

    int m_multi[25] = {
        0,1,1,0,0,
        1,0,0,1,0,
        1,0,0,1,1,
        0,1,1,0,1,
        0,0,1,1,0
    }; // 5-node graph
    int p5[] = {0,2,4}; runtest("TestSP_Multi_no7", m_multi, 5, 0, 4, 0, 2, p5);

    // larger: path of length 4
    int m6[36] = {0}; for (int i=0;i<5;i++) { m6[i*6 + i+1]=1; m6[(i+1)*6 + i]=1; }
    int p6[] = {0,1,2,3,4,5}; runtest("TestSP_Line6_no8", m6, 6, 0, 5, 0, 5, p6);

    // test undirected vs directed difference
    int m_ud[9] = {0,1,0, 0,0,1, 0,0,0}; // 0->1 and 1->2, not symmetric
    runtest("TestSP_UndirectedTreatAsGiven_no9", m_ud, 3, 0, 2, 0, -1, NULL); // undirected flag=0 treats given direction only
    runtest("TestSP_Directed_no10", m_ud, 3, 0, 2, 1, 2, (int[]){0,1,2});

    // extra test: disconnected components
    int md3[9] = {0,1,0, 1,0,0, 0,0,0}; runtest("TestSP_Disconnect_no11", md3, 3, 0, 2, 0, -1, NULL);

    printf("\nAll tests finished.\n");
    return 0;
}
