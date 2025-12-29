#define _CRT_SECURE_NO_WARNINGS
#include "labA.h"

int compare_words(const void* a, const void* b) {
    const WordInfo* wordA = (const WordInfo*)a;
    const WordInfo* wordB = (const WordInfo*)b;

    if (wordA->length != wordB->length) {
        return wordA->length - wordB->length;
    }
    return strcmp(wordA->word, wordB->word);
}

int read_word(FILE* file, char* buffer) {
    int c;
    int index = 0;

    while ((c = fgetc(file)) != EOF && !isalpha(c))
        ;

    if (c == EOF)
        return 0;

    buffer[index++] = tolower(c);
    while ((c = fgetc(file)) != EOF && isalpha(c) &&
        index < MAX_WORD_LENGTH - 1) {
        buffer[index++] = tolower(c);
    }
    buffer[index] = '\0';

    return 1;
}

void insert_sorted(WordInfo* words, int* count, const char* new_word) {

    WordInfo new_word_info;
    strcpy(new_word_info.word, new_word);
    new_word_info.length = strlen(new_word);

    int pos = *count;
    for (int i = 0; i < *count; i++) {
        if (compare_words(&new_word_info, &words[i]) < 0) {
            pos = i;
            break;
        }
    }

    for (int i = *count; i > pos; i--) {
        words[i] = words[i - 1];
    }

    words[pos] = new_word_info;
    (*count)++;
}

void print_words_longer_than(WordInfo* words, int count, int N) {
    for (int i = 0; i < count; i++) {
        if (words[i].length > N) {
            printf("%s\n", words[i].word);
        }
    }
}

void print_words_by_length(WordInfo* words, int count, int target_length) {
    int found = 0;

    for (int i = 0; i < count; i++) {
        if (words[i].length == target_length) {
            printf("%s\n", words[i].word);
            found = 1;
        }
        else if (words[i].length > target_length && found) {
            break;
        }
    }

    if (!found) {
        printf("No words found with length %d\n", target_length);
    }
}

int main() {
    char filename[100];
    WordInfo words[MAX_WORDS];
    int word_count = 0;

    printf("enter file name: ");
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("error '%s'\n", filename);
        return 1;
    }

    char buffer[MAX_WORD_LENGTH];
    while (read_word(file, buffer) && word_count < MAX_WORDS) {
        insert_sorted(words, &word_count, buffer);
    }

    fclose(file);

    printf("success\n");

    int N;
    scanf("%i", &N);

    print_words_longer_than(words, word_count, N);

    int N2;
    scanf("%i", &N2);
    print_words_by_length(words, word_count, N2);

    printf("Starting unit tests...\n\n");

    test_insert_empty_no1();
    test_sort_by_length_no2();
    test_alphabetical_order_no3();
    test_compare_function_no4();
    test_mixed_sorting_no5();
    test_max_length_word_no6();
    test_multiple_insertions_no7();
    test_duplicate_words_no8();
    test_boundary_lengths_no9();
    test_complex_sorting_no10();

    printf("\nAll tests passed! 10/10\n");

    int N3;
    scanf("%i", &N3);

    return 0;
}