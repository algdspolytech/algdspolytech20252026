#pragma once
#include <stdio.h>

typedef struct Birthday_List Birthday_List;

struct Birthday_List {
    char* name;
    char* sur_name;
    char* patr;
    int birth_day;
    int birth_month;
    int birth_year;
    Birthday_List* next;
    Birthday_List* prev;
};

#ifdef __cplusplus
extern "C" {
#endif

    int Len_To_Symb(char* list, char symb);

    char* Realloc_s(char* per, int size);

    char* Read_From_File(FILE* file);

    int* Pars_Birthday_Date(char* date);

    Birthday_List* Add_To_List(char* name, char* sur_name, char* patr, int* date, Birthday_List* list);

    Birthday_List* Create_First_List_Item(char* name, char* sur_name, char* patr, int* date);

    Birthday_List* Create_List(char* file_name);
    
    char* Check_For_Birthday(Birthday_List* list, int* date);
#ifdef __cplusplus
}
#endif



