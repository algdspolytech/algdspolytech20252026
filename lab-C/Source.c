#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node
{
    int vertex;
    struct node* next;
};

struct node* Create(int a) {
    struct node* head = (struct node*)malloc(sizeof(struct node));
    if (head == NULL) {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }
    head->vertex = a;
    head->next = NULL;
    return head;
}

struct node* Add(struct node* head, int a) {
    if (head == NULL) {
        return Create(a);
    }

    struct node* Next = Create(a);
    if (Next == NULL) {
        return head;
    }

    struct node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = Next;
    return head;
}

void converet(int A[], const char* buffer)
{
    int i = 0;
    int n = 0;
    for (int j = 0; j < strlen(buffer) + 1; j++) {
        if (isdigit(buffer[j])) {
            i = i * 10 + buffer[j] - '0';
        }
        else {
            A[n] = i;
            n++;
            i = 0;
        }
    }
    A[n] = -1;
}
int accept(FILE* f, int i, const char** matrix) {
    int y = 1;
    char buffer2[100];

    for (int k = 0; k < i; k++) {
        if (fgets(buffer2, 100, f) == NULL) {
            return 0;
        }

        // Удаляем символ новой строки из buffer2
        size_t len = strlen(buffer2);
        if (len > 0 && buffer2[len - 1] == '\n') {
            buffer2[len - 1] = '\0';
        }

        // Сравниваем содержимое строк
        if (strcmp(matrix[k], buffer2) != 0) {
            return 0;
        }
    }

    // Проверяем, не осталось ли еще строк в f2
    if (y && fgets(buffer2, 100, f) != NULL) {
        return 0;
    }

    return 1;

}
int orig_main() {
    int n;
    int** A = NULL;
    int i = 0;


    char* buffer = malloc(sizeof(char) * 100);
    if (buffer == NULL) {
        printf("Ошибка выделения памяти для buffer\n");
        return 1;
    }

    FILE* f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("Ошибка открытия файла\n");
        free(buffer);
        return 1;
    }
    FILE* f2 = fopen("True.txt", "r");
    if (f2 == NULL) {
        printf("Ошибка открытия файла\n");
        free(buffer);
        return 1;
    }
    FILE* f3 = fopen("False.txt", "r");
    if (f3 == NULL) {
        printf("Ошибка открытия файла\n");
        free(buffer);
        return 1;
    }
    // Сначала подсчитаем количество строк в файле
    int line_count = 0;
    while (fgets(buffer, 100, f) != NULL) {
        line_count++;
    }
    rewind(f);

    // Выделяем память для A
    A = (int**)malloc(line_count * sizeof(int*));
    if (A == NULL) {
        printf("Ошибка выделения памяти для A\n");
        fclose(f);
        free(buffer);
        return 1;
    }

    for (int j = 0; j < line_count; j++) {
        A[j] = (int*)malloc(100 * sizeof(int));
        if (A[j] == NULL) {
            printf("Ошибка выделения памяти для A[%d]\n", j);
            // Освобождаем уже выделенную память
            for (int k = 0; k < j; k++) {
                free(A[k]);
            }
            free(A);
            fclose(f);
            free(buffer);
            return 1;
        }
    }

    struct node* head = NULL;

    // Чтение файла
    while (fgets(buffer, 100, f) != NULL) {
        if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        if (strlen(buffer) > 0) {
            converet(A[i], buffer);
            i++;
            if (i >= line_count) {
                break;
            }
        }
    }


    // Выделяем память для arr (матрица смежности)
    int** arr = (int**)malloc(i * sizeof(int*));
    if (arr == NULL) {
        printf("Ошибка выделения памяти для arr\n");
        // Освобождаем память A
        for (int j = 0; j < line_count; j++) {
            free(A[j]);
        }
        free(A);
        fclose(f);
        free(buffer);
        return 1;
    }

    for (int j = 0; j < i; j++) {
        arr[j] = (int*)calloc(i, sizeof(int));
        if (arr[j] == NULL) {
            printf("Ошибка выделения памяти для arr[%d]\n", j);
            // Освобождаем уже выделенную память
            for (int k = 0; k < j; k++) {
                free(arr[k]);
            }
            free(arr);
            for (int k = 0; k < line_count; k++) {
                free(A[k]);
            }
            free(A);
            fclose(f);
            free(buffer);
            return 1;
        }
    }

    char** matrix = malloc(sizeof(char*) * i);
    if (matrix == NULL) {
        printf("Ошибка выделения памяти для matrix\n");
    }

    for (int k = 0; k < i; k++) {
        matrix[k] = malloc(sizeof(char) * (i * 2));
        if (matrix[k] == NULL) {
            printf("Ошибка выделения памяти для matrix[%d]\n", k);
        }

        for (int g = 0; g < i; g++) {
            matrix[k][g * 2] = '0';
            if (g < i - 1) {
                matrix[k][g * 2 + 1] = ' ';
            }
        }
        matrix[k][i * 2 - 1] = '\0';
    }

    for (int k = 0; k < i; k++) {
        int r = 1;
        while (A[k][r] != -1 && r < 100) {
            if (A[k][r] < i) {
                arr[A[k][0]][A[k][r]] = 1;
                int pos = A[k][r] * 2;
                matrix[A[k][0]][pos] = '1';
            }
            r++;
        }
    }


    if (accept(f2, i, matrix)) {
        printf("for True.txt - TRUE - they are the same\n");
    }
    else {
        printf("for True.txt - FALSE - files have different number of lines\n");
    }
    if (accept(f3, i, matrix)) {
        printf("for False.txt - TRUE - they are the same\n");
    }
    else {
        printf("for False.txt - FALSE - files have different number of lines\n");
    }
    fclose(f);
    fclose(f2);
    fclose(f3);
    free(buffer);

    // Освобождаем память
    for (int j = 0; j < line_count; j++) {
        free(A[j]);
    }
    free(A);

    for (int j = 0; j < i; j++) {
        free(arr[j]);
    }
    free(arr);

    // Освобождаем список, если он использовался
    while (head != NULL) {
        struct node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}