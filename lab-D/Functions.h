typedef struct {
    const char* a;
    int n;
    long long target;

    char* out;
    int out_cap;

    char* expr;
    int found;
} Ctx;


int safe_add(long long x, long long y, long long* res);
int safe_sub(long long x, long long y, long long* res);
int safe_mul(long long x, long long y, long long* res);
void dfs(Ctx* ctx, int pos, long long value, long long last, int len);
