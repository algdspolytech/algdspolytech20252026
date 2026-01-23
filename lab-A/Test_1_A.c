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
Human* insertSorted(Human* head, Human* newHuman);
int startsWith(const char* str, const char* prefix);
void searchByInitials(Human* head, char* surname_prefix, char* name_prefix, char* patronymic_prefix);
void freeList(Human* head);

// Тест 1.1: createNode с валидными данными
TEST(CreateNodeTest, ValidInput_ReturnValidNode_no1) {
    Human* node = createNode("Chupacabra", "Boris", "Konstantinovich");
    
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->surname, "Chupacabra");
    EXPECT_STREQ(node->name, "Boris");
    EXPECT_STREQ(node->patronymic, "Konstantinovich");
    EXPECT_EQ(node->next, nullptr);
    
    free(node);
}

// Тест 1.2: createNode с пустыми строками
TEST(CreateNodeTest, EmptyStrings_ReturnValidNode_no2) {
    Human* node = createNode("", "", "");
    
    ASSERT_NE(node, nullptr);
    EXPECT_STREQ(node->surname, "");
    EXPECT_STREQ(node->name, "");
    EXPECT_STREQ(node->patronymic, "");
    
    free(node);
}

