#include "bigint.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void trim_zeros(char *s) {
    int i = 0;
    while (s[i] == '0' && s[i+1] != '\0') i++;
    if (i > 0) memmove(s, s + i, strlen(s + i) + 1);
}

char* bigint_add(const char *a, const char *b) {
    int na = strlen(a), nb = strlen(b);
    int len = (na > nb ? na : nb) + 2;
    char *res = calloc(len, 1);
    int i = na - 1, j = nb - 1, k = len - 2, carry = 0;

    while (i >= 0 || j >= 0 || carry) {
        int da = (i >= 0) ? a[i--] - '0' : 0;
        int db = (j >= 0) ? b[j--] - '0' : 0;
        int sum = da + db + carry;
        res[k--] = (sum % 10) + '0';
        carry = sum / 10;
    }
    memmove(res, res + k + 1, len - k - 1);
    trim_zeros(res);
    return res;
}

char* bigint_mul(const char *a, const char *b) {
    if (strcmp(a, "0") == 0 || strcmp(b, "0") == 0) {
        char *z = calloc(2,1); strcpy(z, "0"); return z;
    }
    int na = strlen(a), nb = strlen(b);
    int n = na + nb;
    int *tmp = calloc(n, sizeof(int));
    for (int i = na - 1; i >= 0; --i)
        for (int j = nb - 1; j >= 0; --j)
            tmp[i + j + 1] += (a[i]-'0') * (b[j]-'0');
    for (int i = n - 1; i > 0; --i) {
        tmp[i-1] += tmp[i] / 10;
        tmp[i] %= 10;
    }
    int idx = 0; while (idx < n-1 && tmp[idx] == 0) idx++;
    char *res = calloc(n - idx + 1, 1);
    int k = 0;
    for (int i = idx; i < n; ++i) res[k++] = tmp[i] + '0';
    res[k] = '\0';
    free(tmp);
    trim_zeros(res);
    return res;
}

char* bigint_pow(const char *base, unsigned int exp) {
    char *result = calloc(2,1); strcpy(result, "1");
    if (exp == 0) return result;
    char *curr = strdup(base);
    char *tmp = NULL;
    while (exp > 0) {
        if (exp & 1u) {
            tmp = bigint_mul(result, curr);
            free(result);
            result = tmp;
        }
        tmp = bigint_mul(curr, curr);
        free(curr);
        curr = tmp;
        exp >>= 1;
    }
    free(curr);
    return result;
}
