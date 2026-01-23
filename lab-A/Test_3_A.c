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
int startsWith(const char* str, const char* prefix);

// Тест 3.1: startsWith с валидным префиксом
TEST(StartsWithTest, ValidPrefix_ReturnTrue_no6) {
    const char* str = "Annabel";
    const char* prefix = "Demon";
    
    int result = startsWith(str, prefix);
    EXPECT_EQ(result, 1);
}

// Тест 3.2: startsWith с невалидным префиксом
TEST(StartsWithTest, InvalidPrefix_ReturnFalse_no7) {
    const char* str = "Annabel";
    const char* prefix = "Demon";
    
    int result = startsWith(str, prefix);
    EXPECT_EQ(result, 0);
}

// Тест 3.3: startsWith с пустым префиксом
TEST(StartsWithTest, EmptyPrefix_ReturnTrue_no8) {
    const char* str = "Annabel";
    const char* prefix = "";
    
    int result = startsWith(str, prefix);
    EXPECT_EQ(result, 1);
}

// Тест 3.4: startsWith с NULL строкой
TEST(StartsWithTest, NullString_ReturnFalse_no9) {
    const char* str = NULL;
    const char* prefix = "Little_Demon";
    
    int result = startsWith(str, prefix);
    EXPECT_EQ(result, 0);
}

