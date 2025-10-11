#define _CRT_SECURE_NO_WARNINGS
#include "gtest/gtest.h"
#include "birthday.h"

//Test function Len_To_Simb

TEST(LenCounterTest, ValidDate_no1) {
    char str[] = "25.01.2006";
    int result = Len_To_Symb(str, '.');
    EXPECT_EQ(result, 2);
}

TEST(LenCounterTest, NoDate_no2) {
    char str[] = "";
    int result = Len_To_Symb(str, '.');
    EXPECT_EQ(result, 0);
}

TEST(LenCounterTest, WithoutSimbolInString_no3) {
    char str[] = "25482";
    int result = Len_To_Symb(str, '.');
    EXPECT_EQ(result, 5);
}



//Test function Pars_Birthday_Date


TEST(DateParserTest, ValidDate_no4) {
    char date[] = "15.03.1990";
    int* result = Pars_Birthday_Date(date);

    EXPECT_EQ(result[0], 15);
    EXPECT_EQ(result[1], 3); 
    EXPECT_EQ(result[2], 1990); 

    free(result);
}

TEST(DateParserTest, DateWithoutZerosBefor_no5) {
    char date[] = "5.3.1990";
    int* result = Pars_Birthday_Date(date);

    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 3);
    EXPECT_EQ(result[2], 1990);

    free(result);
}

TEST(DateParserTest, NoDate_no6) {
    char date[] = "";
    int* result = Pars_Birthday_Date(date);

    EXPECT_EQ(result, nullptr);

    free(result);
}

TEST(DateParserTest, MinimumDate_no7) {
    char date[] = "1.1.1";
    int* result = Pars_Birthday_Date(date);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 1);

    free(result);
}

TEST(DateParserTest, MaximumReasonableDate_no8) {
    char date[] = "31.12.9999";
    int* result = Pars_Birthday_Date(date);

    EXPECT_EQ(result[0], 31);
    EXPECT_EQ(result[1], 12);
    EXPECT_EQ(result[2], 9999);

    free(result);
}
//Test function Realloc_s


TEST(MemoryFunctionsTest, ReallocBasic_no9) {
    char* str = (char*)malloc(5);
    strcpy(str, "test");

    char* new_str = Realloc_s(str, 10);
    EXPECT_NE(new_str, nullptr);
    EXPECT_STREQ(new_str, "test");

    strcat(new_str, "123");
    EXPECT_STREQ(new_str, "test123");

    free(new_str);
}

//Test function Create_First_List_Item


TEST(ListFunctionsTest, CreateFirstListItem_no10) {
    char name[] = "John";
    char sur_name[] = "Doe";
    char patr[] = "Smith";
    int date[] = { 15, 3, 1990 };

    Birthday_List* item = Create_First_List_Item(name, sur_name, patr, date);

    ASSERT_NE(item, nullptr);
    EXPECT_STREQ(item->name, "John");
    EXPECT_STREQ(item->sur_name, "Doe");
    EXPECT_STREQ(item->patr, "Smith");
    EXPECT_EQ(item->birth_day, 15);
    EXPECT_EQ(item->birth_month, 3);
    EXPECT_EQ(item->birth_year, 1990);
    EXPECT_EQ(item->next, nullptr);
    EXPECT_EQ(item->prev, nullptr);

    free(item);
}

//Test function Add_To_List_Item

