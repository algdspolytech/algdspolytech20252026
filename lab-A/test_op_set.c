#include <gtest/gtest.h>
#include "op_set.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

TEST(OpSetTest, FibSeq1) {
    OpSet* s1 = create_set();
    OpSet* s2 = create_set();

    int a = 1, b = 2;
    for (int i = 0; i < 7; i++) {
        insert_elem(s1, a);
        int nxt = a + b;
        a = b;
        b = nxt;
    }

    a = 0; b = 1;
    for (int i = 0; i < 9; i++) {
        insert_elem(s2, a);
        int nxt = a + b;
        a = b;
        b = nxt;
    }

    OpSet* un = union_sets(s1, s2);
    OpSet* inter = intersect_sets(s1, s2);

    EXPECT_LE(get_set_size(inter), get_set_size(s1));
    EXPECT_LE(get_set_size(inter), get_set_size(s2));
    EXPECT_GE(get_set_size(un), get_set_size(s1));
    EXPECT_GE(get_set_size(un), get_set_size(s2));

    delete_set(s1);
    delete_set(s2);
    delete_set(un);
    delete_set(inter);
}

TEST(OpSetTest, PrimeEven2) {
    OpSet* pr = create_set();
    OpSet* ev = create_set();

    int prm[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
    int pcnt = 16;

    for (int i = 0; i < pcnt; i++) {
        insert_elem(pr, prm[i]);
    }

    for (int v = 2; v <= 60; v += 2) {
        insert_elem(ev, v);
    }

    OpSet* isec = intersect_sets(pr, ev);
    EXPECT_EQ(get_set_size(isec), 1);
    EXPECT_TRUE(has_elem(isec, 2));

    OpSet* un = union_sets(pr, ev);
    EXPECT_EQ(get_set_size(un), 45);

    delete_set(pr);
    delete_set(ev);
    delete_set(isec);
    delete_set(un);
}

TEST(OpSetTest, Powers3) {
    OpSet* p2 = create_set();
    OpSet* p3 = create_set();

    for (int e = 0; pow(2,e) < 2000; e++) {
        insert_elem(p2, (int)pow(2,e));
    }

    for (int e = 0; pow(3,e) < 1500; e++) {
        insert_elem(p3, (int)pow(3,e));
    }

    OpSet* cmn = intersect_sets(p2, p3);
    EXPECT_EQ(get_set_size(cmn), 1);
    EXPECT_TRUE(has_elem(cmn, 1));

    delete_set(p2);
    delete_set(p3);
    delete_set(cmn);
}

TEST(OpSetTest, ArithSeq4) {
    OpSet* sa = create_set();
    OpSet* sb = create_set();

    for (int n = 0; n < 25; n++) {
        insert_elem(sa, 4*n + 2);
        insert_elem(sb, 3*n + 1);
    }

    OpSet* isec = intersect_sets(sa, sb);
    OpSet* un = union_sets(sa, sb);

    for (int v = 0; v < 120; v++) {
        bool in_a = has_elem(sa, v);
        bool in_b = has_elem(sb, v);
        bool in_i = has_elem(isec, v);
        bool in_u = has_elem(un, v);

        if (in_i) EXPECT_TRUE(in_a && in_b);
        if (in_a || in_b) EXPECT_TRUE(in_u);
    }

    delete_set(sa);
    delete_set(sb);
    delete_set(isec);
    delete_set(un);
}

TEST(OpSetTest, Random5) {
    OpSet* s = create_set();
    srand(time(0));

    for (int i = 0; i < 1500; i++) {
        int op = rand() % 3;
        int val = rand() % 150;

        switch (op) {
            case 0: insert_elem(s, val); break;
            case 1: delete_elem(s, val); break;
            case 2: has_elem(s, val); break;
        }
    }

    EXPECT_TRUE(get_set_size(s) <= 150);
    delete_set(s);
}

TEST(OpSetTest, Algebra6) {
    OpSet* X = create_set();
    OpSet* Y = create_set();
    OpSet* Z = create_set();

    for (int v = 0; v < 35; v++) {
        if (v%2==0) insert_elem(X, v);
        if (v%3==0) insert_elem(Y, v);
        if (v%5==0) insert_elem(Z, v);
    }

    OpSet* XuY = union_sets(X, Y);
    OpSet* YuX = union_sets(Y, X);
    EXPECT_EQ(get_set_size(XuY), get_set_size(YuX));

    OpSet* XnY = intersect_sets(X, Y);
    OpSet* YnX = intersect_sets(Y, X);
    EXPECT_EQ(get_set_size(XnY), get_set_size(YnX));

    OpSet* left = union_sets(XuY, Z);
    OpSet* YuZ = union_sets(Y, Z);
    OpSet* right = union_sets(X, YuZ);
    EXPECT_EQ(get_set_size(left), get_set_size(right));

    delete_set(X); delete_set(Y); delete_set(Z);
    delete_set(XuY); delete_set(YuX);
    delete_set(XnY); delete_set(YnX);
    delete_set(left); delete_set(YuZ); delete_set(right);
}

TEST(OpSetTest, Palindromes7) {
    OpSet* pal = create_set();

    for (int num = 0; num < 5000; num++) {
        int orig = num, rev = 0, tmp = num;
        while (tmp > 0) {
            rev = rev*10 + tmp%10;
            tmp /= 10;
        }
        if (orig == rev) insert_elem(pal, orig);
    }

    OpSet* evn = create_set();
    for (int v = 0; v < 5000; v += 2) insert_elem(evn, v);

    OpSet* pal_evn = intersect_sets(pal, evn);

    int exp[] = {0,2,4,6,8,22,44,66,88,202,212,222,232,242};
    int ecnt = 14;

    for (int i = 0; i < ecnt; i++) {
        EXPECT_TRUE(has_elem(pal_evn, exp[i]));
    }

    delete_set(pal);
    delete_set(evn);
    delete_set(pal_evn);
}

TEST(OpSetTest, Geometric8) {
    OpSet* gs = create_set();

    for (int n = 0; n <= 9; n++) {
        insert_elem(gs, (int)pow(2, n));
    }

    int cnt = 0, prev = -1;
    SetIter it = get_iterator(gs);
    while (has_more_elems(&it)) {
        int cur = get_next_elem(&it);
        EXPECT_GT(cur, prev);
        prev = cur;
        cnt++;
    }

    EXPECT_EQ(cnt, 10);
    EXPECT_TRUE(has_elem(gs, 1));
    EXPECT_TRUE(has_elem(gs, 2));
    EXPECT_TRUE(has_elem(gs, 512));

    delete_set(gs);
}

TEST(OpSetTest, Triangular9) {
    OpSet* tri = create_set();

    for (int n = 1; n <= 22; n++) {
        int t = n*(n+1)/2;
        insert_elem(tri, t);
    }

    int exp[] = {1,3,6,10,15,21,28,36,45,55,66,78,91,105,120,136,153,171,190,210,231,253};
    for (int i = 0; i < 22; i++) {
        EXPECT_TRUE(has_elem(tri, exp[i]));
    }

    OpSet* sq = create_set();
    for (int i = 1; i*i <= 253; i++) insert_elem(sq, i*i);

    OpSet* common = intersect_sets(tri, sq);
    EXPECT_TRUE(has_elem(common, 1));
    EXPECT_TRUE(has_elem(common, 36));

    delete_set(tri);
    delete_set(sq);
    delete_set(common);
}

TEST(OpSetTest, Difference10) {
    OpSet* A = create_set();
    OpSet* B = create_set();

    for (int v = 0; v < 60; v++) insert_elem(A, v);
    for (int v = 0; v < 60; v += 2) insert_elem(B, v);

    OpSet* diff = create_set();
    SetIter it = get_iterator(A);
    while (has_more_elems(&it)) insert_elem(diff, get_next_elem(&it));

    it = get_iterator(B);
    while (has_more_elems(&it)) delete_elem(diff, get_next_elem(&it));

    for (int v = 0; v < 60; v++) {
        bool in_diff = has_elem(diff, v);
        bool should = (v % 2 != 0);
        EXPECT_EQ(in_diff, should);
    }

    delete_set(A);
    delete_set(B);
    delete_set(diff);
}

TEST(OpSetTest, SymDiff11) {
    OpSet* M = create_set();
    OpSet* N = create_set();

    for (int v = 1; v <= 40; v++) {
        if (v%2==0 || v%3==0) insert_elem(M, v);
        if (v%3==0 || v%5==0) insert_elem(N, v);
    }

    OpSet* sd = create_set();
    SetIter it = get_iterator(M);
    while (has_more_elems(&it)) {
        int val = get_next_elem(&it);
        if (!has_elem(N, val)) insert_elem(sd, val);
    }

    it = get_iterator(N);
    while (has_more_elems(&it)) {
        int val = get_next_elem(&it);
        if (!has_elem(M, val)) insert_elem(sd, val);
    }

    EXPECT_TRUE(has_elem(sd, 2));
    EXPECT_TRUE(has_elem(sd, 5));
    EXPECT_FALSE(has_elem(sd, 15));
    EXPECT_FALSE(has_elem(sd, 6));

    delete_set(M);
    delete_set(N);
    delete_set(sd);
}

TEST(OpSetTest, Cartesian12) {
    OpSet* X = create_set();
    OpSet* Y = create_set();

    for (int i = 1; i <= 4; i++) insert_elem(X, i);
    for (int i = 10; i <= 30; i += 10) insert_elem(Y, i);

    OpSet* sums = create_set();
    SetIter xi = get_iterator(X);
    while (has_more_elems(&xi)) {
        int xv = get_next_elem(&xi);
        SetIter yi = get_iterator(Y);
        while (has_more_elems(&yi)) {
            insert_elem(sums, xv + get_next_elem(&yi));
        }
    }

    int exp[] = {11,12,13,14,21,22,23,24,31,32,33,34};
    EXPECT_EQ(get_set_size(sums), 12);
    for (int i = 0; i < 12; i++) EXPECT_TRUE(has_elem(sums, exp[i]));

    delete_set(X);
    delete_set(Y);
    delete_set(sums);
}

TEST(OpSetTest, Perfect13) {
    OpSet* perf = create_set();
    int p[] = {6,28,496,8128,33550336};
    int pcnt = 5;
    for (int i = 0; i < pcnt; i++) insert_elem(perf, p[i]);

    OpSet* tri = create_set();
    for (int n = 1; n*(n+1)/2 <= 100000; n++) insert_elem(tri, n*(n+1)/2);

    for (int i = 0; i < pcnt; i++) EXPECT_TRUE(has_elem(tri, p[i]));

    OpSet* inter = intersect_sets(perf, tri);
    EXPECT_EQ(get_set_size(inter), pcnt);

    delete_set(perf);
    delete_set(tri);
    delete_set(inter);
}

TEST(OpSetTest, Modular14) {
    OpSet* m0 = create_set();
    OpSet* m2 = create_set();

    for (int v = 0; v < 120; v++) {
        if (v%6==0) insert_elem(m0, v);
        if (v%6==2) insert_elem(m2, v);
    }

    OpSet* isec = intersect_sets(m0, m2);
    EXPECT_TRUE(is_set_empty(isec));

    OpSet* un = union_sets(m0, m2);
    for (int v = 0; v < 120; v++) {
        bool should = (v%6==0) || (v%6==2);
        EXPECT_EQ(has_elem(un, v), should);
    }

    EXPECT_EQ(get_set_size(m0), 20);
    EXPECT_EQ(get_set_size(m2), 20);
    EXPECT_EQ(get_set_size(un), 40);

    delete_set(m0);
    delete_set(m2);
    delete_set(isec);
    delete_set(un);
}

TEST(OpSetTest, Large15) {
    OpSet* big = create_set();
    for (int i = 0; i < 15000; i++) insert_elem(big, i*3 % 10009);

    OpSet* cpy = create_set();
    SetIter it = get_iterator(big);
    while (has_more_elems(&it)) insert_elem(cpy, get_next_elem(&it));

    OpSet* un = union_sets(big, cpy);
    OpSet* inter = intersect_sets(big, cpy);

    EXPECT_EQ(get_set_size(big), get_set_size(cpy));
    EXPECT_EQ(get_set_size(big), get_set_size(un));
    EXPECT_EQ(get_set_size(big), get_set_size(inter));

    delete_set(big);
    delete_set(cpy);
    delete_set(un);
    delete_set(inter);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
