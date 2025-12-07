#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "A_file.h" 
}

typedef struct Human {
    char surname[50];
    char name[50];
    char patronymic[50];
    struct Human* next;
} Human;

Human* createNode(char* surname, char* name, char* patronymic);
void freeList(Human* head);

// Тест 6.1: freeList с пустым списком
TEST(FreeListTest, EmptyList_NoCrash_no15) {
    Human* head = NULL;
    
    // Должно выполниться без ошибок
    freeList(head);
    
    SUCCEED();
}

// Тест 6.2: freeList с одним элементом
TEST(FreeListTest, SingleElement_NoCrash_no16) {
    Human* head = createNode("Ivanov", "Ivan", "Ivanovich");
    
    // Должно выполниться без ошибок
    freeList(head);
    
    SUCCEED();
}