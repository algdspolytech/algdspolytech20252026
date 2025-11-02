#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 2000

typedef struct {
    char text[MAX_WORD_LEN];
} Word;

int compare_words(const void* a, const void* b) {
    return strcmp(((Word*)a)->text, ((Word*)b)->text);
}

int read_words(const char* filename, Word words[]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return -1;
    }

    int count = 0;
    char buffer[MAX_WORD_LEN];

    while (fscanf(file, "%99s", buffer) == 1 && count < MAX_WORDS) {
        if (strlen(buffer) == 0 || strlen(buffer) >= MAX_WORD_LEN - 1)
            continue;

        strcpy(words[count++].text, buffer);
    }

    fclose(file);
    return count;
}

int main() {
    setlocale(LC_CTYPE, "Russian");

    Word words1[MAX_WORDS], words2[MAX_WORDS], result[MAX_WORDS * 2];
    int count1, count2, total = 0;

    if ((count1 = read_words("input1.txt", words1)) <= 0 ||
        (count2 = read_words("input2.txt", words2)) <= 0) {
        fprintf(stderr, "Ошибка чтения файлов\n");
        return 1;
    }

    printf("Прочитано: %d из input1.txt, %d из input2.txt\n", count1, count2);

    qsort(words1, count1, sizeof(Word), compare_words);
    qsort(words2, count2, sizeof(Word), compare_words);

    for (int i = 0; i < count1; i++)
        result[total++] = words1[i];
    for (int i = 0; i < count2; i++)
        result[total++] = words2[i];

    qsort(result, total, sizeof(Word), compare_words);

    FILE* out = fopen("output.txt", "w");
    if (!out) {
        fprintf(stderr, "Ошибка создания output.txt\n");
        return 1;
    }

    for (int i = 0; i < total; i++)
        fprintf(out, "%s\n", result[i].text);

    fclose(out);
    printf("Записано %d слов в output.txt\n", total);

    return 0;
}