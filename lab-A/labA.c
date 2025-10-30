#pragma once
#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)

struct word_st {
    char name[21];
};

void sort_func(struct word_st words[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(words[j].name, words[j + 1].name) > 0) {

                struct word_st temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

int all_arrays(struct word_st dest[], struct word_st src1[], int count1,
    struct word_st src2[], int count2) {
    int total_count = 0;
    for (int i = 0; i < count1; i++) {
        strcpy(dest[total_count].name, src1[i].name);
        total_count++;
    }
    for (int i = 0; i < count2; i++) {
        strcpy(dest[total_count].name, src2[i].name);
        total_count++;
    }

    return total_count;
}

int fileswork(char* name, struct word_st words[]) {
    FILE* file;
    int i = 0;

    file = fopen(name, "r");
    if (file == NULL) {
        printf("error open file\n");
        return;
    }
    while (fscanf(file, "%20s", words[i].name) != EOF) {
        i++;
    }

    fclose(file);
    return i;
}

int main() {
    struct word_st words1[100], words2[100], all_words[200];
    int word_numb1, word_numb2, total_numb;
    char filename1[] = "input1.txt";
    char filename2[] = "input2.txt";

    word_numb1 = fileswork(filename1, words1);
    word_numb2 = fileswork(filename2, words2);

    sort_func(words1, word_numb1);
    sort_func(words2, word_numb2);

    total_numb = all_arrays(all_words, words1, word_numb1, words2, word_numb2);
    sort_func(all_words, total_numb);

    FILE* file = fopen("output.txt", "w"); 
    if (file == NULL) {
        printf("Error of output.txt exist\n");
        return;
    }

    
    for (int i = 0; i < total_numb; i++) {
        fprintf(file, "%s\n", all_words[i].name);
    }

    fclose(file);
    return 0;
}