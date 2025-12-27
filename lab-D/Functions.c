#include <stdio.h>
#include <string.h>
#include <limits.h>

#pragma warning(disable: 4996)

typedef struct {
    const char* a;      
    int n;              
    long long target;   

    char* out;          
    int out_cap;

    char* expr;         
    int found;
} Ctx;

int safe_add(long long x, long long y, long long* res) {
    if (y > 0 && x > LLONG_MAX - y) return 0;
    if (y < 0 && x < LLONG_MIN - y) return 0;
    *res = x + y;
    return 1;
}

int safe_sub(long long x, long long y, long long* res) {
    return safe_add(x, -y, res);
}

int safe_mul(long long x, long long y, long long* res) {
    if (x == 0 || y == 0) { *res = 0; return 1; }
    if (x == LLONG_MIN && y == -1) return 0;
    if (y == LLONG_MIN && x == -1) return 0;

    long long ax = x < 0 ? -x : x;
    long long ay = y < 0 ? -y : y;

    if (ax > LLONG_MAX / ay) return 0;
    *res = x * y;
    return 1;
}

void dfs(Ctx* ctx, int pos, long long value, long long last, int len) {
    if (ctx->found) return;

    if (pos == ctx->n) {
        if (value == ctx->target) {
            ctx->expr[len] = '\0';
            strncpy(ctx->out, ctx->expr, ctx->out_cap - 1);
            ctx->out[ctx->out_cap - 1] = '\0';
            ctx->found = 1;
        }
        return;
    }

    long long num = 0;
    for (int i = pos; i < ctx->n; i++) {
        if (i > pos && ctx->a[pos] == '0') break;

        int d = ctx->a[i] - '0';

       
        if (num > (LLONG_MAX - d) / 10) break;
        num = num * 10 + d;


        char chunk[32];
        int chunk_len = snprintf(chunk, sizeof(chunk), "%lld", num);

        if (pos == 0) {
            memcpy(ctx->expr + len, chunk, chunk_len);
            dfs(ctx, i + 1, num, num, len + chunk_len);
            if (ctx->found) return;
        }
        else {
            long long newv, tmp, prod;

            
            if (safe_add(value, num, &newv)) {
                ctx->expr[len] = '+';
                memcpy(ctx->expr + len + 1, chunk, chunk_len);
                dfs(ctx, i + 1, newv, num, len + 1 + chunk_len);
                if (ctx->found) return;
            }

            
            if (safe_sub(value, num, &newv)) {
                ctx->expr[len] = '-';
                memcpy(ctx->expr + len + 1, chunk, chunk_len);
                dfs(ctx, i + 1, newv, -num, len + 1 + chunk_len);
                if (ctx->found) return;
            }


            if (safe_mul(last, num, &prod) &&
                safe_sub(value, last, &tmp) &&
                safe_add(tmp, prod, &newv)) {
                ctx->expr[len] = '*';
                memcpy(ctx->expr + len + 1, chunk, chunk_len);
                dfs(ctx, i + 1, newv, prod, len + 1 + chunk_len);
                if (ctx->found) return;
            }


            if (num != 0 && (last % num == 0)) {
                long long quot = last / num;
                if (safe_sub(value, last, &tmp) &&
                    safe_add(tmp, quot, &newv)) {
                    ctx->expr[len] = '/';
                    memcpy(ctx->expr + len + 1, chunk, chunk_len);
                    dfs(ctx, i + 1, newv, quot, len + 1 + chunk_len);
                    if (ctx->found) return;
                }
            }
        }
    }
}

