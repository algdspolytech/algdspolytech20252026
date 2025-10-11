#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <malloc.h>
#include "birthday.h"
#pragma warning(disable: 4996)


int Len_To_Symb(char* list, char symb) {
    int cnt = 0;
    while (list[cnt] != symb && list[cnt] != '\0') {
        cnt++;
    }
    return cnt;
}

char* Realloc_s(char* per, int size) {
    char* new_per = realloc(per,sizeof(char) * size);
    if (new_per == NULL) {
        return per;
    }
    else {
        return new_per;
    }
}

char* Read_From_File(FILE* file) {
    char* new_per=malloc(sizeof(char));
    char a;
    int size=1;
    while (fscanf(file, "%c", &a)!=EOF && a != ' ' && a!='\n') {
        new_per = Realloc_s(new_per, size);
        new_per[size - 1] = a;
        size++;
    }
    new_per = Realloc_s(new_per, size);
    new_per[size-1] = '\0';
    return new_per;
}

int* Pars_Birthday_Date(char* date) {
    int *date_int = NULL;
    int per=0;
    int cnt = 0;
    int index = 0;
    int counter = 0;
    int degree[3];
    degree[0] = Len_To_Symb(date, '.') - 1;
    int ind = 1;
    while (date[counter] != '\0') {
        if (date[counter] == '.') {
            degree[ind] = Len_To_Symb(date+counter+1, '.') - 1;
            ind++;
        }
        counter++;
    }
    int flag = 0;
    while (date[cnt] != '\0') {
        if (date[cnt] == '.' || date[cnt] == '\0') {
            flag = 0;
            index++;

        }
        else {
            if (flag == 0) {
                date_int = realloc(date_int, sizeof(int) * (index + 1));
                date_int[index] = 0;
                flag = 1;
            }
            date_int[index] += (date[cnt] - 48) * pow(10, degree[index]);
            degree[index]--;
        }
        cnt++;
    }
    return date_int;
}

Birthday_List *Add_To_List(char* name, char* sur_name, char* patr,int *date, Birthday_List *list) {
    Birthday_List* item=malloc(sizeof(Birthday_List));
    Birthday_List* cur_item = list;
    Birthday_List* per;
    item->birth_day = date[0];
    item->birth_month = date[1];
    item->birth_year = date[2];
    item->name = name;
    item->sur_name = sur_name;
    item->patr = patr;
    while (1) {
        if (item->birth_year < cur_item->birth_year) {
            per = cur_item->prev;
            if (cur_item->prev != NULL) {
                per->next = item;
            }
            cur_item->prev = item;
            item->next = cur_item;
            item->prev = per;
            break;
        }
        if (item->birth_year == cur_item->birth_year) {
            if (item->birth_month < cur_item->birth_month) {
                per = cur_item->prev;
                if (cur_item->prev != NULL) {
                    per->next = item;
                }
                cur_item->prev = item;
                item->next = cur_item;
                item->prev = per;
                break;
            }
            if (item->birth_month == cur_item->birth_month) {
                if (item->birth_day < cur_item->birth_day) {
                    per = cur_item->prev;
                    if (cur_item->prev != NULL) {
                        per->next = item;
                    }
                    cur_item->prev = item;
                    item->next = cur_item;
                    item->prev = per;
                    break;
                }
            }
        }
        if (cur_item->next == NULL) {
            cur_item->next = item;
            item->prev = cur_item;
            item->next = NULL;
            break;
        }
        cur_item = cur_item->next;
    }
    while (cur_item->prev != NULL) {
        cur_item = cur_item->prev;
    }
    return cur_item;
}

Birthday_List *Create_First_List_Item(char* name, char* sur_name, char* patr, int* date) {
    Birthday_List* item = malloc(sizeof(Birthday_List));
    item->birth_day = date[0];
    item->birth_month = date[1];
    item->birth_year = date[2];
    item->name = name;
    item->sur_name = sur_name;
    item->patr = patr;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

Birthday_List* Create_List(char* file_name) {
    FILE* f = fopen(file_name, "r");
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* sur_name=Read_From_File(f);
    char* name = Read_From_File(f);
    char* patr = Read_From_File(f);
    char* birth_date = Read_From_File(f);
    int* date = Pars_Birthday_Date(birth_date);
    Birthday_List* list = Create_First_List_Item(name, sur_name, patr, date);
    while (ftell(f) != size) {
        sur_name = Read_From_File(f);
        name = Read_From_File(f);
        patr = Read_From_File(f);
        birth_date = Read_From_File(f);
        date = Pars_Birthday_Date(birth_date);
        list = Add_To_List(name, sur_name, patr,date, list);
    }
    fclose(f);
    return list;
}

char* Check_For_Birthday(Birthday_List* list, int* date) {
    int flag = 0;
    while (list->birth_day <= date[0] && list->birth_month <= date[1] && list->birth_year <= date[2] ) {
        if (list->birth_day == date[0] && list->birth_month == date[1] && list->birth_year == date[2]) {
            flag = 1;
            break;
        }
        if (list->next == NULL) {
            break;
        }
        list = list->next;
    }
    if (flag == 1) {
        return "There is a person with such a birthday";
    }
    else {
        return "There is no person with such a birthday";
    }
}