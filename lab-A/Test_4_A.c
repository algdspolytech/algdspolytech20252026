#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    #include "A_file.h" // Заголовочный файл с вашими структурами и функциями
}

// Если функции объявлены в main.c, можно вынести их в отдельный заголовочный файл
// или скопировать сюда необходимые структуры и функции

typedef struct Human {
    char surname[50];
    char name[50];
    char patronymic[50];
    struct Human* next;
} Human;

Human* createNode(char* surname, char* name, char* patronymic);
Human* insertSorted(Human* head, Human* newHuman);
int startsWith(const char* str, const char* prefix);
void searchByInitials(Human* head, char* surname_prefix, char* name_prefix, char* patronymic_prefix);
void freeList(Human* head);


// Тест 4.1: insertSorted в пустой список
TEST(InsertSortedTest, EmptyList_ReturnNewHead_no10) {
    Human* head = NULL;
    Human* newHuman = createNode("Witch", "Vera", "Petrovovna");
    
    head = insertSorted(head, newHuman);
    
    EXPECT_EQ(head, newHuman);
    EXPECT_EQ(head->next, nullptr);
    
    freeList(head);
}

// Тест 4.2: insertSorted в начало списка
TEST(InsertSortedTest, InsertAtBeginning_ReturnNewHead_no11) {
    Human* head = createNode("Petrov", "Petr", "Petrovich");
    Human* newHuman = createNode("Witch", "Vera", "Petrovovna");
    
    head = insertSorted(head, newHuman);
    
    EXPECT_STREQ(head->surname, "Witch");
    EXPECT_STREQ(head->next->surname, "Petrov");
    
    freeList(head);
}

// Тест 4.3: insertSorted в конец списка
TEST(InsertSortedTest, InsertAtEnd_ReturnOriginalHead_no12) {
    Human* head = createNode("Ivanov", "Ivan", "Ivanovich");
    Human* newHuman = createNode("Witch", "Vera", "Petrovovna");
    
    head = insertSorted(head, newHuman);
    
    EXPECT_STREQ(head->surname, "Ivanov");
    EXPECT_STREQ(head->next->surname, "Witch");
    
    freeList(head);
}