#ifndef BIGINT_H
#define BIGINT_H

// Возвращаемые строки выделяются через malloc, вызывающий должен free()
char* bigint_add(const char *a, const char *b);
char* bigint_mul(const char *a, const char *b);
char* bigint_pow(const char *base, unsigned int exp);

#endif // BIGINT_H
