#include "DoublyLinkedList.h"

// Функция создания нового узла
linkedListNode* createNode(const char* data) {
    linkedListNode* newNode = (linkedListNode*)malloc(sizeof(linkedListNode));
    if (!newNode) {
        fprintf(stderr, "Ошибка выделения памяти для узла\n");
        return NULL;
    }

    newNode->data = (char*)malloc(strlen(data) + 1);
    if (!newNode->data) {
        fprintf(stderr, "Ошибка выделения памяти для данных\n");
        free(newNode);
        return NULL;
    }

    strcpy(newNode->data, data);
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

// Функция добавления узла в конец списка
linkedListNode* appendNode(linkedListNode* head, const char* data) {
    linkedListNode* newNode = createNode(data);
    if (!newNode) {
        return head;
    }

    // Если список пуст, новый узел становится головой
    if (head == NULL) {
        return newNode;
    }

    // Находим последний узел
    linkedListNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Добавляем новый узел в конец
    current->next = newNode;
    newNode->prev = current;

    return head;
}

// Функция подсчета длины списка
int listLength(linkedListNode* head) {
    int count = 0;
    linkedListNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Функция освобождения памяти списка
void freeList(linkedListNode* head) {
    linkedListNode* current = head;
    while (current != NULL) {
        linkedListNode* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

// Функция печати списка
void printList(linkedListNode* head) {
    linkedListNode* current = head;
    while (current != NULL) {
        printf("%s", current->data);
        if (current->next != NULL) {
            printf(" <-> ");
        }
        current = current->next;
    }
    printf(" -> NULL\n");
}

// Простая и надежная сортировка пузырьком с обменом данных
linkedListNode* bubbleSort(linkedListNode* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    int length = listLength(head);
    int swapped;

    do {
        swapped = 0;
        linkedListNode* current = head;

        while (current != NULL && current->next != NULL) {
            if (strcmp(current->data, current->next->data) > 0) {
                // Обмен данными (просто и надежно)
                char* temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);

    return head;
}