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

// Тест 2.1: compareHumans с разными фамилиями
TEST(CompareHumansTest, DifferentSurnames_ReturnNonZero_no3) {
    Human human1 = {"Hannibal", "Lecter", "Ivanovich", NULL};
    Human human2 = {"O'Hara", "Lecter", "Ivanovich", NULL};
    
    int result = compareHumans(&human1, &human2);
    EXPECT_LT(result, 0);
}

// Тест 2.2: compareHumans с одинаковыми данными
TEST(CompareHumansTest, IdenticalHumans_ReturnZero_no4) {
    Human human1 = {"Hannibal", "Lecter", "Ivanovich", NULL};
    Human human2 = {"Hannibal", "Lecter", "Ivanovich", NULL};

    int result = compareHumans(&human1, &human2);
    EXPECT_EQ(result, 0);
}

// Тест 2.3: compareHumans с одинаковыми фамилиями но разными именами
TEST(CompareHumansTest, SameSurnameDifferentNames_ReturnNonZero_no5) {
    Human human1 = {"Hannibal", "Lecter", "Ivanovich", NULL};
    Human human2 = {"Hannibal", "Skarlett", "Ivanovich", NULL};
    
    int result = compareHumans(&human1, &human2);
    EXPECT_GT(result, 0);
}
