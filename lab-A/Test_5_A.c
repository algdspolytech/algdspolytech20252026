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
int compareHumans(Human* a, Human* b);
void searchByInitials(Human* head, char* surname_prefix, char* name_prefix, char* patronymic_prefix);
void freeList(Human* head);

// Тест 5.1: searchByInitials с пустым списком
TEST(SearchByInitialsTest, EmptyList_PrintNotFound_no13) {
    Human* head = NULL;
    
    testing::internal::CaptureStdout();
    searchByInitials(head, "I", "I", "I");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("не найдены"), std::string::npos);
}

// Тест 5.2: searchByInitials с одним совпадением
TEST(SearchByInitialsTest, OneMatch_PrintFound_no14) {
    Human* head = createNode("Ibragim", "Ivan", "L'vovich");
    Human* second = createNode("Fool", "Ivanushka", "Petrovich");
    head->next = second;
    
    testing::internal::CaptureStdout();
    searchByInitials(head, "I", "I", "L");
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("Ibragim Ivan L'vovich"), std::string::npos);
    
    freeList(head);
}
