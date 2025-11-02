#pragma once
#ifdef __cplusplus
extern "C" {
#endif

    struct Item {
        char* Word;
        struct Item* NextItem;
    };

    int compareWords(const char* word1, const char* word2);
    void InsertWord(struct Item** head, const char* word);
    void PrintLongWords(struct Item* head, int n);
    void PrintWordsByLength(struct Item* head, int length);
    void FreeList(struct Item* head);

#ifdef __cplusplus
}
#endif