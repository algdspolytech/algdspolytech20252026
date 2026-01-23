#ifndef LIST_OPERATIONS_H
#define LIST_OPERATIONS_H

typedef struct Human {
    char surname[50];
    char name[50];
    char patronymic[50];
    struct Human* next;
} Human;

Human* createNode(char* surname, char* name, char* patronymic);

int compareHumans(Human* a, Human* b);

Human* insertSorted(Human* head, Human* newHuman);

int startsWith(const char* str, const char* prefix);

void searchByInitials(Human* head, char* surname_prefix, char* name_prefix, char* patronymic_prefix);
void printSurnames(Human* head);

void freeList(Human* head);

#endif