//Adding a younger date to the list
TEST(ListFunctionsTest, AddToListYoungerDate_no11) {
    char name1[] = "John";
    char sur_name1[] = "Doe";
    char patr1[] = "Smith";
    int date1[] = { 15, 3, 1990 };

    Birthday_List* list = Create_First_List_Item(name1, sur_name1, patr1, date1);

    char name2[] = "Kim";
    char sur_name2[] = "Chen";
    char patr2[] = "In";
    int date2[] = { 20, 5, 1995 };

    Birthday_List* new_list = Add_To_List(name2, sur_name2, patr2, date2, list);

    EXPECT_STREQ(new_list->name, "John");
    EXPECT_STREQ(new_list->sur_name, "Doe");
    EXPECT_STREQ(new_list->patr, "Smith");
    EXPECT_EQ(new_list->birth_day, 15);
    EXPECT_EQ(new_list->birth_month, 3);
    EXPECT_EQ(new_list->birth_year, 1990);
    EXPECT_EQ(new_list->prev, nullptr);
    EXPECT_STREQ(new_list->next->name, "Kim");
    EXPECT_STREQ(new_list->next->sur_name, "Chen");
    EXPECT_STREQ(new_list->next->patr, "In");
    EXPECT_EQ(new_list->next->birth_day, 20);
    EXPECT_EQ(new_list->next->birth_month, 5);
    EXPECT_EQ(new_list->next->birth_year, 1995);
    EXPECT_EQ(new_list->next->next, nullptr);


    free(new_list->next);
    free(new_list);
}

//Adding a older date to the list
TEST(ListFunctionsTest, AddToListYoungerDate_no12) {
    char name1[] = "John";
    char sur_name1[] = "Doe";
    char patr1[] = "Smith";
    int date1[] = { 15, 3, 1990 };

    Birthday_List* list = Create_First_List_Item(name1, sur_name1, patr1, date1);

    char name2[] = "Kim";
    char sur_name2[] = "Chen";
    char patr2[] = "In";
    int date2[] = { 14, 10, 1980 };

    Birthday_List* new_list = Add_To_List(name2, sur_name2, patr2, date2, list);

    EXPECT_STREQ(new_list->name, "Kim");
    EXPECT_STREQ(new_list->sur_name, "Chen");
    EXPECT_STREQ(new_list->patr, "In");
    EXPECT_EQ(new_list->birth_day, 14);
    EXPECT_EQ(new_list->birth_month, 10);
    EXPECT_EQ(new_list->birth_year, 1980);
    EXPECT_EQ(new_list->prev, nullptr);
    EXPECT_STREQ(new_list->next->name, "John");
    EXPECT_STREQ(new_list->next->sur_name, "Doe");
    EXPECT_STREQ(new_list->next->patr, "Smith");
    EXPECT_EQ(new_list->next->birth_day, 15);
    EXPECT_EQ(new_list->next->birth_month, 3);
    EXPECT_EQ(new_list->next->birth_year, 1990);
    EXPECT_EQ(new_list->next->next, nullptr);

    free(new_list->next);
    free(new_list);
}

//Adding a same date to the list
TEST(ListFunctionsTest, AddToListYoungerDate_no13) {
    char name1[] = "John";
    char sur_name1[] = "Doe";
    char patr1[] = "Smith";
    int date1[] = { 15, 3, 1990 };

    Birthday_List* list = Create_First_List_Item(name1, sur_name1, patr1, date1);

    char name2[] = "Kim";
    char sur_name2[] = "Chen";
    char patr2[] = "In";
    int date2[] = { 15, 3, 1990 };

    Birthday_List* new_list = Add_To_List(name2, sur_name2, patr2, date2, list);

    EXPECT_EQ(new_list->birth_year, 1990);
    EXPECT_STREQ(new_list->sur_name, "Doe");
    EXPECT_EQ(new_list->next->birth_year, 1990);
    EXPECT_STREQ(new_list->next->sur_name, "Chen");

    free(new_list->next);
    free(new_list);
}

//Test function Check_For_Birthday
//Found
TEST(ListFunctionsTest, CheckBirthdayFound_no14) {
    char name[] = "John";
    char sur_name[] = "Doe";
    char patr[] = "Smith";
    int date[] = { 15, 3, 1990 };
    Birthday_List* list = Create_First_List_Item(name, sur_name, patr, date);

    int search_date[] = { 15, 3, 1990 };
    char* result = Check_For_Birthday(list, search_date);
    EXPECT_EQ(result, "There is a person with such a birthday");


}

