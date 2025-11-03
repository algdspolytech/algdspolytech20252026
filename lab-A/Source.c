#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 

struct Node
{
    char str[21];
    struct Node* next;
};

struct Node* create(const char* a)
{
    if (a == NULL) return NULL;

    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    if (head == NULL) return NULL;

    errno_t err = strncpy_s(head->str, sizeof(head->str), a, _TRUNCATE);
    if (err != 0 && err != STRUNCATE) {
        printf("error copying string: %d\n", err);
        free(head);
        return NULL;
    }
    head->next = NULL;
    return head;
}

void Add(struct Node** head, const char* a) {
    if (a == NULL || strlen(a) == 0) return;

    struct Node* new = create(a);
    if (new == NULL) return;

    if (*head == NULL) {
        *head = new;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new;
}

void bSort(struct Node* head, int l)
{
    if (head == NULL || l <= 1) return;

    int swapped;
    struct Node* ptr1;
    struct Node* lptr = NULL;
    char temp[21];

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->str, ptr1->next->str) > 0) {
                strncpy_s(temp, 21, ptr1->str, _TRUNCATE);
                strncpy_s(ptr1->str, 21, ptr1->next->str, _TRUNCATE);
                strncpy_s(ptr1->next->str, 21, temp, _TRUNCATE);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void print(struct Node* head, FILE* f3) {
    struct Node* temp = head;
    while (temp != NULL) {
        fprintf(f3, "%s\n", temp->str);
        temp = temp->next;
    }
}

int orig_main() {
    SetConsoleOutputCP(1251);
    int i = 0;
    int j = 0;
    char* A[200];
    char* B[200];
    FILE* f1 = fopen("text.txt", "r");
    FILE* f2 = fopen("text1.txt", "r");
    FILE* f3 = fopen("out.txt", "w");
    char* buffer = malloc(sizeof(char) * 21);

    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        printf("Ошибка открытия файла\n");
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        if (f3) fclose(f3);
        free(buffer);
        return 1;
    }

    while (fgets(buffer, 21, f1) != NULL && i < 200) {
        if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        // Пропускаем пустые строки
        if (strlen(buffer) == 0) continue;

        A[i] = malloc(strlen(buffer) + 1);
        if (A[i] != NULL) {
            strncpy_s(A[i], strlen(buffer) + 1, buffer, _TRUNCATE);
            i++;
        }
    }

    while (fgets(buffer, 21, f2) != NULL && j < 200) {
        if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        // Пропускаем пустые строки
        if (strlen(buffer) == 0) continue;

        B[j] = malloc(strlen(buffer) + 1);
        if (B[j] != NULL) {
            strncpy_s(B[j], strlen(buffer) + 1, buffer, _TRUNCATE);
            j++;
        }
    }

    struct Node* head = NULL;
    for (int k = 0; k < i; k++) {
        Add(&head, A[k]);
    }
    for (int k = 0; k < j; k++) {
        Add(&head, B[k]);
    }

    bSort(head, i + j);
    print(head, f3);

    // Освобождение памяти
    for (int k = 0; k < i; k++) {
        free(A[k]);
    }
    for (int k = 0; k < j; k++) {
        free(B[k]);
    }
    free(buffer);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}