//Not found
TEST(ListFunctionsTest, CheckBirthdayNotFound_no15) {
    char name[] = "John";
    char sur_name[] = "Doe";
    char patr[] = "Smith";
    int date[] = { 15, 3, 1990 };
    Birthday_List* list = Create_First_List_Item(name, sur_name, patr, date);

    int search_date[] = { 27, 8, 2009 };
    char* result = Check_For_Birthday(list, search_date);
    EXPECT_EQ(result, "There is no person with such a birthday");


}
//Test function Create_List
TEST(FileOperationsTest, CreateListFromFile_no16) {
    char name[] = "test_input.txt";
    FILE* test_file = fopen(name, "w");
    ASSERT_NE(test_file, nullptr) ;

    fprintf(test_file, "Ivanov Ivan Ivanovich 15.03.1990\n");
    fprintf(test_file, "Petrov Petr Petrovich 20.05.1985\n");
    fprintf(test_file, "Sidorova Maria Alexeevna 10.01.1995\n");
    fclose(test_file);

    
    Birthday_List* list = Create_List(name);
    ASSERT_NE(list, nullptr);


    EXPECT_STREQ(list->name, "Petr");
    EXPECT_STREQ(list->sur_name, "Petrov");
    EXPECT_STREQ(list->patr, "Petrovich");
    EXPECT_EQ(list->birth_day, 20);
    EXPECT_EQ(list->birth_month, 5);
    EXPECT_EQ(list->birth_year, 1985);
    EXPECT_EQ(list->prev, nullptr);


    EXPECT_STREQ(list->next->name, "Ivan");
    EXPECT_STREQ(list->next->sur_name, "Ivanov");
    EXPECT_STREQ(list->next->patr, "Ivanovich");
    EXPECT_EQ(list->next->birth_day, 15);
    EXPECT_EQ(list->next->birth_month, 3);
    EXPECT_EQ(list->next->birth_year, 1990);


    EXPECT_STREQ(list->next->next->name, "Maria");
    EXPECT_STREQ(list->next->next->sur_name, "Sidorova");
    EXPECT_STREQ(list->next->next->patr, "Alexeevna");
    EXPECT_EQ(list->next->next->birth_day, 10);
    EXPECT_EQ(list->next->next->birth_month, 1);
    EXPECT_EQ(list->next->next->birth_year, 1995);
    EXPECT_EQ(list->next->next->next, nullptr);


    Birthday_List* current = list;
    while (current != NULL) {
        Birthday_List* next = current->next;
        free(current);
        current = next;
    }

    remove("test_input.txt");
}

//Test function Read_From_File

TEST(ReadFromFileTest, ReadNormalString_no17){
    FILE* test_file = fopen("test_read.txt", "w");
    fprintf(test_file, "Ivanov Ivan");
    fclose(test_file);

    test_file = fopen("test_read.txt", "r");
    char* result = Read_From_File(test_file);
    fclose(test_file);

    EXPECT_STREQ(result, "Ivanov");

    free(result);
    remove("test_read.txt");
}

TEST(ReadFromFileTest, ReadStringWithNewline_no18) {
    FILE* test_file = fopen("test_read.txt", "w");
    fprintf(test_file, "Ivanov\nIvan");
    fclose(test_file);

    test_file = fopen("test_read.txt", "r");
    char* result = Read_From_File(test_file);
    fclose(test_file);

    EXPECT_STREQ(result, "Ivanov");

    free(result);
    remove("test_read.txt");
}

TEST(ReadFromFileTest, ReadEmptyFile_no19) {
    FILE* test_file = fopen("test_read.txt", "w");
    fclose(test_file);

    test_file = fopen("test_read.txt", "r");
    char* result = Read_From_File(test_file);
    fclose(test_file);

    EXPECT_STREQ(result, "");

    free(result);
    remove("test_read.txt");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}